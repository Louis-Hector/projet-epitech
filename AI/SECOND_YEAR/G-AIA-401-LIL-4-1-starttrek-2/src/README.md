# Start Trek

**Start Trek** is a project from the module ***G4-MachineLearning***. The goal is to train a module to land by itself.

---

## Content

- [Summary](#summary)
- [Installation](#installation)
- [Project structure](#project-structure)
- [Authors](#authors)

---

## Summary

The goal of this project is to implement a reinforcement learning algorithm for Gymansium's LunarLander-v3. Based on the **Epitech** project, you will see various aspects in this readme. From ablation and code evolution to results, let yourself be guided through this excellent presentation of the **Start Trek** project.


## Installation

---

### 1. Git clone the repository on your PC.

```bash
git clone git@github.com:EpitechPGE2-2025/G-AIA-401-LIL-4-1-starttrek-2.git
cd G-AIA-401-LIL-4-1-starttrek-2
```

### 2. Create a Virtual Environment

```bash
python -m venv venv
source venv/bin/activate
```
This can be really useful for avoid conflict on your PC.

### 3. Install the librairies

```bash
python install -r requirements.txt
```

### 4. If you don't have any model in the folder src/train/models:
```bash
python src/train/train.py (config)
```
#### The config is a file .yaml optionnal for the parameters (src/config)


### 5. If you have a model to eval:
```bash
python src/eval/eval.py
```
#### Then you have the result of the model train.

---

## Project structure

---

```bash
.
├── doc
│   ├── ABLATION.md
│   ├── CODE.md
│   ├── DOCUMENTATION.md 
│   ├── images
│   └── notebook
│       └── visualisation.ipynb
├── README.md
├── requirements.txt                #List of Python libraries required to run the project
├── runs
└── src
    ├── config                      # Folder contains the .yaml for config the project
    ├── eval
    │   ├── eval.py
    │   └── logs
    └── train
        ├── Agent.py
        ├── Config.py
        ├── Log.py
        ├── logs
        ├── models
        │   ├── default.pth
        │   ├── earth.pth
        │   └── moon.pth
        └── train.py             
```

---

## Author

- [Paul Ammeloot](https://github.com/PaulAmmeloot)
- [Louis Hector](https://github.com/MinFlag)
- [Logan Capoen](https://github.com/logan-capoen)