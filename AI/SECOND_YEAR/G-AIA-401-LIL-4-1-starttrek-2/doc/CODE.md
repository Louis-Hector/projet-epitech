# Program codes

This file contains all the programs since the beginning of the project, including both progress and setbacks.

---

## Version 1

### Train.py

```py
import gymnasium as gym
env = gym.make("LunarLander-v3", render_mode="human")

# Reset the environment to generate the first observation
observation, info = env.reset(seed=42)
for _ in range(1000):
    # this is where you would insert your policy
    action = env.action_space.sample()

    # step (transition) through the environment with the action
    # receiving the next observation, reward and if the episode has terminated or truncated
    observation, reward, terminated, truncated, info = env.step(action)

    # If the episode has ended then we can reset to start a new episode
    if terminated or truncated:
        observation, info = env.reset()

env.close()
```

### Eval.py

No version for this file .py

---

## Version 2

### Train.py
```py
import gymnasium as gym
import matplotlib.pyplot as plt
import torch
from torchrl.envs import TransformedEnv, Compose, DoubleToFloat, ObservationNorm, StepCounter

#This function allows you to finish the problem that occurred during the episode
def error_launcher(truncated, terminated, reward):
    if terminated == True:
        if reward >= 200:
            return "success"
        else:
            return "crash"
    elif truncated == True:
        return "timeout"
    else:
        return "Ok"
    
#A heuristic function is missing

#This function launches the program as seen in the bootstrap
def launch_programm(env, seed, results):
    for test in range(1):
        observation, info = env.reset(seed=seed + test)
        total_reward = 0
        time_episode = 0
        for _ in range(1000):
            action = env.action_space.sample() # Random policy (He chooses a random action (we must replace it with heuristic)
            next_obs, reward, terminated, truncated, info = env.step(action)
            total_reward += reward
            time_episode += 1
            observation = next_obs
            if terminated or truncated:
                results.append({"Episode": test, "Total_reward": total_reward, "Episode_length": time_episode, "Terminated": terminated, "Truncated": truncated, "Cause": error_launcher(truncated, terminated, total_reward)})
                break
        print(f"Episode test {test} ! Total reward: {total_reward}")

#This will create a log file with the retrieved information
def write_in_file(results):
    with open("log.txt", "w") as f:
        f.writelines("Episode, Total_reward, Total_time, Terminated, Truncated, Cause\n")
        for i in results:
            f.writelines(str(i["Episode"]) + ', ' + str(i["Total_reward"]) + ', ' + str(i["Episode_length"]) + ', ' + str(i["Terminated"]) + ', ' +  str(i["Truncated"]) + ', ' + i["Cause"] + "\n")
  
env = gym.make("LunarLander-v3", render_mode="human")            
results = []
launch_programm(env, 42, results)
write_in_file(results)
env.close()
```

### Eval.py

No version for this file .py

---

## Version 3

### Train.py
```py
import gymnasium as gym
import matplotlib.pyplot as plt
import torch
from torchrl.envs import TransformedEnv, Compose, DoubleToFloat, ObservationNorm, StepCounter
import sys

#This function allows you to finish the problem that occurred during the episode
def error_launcher(truncated, terminated, reward):
    if terminated == True:
        if reward >= 200:
            return "success"
        else:
            return "crash"
    elif truncated == True:
        return "timeout"
    else:
        return "Ok"

def simple_heuristic(observation):
    horizontal, vertical, vit_horizontal, vit_vertical, angle, angle_dot, left_leg_contact, right_leg_contact = observation
    
    if (angle > 0.2):
        return 3
    if (angle < -0.1):
        return 1 
    if (horizontal > 0.2):
        return 1
    if (horizontal < -0.2):
        return 3
    if (vit_vertical < -0.5):
        return 2
    return 0 

#This function launches the program as seen in the bootstrap
def launch_programm(env, seed, results):
    for test in range(10):
        observation, info = env.reset(seed=seed + test)
        total_reward = 0
        time_episode = 0
        for _ in range(1000):
            action = simple_heuristic(observation) # Random policy (He chooses a random action (we must replace it with heuristic)
            next_obs, reward, terminated, truncated, info = env.step(action)
            total_reward += reward
            time_episode += 1
            observation = next_obs
            if terminated or truncated:
                results.append({"Episode": test, "Total_reward": total_reward, "Episode_length": time_episode, "Terminated": terminated, "Truncated": truncated, "Cause": error_launcher(truncated, terminated, total_reward)})
                break
        print(f"Episode test {test} ! Total reward: {total_reward}")

#This will create a log file with the retrieved information
def write_in_file(results):
    with open("log.txt", "w") as f:
        f.writelines("Episode, Total_reward, Total_time, Terminated, Truncated, Cause\n")
        for i in results:
            f.writelines(str(i["Episode"]) + ', ' + str(i["Total_reward"]) + ', ' + str(i["Episode_length"]) + ', ' + str(i["Terminated"]) + ', ' +  str(i["Truncated"]) + ', ' + i["Cause"] + "\n")
  
#We set up our environment and choose the rendering style, such as human or terminal.
def check_args():
    if (len(sys.argv) == 2 and sys.argv[1] == "Machine"):
        return gym.make("LunarLander-v3", render_mode="rgb_array")
    elif (len(sys.argv) == 2 and sys.argv[1] == "Human"):
        return gym.make("LunarLander-v3", render_mode="human")
    else:
        return gym.make("LunarLander-v3", render_mode="human")

env = check_args()
results = []
launch_programm(env, 42, results)
write_in_file(results)
env.close()
```

