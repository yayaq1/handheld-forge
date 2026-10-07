# Art pipeline (pixel, GBC-class)

## Constraints

- Native resolution **160×144**
- Background and sprite palettes: **4 colours each**
- Prefer every tile fitting a palette with **0 remapped pixels** when possible
- Theme palettes can swap colours on the same tile data for dusk/dawn/etc.

## Quantise vs hand 1×

- Gameplay tiles: controlled quantise into locked palettes is OK if silhouettes survive.
- Title / key cards: often draw **1× straight in target colours** – blind quantise destroys ink craft.
- Avoid muddy dithering that collapses at native size; prefer clean value clusters.

## Tooling tips

- `png2asset` (GBDK) for PNG → C tile/map/sprite data
- Keep source PNGs indexed or carefully converted; document palette IDs in `art/LEDGER.md`
- Generation passes (if used) must be cleaned to the palette – never ship full-colour PNGs to the ROM

## Critic focus

- Silhouette readability at 1×
- Palette discipline
- Consistent tile grid
- No mid-load flashing

## Agent checklist

- LEDGER status rows updated (`placeholder` → `final`)
- BAR criteria C1–C2 evidence in stills
- No ref images traced into assets
