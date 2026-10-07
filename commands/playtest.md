---
name: playtest
description: Headless PyBoy playtest – boot cards, smoke the play scene, check freezes/lag, save screenshots (capped 10–15 emulated minutes).
---

# /playtest

Stage B/D evidence gatherer for `handheld-game-forge`.

## Steps

1. Resolve ROM path (argument, or latest `build/<slug>_v*.gbc`).
2. Ensure PyBoy venv exists (`scripts/setup.sh` if needed).
3. Run:

```bash
./scripts/playtest.py --rom <path.gbc> [--minutes 12] [--out qa]
```

4. Script must: boot → press through title/premise/lore cards → reach play → light input → watchdog freezes → write screenshots + `qa/report.json`.
5. Cap at **10–15 emulated minutes** unless the user explicitly raises it.
6. Hand stills to a fresh Critic for visual gates; do not soft-WIN from a green lag report alone.

## Guardrails

- Headless only in agent contexts
- No publish / device side effects
- Report freezes as FAIL evidence even if some stills look fine