### Eval.py

No version of this file .py

---

## Version 4

### Train.py
```py
from torch.utils.tensorboard import SummaryWriter
from collections import namedtuple, deque
from itertools import count
import torch
import torch.nn as nn
import torch.optim as optim
import gymnasium as gym
import sys
import random
import math

BATCH_SIZE = 128
GAMMA = 0.99
EPS_START = 0.9
EPS_END = 0.01
EPS_DECAY = 2500
TAU = 0.005
LR = 3e-4
    
class ReplayMemory(object):

    def __init__(self, capacity):
        self.memory = deque([], maxlen=capacity)

    def push(self, *args):
        """Save a transition"""
        self.memory.append(Transition(*args))

    def sample(self, batch_size):
        return random.sample(self.memory, batch_size)

    def __len__(self):
        return len(self.memory)
       
class DQN(nn.Module):
    """DQN, short for Deep Q-Network, is a reinforcement learning (RL) algorithm that combines 
    the classical Q-learning approach with deep neural networks (DNNs).
    Args:
        nn (n_observations, n_actions): the observation shape of the lunar lander and his actions
    """

    def __init__(self, n_observations, n_actions):
        super().__init__()
        self.seq = nn.Sequential(
            nn.Linear(n_observations, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, n_actions)
        )

    def forward(self, x):
        return self.seq(x.float())

steps_done = 0
def select_action(env, policy_net, state):
    """Its objective is to be able to decide on the type of action, therefore exploration or exploitation, for
    the lunar lander thanks to the determination of epsilon
    Args:
        state (Tensor): a matrix tensor with the state of the lunar lander
    Returns:
        _type_: _description_
    """
    global steps_done
    eps_threshold = EPS_END + (EPS_START - EPS_END) * math.exp(-1. * steps_done / EPS_DECAY)
    steps_done += 1
    if random.random() > eps_threshold:
        with torch.no_grad():
            return policy_net(state).max(1).indices.view(1, 1)
    else:
        return torch.tensor([[env.action_space.sample()]], device=device, dtype=torch.long)

def optimize_model(device, policy_net, target_net, optimizer, memory):
    if len(memory) < BATCH_SIZE:
        return
    transitions = memory.sample(BATCH_SIZE)
    batch = Transition(*zip(*transitions))
    non_final_mask = torch.tensor(tuple(map(lambda s: s is not None, batch.next_state)), device=device, dtype=torch.bool)
    non_final_next_states = torch.cat([s for s in batch.next_state if s is not None])
    state_batch = torch.cat(batch.state)
    action_batch = torch.cat(batch.action)
    reward_batch = torch.cat(batch.reward)
    state_action_values = policy_net(state_batch).gather(1, action_batch)
    next_state_values = torch.zeros(BATCH_SIZE, device=device)
    with torch.no_grad():
        next_state_values[non_final_mask] = target_net(non_final_next_states).max(1).values
    expected_state_action_values = (next_state_values * GAMMA) + reward_batch
    criterion = nn.SmoothL1Loss()
    loss = criterion(state_action_values, expected_state_action_values.unsqueeze(1))
    optimizer.zero_grad()
    loss.backward()
    torch.nn.utils.clip_grad_value_(policy_net.parameters(), 100)
    optimizer.step()

def launch_programm_with_agent(env, device, writer, policy_net, target_net, optimizer, memory):
    """The purpose of this function is to launch episodes and 
    call agents so that our lunar lander improves over time.
    Args:
        writer (SummaryWirter()): A file where the output results can be written.
    """
    for episode in range(500):
        observation, _ = env.reset()
        matrix_observation = torch.tensor(observation, dtype=torch.float32, device=device).unsqueeze(0)
        total_reward = 0
        episode_finish = False
        while not episode_finish:
            action = select_action(env, policy_net, matrix_observation)
            next_observation, reward, terminated, truncated, _ = env.step(action.item())
            matrix_reward = torch.tensor([reward], device=device)
            total_reward += reward
            if terminated == True or truncated == True:
                matrix_next_observation = torch.zeros_like(matrix_observation)
            else:
                matrix_next_observation = torch.tensor(next_observation, dtype=torch.float32, device=device).unsqueeze(0)
            memory.push(matrix_observation, action, matrix_next_observation, matrix_reward)
            matrix_observation = matrix_next_observation
            optimize_model(device, policy_net, target_net, optimizer, memory)
            for target_param, policy_param in zip(target_net.parameters(), policy_net.parameters()):
                target_param.data.copy_(TAU * policy_param.data + (1.0 - TAU) * target_param.data)
            if terminated == True or truncated == True:
                writer.add_scalar("Reward", total_reward, episode)
                episode_finish = True
        print(f"Episode {episode}, Reward: {total_reward:.2f} Terminated: {terminated}, Truncated: {truncated}")

def check_args():
    """The goal of this function is to parse args and change the render_mode in function of what the user
    wants
    Returns:
        _type_: an environment
    """
    if (len(sys.argv) == 2 and sys.argv[1] == "Machine"):
        return gym.make("LunarLander-v3", render_mode="rgb_array")
    elif (len(sys.argv) == 2 and sys.argv[1] == "Human"):
        return gym.make("LunarLander-v3", render_mode="human")
    else:
        return gym.make("LunarLander-v3", render_mode="human")

#1. First step define the environment, device for torch
#-------------------------------------------------------------------------------
env = check_args()
device = torch.device("cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else"cpu")
#2. Second, with define the variable
#--------------------------------------------------------------------------------
Transition = namedtuple('Transition', ('state', 'action', 'next_state', 'reward'))
n_observations = env.observation_space.shape[0] 
n_actions = env.action_space.n
policy_net = DQN(n_observations, n_actions).to(device)
target_net = DQN(n_observations, n_actions).to(device) 
target_net.load_state_dict(policy_net.state_dict())
optimizer = optim.AdamW(policy_net.parameters(), lr=LR, amsgrad=True)
memory = ReplayMemory(10000)
#3. third, Set the writer file and launch the main programm
#------------------------
writer = SummaryWriter()
launch_programm_with_agent(env, device, writer, policy_net, target_net, optimizer, memory)
writer.flush()
writer.close()
env.close()
```

