---
name: install-on-device
description: LOCKED – push a versioned ROM to a paired handheld (disabled unless HANDHELD_FORGE_UNLOCK_DEVICE=1).
---

# /install-on-device

## Lock check (do this first)

If environment variable `HANDHELD_FORGE_UNLOCK_DEVICE` is not set to `1`:

1. Tell the user this command is **LOCKED** for v0.
2. Explain unlock: export `HANDHELD_FORGE_UNLOCK_DEVICE=1` and log who/when in `artifacts/rounds.log`.
3. **Stop. Do not copy ROMs anywhere outside the project.**

## When unlocked – preferred order

Never write outside the user's project without asking.

### 1. Cloud push inbox (preferred)

Env:

- `GAMEFORGE_API_BASE`
- `GAMEFORGE_SENDER_TOKEN` (`gfs_…`, from pairing)

Flow:

1. `GET /v1/senders/devices` – pick device
2. `POST /v1/devices/:deviceId/pushes` with `{filename, size, sha256, platform?}`
3. `PUT` ROM bytes to `uploadUrl`
4. `POST /v1/pushes/:pushId/ready`
5. Poll status until delivered/installed (or report failure)

Pairing (once): `POST /v1/senders/pair` with the 6-digit code shown on the handheld.

### 2. LAN CLI fallback

If `gameforge-device` is on PATH:

```bash
gameforge-device push <file.gbc|.gba> [--device name]
```

### 3. Syncthing folder (last resort)

Ask the user for the exact sync folder path. Copy only the versioned ROM they approve. Never assume `/workspace/handheld-sync` or any path on their machine.

## Guardrails

- Prefer a committed, versioned ROM the user named
- Fan IP may be pushed privately to one's own device, but still ask before any filesystem write outside the project
- Wrong token scope / unlock missing → stop
