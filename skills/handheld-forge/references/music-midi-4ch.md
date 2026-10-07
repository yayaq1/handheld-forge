# Music: MIDI → 4 channels

## Hardware budget

GBC-class audio is four channels roughly:

1. Pulse (lead / melody)
2. Pulse (harmony / mid)
3. Wave (bass or expressive lead)
4. Noise (percussion / texture)

SFX often shares pulse or noise – arrange so gameplay SFX can duck or steal a channel briefly without silence.

## Pipeline pattern

1. Keep reference MIDI / analysis notes out of the shipped ROM tree if they contain non-owned material (`ref/` locally, gitignored for private work).
2. Arrange with a script (`mido` or similar) into pattern tables consumed by a tiny driver.
3. Export **derived C arrays only** into the project.
4. Title may use a fuller arrange; gameplay uses a sparser bed so SFX stays clear.

## Agent checklist

- Channel roles documented in PLAN
- No copyrighted sequence data committed as "original" without rights
- Playtest still runs if music init fails soft (prefer hard fail in debug)