### Evaly.py

No version for this file .py

---

## Version 5

### Train.py
```py
from torch.utils.tensorboard import SummaryWriter
# from gymnasium.wrappers import RecordVideo, RecordEpisodeStatistics
from collections import namedtuple, deque
from itertools import count
import torchplot as plt
import torch
import torch.nn as nn
import torch.optim as optim
import gymnasium as gym
import sys
import random
import math
import yaml
    
Transition = namedtuple('Transition', ('state', 'action', 'next_state', 'reward'))
class ReplayMemory(object):

    def __init__(self, capacity):
        self.memory = deque([], maxlen=capacity)

    def push(self, *args):
        """Save a transition"""
        self.memory.append(Transition(*args))

    def sample(self, batch_size):
        return random.sample(self.memory, batch_size)

    def __len__(self):
        return len(self.memory)
       
class DQN(nn.Module):
    """DQN, short for Deep Q-Network, is a reinforcement learning (RL) algorithm that combines 
    the classical Q-learning approach with deep neural networks (DNNs).
    Args:
        nn (n_observations, n_actions): the observation shape of the lunar lander and his actions
    """

    def __init__(self, n_observations, n_actions):
        super().__init__()
        self.seq = nn.Sequential(
            nn.Linear(n_observations, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, n_actions)
        )

    def forward(self, x):
        return self.seq(x.float())

def select_action(env, policy_net, state, device, hyperparameters, steps_done):
    """Its objective is to be able to decide on the type of action, therefore exploration or exploitation, for
    the lunar lander thanks to the determination of epsilon
    Args:
        state (Tensor): a matrix tensor with the state of the lunar lander
    Returns:
        _type_: _description_
    """
    eps_threshold = hyperparameters["Eps_end"] + (hyperparameters["Eps_start"] - hyperparameters["Eps_end"]) * math.exp(-1. * steps_done / hyperparameters["Eps_decay"])
    steps_done += 1
    if random.random() > eps_threshold:
        with torch.no_grad():
            return policy_net(state).max(1).indices.view(1, 1), steps_done
    else:
        return torch.tensor([[env.action_space.sample()]], device=device, dtype=torch.long), steps_done

def optimize_model(device, policy_net, target_net, optimizer, memory, hyperparameters):
    if len(memory) < hyperparameters["Batch"]:
        return
    transitions = memory.sample(hyperparameters["Batch"])
    batch = Transition(*zip(*transitions))
    non_final_mask = torch.tensor(tuple(map(lambda s: s is not None, batch.next_state)), device=device, dtype=torch.bool)
    non_final_next_states = torch.cat([s for s in batch.next_state if s is not None])
    state_batch = torch.cat(batch.state)
    action_batch = torch.cat(batch.action)
    reward_batch = torch.cat(batch.reward)
    state_action_values = policy_net(state_batch).gather(1, action_batch)
    next_state_values = torch.zeros(hyperparameters["Batch"], device=device)
    with torch.no_grad():
        next_state_values[non_final_mask] = target_net(non_final_next_states).max(1).values
    expected_state_action_values = (next_state_values * hyperparameters["Gamma"]) + reward_batch
    criterion = nn.SmoothL1Loss()
    loss = criterion(state_action_values, expected_state_action_values.unsqueeze(1))
    optimizer.zero_grad()
    loss.backward()
    torch.nn.utils.clip_grad_value_(policy_net.parameters(), 100)
    optimizer.step()
    return loss

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

episodes = 600

def launch_programm_with_agent(env, writer, device, policy_net, target_net, optimizer, memory, hyperparameters, seed, steps_done):
    """The purpose of this function is to launch episodes and 
    call agents so that our lunar lander improves over time.
    Args:
        writer (SummaryWirter()): A file where the output results can be written.
    """
    env.reset(seed=seed)
    env.action_space.seed(seed)
    for episode in range(episodes):
        observation, _ = env.reset()
        matrix_observation = torch.tensor(observation, dtype=torch.float32, device=device).unsqueeze(0)
        total_reward = 0
        for t in count():
            action, steps_done = select_action(env, policy_net, matrix_observation, device, hyperparameters, steps_done)
            next_observation, reward, terminated, truncated, _ = env.step(action.item())
            matrix_reward = torch.tensor([reward], device=device)
            total_reward += reward
            if terminated or truncated:
                matrix_next_observation = None
            else:
                matrix_next_observation = torch.tensor(next_observation, dtype=torch.float32, device=device).unsqueeze(0)
            memory.push(matrix_observation, action, matrix_next_observation, matrix_reward)
            matrix_observation = matrix_next_observation
            loss = optimize_model(device, policy_net, target_net, optimizer, memory, hyperparameters)
            for target_param, policy_param in zip(target_net.parameters(), policy_net.parameters()):
                target_param.data.copy_(hyperparameters["Tau"] * policy_param.data + (1.0 - hyperparameters["Tau"]) * target_param.data)
            if terminated == True or truncated == True:
                writer.add_scalar("Reward", total_reward, episode)
                writer.add_scalar("Episode_length", t, episode)
                if loss is not None:
                    writer.add_scalar("Loss", loss.item(), episode)
                #log.append({"Episode" : episode, "Reward" : total_reward, "Episode_length" : t, "Status" :  determinate_status(terminated, truncated, total_reward)})
                break
        print(f"Episode {episode}, Reward: {total_reward:.2f} Terminated: {terminated}, Truncated: {truncated}")
    return steps_done

def write_logs(log):
    """Write some informations in a file for the user
    """
    with open("log.txt", "w") as f:
        f.writelines("Episode, Total_reward, Total_time, Terminated, Truncated, Cause\n")
        for i in log:
            f.writelines(str(i["Episode"]) + ', ' + str(i["Reward"]) + ', ' + str(i["Episode_length"]) + ', ' + i["Status"] + "\n")

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
    eps_start = hypers.get("EPS_START", 0.9)
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
    if (config is not None):
        return gym.make(config["env"]["environment"], render_mode=config["env"]["render_mode"])
    else:
        return gym.make("LunarLander-v3", render_mode="rgb_array")

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
  
def start_train():
    """The goal of his function is to start the project and launch the agent
    """
    config = open_yaml()
    hyperparameters = init_hyperameters(config)
    device = torch.device("cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else"cpu")
    #log = []
    if config is None or config["seed"] is None or config["seed"]["number"] is None:
        seeds = [0, 1, 2, 3, 4]
    else:
        seeds = config["seed"]["number"]
    for s in seeds:
        random.seed(s)
        torch.manual_seed(s)
        env = init_env(config)
        n_observations = env.observation_space.shape[0] 
        n_actions = env.action_space.n
        policy_net = DQN(n_observations, n_actions).to(device)
        target_net = DQN(n_observations, n_actions).to(device) 
        target_net.load_state_dict(policy_net.state_dict())
        optimizer = optim.AdamW(policy_net.parameters(), lr=hyperparameters["Lr"], amsgrad=True)
        memory = ReplayMemory(30000)
        writer = SummaryWriter(log_dir=f"runs/seed:{s}")
        steps_done = 0
        steps_done = launch_programm_with_agent(env, writer, device, policy_net, target_net, optimizer, memory, hyperparameters, s, steps_done)
        model = {'episodes': episodes, 'model_state_dict': policy_net.state_dict(), 'optimizer_state_dict': optimizer.state_dict(), 'steps_done': steps_done, 'hyperparameters': hyperparameters}
        torch.save(model, f"train/models/lunar_dqn_seed:{s}.pth")
        writer.flush()
        writer.close()
        #write_logs(log) Remplace le fonctionnement par celui de Paul
        env.close()

if __name__ == "__main__":
    start_train()
```

