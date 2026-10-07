# Versioning and device install

## ROM filenames

- Versioned: `build/<slug>_vX.Y.gbc` (example: `harbor_lights_v0.1.gbc`)
- Optional floating "current": `build/<slug>.gbc`
- API / catalog `version` field is often without the leading `v` (`0.1`), while the filename keeps `_v0.1`
- Record md5 or sha256 in commit messages and `qa/report.json`

## Git discipline (recommended)

- Tag device-bound releases `<slug>-vX.Y` when you maintain a monorepo
- Feature branches do not install to hardware by default

## Device install (LOCKED in v0)

`/install-on-device` stays disabled unless `HANDHELD_FORGE_UNLOCK_DEVICE=1`.

When unlocked, preferred order:

1. **Cloud push inbox** with `GAMEFORGE_SENDER_TOKEN` (`gfs_` prefix) against `GAMEFORGE_API_BASE`
   - Pair once with handheld 6-digit code → sender token
   - `POST /v1/devices/:deviceId/pushes` → `PUT` ROM bytes → `POST /v1/pushes/:pushId/ready`
2. **LAN CLI fallback:** `gameforge-device push <file.gbc>` if on PATH
3. **Syncthing folder last** – and **only after asking the user** where to write. Never write outside the project without consent.

Refuse dirty / unapproved installs when your local policy requires a clean main checkout.

## Agent checklist

- Version bump intentional
- Unlock env set before any push
- User confirmed destination path for Syncthing fallback
- No secrets committed
