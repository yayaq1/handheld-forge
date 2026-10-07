# GBDK-2020 workflow

## Toolchain

- Install GBDK-2020 (Linux x64 tarball is fine for CI/agents). Default path: `/opt/gbdk` or project-local `tools/gbdk/` (do not commit the toolchain).
- `lcc` drives compile + link. Prefer a project `build.sh` that fails on error and prints bank usage.
- Plugin helper: `scripts/setup.sh` installs GBDK + PyBoy; `scripts/build.sh` builds a GBDK project.

## Project layout (template)

```
src/          C sources
include/      headers
res/          optional png → png2asset outputs
build/        objects + versioned .gbc
build.sh      deterministic build
```

## Build rules

- Output a **versioned** ROM: `build/<slug>_vX.Y.gbc` (and optionally a `build/<slug>.gbc` "current" copy).
- Fail the build on bank overflow / link errors – never ship a truncated ROM.
- Keep builds deterministic: fixed GBDK path, checked-in sources, no wall-clock stamps in binaries when avoidable.
- Print md5/sha256 of the ROM in the build log for commit messages.

## Platform header

- For GBC-class colour features, set CGB compatibility flags appropriately in the template.
- Say "handheld" / "GBC-class" in docs – never console trademarks.

## Agent checklist

1. `scripts/setup.sh` once per machine
2. Edit sources in the game project
3. `scripts/build.sh <project-dir>` → versioned `.gbc`
4. `scripts/playtest.py` on that ROM
