#!/bin/bash

set -eu

SERVICE_DIR="$HOME/.config/systemd/user"
SERVICE_FILE="$SERVICE_DIR/famine.service"

# Only try to stop/disable if the unit is actually known to systemd
if systemctl --user list-unit-files famine.service &>/dev/null; then
	systemctl --user disable --now famine.service 2>/dev/null || true
fi

# Remove the unit file itself
if [ -f "$SERVICE_FILE" ]; then
	rm "$SERVICE_FILE"
fi

systemctl --user daemon-reload
systemctl --user reset-failed

# Confirm the unit is fully gone
if ! systemctl --user list-unit-files famine.service &>/dev/null; then
	echo "famine.service uninstalled"
else
	echo "Failed: famine.service still present" >&2
	exit 1
fi
