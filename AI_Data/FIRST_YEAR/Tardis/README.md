# 🚆 TARDIS

**TARDIS** is a project from the *Introduction to Data Analysis*. The goal is to develop a system to predict train delays and improve the passenger experience. Using data analysis and predictive modeling, this project offers an interactive and visual solution for understanding and anticipating delays.

---

## Table of Contents

- [Project Structure](#project-structure)
- [Objectives](#objectives)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [Usage](#usage)
- [Technologies](#technologies)
- [Authors](#authors)

---

## Project Structure

```bash
.
├── tardis_eda.ipynb        #Jupyter notebook for data cleaning and analysis
├── tardis_model.ipynb      #Jupyter notebook for modeling and machine learning
├── tardis_dashboard.py     #Streamlit dashboard app for data visualization
├── predictions.csv         #2026 predition generated with our model
├── stations_sncf           #contains true details about each station
├── requirements.txt        #List of Python libraries required to run the project
└── README.md               #This file
```

---

## Objectives

- Clean and preprocess raw SNCF train delay data.

- Perform exploratory data analysis to understand delay patterns.

- Train a predictive model to estimate future delays based on historical patterns.

- Develop an interactive dashboard using Streamlit to present findings and allow real-time prediction.

- Delay distribution visualization (histograms, boxplots ...)

- Clean output data file: cleaned_dataset.csv

---

## Installation
### 1. Clone the Repository

```bash
git clone git@github.com:EpitechPGEPromo2029/G-AIA-210-LIL-2-1-tardis-louis.hector.git tardis
cd tardis
```

### 2. Create a Virtual Environment (optional but recommended)

```bash
python -m venv venv
source venv/bin/activate
```

### 3. Install Dependencies

```bash
pip install -r requirements.txt
```

---

## Usage
### Step 1: Clean & Explore the Data

Launch the notebook and run step-by-step:

You should have a file called dataset.csv that contains these columns:

`Date`;`Service`;`Departure station`;`Arrival station`;`Average journey time`;`Number of scheduled trains`;`Number of cancelled trains`;`Cancellation comments`;`Number of trains delayed at departure`;`Average delay of late trains at departure`;`Average delay of all trains at departure`;`Departure delay comments`;`Number of trains delayed at arrival`;`Average delay of late trains at arrival`;`Average delay of all trains at arrival`;`Arrival delay comments`;`Number of trains delayed > 15min`;`Average delay of trains > 15min (if competing with flights)`;`Number of trains delayed > 30min`;`Number of trains delayed > 60min`;`Pct delay due to external causes`;`Pct delay due to infrastructure`;`Pct delay due to traffic management`;`Pct delay due to rolling stock`;`Pct delay due to station management and equipment reuse`;`Pct delay due to passenger handling (crowding, disabled persons, connections)`

jupyter notebook `tardis_eda.ipynb`

- Input: `dataset.csv`

- Output: `cleaned_dataset.csv`

### Step 2: Train the Prediction Model

jupyter notebook `tardis_model.ipynb`

- Outputs: MAE, R², graphic about the accuracy of model.

### Step 3: Launch the Dashboard

```bash
streamlit run tardis_dashboard.py
```

View visualizations, interact with delay filters, and get predictions.

---

## Bonus

If you want to use another dataset.csv that the one provided by deflaut you can do by using the contents of the bonus file to generate a new prediction.csv file specific to this new dataset (the process can take a long time ~30 min or more if your machine is slow).
During step 2, instead of running tardis_model.ipynb, you must run bonus.ipynb in the bonus directory and move the new prediction.csv file to the root of the project to replace the old one.

---

## Technologies

### Language: Python

### Libraries:

- `pandas`, `numpy`, `matplotlib`, `seaborn` – data handling & visualization

- `scikit-learn` – ML models & evaluation (RandomForestRegressor)

- `streamlit` – dashboard interface

Formatting: ruff for code linting & styling

## Authors

- [Paul Ammeloot](https://github.com/PaulAmmeloot)
- [Louis Hector](https://github.com/MinFlag)
- [Silas Defossez](https://github.com/Silasdef)
