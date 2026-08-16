import subprocess
import sys
from pathlib import Path

def run(script):
    print(f"\n'{script}' running\n")
    result = subprocess.run(script, shell=True)
    if result.returncode != 0:
        print(f"'{script}' fail")
        sys.exit(result.returncode)

def step_train(config_file, nb_episode):
    run(f"python src/train/train.py {config_file} {nb_episode}")

def step_eval():
    run("python -m src.eval.eval")

def launch_all(config_file, nb_episode):
    step_train(config_file, nb_episode)
    step_eval()
    print("\neverything good, go \"run all\" in visualisation.ipynb in doc/notebook/\n")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python makefile.py <config.yaml> <nb_episode>")
        sys.exit(1)
    config_file = sys.argv[1]
    nb_episode = sys.argv[2]
    launch_all(config_file, nb_episode)