### Eval.py
```py
import torch
import gymnasium as gym
import numpy as np
from test import DQN 

def evaluate():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    env = gym.make("LunarLander-v3", render_mode="rgb-array")
    n_observations = env.observation_space.shape[0]
    n_actions = env.action_space.n
    policy_net = DQN(n_observations, n_actions).to(device)
    checkpoint = torch.load("train/models/model.pth", map_location=device)
    policy_net.load_state_dict(checkpoint['model_state_dict'])
    policy_net.eval()
    all_rewards = []
    for episode in range(100):
        observation, _ = env.reset()
        terminated = False
        truncated = False
        total_reward = 0
        while not (terminated or truncated):
            state = torch.tensor(observation, dtype=torch.float32, device=device).unsqueeze(0)
            with torch.no_grad():
                action = policy_net(state).max(1).indices.view(1, 1)
            observation, reward, terminated, truncated, _ = env.step(action.item())
            total_reward += reward
        all_rewards.append(total_reward)  
        print(f"Épisode ", episode, "  | Score: ", total_reward)
    mean_reward = np.mean(all_rewards)
    std_reward = np.std(all_rewards)
    print("-" * 30)
    print(f"ÉVALUATION TERMINÉE SUR", episode + 1 ," ÉPISODES")
    print(f"Moyenne des récompenses : {mean_reward:.2f}")
    print(f"Écart-type (stabilité) : {std_reward:.2f}")
    print(f"Meilleur score : {np.max(all_rewards):.2f}")
    print(f"Pire score : {np.min(all_rewards):.2f}")
    print("-" * 30)
    env.close()

if __name__ == "__main__":
    evaluate()
```

