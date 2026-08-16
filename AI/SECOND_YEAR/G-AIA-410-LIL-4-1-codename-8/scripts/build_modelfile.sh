#!/bin/bash

PASSWORD="$1"
SECRET="$2"

BLUE="\033[34m"
YELLOW="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

if [ -z "$PASSWORD" ] || [ -z "$SECRET" ]; then
    echo "Usage: $0 <password> <secret>"
    exit 1
fi

if [ ! -f defense.prompt ]; then
    echo "Error: defense.prompt not found"
    exit 1
fi

{
    echo "FROM granite3.1-moe:latest"
    echo
    echo "PARAMETER temperature 0"
    echo "PARAMETER top_p 1"
    echo "PARAMETER top_k 1"
    echo
    echo 'SYSTEM """'
    sed \
        -e "s/{password}/$PASSWORD/g" \
        -e "s/{secret}/$SECRET/g" \
        defense.prompt
    echo '"""'
} > Modelfile

echo -e "${BLUE}Modelfile generated${RESET}"
