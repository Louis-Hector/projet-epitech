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
            matrix_reward = torch.tensor([reward], dtype=torch.float32, device=device)
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

def start_train(config_file, episode_nb = 600):
    """The goal of his function is to start the project and launch the agent
    """
    config = open_yaml(config_file)
    hyperparameters = init_hyperameters(config)
    device = torch.device("cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else"cpu")
    if config is None or config["seed"] is None or config["seed"]["number"] is None:
        seeds = [0, 1, 2, 3, 4]
    else:
        seeds = config["seed"]["number"]
    name = Path(config_file).stem
    for s in seeds:
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
    config_file = sys.argv[1]
    episode_nb = int(sys.argv[2])
    start_train(config_file, episode_nb)
