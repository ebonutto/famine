#!/bin/bash

set -eu

SERVICE_DIR="$HOME/.config/systemd/user"
SERVICE_FILE="$SERVICE_DIR/famine.service"

if systemctl --user list-unit-files famine.service &>/dev/null; then
    systemctl --user stop famine.service 2>/dev/null || true
    systemctl --user disable famine.service 2>/dev/null || true
fi

if [ -f "$SERVICE_FILE" ]; then
    rm "$SERVICE_FILE"
fi

systemctl --user daemon-reload
systemctl --user reset-failed

if ! systemctl --user list-unit-files famine.service &>/dev/null; then
    echo "famine.service uninstalled"
else
    echo "Failed: famine.service still present" >&2
    exit 1
fi
