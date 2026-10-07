---
name: build
description: Compile the current GBDK-2020 handheld project to a versioned .gbc ROM.
---

# /build

Compile the active handheld project with GBDK-2020.

## Steps

1. Confirm GBDK is available (`$GBDK_DIR` or `/opt/gbdk`, else run `scripts/setup.sh`).
2. Identify project root (contains `src/` + Makefile/`build.sh`).
3. Run the plugin builder:

```bash
./scripts/build.sh <project-dir> [--version X.Y] [--clean]
```

4. Expect output `build/<slug>_vX.Y.gbc` plus md5/sha256 in the log.
5. Fail honestly on compiler/linker/bank overflow errors – do not ship a broken ROM.
6. Optionally refresh dirty art/music generators if the project documents them.

## Guardrails

- Never write outside the project (no device sync folders)
- Never tag a "device build" without user approval
- Deterministic: prefer checked-in sources only
