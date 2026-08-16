# Project Progress

This file contains the progress of our project over time.

---

## 13/04/2026

**Code**: [CODE_v1](CODE.md#version-1)

**Explanation**:

On April 13th, we explored the topic of START TREK with the bootstrap framework. This led to the creation of the first version of the code. It comes directly from the gymnasium documentation but is very useful for understanding the fundamentals of our future code.

In addition, we also added a :
- requirement.txt
- README.md
To make things easier for new users

**Result**:

The code is functional and allows us to see how the LunarLander from gymansium works.

---

## 22/04/2026

**Code**: [CODE_v2](CODE.md#version-2)

**Explanation**:

We decided to focus on task 1 of the project, which was to thoroughly understand the Baseline & Instrumentation requirements. This led to the implementation of the Random policy, log return, and why it ended (crash/out-of-view/sleep).
However, video recording and the heuristic function are still missing.

**Result**:

A functional code that stores information in a log.txt file and provides additional information about the episodes.

---

## 23/04/2026

**Code**: [CODE_v3](CODE.md#version-3)

**Explanation**:

The task with the heuristic function is complete, and the first results are in. The video is still missing, the implementation of a DQN agent for task 2 will begin. We can also note the distinction between machine and human mode for the render mode

**Result**:

A working code that tests with a simple heuristic function

---

## 24/04/2026


**Code**: [CODE_v4](CODE.md#version-4)

**Explanation**:

We decided to focus on task 2 of the project, which is the implementation of an MLP agent. We therefore chose the DQN, an agent that relies on QLearning with a neural network. To do this, we used the PyTorch documentation and information searches.
The implementation of the epsilon, the log, and the chosen model
Furthermore, the use of a writer to store data in a tensorboard

**Result**:

A functional code, with an agent that learns over time, while saving reward data

---

## 26/04/2026 - 28/04/2026

**Code**: [CODE_v5](CODE.md#version-5)

**Explanation**:

We added the ability to manually create a log.txt file with information such as the episode's duration and the cause/result of its termination.

In addition, we added YAML file management to facilitate the use and experimentation of the ablation in task 3. This implies argument handling; if we run it by default, we are in human mode.

The implementation of seeds to verify that our model is not due to chance and the personalization of parameters for removal.

**Result**:

Two functional codes, train and eval, for ongoing optimization.

## 06/05/2026

**Code**: [CODE_v6](CODE.md#version-6)

**Explanation**:

We decided to make the code even cleaner by splitting it into files and also adding more advanced log management (notebook and evaluation logs).
The evaluation file is progressing very well and is practically finished.
One last interesting fact is the implementation of video recordings to document the project during the train journey.

**Result**:

Both codes are practically finished, optimized, and clean.

## 07/05/2026
