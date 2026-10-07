# PyBoy QA

## Setup

- Python venv with `pyboy` (and `pillow` for screenshots). Plugin: `scripts/setup.sh`.
- Always run **headless** / window off for agents.
- Use CGB mode for GBC-class ROMs.

## Default suite (v0)

`scripts/playtest.py`:

1. Boot ROM
2. Press through title / premise / lore cards (A to advance, optional START skip)
3. Reach play scene; light input smoke
4. Watchdog: freeze if main-loop / LCD stall exceeds threshold
5. Optional: read ROM lag counter if present
6. Save screenshots + `qa/report.json`

## Hard cap

- Default budget: **10–15 emulated minutes** per `/playtest`.
- Longer fuzz or soak only when the user explicitly asks.
- Stop early on freeze; report best-so-far.

## Softlock watchdogs (recommended)

- Main-loop counter must advance while LCD is on (e.g. 45-frame stall = softlock)
- No menu/card may hold forever without input path
- Game state enum always valid

## Bots (later rounds)

- Perfect / sloppy / fuzz input profiles
- Contact sheets for Critic
- APU WAV spot checks for title theme (optional)

## Agent checklist

- ROM path and hash recorded
- Stills at native 160×144
- Report lists lag, freezes, frames advanced
- Time cap respected
