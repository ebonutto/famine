#!/bin/bash

set -eu

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
FAMINE_DIR="$(dirname "$SCRIPT_DIR")"
FAMINE_BIN="$FAMINE_DIR/famine"

SERVICE_DIR="$HOME/.config/systemd/user"
SERVICE_FILE="$SERVICE_DIR/famine.service"

# Make sure the binary exists and is executable before creating the service
if [ ! -x "$FAMINE_BIN" ]; then
    echo "Error: $FAMINE_BIN not found or not executable" >&2
    exit 1
fi

mkdir -p "$SERVICE_DIR"

# Generate the systemd user unit
cat > "$SERVICE_FILE" <<EOF
[Unit]
Description=Famine

[Service]
Type=oneshot
RemainAfterExit=yes
ExecStart=$FAMINE_BIN
WorkingDirectory=$FAMINE_DIR

[Install]
WantedBy=default.target
EOF

systemctl --user daemon-reload
systemctl --user enable --now famine.service

# Confirm the service actually started
if systemctl --user is-active --quiet famine.service; then
    echo "famine.service installed and active"
else
    echo "Failed: check systemctl --user status famine.service" >&2
    exit 1
fi
