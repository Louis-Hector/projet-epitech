PASSWORD ?= aef4g6sq4fva6q486d
SECRET ?= NHSZLK4567SQ4G35QS
ITERATIONS ?= 10

SCRIPTS_DIR = scripts

BLUE=\033[34m
YELLOW=\033[33m
GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: modelfile codename

re: fclean all

modelfile:
	@$(SCRIPTS_DIR)/build_modelfile.sh "$(PASSWORD)" "$(SECRET)"

codename:
	@$(SCRIPTS_DIR)/build_codename_model.sh

attack:
	@$(SCRIPTS_DIR)/run_attack_prompt.sh "$(PASSWORD)" "$(SECRET)"

loop_attack:
	@$(SCRIPTS_DIR)/loop_attack_prompt.sh "$(PASSWORD)" "$(SECRET)" "$(ITERATIONS)"

at:
	@$(SCRIPTS_DIR)/simulate_at.sh "$(PASSWORD)" "$(SECRET)"

clean:
	@echo "$(YELLOW)Removing Modelfile$(RESET)"
	@rm -f Modelfile

fclean: clean
	@echo "$(YELLOW)Removing model 'codename' from ollama list$(RESET)"
	@ollama rm codename > /dev/null 2>&1 || true
	@echo "$(YELLOW)Removing get_secret.prompt$(RESET)"
	@rm -f get_secret.prompt

.PHONY: all re modelfile codename attack loop_attack at clean fclean
