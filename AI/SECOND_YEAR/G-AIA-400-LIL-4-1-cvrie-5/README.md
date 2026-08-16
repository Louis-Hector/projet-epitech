# CVRIE

**CVRIE** is a project from the module ***G4-MachineLearning***. The goal is to build, developp and test a two-part machine learning assistant.

---

## Content

- [Summary](#summary)
- [Installation](#installation)
- [Project structure](#project-structure)
- [Authors](#authors)

---

## Summary

### This repository is in two parts so:

- **Supervised learning section** (supervised_learning.ipynb):
=> Choose a medical imaging dataset, assess its quality, and train a model to predict outcomes for new images.

This section focuses on building a supervised learning model to predict Alzheimer’s disease from medical images. The goal is to preprocess the dataset, train models, and evaluate their performance to select the best predictor.

- Dataset:

Disease: Alzheimer’s
Type: Medical imaging (brain scans)
Description: The dataset contains labeled images of patients with and without Alzheimer’s disease.
Purpose: Predict the presence or stage of Alzheimer’s disease in new patients.

- **Unsupervised learning section** (unsupervised_learning.ipynb):
=> Work with a dataset of patient testimonies and use unsupervised learning to cluster them by pathology.

## Installation

---

### 1. Git clone the repository on your PC.

```bash
git clone git@github.com:EpitechPGE2-2025/G-AIA-400-LIL-4-1-cvrie-5.git
cd G-AIA-400-LIL-4-1-cvrie-5
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

### 4. Launch a Jupyter notebook

You can now go in a Jupyter notebook and clickon the button **Run all**
![alt text](<Screenshot/run_all.png>)

---

## Project structure

---

```bash
.
├── supervised_learning.ipynb        #Jupyter notebook for supervised learning
├── unsupervised_learning.ipynb      #Jupyter notebook for unsupervised learning
├── requirements.txt                 #List of Python libraries required to run the project
└── README.md                        #This file
```

---

## Author

- [Paul Ammeloot](https://github.com/PaulAmmeloot)
- [Louis Hector](https://github.com/MinFlag)