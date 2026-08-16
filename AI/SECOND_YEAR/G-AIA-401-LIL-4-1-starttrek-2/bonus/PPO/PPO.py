##
## EPITECH PROJECT, 2026
## PPO Training
##

from stable_baselines3 import PPO
from stable_baselines3.common.callbacks import (EvalCallback, CheckpointCallback, CallbackList)
from Config import open_yaml, init_env, sys
from Log import Path
import torch
import random

episode_nb = 600
def start_train():
    config = open_yaml()
    if config is None or config["seed"] is None or config["seed"]["number"] is None:
        seeds = [0, 1, 2, 3, 4]
    else:
        seeds = config["seed"]["number"]
    if config is None:
        name = "default"
    else:
        name = Path(sys.argv[1]).stem
    for seed in seeds:
        random.seed(seed)
        torch.manual_seed(seed)
        env = init_env(config)
        env.reset(seed=seed)
        env.action_space.seed(seed)
        eval_env = init_env(config)
        eval_env.reset(seed=seed + 100)
        model = PPO("MlpPolicy", env, verbose=1, tensorboard_log=f"runs/seed_{seed}", learning_rate=1e-4, n_steps=2048, batch_size=128, gamma=0.99, gae_lambda=0.97, n_epochs=10, ent_coef=0.015, clip_range=0.1, policy_kwargs=dict(net_arch=[256, 256, 256]), seed=seed, device="auto")
        total_training = 5_000_000
        eval_callback = EvalCallback(eval_env, best_model_save_path=f"best_models/seed_{seed}", log_path=f"runs/seed_{seed}", eval_freq=100_000, n_eval_episodes=10, deterministic=True, render=False, verbose=1)
        checkpoint_callback = CheckpointCallback(save_freq=100_000, save_path=f"checkpoints/seed_{seed}", name_prefix="ppo_agent", verbose=1)
        callback_list = CallbackList([eval_callback, checkpoint_callback])
        episode_nb = 600
        average_episode_length = 500
        total_training = episode_nb * average_episode_length
        model.learn(total_timesteps=total_training, callback=callback_list,progress_bar=True)
        model.save(f"models/{name}_seed_{seed}")
        env.close()
        eval_env.close()

if __name__ == "__main__":
    start_train()