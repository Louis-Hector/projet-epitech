# Corewar

> Corewar is a project from the CPE module, aiming to simulate a virtual battle between programs called champions. **These champions compete inside a virtual machine according to a strict set of rules, trying to outlast their opponents.**  
> Think of it as a mini battle of robots

---
## Summary

- [Features](#-features)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Authors](#-authors)

---
## Features


Basic Features:

    Parses and loads .cor binary files representing compiled champions.

    Executes Redcode instructions cycle by cycle (live, ld, st, add, sub, etc.).

    Manages multiple processes (each champion can spawn new ones).

    Declares the winner based on the last valid live instruction.

Flags as:

    -dump <n>: dumps memory after n cycles.

    -n <number>: manually sets the champion’s number.

    -a <number> change the load memory of a champion

## Usage

#### Copy the repository to your computer

```http
git clone "repo_link"
cd "repo_name"
```

### Compile the program
```http
make
```

#### Use the executable
```http
./corewar[-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...
```
#### Exemple
```http
./corewar -n 1 -a 100 champ1.cor -n 2 champ2.cor -dump 5000
```



## Project Organization

```bash
corewar/
├── src/         # Main source code
├── include/     # Header files
├── lib/         # Utility functions
├── Makefile     # Compilation script
└── README.md    # This file
```
## Authors

- Louis Hector
- Laume Laqueste