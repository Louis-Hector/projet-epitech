##
## EPITECH PROJECT, 2026
## G-AIA-401-LIL-4-1-starttrek-2
## File description:
## Agent
##

import torch.nn as nn
from torch.distributions import Categorical

class PPO(nn.Module):

    def __init__(self, n_observations, n_actions):
        super().__init__()
        self.actor = nn.Sequential(
            nn.Linear(n_observations, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, n_actions)
        )
        self.critic = nn.Sequential(
            nn.Linear(n_observations, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, 1)
        )
    def forward(self, x):
        action_logits = self.actor(x.float())
        state_value = self.critic(x.float())
        return action_logits, state_value

    def select_action(self, state):
        actor_value, critic_value = self.forward(state)
        prob = Categorical(logits=actor_value)
        action = prob.sample()
        log = prob.log_prob(action)
        return action.item(), log, critic_value