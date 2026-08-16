##
## EPITECH PROJECT, 2026
## G-AIA-401-LIL-4-1-starttrek-2
## File description:
## Log
##

from datetime import datetime
from pathlib import Path

def determinate_status(terminated, truncated, total_reward):
    """The goal of this function is to check the terminated and truncated observations
    to determinate the status of the lunar lander.

    Args:
        terminated (bool): True or False
        truncated (bool): True or False 
        total_reward (float): the value for determinate the status

    Returns:
        string: determinate status
    """
    if (terminated == True):
        if (total_reward >= 200):
            return "Terminated: Landed"
        elif (total_reward <= -300):
            return "Terminated: Out of view"
        else:
            return "Terminated: Crash"
    elif (truncated == True):
        return "Truncated: Sleep"
    else:
        return "Ok"
    
def create_log_file(episode_nb):
    """
    Create a unique log file name based on current datetime.
    """

    logs_dir = Path("src/train/logs")
    logs_dir.mkdir(exist_ok=True)

    date_str = datetime.now().strftime("%Y-%m-%d_%Hh%Mm%Ss")
    filename = f"run_{episode_nb}_{date_str}.csv"

    return logs_dir / filename

def write_logs(log, log_file, config, hyperparameters):
    """
    Write episode logs into a CSV file.
    One file is created for each program execution.
    """

    with open(log_file, "w") as f:
        f.write("# Run configuration\n")

        if config is not None:
            f.write(f"# Environment,{config.get('env', {}).get('environment', 'unknown_env')}\n")
            f.write(f"# Render mode,{config.get('env', {}).get('render_mode', 'unknown_render_mode')}\n")
        else:
            f.write("# Environment,LunarLander-v3\n")
            f.write("# Render mode,rgb_array\n")

        for key, value in hyperparameters.items():
            f.write(f"# {key},{value}\n")

        f.write("\n")
        f.write("Episode,Reward,Episode_length,Status\n")

        for i in log:
            f.write(f"{i['Episode']},"f"{i['Reward']},"f"{i['Episode_length']},"f"{i['Status']}\n")
