# The Plazza

## Description

**The Plazza** is a C++ project that simulates a pizzeria.

The program is built around three main components:

- the **Reception**, which reads user commands and distributes pizzas.
- the **Kitchens**, which are dynamically created as child processes.
- the **Cookers**, which are represented by threads inside each kitchen.

The Reception and the Kitchens communicate through **FIFO IPC**.

IPC messages are serialized and deserialized using a fixed structure with `pack()` and `unpack()`.

## Installation

```bash
git clone git@github.com:EpitechPGE2-2025/G-CCP-400-LIL-4-1-theplazza-13.git
cd G-CCP-400-LIL-4-1-theplazza-13
```

## Build

To compile the project:

```bash
make
```

To fully rebuild the project:

```bash
make re
```

To remove object files:
```bash
make clean
```

To remove object files and the binary:
```bash
make fclean
```

## Run

The binary is named:

```bash
./plazza
```

It takes three arguments:

```bash
./plazza [cooking_time_multiplier] [number_of_cooks_per_kitchen] [stock_refill_time_ms]
```

Example:

```bash
./plazza 1 2 2000
```

Arguments:

- cooking_time_multiplier: multiplier applied to pizza cooking times.
- number_of_cooks_per_kitchen: number of cooker threads per kitchen.
- stock_refill_time_ms: ingredient stock refill delay in milliseconds.

Example:

```bash
./plazza 1 2 2000
```

This starts the program with:

- normal cooking time.
- 2 cookers per kitchen.
- stock refill every 2000 ms.

## Available Commands

Once the program is running, an interactive shell is displayed.

### Order pizzas

Command format:

```bash
TYPE SIZE xNUMBER
```

Example:

```bash
regina S x3
```

This orders 3 Regina pizzas of size S.

You can also send several orders in one line by separating them with ';'.

```bash
regina S x3 ; americana XL x2 ; fantasia M x1
```

### Pizza Types

Available pizza types are:

- regina
- margarita
- americana
- fantasia

### Pizza Sizes

Available sizes are:

- S
- M
- L
- XL
- XXL

### Status Command

To display the status of the active kitchens:

```bash
status
```

The status displays:

- active kitchens.
- kitchen capacity.
- number of pizzas currently handled by each kitchen.
- ingredient stock.
- cooker thread status.
- pizzas currently being cooked.

### Exit the Shell

To leave the shell cleanly, use:

```bash
CTRL + D
```

This closes the standard input and lets the program exit naturally.

## Logs

Logs are written into:

```bash
log.txt
```

This file is automatically created when Plazza is launched and is stored at the root of the project. Each time the program starts, the existing log file is overwritten.

The log file can be used to follow the full lifecycle of an order:

- user input.
- order creation.
- kitchen creation.
- pizza dispatching.
- pizza reception by kitchens.
- cooker activity.
- pizza completion.
- order progress.
- kitchen shutdown.
- errors.

## Project Architecture

```bash
.
├── log.txt
├── main.cpp
├── Makefile
├── README.md
└── src
    ├── Constant.hpp
    ├── Encapsulate
    │   ├── CondVar.cpp
    │   ├── CondVar.hpp
    │   ├── Mutex.cpp
    │   ├── Mutex.hpp
    │   ├── Processus.cpp
    │   ├── Processus.hpp
    │   ├── SafeQueue.cpp
    │   ├── SafeQueue.hpp
    │   ├── ScopedLock.cpp
    │   ├── ScopedLock.hpp
    │   ├── Thread.cpp
    │   └── Thread.hpp
    ├── Factory
    │   ├── Factory.cpp
    │   └── Factory.hpp
    ├── Interface
    │   ├── APizza.cpp
    │   ├── APizza.hpp
    │   └── IPizza.hpp
    ├── IPCMessage
    │   ├── IPC.cpp
    │   ├── IPC.hpp
    │   ├── IPCMessage.cpp
    │   └── IPCMessage.hpp
    ├── Kitchen
    │   ├── Kitchen.cpp
    │   ├── Kitchen.hpp
    │   ├── Stock.cpp
    │   └── Stock.hpp
    ├── Log
    │   ├── Log.cpp
    │   └── Log.hpp
    ├── Parsing
    │   ├── Parsing.cpp
    │   └── Parsing.hpp
    ├── Pizza
    │   ├── Americana.cpp
    │   ├── Americana.hpp
    │   ├── Fantasia.cpp
    │   ├── Fantasia.hpp
    │   ├── Margarita.cpp
    │   ├── Margarita.hpp
    │   ├── Regina.cpp
    │   └── Regina.hpp
    ├── Reception
    │   ├── Reception.cpp
    │   └── Reception.hpp
    └── Shell
        ├── Shell.cpp
        └── Shell.hpp
```

## Author

- [Paul Ammeloot](https://github.com/PaulAmmeloot)
- [Louis Hector](https://github.com/MinFlag)
- [Logan Capoen](https://github.com/logan-capoen)