---

## Version 6

### Train.py
```py
from Config import open_yaml, init_env, init_hyperameters, gym, sys
from Agent import select_action, optimize_model, DQN, ReplayMemory, torch, random
from Log import create_log_file, write_logs, determinate_status, Path
from gymnasium.wrappers import RecordVideo, RecordEpisodeStatistics
from torch.utils.tensorboard import SummaryWriter
from itertools import count
import torch.optim as optim    
    
def launch_programm_with_agent(env, writer, device, policy_net, target_net, optimizer, memory, hyperparameters, log, seed, steps_done, episode_nb):
    """The purpose of this function is to launch episodes and 
    call agents so that our lunar lander improves over time.
    Args:
        writer (SummaryWirter()): A file where the output results can be written.
    """
    env.reset(seed=seed)
    env.action_space.seed(seed)
    for episode in range(episode_nb):
        observation, _ = env.reset()
        matrix_observation = torch.tensor(observation, dtype=torch.float32, device=device).unsqueeze(0)
        total_reward = 0
        for t in count():
            action, steps_done = select_action(env, policy_net, matrix_observation, device, hyperparameters, steps_done)
            next_observation, reward, terminated, truncated, _ = env.step(action.item())
            reward = max(-1.0, min(1.0, reward))
            matrix_reward = torch.tensor([reward], device=device)
            total_reward += reward
            if terminated or truncated:
                matrix_next_observation = None
            else:
                matrix_next_observation = torch.tensor(next_observation, dtype=torch.float32, device=device).unsqueeze(0)
            memory.push(matrix_observation, action, matrix_next_observation, matrix_reward)
            matrix_observation = matrix_next_observation
            loss = optimize_model(device, policy_net, target_net, optimizer, memory, hyperparameters)
            for target_param, policy_param in zip(target_net.parameters(), policy_net.parameters()):
                target_param.data.copy_(hyperparameters["Tau"] * policy_param.data + (1.0 - hyperparameters["Tau"]) * target_param.data)
            if terminated == True or truncated == True:
                writer.add_scalar("Reward", total_reward, episode)
                writer.add_scalar("Episode_length", t, episode)
                if loss is not None:
                    writer.add_scalar("Loss", loss.item(), episode)
                log.append({"Episode" : episode, "Reward" : total_reward, "Episode_length" : t, "Status" :  determinate_status(terminated, truncated, total_reward)})
                break
        print(f"Episode {episode}, Reward: {total_reward:.2f} Terminated: {terminated}, Truncated: {truncated}")
    return steps_done

episode_nb = 600
def start_train():
    """The goal of his function is to start the project and launch the agent
    """
    config = open_yaml()
    hyperparameters = init_hyperameters(config)
    device = torch.device("cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else"cpu")
    if config is None or config["seed"] is None or config["seed"]["number"] is None:
        seeds = [0, 1, 2, 3, 4]
    else:
        seeds = config["seed"]["number"]

    if config is None:
        name = "default"
    else:
        name = Path(sys.argv[1]).stem
    for s in seeds:
        print(f"round {s}")
        random.seed(s)
        torch.manual_seed(s)
        env = init_env(config)
        #env = RecordVideo(env, video_folder="doc/video", name_prefix="training", episode_trigger=lambda x: x % 25 == 0)
        log_file = create_log_file(episode_nb)
        log = []
        n_observations = env.observation_space.shape[0] 
        n_actions = env.action_space.n
        policy_net = DQN(n_observations, n_actions).to(device)
        target_net = DQN(n_observations, n_actions).to(device) 
        target_net.load_state_dict(policy_net.state_dict())
        optimizer = optim.AdamW(policy_net.parameters(), lr=hyperparameters["Lr"], amsgrad=True)
        memory = ReplayMemory(30000)
        writer = SummaryWriter(log_dir=f"runs/seed:{s}")
        steps_done = 0
        steps_done = launch_programm_with_agent(env, writer, device, policy_net, target_net, optimizer, memory, hyperparameters, log, s, steps_done, episode_nb)
        config = config or {}
        model = {'episodes': episode_nb, 'model_state_dict': policy_net.state_dict(), 'optimizer_state_dict': optimizer.state_dict(), 'steps_done': steps_done, 'hyperparameters': hyperparameters, 'parameters': config.get("parameters", {}), 'env': config.get("env", {}), "name": name}
        torch.save(model, "src/train/models/" + name + ".pth")
        write_logs(log, log_file, config, hyperparameters)
        writer.flush()
        writer.close()
        env.close()

if __name__ == "__main__":
    start_train()
```

