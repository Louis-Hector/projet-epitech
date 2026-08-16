#!/bin/bash

BLUE="\033[34m"
YELLOW="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

echo -e "${BLUE}Ollama model 'codename' created based on 'Modelfile'${RESET}"
ollama create codename -f Modelfile > /dev/null 2>&1