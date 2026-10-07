# VRAM and sprites (GBC-class)

## VBlank-scheduled writes

- Never thrash `set_bkg_tiles` / VRAM mid-frame while the LCD is drawing the region you are editing – that causes tearing and lag.
- Compose HUD or card rows in RAM, then copy **after VBlank**, ideally ≤1 row per frame when under pressure.
- Queue background writes; drain the queue in the VBlank ISR or right after wait_vbl_done.
- Heavy loads (portrait tiles, backdrop banks): turn LCD off or keep the screen black and stream **~16 tiles per frame**, then map rows over subsequent frames.

## Sprites / scanline limit

- Hardware allows on the order of **10 sprites per scanline**. Exceeding that drops sprites (flicker).
- Budget OAM entries for the hero carefully (multi-sprite metasprites). Prefer 8×16 sprite mode when it halves entry count for tall characters.
- Stagger actors vertically when crowds would share a line.
- Ambient particles count toward the same limit – cut them first when flicker appears.

## Lag counter pattern

- In the VBlank ISR, if the main loop has not flagged "frame done", increment a lag counter in RAM.
- PyBoy reads that counter for QA. Target **0 lag frames** in normal gameplay; investigate any streak.

## Agent checklist

- HUD stable across stills
- No flashing tiles during card loads
- No sprite dropout on planned cameras
- `qa/report.json` lag within target
