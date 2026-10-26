#!/bin/bash

# 1. Namen des aktuellen Projektordners dynamisch holen
PROJ_NAME=$(basename "$PWD")

# 2. Aktiven Branch ermitteln (z. B. main oder master)
BRANCH=$(git branch --show-current 2>/dev/null)
if [ -z "$BRANCH" ]; then
    BRANCH="main"
fi

# 3. Commit-Nachricht setzen
MSG=$1
if [ -z "$MSG" ]; then
    MSG="Auto-Sync: $PROJ_NAME Update"
fi

echo "=========================================="
echo "  Universal Sync: $PROJ_NAME"
echo "  Branch:         $BRANCH"
echo "=========================================="

# 4. Dateien stagen
git add .

# 5. Nur committen, wenn es echte Änderungen gibt
if git diff-index --quiet HEAD -- 2>/dev/null; then
    echo "Keine Änderungen zum Committen vorhanden."
else
    git commit -m "$MSG"
fi

# 6. Direkt zu GitHub pushen
echo "Pushe zu origin/$BRANCH..."
git push origin "$BRANCH"

if [ $? -eq 0 ]; then
    echo "=========================================="
    echo "  Fertig! $PROJ_NAME ist auf GitHub."
    echo "=========================================="
else
    echo "FEHLER: Push fehlgeschlagen!"
fi