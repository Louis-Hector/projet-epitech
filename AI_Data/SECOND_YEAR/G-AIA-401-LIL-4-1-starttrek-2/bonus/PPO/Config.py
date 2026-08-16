##
## EPITECH PROJECT, 2026
## G-AIA-401-LIL-4-1-starttrek-2
## File description:
## Config
##

import gymnasium as gym
import sys, yaml

def init_hyperameters(config):
    """If we have no config file yaml, we define the hyperparameters with the default values, else
    we recover hyperparameters in the file.
    Args:
        config (dict): dictionnary about yaml
    Returns:
        tab: hyperparameters values
    """
    config = config or {}
    hypers = config.get("hypers", {})
    batch_size = hypers.get("BATCH_SIZE", 128)
    gamma = hypers.get("GAMMA", 0.99)
    eps_start = hypers.get("EPS_START", 1.0)
    eps_end = hypers.get("EPS_END", 0.01)
    eps_decay = hypers.get("EPS_DECAY", 2500)
    tau = hypers.get("TAU", 0.005)
    lr = hypers.get("LR", 3e-4)
    return {"Batch" : batch_size, "Gamma" : gamma, "Eps_start" :  eps_start, "Eps_end" :  eps_end, "Eps_decay" : eps_decay, "Tau" : tau, "Lr" : lr}

def init_env(config):
    """The goal of this function is to init the env change the render_mode in function of what the user
    wants with the yaml or not
    Returns:
        _type_: an environment
    """
    config = config or {}
    parameters = config.get("parameters", {})
    turbulence = parameters.get("TURBULENCE_POWER", 1.5)
    env = config.get("env", {})
    print(parameters)
    return gym.make(env.get("environment", "LunarLander-v3"), render_mode=env.get("render_mode", "rgb_array"), gravity=parameters.get("GRAVITY", -10), enable_wind=parameters.get("ENABLE_WIND", False), wind_power=parameters.get("WIND_POWER", 15.0), turbulence_power=parameters.get("TURBULENCE_POWER", 0.0))
  

def open_yaml():
    """Goal: Check the number of args to recover the info of yaml file
    Returns:
        dict: A dictionnary with info in the yaml
    """
    if (len(sys.argv) > 2):
        print("The number of args is invalid")
        sys.exit(84)
    if (len(sys.argv) == 2):
        try:
            with open(sys.argv[1], "r") as file:
                config = yaml.safe_load(file)
        except (FileNotFoundError, PermissionError):
            print("File not found or permission denied")
            sys.exit(84)
    else:
        config = None
    return config