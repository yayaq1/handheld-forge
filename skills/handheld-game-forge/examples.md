# Examples (handheld Critic / Orchestrator)

Illustrative only. Original placeholder content – no fan IP.

## Good: Stage B pass

```
VERDICT: B-PASS (loop only, NOT A VISUAL WIN)

Evidence: artifacts/stage-b/loop-frames/01-title.png … 10-play.png
Boot: build exit 0; ROM build/harbor_lights_v0.1.gbc
Cards advance on A; START skips premise; play scene reachable in ≤30s emulated.
```

## Bad: Stage B soft-pass (invalid)

```
VERDICT: B-PASS
Looks fine for a prototype.
```

Why invalid: missing `NOT A VISUAL WIN`; banned soft-pass phrase.

## Good: FAIL with punch list

```
VERDICT: FAIL
CRITERIA:
- C1: FAIL – stills/03-lore.png palette shows banding; muddy mid greys
- C2: FAIL – hero silhouette unreadable at native 160×144 in stills/05-play.png
- C3: FAIL – sxs/03 blur: game half collapses to flat wash
- C4: PASS – stills from PyBoy at commit abc1234
- C5: FAIL – lore card line 3 wraps mid-word; portrait flash during load
PUNCH:
1. still=03-lore.png ref=ref-02 region=portrait observed=banding + flash during load
   ref_shows=stable ink portrait on solid panel done_when=no flash; ≤4 colours; clear outline
2. still=05-play.png ref=ref-01 region=hero observed=blob silhouette
   ref_shows=readable side profile done_when=readable at 1× without upscale
```

## Bad: numeric soft score (invalid)

```
VERDICT: WIN (7.5/10) – close enough for handheld
```

## Good: status lines

```
R3 FAIL: failing C1,C2,C5; punch items 4; escalation rung 1 (VBlank HUD); next: Builder R4
R7 WIN: failing none; punch items 0; next: harsh visual
R7 WIN voided: cohesion fail on card panel vs play palette; next: Builder R8
```

## Good: Builder handback

```
ROUND R4 COMPLETE
commit: def5678
rom: build/harbor_lights_v0.1.gbc
captures: artifacts/stills/ (12)
addressed: 1, 2, 3
not addressed: 4 (needs bank split for portrait tiles; propose escalation rung 2)
```

## Bad: Builder quality claim (invalid)

```
ROUND R4 COMPLETE – art looks great now, should be a WIN
```

## Diagnoser steer (after 3 hard FAILs)

```
DIAGNOSIS: C5 flash caused by set_bkg_tiles during active draw.
STEER: compose card map in RAM; copy after VBlank ≤1 row/frame while LCD on,
or load 16 tiles/frame while LCD off. Do not lower BAR. Do not swap refs.
```
