---
name: publish-to-arcade
description: LOCKED – publish an original .gbc/.gba to the Game Forge arcade (disabled unless HANDHELD_FORGE_UNLOCK_PUBLISH=1).
---

# /publish-to-arcade

## Lock check (do this first)

If environment variable `HANDHELD_FORGE_UNLOCK_PUBLISH` is not set to `1`:

1. Tell the user this command is **LOCKED** for v0.
2. Explain unlock: export `HANDHELD_FORGE_UNLOCK_PUBLISH=1` and log who/when in `artifacts/rounds.log`.
3. **Stop. Do not call the API. Do not upload files.**

## When unlocked – eventual flow

Requires env (never commit secrets):

- `GAMEFORGE_API_BASE` (default `https://gforge.pages.dev`)
- `GAMEFORGE_PUBLISHER_TOKEN` (Bearer `gfp_…`)

Client-side checks before POST:

- Originals only: `isFanDemake: false`, `visibility: public`
- `aiDisclosure` required (non-empty string or object)
- slug `^[a-z0-9-]{3,48}$`
- platform lowercase (`gbc` / `gba`)
- ROM size limits (gbc ≤8 MiB, gba ≤24 MiB); cover PNG ≤512 KiB
- Franchise / console denylist on slug/title/romFile

API sequence:

1. `POST /v1/publish` JSON (premise preferred, coverStill optional, rom sha256/size/romFile/version without leading `v`)
2. `PUT` raw bytes to `romUploadUrl` / `coverUploadUrl` (signed, ~15 min)
3. `POST /v1/publish/:submissionId/complete` → `pending_review`
4. Poll `GET /v1/publish/:submissionId` – nothing public until admin approval

Production may return `403 publish_disabled` until the server flag is on – report that honestly.
