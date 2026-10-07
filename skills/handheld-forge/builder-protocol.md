# Builder protocol (handheld)

Stage-by-stage runbook for Handheld Forge. Orchestrator follows all of it and hands each role only the parts that apply. Rubric: `visual-bar.md`. Critic prompt: `critic-prompt.md`.

Adapted from Eric Zakariasson's game-builder stage gates (MIT), retargeted to GBDK-2020 + PyBoy. No Blender, no 3D, no browser-toy preview as the primary gate.

## Stage gates

Each stage lists Entry, Work, Exit checklist, and Gate owner. Do not start a stage before the previous Exit checklist is fully checked. Record every gate result in `artifacts/rounds.log`.

v0 thin slice emphasizes **A, B, and D**. Full Stage C art ladder is documented for later rounds; do not soft-pass weak art by skipping Critic.

---

## Stage A: Brief, refs, plan, scaffold

**Entry:** user request or `/new-game`.

**Work:**

1. Collect **release posture** (required): `personal` | `renamed-homage` | `original`. Refuse to start if missing. Fan / private homage → mark `private` in BRIEF; public path must stay original.
2. Write `BRIEF.md` (one page): original working title, premise, genre loop, session length target (depth over a two-minute loop), win/fail, non-goals, platform (`gbc` default), stack (GBDK-2020), deliverables, `Publish: LOCKED`, `Device: LOCKED`.
3. Lock refs (4–8) into `refs-locked/` with `SOURCES.md`. Prefer polished homebrew / public-domain / self-captured handheld stills. Slots: title or card craft, mid-gameplay, HUD or dialogue card, mood/palette. Note: review only, not shipped. Never official first-party console screenshots.
4. Dispatch Planner → `PLAN.md`: loop and pacing; screen flow (title → premise → lore cards → play); entity boundaries; bank map sketch; VRAM/OAM budget; music channel plan; art plan; risk list with escalation triggers (banks, VRAM schedule, quantise, cut scope).
5. Scaffold from `templates/gbc-gbdk-minimal/` (or project copy). Create `art/LEDGER.md` v0 and `art/BAR.md` per `visual-bar.md`.
6. Recommended: Critic plan review → `PLAN-OK` or `PLAN-GAPS`.

**Exit checklist:**

- [ ] `BRIEF.md` frozen with Publish/Device LOCKED and release posture set
- [ ] `refs-locked/` + `SOURCES.md` (4–8 refs)
- [ ] `PLAN.md` covers loop, cards, banks, VRAM, risks
- [ ] `art/BAR.md` locked (5–15 criteria)
- [ ] `art/LEDGER.md` v0 covers planned visible elements
- [ ] Project scaffolds and `./scripts/build.sh` (or project build) is documented
- [ ] No console trademarks; no fan IP names in public posture
- [ ] No secrets or model identifiers in artifacts

**Gate owner:** Orchestrator (Critic plan review recommended).

---

## Stage B: Playable foundation

**Entry:** Stage A exit. Triggered by Builder work after `/new-game` / `/build`.

**Work:**

- Implement boot path: title card → premise card → at least one lore card → tiny playable scene.
- Placeholders allowed here and nowhere later for final art claims.
- Input: A advances cards; START skips; play scene has a minimal verb (move / interact).
- Evidence: `artifacts/stage-b/boot.log`, `artifacts/stage-b/loop-frames/` (8–12 frames from PyBoy), ROM path + md5.

**Exit checklist:**

- [ ] Boot documented; build exit 0; versioned ROM written
- [ ] Cards advance without freeze; play scene reachable
- [ ] Critic returns `VERDICT: B-PASS (loop only, NOT A VISUAL WIN)` or FAIL with punch list on loop/boot

**Gate owner:** Critic, loop-only. Verdict string must contain `NOT A VISUAL WIN`.

---

## Stage C: Art pipeline (staged; full ladder optional in v0)

**Entry:** Stage B exit.

Run sub-gates when polishing beyond placeholders. After each: re-verify boot/loop, update ledger, fresh Critic `ART-PASS C<n>`.

| Sub-gate | Focus |
|---|---|
| C0 | Look decomposition in `art/LOOK.md` (palette families, silhouette language, card grammar) |
| C1 | Palette and value structure; theme palettes on shared tile data |
| C2 | Tile economy and fit (prefer 0 remapped pixels per tile↔palette) |
| C3 | Sprite/OAM density within ~10/scanline; readable hero silhouette |
| C4 | Lore-card and HUD typography craft |
| C5 | Motion polish, load schedules while screen black, music 4-channel arrange |

**Escalation ladder** (never "upgrade to a 3D engine"):

1. Fix VBlank-scheduled VRAM writes / HUD compose-in-RAM
2. Re-bank; fail build on bank overflow
3. Re-quantise or hand-author 1× in target colours (no blind quantise on title)
4. Cut sprite overdraw / reduce simultaneous actors
5. Cut scope (fewer cards, smaller map) – log honestly

---

## Stage D: Capture and Critic loop

**Entry:** Stage B exit (and Stage C if art was claimed final).

**Work:**

1. `/playtest` (or `scripts/playtest.py`) on the versioned ROM. Cap **10–15 emulated minutes**.
2. Save stills under `artifacts/stills/`, optional contact sheet, `qa/report.json` (lag, freezes, softlocks).
3. Fresh Critic with `critic-prompt.md` + BAR + stills (+ SxS vs refs when available).
4. On FAIL: numbered punch list → Builder round → full re-capture → Critic. Rounds R1…Rn.
5. After 3+ consecutive hard FAILs: pause punches, spawn **Diagnoser**, steer Builder – never lower the bar.
6. After Critic WIN: pre-handoff verification + Orchestrator harsh visual of every still. Void WIN if cohesion fails.

**Exit checklist:**

- [ ] Critic WIN on every BAR criterion
- [ ] `qa/report.json` shows no freezes; lag within target (prefer 0 gameplay lag frames)
- [ ] Pre-handoff IP/secrets/refs-in-build scan clean
- [ ] Orchestrator harsh visual PASS
- [ ] Publish still LOCKED unless user unlock logged

**Gate owner:** Critic for WIN; Orchestrator for process + harsh visual.

---

## Stage E: Comparison matrix (optional)

Only if the user names legs. One Builder + Critic loop per leg in its own workdir. No copying from another leg.

---

## Deliverables tree

```
BRIEF.md
PLAN.md
refs-locked/ + SOURCES.md
art/{LOOK,BAR,LEDGER,GENERATION-LOG}.md
artifacts/{stills,sxs,verdicts,rounds.log,stage-b/}
build/<slug>_vX.Y.gbc
qa/report.json
tools/ or scripts/ as needed
```

## Pre-handoff verification

- [ ] IP scan: no franchise denylist hits in slug/title for public posture
- [ ] Secrets scan: no tokens in tree
- [ ] No `refs-locked/` imagery inside ROM assets
- [ ] Ledger: zero `placeholder` rows if claiming visual WIN
- [ ] Versioned ROM filename matches BRIEF version
- [ ] Branding scan: no forbidden console trademarks in strings/docs

## Handoff template

```
HANDOFF
title: <original title>
platform: gbc
rom: build/<slug>_vX.Y.gbc
md5: <hash>
stage: D WIN
publish: LOCKED
device: LOCKED
notes: <one paragraph>
```

## Failure modes

- Soft-pass language → process FAIL; re-run Critic
- Bank overflow ignored → build must fail; fix map
- Mid-frame VRAM thrash → lag FAIL; schedule after VBlank
- Playtest over time cap without user OK → stop and report best-so-far
- Attempted publish/device without unlock → stop; print lock message
