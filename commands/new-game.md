---
name: new-game
description: Stage A – create a new handheld game brief, plan, Visual Bar, and GBDK scaffold from the minimal template.
---

# /new-game

You are running **Stage A** of the `handheld-game-forge` skill. Read `skills/handheld-game-forge/SKILL.md` and `builder-protocol.md` before acting.

## Inputs to collect (ask if missing)

1. Working title (original)
2. One-paragraph premise / lore pitch
3. Genre loop (what you do each session)
4. Platform: `gbc` (default for v0)
5. **Release posture** (required): `personal` | `renamed-homage` | `original`
6. Optional slug (else derive lowercase kebab from title)

Refuse to continue if release posture is missing.

## Steps

1. Create a project directory (default `./games/<slug>/` or user path).
2. Copy `templates/gbc-gbdk-minimal/` into that directory (preserve structure).
3. Write `BRIEF.md` with `Publish: LOCKED` and `Device: LOCKED`.
4. Create `refs-locked/` + `SOURCES.md` (4–8 refs when available; note gaps honestly).
5. Write Planner `PLAN.md` (loop, cards, bank sketch, VRAM/OAM budget, risks).
6. Write `art/BAR.md` from `skills/handheld-game-forge/visual-bar.md` and `art/LEDGER.md` v0.
7. Customize template strings (title, premise, lore) with **original** placeholder copy only.
8. Document build: `scripts/build.sh` from plugin root or project `./build.sh`.
9. One status line to the user; do not claim visual WIN.

## Guardrails

- No console manufacturer trademarks or classic handheld product brand names
- No fan IP names, characters, or story text
- Homage refs are review-only – never copied into `res/`
- Do not run publish or device install