### Eval.py
```py
import torch
import gymnasium as gym
import numpy as np
from train.Agent import DQN 
from pathlib import Path
from datetime import datetime
import sys

def save_evaluation_log(model_path, checkpoint, stats, episode_rewards):
    """Handles the clean writing of results into a text file."""
    log_dir = Path("eval/logs")
    log_dir.mkdir(parents=True, exist_ok=True)
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    model_name = checkpoint.get('name', model_path.stem)
    log_filename = log_dir / f"eval_{model_path.stem}_{timestamp}.log"
    
    params = checkpoint.get('parameters', {})    
    with open(log_filename, "w", encoding="utf-8") as f:
        f.write(f"EVALUATION REPORT: {model_name}\n")
        f.write("="*60 + "\n")
        f.write(f"Date : {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write(f"Model File : {model_path.name}\n")
        f.write(f"Environment : {checkpoint['env'].get('environment', 'N/A')}\n")
        f.write("Env Configuration   :\n")
        for key, value in params.items():
            f.write(f"  - {key}: {value}\n")
        f.write("-" * 60 + "\n")
        f.write(f"Number of Episodes : {len(episode_rewards)}\n")
        f.write(f"MEAN SCORE : {stats['mean']:.2f}\n")
        f.write(f"Std Deviation : {stats['std']:.2f}\n")
        f.write(f"Best / Worst : {stats['max']:.2f} / {stats['min']:.2f}\n")
        f.write("-" * 60 + "\n\n")
        f.write("EPISODE DETAILS:\n")
        for i, score in enumerate(episode_rewards):
            f.write(f"Ep {i+1:03d}: {score:7.2f} | ")
            f.write("\n")
    return log_filename

def evaluate(path):
    path = Path(path)
    if not path.exists() and path.suffix != ".pth":
        print(f"Error: File {path} not found.")
        return

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    checkpoint = torch.load(path, map_location=device)
    
    params = checkpoint.get('parameters', {})
    env = gym.make(checkpoint['env'].get("environment", "LunarLander-v3"), render_mode="rgb_array", gravity=params.get("GRAVITY", -10), enable_wind=params.get("ENABLE_WIND", False), wind_power=params.get("WIND_POWER", 15.0), turbulence_power=params.get("TURBULENCE_POWER", 0.0))
    n_observations = env.observation_space.shape[0]
    n_actions = env.action_space.n
    policy_net = DQN(n_observations, n_actions).to(device)
    policy_net.load_state_dict(checkpoint['model_state_dict'])
    policy_net.eval()
    all_rewards = []
    print(f"\n--- Evaluating: {path.name} ---")
    
    for episode in range(100):
        observation, _ = env.reset()
        terminated = truncated = False
        total_reward = 0
        
        while not (terminated or truncated):
            state = torch.tensor(observation, dtype=torch.float32, device=device).unsqueeze(0)
            with torch.no_grad():
                action = policy_net(state).max(1).indices.view(1, 1)
            observation, reward, terminated, truncated, _ = env.step(action.item())
            total_reward += reward
        
        all_rewards.append(total_reward)  
        print(f"Episode {episode + 1}/100 | Last Score: {total_reward:.2f}")

    stats = {"mean": np.mean(all_rewards), "std": np.std(all_rewards), "max": np.max(all_rewards), "min": np.min(all_rewards)}
    log_path = save_evaluation_log(path, checkpoint, stats, all_rewards)
    print(f"Finished. Mean Score: {stats['mean']:.2f}. Log: {log_path}")
    env.close()

def run_evaluation():
    # Check if user provided paths in the terminal
    args = sys.argv[1:]

    if args:
        for model_path in args:
            evaluate(model_path)
    else:
        model_dir = Path("train/models")
        if not model_dir.exists():
            print(f"Default directory {model_dir} does not exist.")
            return
        for file in model_dir.glob("*.pth"):
            evaluate(file)

if __name__ == "__main__":
    run_evaluation()
```

## Version 7

### Train.py

### Eval.py

---