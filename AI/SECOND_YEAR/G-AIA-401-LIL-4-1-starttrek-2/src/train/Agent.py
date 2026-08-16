##
## EPITECH PROJECT, 2026
## G-AIA-401-LIL-4-1-starttrek-2
## File description:
## Agent
##

from collections import namedtuple, deque
import random
import math
import torch.nn as nn
import torch

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
    criterion = nn.HuberLoss()
    loss = criterion(state_action_values, expected_state_action_values.unsqueeze(1))
    optimizer.zero_grad()
    loss.backward()
    torch.nn.utils.clip_grad_value_(policy_net.parameters(), 100)
    optimizer.step()
    return loss