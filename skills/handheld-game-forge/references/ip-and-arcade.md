# IP and arcade publish

## Branding

- Allowed: handheld, GBC-class, `.gbc`, `.gba`, homebrew, pixel
- Forbidden in repo text, templates, and shipped strings: console manufacturer trademarks and classic handheld product brand names

## Release postures

| Posture | Public arcade | Notes |
|---|---|---|
| `original` | Allowed when unlocked | Original title, names, art, audio |
| `renamed-homage` | Usually private | Original names/art; refs review-only |
| `personal` / fan | Private only | Never set `isFanDemake: true` on public publish |

## Publish (LOCKED)

`/publish-to-arcade` requires `HANDHELD_FORGE_UNLOCK_PUBLISH=1`.

Env:

- `GAMEFORGE_API_BASE` (default live worker URL from contracts docs)
- `GAMEFORGE_PUBLISHER_TOKEN` (`gfp_` prefix) – never commit; never paste into chat logs

Flow:

1. Client-side checks: slug `^[a-z0-9-]{3,48}$`, size limits, extension, denylist, `aiDisclosure` present, `isFanDemake: false`, `visibility: public`, platform lowercase
2. `POST /v1/publish` with premise, rom metadata, coverStill optional, aiDisclosure required
3. `PUT` ROM (and cover) to signed URLs
4. `POST /v1/publish/:submissionId/complete` → `pending_review`
5. Nothing is public until admin approval

Denylist is whole-token after normalize (franchise and console marks). Prefer failing early locally.

## Agent checklist

- Unlock set
- Originals only for public
- aiDisclosure non-empty
- Tokens only from env
