##
## EPITECH PROJECT, 2026
## G-AIA-401-LIL-4-1-starttrek-2
## File description:
## eval
##

import torch
import gymnasium as gym
import numpy as np
from src.train.Agent import DQN
from pathlib import Path
from datetime import datetime
import sys

def determinate_status(terminated, truncated, total_reward):
    if terminated:
        if total_reward >= 200:
            return "Terminated: Landed"
        elif total_reward <= -300:
            return "Terminated: Out of view"
        else:
            return "Terminated: Crash"
    elif truncated:
        return "Truncated: Sleep"
    return "Ok"

def create_log_file(model_name):
    logs_dir = Path("src/eval/logs")
    logs_dir.mkdir(parents=True, exist_ok=True)

    date_str = datetime.now().strftime("%Y-%m-%d_%Hh%Mm%Ss")
    filename = f"run_{model_name}_eval_{date_str}.csv"

    return logs_dir / filename

def write_logs(log, log_file, config, hyperparameters):
    with open(log_file, "w") as f:
        f.write("# Run configuration\n")

        if config is not None:
            f.write(f"# Environment,{config.get('env', {}).get('environment', 'unknown_env')}\n")
            f.write(f"# Render mode,rgb_array\n")
        else:
            f.write("# Environment,LunarLander-v3\n")
            f.write("# Render mode,rgb_array\n")

        for key, value in hyperparameters.items():
            f.write(f"# {key},{value}\n")

        f.write("\n")
        f.write("Episode,Reward,Episode_length,Status\n")

        for entry in log:
            f.write(f"{entry['Episode']},{entry['Reward']},{entry['Episode_length']},{entry['Status']}\n")

def evaluate(path):
    path = Path(path)
    if not path.exists() or path.suffix != ".pth":
        print(f"Error: File {path} not found.")
        return

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    checkpoint = torch.load(path, map_location=device)
    params = checkpoint.get("parameters", {})
    env_name = checkpoint["env"].get("environment", "LunarLander-v3")
    env = gym.make(env_name, render_mode="rgb_array", gravity=params.get("GRAVITY", -10), enable_wind=params.get("ENABLE_WIND", False), wind_power=params.get("WIND_POWER", 15.0), turbulence_power=params.get("TURBULENCE_POWER", 0.0))
    n_obs = env.observation_space.shape[0]
    n_actions = env.action_space.n
    policy_net = DQN(n_obs, n_actions).to(device)
    policy_net.load_state_dict(checkpoint["model_state_dict"])
    policy_net.eval()
    log_entries = []
    for episode in range(100):
        observation, _ = env.reset()
        terminated = truncated = False
        total_reward = 0
        steps = 0
        while not (terminated or truncated):
            state = torch.tensor(observation, dtype=torch.float32, device=device).unsqueeze(0)
            with torch.no_grad():
                action = policy_net(state).max(1).indices.view(1, 1)
            observation, reward, terminated, truncated, _ = env.step(action.item())
            total_reward += reward
            steps += 1
        status = determinate_status(terminated, truncated, total_reward)
        log_entries.append({"Episode": episode, "Reward": total_reward, "Episode_length": steps, "Status": status})
        print(f"Episode {episode+1}/100 | Reward: {total_reward:.2f} | Steps: {steps} | {status}")
    log_file = create_log_file(path.stem)
    write_logs(log_entries, log_file, checkpoint, params)
    print(f"Finished. Log saved to: {log_file}")
    env.close()

def run_evaluation():
    args = sys.argv[1:]
    if args:
        for model_path in args:
            evaluate(model_path)
    else:
        model_dir = Path("src/train/models")
        if not model_dir.exists():
            print(f"Default directory {model_dir} does not exist.")
            return
        for file in model_dir.glob("*.pth"):
            evaluate(file)

if __name__ == "__main__":
    run_evaluation()