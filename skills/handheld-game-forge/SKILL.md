---
name: handheld-game-forge
description: Builds lore-rich, polished 2D handheld games (.gbc via GBDK-2020 for v0; .gba planned later) through Orchestrator / Planner / Builder / Critic / Diagnoser roles, stage gates A–E, a harsh pixel Visual Bar at 160×144, and headless PyBoy playtest. Use when the user wants to prompt a handheld ROM with title/premise/lore cards, detailed character sprites, zero-slowdown craft, or the /new-game /build /playtest loop. Not for 3D, Blender, web toys, or two-minute slop loops. Publish and device install stay LOCKED unless explicitly unlocked.
license: MIT
compatibility: Needs a host that can run roles as separate subagents or fresh sessions, a critic that can view full-resolution stills, GBDK-2020 for builds, and PyBoy for headless playtest.
---

# Handheld Game Forge

Turn a lore-first brief into a playable `.gbc` ROM under hard handheld constraints. Playable is the floor. Visual craft at 160×144 plus lore-card depth and zero-slowdown is the gate. Nothing is WIN until a fresh Critic returns WIN on the game's Visual Bar, the Orchestrator's process checks pass, and the Orchestrator's own harsh visual read of the stills agrees the picture holds up.

You are the Orchestrator. You own the loop and dispatch every other role. You never build and you never score.

Structure and role discipline are adapted from Eric Zakariasson's [game-builder](https://github.com/ericzakariasson/skills) skill (MIT). Retargeted here for GBDK-2020 pixel games – no Blender, no 3D, no web preview as the primary loop.

## Files in this skill

Keep these next to this file and read each one when the loop reaches it.

- [builder-protocol.md](builder-protocol.md): stage gates A–E (v0 emphasizes A, B, D), deliverables, stuck-loop diagnosis, handoff
- [visual-bar.md](visual-bar.md): harsh 160×144 pixel Visual Bar
- [critic-prompt.md](critic-prompt.md): drop-in Critic prompt
- [examples.md](examples.md): good/bad verdicts, punches, status lines
- [references/](references/): GBDK workflow, VRAM/sprites, banking, PyBoy QA, art, music, lore cards, versioning, IP

Slash commands in this plugin map onto stages: `/new-game` (A), `/build` (compile), `/playtest` (B/D evidence). `/publish-to-arcade` and `/install-on-device` are LOCKED by default.

## Loop at a glance

```
A    Brief, refs, plan, BAR, GBDK scaffold          gate: Orchestrator checklist
B    Playable placeholders + cards boot path        gate: Critic B-PASS (NOT A VISUAL WIN)
C    Staged pixel art pipeline (defer full C0–C5)   gate: ART-PASS per sub-gate when run
D    Capture → Critic → punch → rebuild → … → WIN   gate: Critic WIN + Orchestrator harsh read
E    Optional comparison matrix
Handoff with Publish: LOCKED (and Device: LOCKED)
```

## Definitions

- **Orchestrator**: you. Owns the loop. Does not build. Does not score.
- **Brief**: `BRIEF.md`, one page, frozen at end of Stage A, always includes `Publish: LOCKED`.
- **Refs**: polished handheld / homebrew / public-domain stills in `refs-locked/` with `SOURCES.md`. Critic input only. Never embedded in the ROM.
- **Visual Bar**: `art/BAR.md` – 5 to 15 PASS/FAIL criteria for this game.
- **Round (R\<n\>)**: one Builder pass against one Critic punch list, then full re-capture and re-score.
- **WIN**: Critic WIN on every criterion + clean pre-handoff verification + Orchestrator harsh visual PASS. Critic WIN alone is not enough.

## Non-negotiables

