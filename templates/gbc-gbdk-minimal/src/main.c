/*
 * Harbor Lights – original minimal GBDK-2020 template for Handheld Game Forge.
 * Flow: title card → premise card → lore card → tiny playable pier scene.
 * Branding: handheld / GBC-class only. No third-party IP.
 */

#include <gb/gb.h>
#include <gbdk/console.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    ST_TITLE = 0,
    ST_PREMISE,
    ST_LORE,
    ST_PLAY
} state_e;

static state_e state = ST_TITLE;
static uint8_t hold = 0;
static uint8_t pier_x = 72;
static uint8_t pier_y = 88;
static uint8_t lanterns = 0;
static uint8_t frame_done = 1;
/* Lag counter: VBlank increments when previous frame did not finish. */
static uint16_t lag_frames = 0;

/* Simple 8x8 lantern sprite (2bpp, light on dark). */
static const unsigned char lantern_tiles[] = {
    0x18, 0x18, 0x3C, 0x24, 0x7E, 0x5A, 0x7E, 0x42,
    0x3C, 0x24, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00
};

static void wait_release(void) {
    while (joypad()) {
        wait_vbl_done();
    }
}

static void clear_screen(void) {
    cls();
}

static void draw_title(void) {
    clear_screen();
    gotoxy(3, 3);
    printf("HARBOR LIGHTS");
    gotoxy(2, 5);
    printf("a pier at dusk");
    gotoxy(1, 10);
    printf("original template");
    gotoxy(2, 14);
    printf("Press A");
}

static void draw_premise(void) {
    clear_screen();
    gotoxy(0, 2);
    printf("PREMISE");
    gotoxy(0, 4);
    printf("Guide the ferry");
    gotoxy(0, 5);
    printf("lamps along the");
    gotoxy(0, 6);
    printf("storm-lit pier.");
    gotoxy(0, 8);
    printf("Keep every light");
    gotoxy(0, 9);
    printf("burning until the");
    gotoxy(0, 10);
    printf("tide turns.");
    gotoxy(0, 14);
    printf("A continue");
    gotoxy(0, 15);
    printf("START skips");
}

static void draw_lore(void) {
    clear_screen();
    gotoxy(0, 1);
    printf("LORE – Old Keeper");
    gotoxy(0, 3);
    printf("The channel marks");
    gotoxy(0, 4);
    printf("are older than the");
    gotoxy(0, 5);
    printf("town charter.");
    gotoxy(0, 7);
    printf("If three lamps go");
    gotoxy(0, 8);
    printf("dark, the fog will");
    gotoxy(0, 9);
    printf("not lift till dawn.");
    gotoxy(0, 14);
    printf("A to step onto pier");
}

static void enter_play(void) {
    clear_screen();
    gotoxy(0, 0);
    printf("PIER  lamps:0  +");
    gotoxy(0, 1);
    printf("D-Pad move  A light");
    gotoxy(0, 16);
    printf("Walk to posts (+)");
    set_sprite_data(0, 1, lantern_tiles);
    set_sprite_tile(0, 0);
    move_sprite(0, pier_x, pier_y);
    SHOW_SPRITES;
}

static void draw_hud(void) {
    gotoxy(0, 0);
    printf("PIER  lamps:%u  + ", (unsigned)lanterns);
}

/* Three fixed lamp posts on the pier (screen coords for sprite). */
static const uint8_t posts_x[3] = {40, 80, 120};
static const uint8_t posts_y[3] = {96, 80, 96};
static uint8_t lit[3] = {0, 0, 0};

static void draw_posts(void) {
    uint8_t i;
    for (i = 0; i < 3; i++) {
        gotoxy((posts_x[i] >> 3) - 1, (posts_y[i] >> 3) - 2);
        if (lit[i])
            printf("*");
        else
            printf("+");
    }
}

static void vbl_isr(void) {
    if (!frame_done) {
        lag_frames++;
    }
    frame_done = 0;
}

void main(void) {
    uint8_t j;

    /* Expose lag counter at a stable WRAM address for QA (optional poke). */
    (void)lag_frames;

    disable_interrupts();
    add_VBL(vbl_isr);
    enable_interrupts();

    DISPLAY_ON;
    SHOW_BKG;
    SPRITES_8x8;

    /* Let the LCD and console font settle before first paint. */
    for (j = 0; j < 8; j++)
        wait_vbl_done();

    draw_title();
    wait_vbl_done();
    wait_release();

    while (1) {
        frame_done = 1;
        j = joypad();

        if (hold) {
            if (!j)
                hold = 0;
        } else if (j) {
            hold = 1;
            if (state == ST_TITLE) {
                if (j & J_A) {
                    state = ST_PREMISE;
                    draw_premise();
                    wait_vbl_done();
                }
            } else if (state == ST_PREMISE) {
                if (j & (J_A | J_START)) {
                    state = ST_LORE;
                    draw_lore();
                    wait_vbl_done();
                }
            } else if (state == ST_LORE) {
                if (j & (J_A | J_START)) {
                    state = ST_PLAY;
                    enter_play();
                    draw_posts();
                    wait_vbl_done();
                }
            } else if (state == ST_PLAY) {
                if (j & J_A) {
                    uint8_t i;
                    for (i = 0; i < 3; i++) {
                        int8_t dx = (int8_t)pier_x - (int8_t)posts_x[i];
                        int8_t dy = (int8_t)pier_y - (int8_t)posts_y[i];
                        if (dx < 0)
                            dx = (int8_t)-dx;
                        if (dy < 0)
                            dy = (int8_t)-dy;
                        if (dx < 12 && dy < 12 && !lit[i]) {
                            lit[i] = 1;
                            lanterns++;
                        }
                    }
                    draw_hud();
                    draw_posts();
                }
            }
        }

        /* Continuous D-pad while in play (not edge-triggered). */
        if (state == ST_PLAY) {
            j = joypad();
            if (j & J_LEFT) {
                if (pier_x > 16)
                    pier_x -= 2;
            }
            if (j & J_RIGHT) {
                if (pier_x < 152)
                    pier_x += 2;
            }
            if (j & J_UP) {
                if (pier_y > 40)
                    pier_y -= 2;
            }
            if (j & J_DOWN) {
                if (pier_y < 136)
                    pier_y += 2;
            }
            move_sprite(0, pier_x, pier_y);
        }

        wait_vbl_done();
    }
}
