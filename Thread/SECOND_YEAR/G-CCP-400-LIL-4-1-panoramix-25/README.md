# Panoramix

**Panoramix** is a project from the module ***G4 - Concurrent Programming***. Panoramix is a project 
to study examples of threads and mutex programming and the algorithmic difficulties that go with it.

---

## Content

- [Summary](#summary)
- [Usage](#installation)
- [Project structure](#project-structure)
- [Authors](#authors)

---

## Summary

Each villager is identified by an id (a number unique to the villager). It will fight nb_fights time beforeeaving the battlefield. Before each fight, it must take a serving of magical potion from the pot (if the pot is empty, it must inform the druid and wait until the pot is refilled).

The druid will wait to be called by a villager; then it will refill the pot with pot_size servings. When nb_refills have been done, the druid has run out of ingredients and it's thread must stop

## Installation

---

### 1. Git clone the repository on your PC.

```bash
git clone git@github.com:EpitechPGE2-2025/G-CCP-400-LIL-4-1-panoramix-25.git
cd G-CCP-400-LIL-4-1-panoramix-25
```

### 2. Compile

```bash
make
```

### 3. Launch Arcade

Remplace the values between <> by your values.

```bash
./panoramix  <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```


---

## Project structure

---

```bash
.  
├── include                     #The folder for include elements
│   └── my.h  
├── main.c                      #Parsing arguments and launch the project
├── Makefile                    #For compile the project
├── README.md                   #This file
└── src
    └── core.c                  #This file contains the logic for thread
```

---

## Author

- [Louis Hector](https://github.com/MinFlag)

---
