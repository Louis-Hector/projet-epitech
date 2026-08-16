# Conclusion report

This file is the conclusion about the project Start trek, don't hesitate to check the file CODE.md or maybe the Ablation.md before read this part.
---

## **Setup**

The project is based on the ***LunarLander-v3*** environment, whose parameters can be fully customized using YAML configuration files. This allows for modifications to elements such as gravity, wind, and the characteristics of the different simulated planets. Hyperparameters are also configurable to test numerous training variants. Finally, the use of different seeds ensures greater experimental diversity and avoids always working with the same initial conditions.

The project is structured around two main files:

- **train.py**, which contains the algorithm for training the model from the defined configurations, as well as the generation of results and logs (CSV, TensorBoard, etc.)

- **eval.py** , used to evaluate the final performance of the model after training.

Regarding the choice of algorithm, we initially studied several approaches adapted to LunarLander-v3, based in particular on:

- https://pub.towardsai.net/apollo-dqn-building-an-rl-agent-for-lunarlander-v3-5040090a7442
- https://docs.pytorch.org/tutorials/intermediate/reinforcement_q_learning.html

We then conducted our own experiments to compare several methods, including standard DQN, Double DQN, and PPO. Detailed results of these experiments are available in ABLATION.md. These tests allowed us to confirm that single DQN was the most suitable approach for our project.

---
## **Results** 

We are very pleased with the results obtained on this project. Indeed, the mathematical validation of the results using the notebook, as well as the evolution of our video-based training model, confirms the robustness of our approach.

The execution of the eval.py script also supports these conclusions, with an average score reaching 285, one of the best scores achieved.

Thanks to the analyses performed with TensorBoard, we can also confirm the good reproducibility of the experiments: the different seeds converge towards the expected performance with consistent stability of the results.

At the end of the project, we thus have two functional implementations as well as a high-performing model, effectively meeting the set objectives. This approach also brings a more scientific and rigorous dimension to the project's development.

---

## **≥1 Ablation** 

Regarding the ablation study, we were able to leverage the Ablation.md file, which was particularly well-structured and customized. This file compiles a large number of experiments conducted to analyze the impact of various hyperparameters on the model's performance.

### ABLATION.md

All of these tests are also viewable via TensorBoard, where each experiment is identified by an explicit seed name and the associated test objective. For example, the experiment seed:10:EPS_decay_2500 aimed to evaluate the influence of the EPS_decay parameter set to 2500 on the agent's behavior during training.

---

## **Limits**

It is therefore important to note that our project has encountered many limitations over time.

- Secondly, during the testing phases, we observed a progressive drop in model performance after a certain number of episodes. After several analyses and investigations, we concluded that this phenomenon was likely linked to catastrophic forgetting, leading to performance degradation and a partial loss of the knowledge acquired by the model. This issue highlights the current limitations of the training methods used for reinforcement models.

- Finally, the ablation study also represents a major limitation of the project. Although several experiments were conducted, we did not have sufficiently powerful hardware resources to exhaustively test all possible hyperparameter combinations. This type of analysis requires particularly significant computation time, especially for training and evaluating multiple models in various configurations. This therefore constitutes a relevant area for improvement in future work, particularly through the use of more powerful computing infrastructures or automated hyperparameter optimization methods.

---

## **Next steps**

One of the next steps would be to push our model further. So far, we have focused on optimizing its performance in terms of speed and efficiency. It would be interesting to go further by evaluating its behavior over a much larger number of episodes, for example, 10,000, in order to observe its long-term evolution and verify its ability to maintain good performance over time.

Furthermore, several other avenues for improvement could be explored. We could, for example, test other neural network architectures or compare more reinforcement learning algorithms to identify the one best suited to the problem under study. Exploring new exploration/exploitation strategies, as well as a more in-depth study of hyperparameter sensitivity, could also improve the results.

---

## FINAL:

In conclusion, we particularly enjoyed this Start Trek project dedicated to the discovery of reinforcement learning. It allowed us to explore various algorithms such as DQN, Double DQN, and PPO, and to better understand their operating principles.

This work also highlighted the autonomous learning of an agent, which evolves progressively over time through interaction with its environment. Furthermore, the customization of hyperparameters allowed us to delve deeper into their role, their usefulness, and their impact on model performance.

Throughout the project, we progressed gradually, documenting our discoveries and results to track the evolution of our thinking and complete the experimental approach. However, some avenues for improvement remain to be explored to further develop the study.

Thank you for reading, and please do not hesitate to contact us with any questions.

Louis Hector
Paul Ammeloot
Logan Capoen