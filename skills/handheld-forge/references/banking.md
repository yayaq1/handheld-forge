# Banking

## Why banks matter

GBC-class ROMs use banked cartridges. Graphics, music, and card data often live outside bank 0. Bank-0 code owns loaders that switch banks briefly, copy into VRAM/WRAM, then switch back.

## Practices

- Keep an explicit **bank map** in DESIGN or PLAN (engine / music / gfx / cards / maps).
- Put hot gameplay code and loaders in bank 0 (or a fixed small set).
- Spread large loads over frames while the screen is black (tiles, then map rows).
- Build must **fail on bank overflow** – never silence the linker and ship.

## Escalation

When content does not fit:

1. Move cold data (cards, title) to higher banks
2. Share tile data across screens with palette swaps
3. Cut unique tiles; reuse metasprites
4. Reduce map unique tiles before raising ROM size class

## Agent checklist

- PLAN lists bank owners
- Loader paths never call banked code unsafely
- Build log shows free space / no overflow
