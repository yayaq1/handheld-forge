# Visual Bar (handheld, hard gate)

The bar is per game. Judge every locked criterion on the current capture set at full resolution (native 160×144 for GBC-class), then on blurred SxS when refs exist. Every criterion is PASS or FAIL. One failing still fails the criterion. WIN requires every criterion in `art/BAR.md` to PASS.

Adapted from Eric Zakariasson's Visual Bar pattern (MIT), retargeted to pixel handheld craft.

## Building the bar (Stage A)

1. Start from the universal core below (always present).
2. Add game-specific criteria from BRIEF, locked refs, and `art/LOOK.md`.
3. Write `art/BAR.md` before Stage B. Each row: id, name, PASS when, FAIL signs, justifying ref ids, `core` or `game`.
4. Size band: 5 to 15 criteria. Freeze after Stage A. Mid-loop you may only `BAR-EXPAND` (add, log, stay ≤15). Never remove or soften to exit.

## Universal core (handheld)

**C1. Palette and value structure.** PASS when each used palette has ≤4 colours; value groups read clearly at 160×144; theme swaps change colours on shared tile data without muddy mid-tones. FAIL: more than 4 colours per palette in assets, grey mush, random rainbow noise, blind quantise banding.

**C2. Silhouette and tile density.** PASS when hero and key props read as shapes at native res; consistent 8×8 tile grid; no accidental half-pixel shimmer; density matches the locked refs' craft tier. FAIL: unreadable blobs, broken outlines, sparse empty planes where refs are deliberate, tile seams that fight the grid.

**C3. SxS blur / downscale test.** Blur or downscale both halves until fine detail collapses. PASS when value structure and palette family still read as the same production tier. FAIL when the game half reads like a muddy web toy next to polished handheld craft.

**C4. Live capture provenance.** PASS when every still is from the running ROM at the delivered commit via PyBoy (or equivalent), native resolution, manifest complete. FAIL: mockups, edited plates, wrong build.

**C5. Cards, text, and motion consistency.** PASS when title/premise/lore cards are legible (≤4 lines × ~18 chars on dialogue cards), portraits have readable silhouettes, A/START advance works, walkthrough frames match still quality, no flicker from mid-frame VRAM writes. FAIL: illegible text, placeholder lorem, freeze on cards, flashing tiles, pop-in mid-fade.

## Recommended game-specific criteria (pick what refs justify)

- Sprite line budget: no flicker from >~10 sprites on a scanline in planned cameras
- Lore-card portrait craft (ink/pixel portrait, name/tag hierarchy)
- HUD compose-in-RAM / after-VBlank discipline (observable: stable HUD, low lag)
- Zero-slowdown: lag counter 0 (or agreed bound) in gameplay windows
- Music: 4-channel arrange that does not starve SFX
- Load-while-black: no visible tile tearing during bank loads

## Automatic FAIL (visual)

- Placeholder primitives claimed as final art in Stage D stills
- Muddy dithering that destroys silhouettes at 160×144
- Illegible dialogue or title text
- Visible VRAM tearing / flashing during loads
- SxS blur test fail against locked refs
- Stills not from the live ROM build

## Automatic FAIL (process)

- BAR missing, <5 or >15 criteria, or missing PASS/FAIL observables
- Ledger still has `placeholder` rows at Stage D when claiming visual WIN
- Refs not locked or swapped weaker without `REF-SWAP` log
- Critic verdict uses numeric scores or banned phrases
- Secrets or ref imagery inside the ROM tree
- Forbidden console trademarks in shipped strings

## Banned phrases

Any of these in a Critic verdict, Builder handback, or status line invalidates the verdict (process FAIL):

- "fine for a prototype"
- "close enough"
- "conditional WIN"
- "good enough for handheld"
- "players won't notice"
- "AI art is expected to look like this"
- "pass with notes" (as a WIN substitute)

Use PASS or FAIL only. Soft-passing weak pixel art is exactly what this bar exists to prevent.