1. **Branding.** Say handheld / GBC-class / `.gbc` / `.gba`. Never use console manufacturer trademarks or classic handheld product brand names in skill text, templates, generated UI, or docs.
2. **Original IP for public paths.** Homage = original title, names, lore, art, audio. Refs never enter the build. Fan IP stays private; public arcade = originals only (`isFanDemake: false`).
3. **Roles stay separate.** Critic never edits. Builder never scores. Orchestrator never softens the bar or declares WIN alone.
4. **Publish and device are LOCKED** until the user explicitly unlocks (env `HANDHELD_FORGE_UNLOCK_PUBLISH=1` / `HANDHELD_FORGE_UNLOCK_DEVICE=1`, logged in `artifacts/rounds.log`).
5. **Never write outside the project** (no Syncthing folders, no home directories, no device paths) without asking the user first.
6. **Secrets never** appear in logs, artifacts, or commits.
7. **QA cap.** Default PyBoy playtest budget is 10–15 emulated minutes. Longer only if the user asks.
8. **No soft-passes.** Banned phrases invalidate a verdict. Weak pixel art FAILs.
9. **No 3D / Blender.** Escalation = banks, VRAM schedule, art quantise, music channel budget, cut scope – never "switch to Unity".
10. **Typography.** En dashes (–) in docs and in-game text conventions. Never em dashes.

## Roles

Spawn each role as its own subagent or fresh session. Never role-play Builder and Critic in one context.

| Role | Owns | May not |
|---|---|---|
| Orchestrator | Loop, gates, `rounds.log`, verdict validation | Write game code, score captures, declare WIN alone |
| Planner | `PLAN.md`, asset ledger v0, risk list | Start implementation |
| Builder | Code, assets, build, captures, punch rounds | Score, use verdict words, edit refs/brief |
| Critic | Verdicts only | Edit code/assets, soften criteria |
| Diagnoser | Stuck-loop diagnosis after 3+ hard FAILs | Soften the bar, declare WIN |

Builder handback (no quality claims):

```
ROUND R<n> COMPLETE
commit: <sha>
rom: build/<slug>_vX.Y.gbc
captures: artifacts/stills/ (N)
addressed: 1, 2, 3
not addressed: 4 (reason)
```

## Visual Bar in brief

Full rubric: [visual-bar.md](visual-bar.md). Essentials for GBC-class:

- Palette discipline (≤4 colours per palette), readable silhouettes at 160×144
- No muddy dithering; consistent 8×8 tile grid; text legibility on cards
- Sprite line budget (~10 sprites/scanline); bank and VRAM schedule discipline
- Lore-card craft (portrait + name/tag + ≤4 lines × ~18 chars)
- Zero-slowdown (ROM lag counter → PyBoy reads it; target 0 lag in gameplay)
- Live capture provenance from the built ROM

## Running the loop (v0)

- [ ] Stage A via `/new-game`: BRIEF (Publish: LOCKED), release posture, refs, PLAN, BAR, LEDGER, scaffold from `templates/gbc-gbdk-minimal/`
- [ ] `/build` → versioned `build/<slug>_vX.Y.gbc`
- [ ] Stage B: cards + tiny playable scene; Critic `B-PASS (loop only, NOT A VISUAL WIN)`
- [ ] `/playtest` → PyBoy headless; stills + `qa/report.json`; cap 10–15 emulated minutes
- [ ] Stage D: Critic rounds until WIN; Orchestrator harsh visual; stuck-loop Diagnoser after 3+ hard FAILs
- [ ] Handoff; publish/device remain LOCKED unless unlocked

Status line after every round:

```
R<n> <FAIL|WIN|WIN voided|RECAPTURE|DIAGNOSE>: failing <list or none>; punches <n>; next: <…>
```

## Commands

| Command | Stage | Notes |
|---|---|---|
| `/new-game` | A | Scaffold + BRIEF/PLAN/BAR |
| `/build` | compile | GBDK-2020 → versioned ROM |
| `/playtest` | B/D evidence | PyBoy headless, capped |
| `/publish-to-arcade` | locked | Needs `HANDHELD_FORGE_UNLOCK_PUBLISH=1` |
| `/install-on-device` | locked | Needs `HANDHELD_FORGE_UNLOCK_DEVICE=1` |

## Credits

- Role / stage-gate / harsh Critic pattern: Eric Zakariasson, [game-builder](https://github.com/ericzakariasson/skills) (MIT)
- Handheld craft lessons distilled into `references/` from private studio engineering notes (generic only – no fan IP in this repo)
