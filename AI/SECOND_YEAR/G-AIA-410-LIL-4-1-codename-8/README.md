# CODENAME

**CODENAME** is a project from the module ***G4 - Prompt Engineering***.

---

## Content

- [Summary](#summary)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Documentation](#documentation)
- [Authors](#authors)

---

## Summary

**CODENAME** is a prompt‑engineering project built around two prompts:

- a **defense prompt** that contains a password and a secret  
- an **attack prompt** that tries to extract them

The model is created with the defense prompt as its system prompt.  
Its rule is:

- **never reveal the password or the secret**
- **except** when the user provides the correct password, then it must reveal the secret

The attack prompt’s goal is to break this rule in a single message and recover the password the model is trying to protect.

---

## Usage

### Prerequisites

Before using the project, make sure you have:

- [Ollama](https://ollama.com/) installed
- the **granite3.1-moe:latest** model available in your Ollama installation
- execution rights on the scripts
- a shell environment able to run the project scripts

You may need to make the scripts executable with:

```bash
chmod +x scripts/*.sh
```

### Build the model

To create the `Modelfile` and then build the Ollama model `codename`, run:

```bash
make
```

This command runs the default workflow of the project:

- `make modelfile`
- `make codename`

#### Step 1: generate the Modelfile

```bash
make modelfile
```

This command executes:

```bash
scripts/build_modelfile.sh "$(PASSWORD)" "$(SECRET)"
```

It generates a `Modelfile` from the content of `defense.prompt`.

In other words:

- `defense.prompt` contains the defensive system instructions
- these instructions are copied into the `Modelfile`
- the values of `PASSWORD` and `SECRET` are injected during this step

#### Step 2: build the Ollama model

```bash
make codename
```

This command executes:

```bash
scripts/build_codename_model.sh
```

It builds an Ollama model called `codename` from the generated `Modelfile`.

So the model is not created directly from `defense.prompt`, but from the `Modelfile` that was generated using `defense.prompt`.

### Run one attack

To launch a single attack against the protected model, run:

```bash
make attack
```

This command executes:

```bash
scripts/run_attack_prompt.sh "$(PASSWORD)" "$(SECRET)"
```

- the script reads the attack prompt from the file `attack.prompt`
- it sends this prompt to the model `codename`
- it checks whether the model reveals or protects the password and the secret

### Run multiple attacks

To repeat the attack several times, run:

```bash
make loop_attack
```

This command executes:

```bash
scripts/loop_attack_prompt.sh "$(PASSWORD)" "$(SECRET)" "$(ITERATIONS)"
```

It launches `attack.prompt` several times on the `codename` model.

By default, the number of iterations is:

```bash
ITERATIONS=10
```

You can override this value like this:

```bash
make loop_attack ITERATIONS=20
```

### Simulate automatic tests

To run the automatic test simulation, use:

```bash
make at
```

This command executes:

```bash
scripts/simulate_at.sh "$(PASSWORD)" "$(SECRET)"
```

During this step, the script generates a file called `get_secret.prompt`, which contains only the password.
The automatic test then runs 10 checks:
- 5 tests send `get_secret.prompt` to verify that the model returns the secret when the correct password is provided.
- 5 tests send `attack.prompt` to verify that the model does not leak either the password or the secret.

### Customize the password and secret

The Makefile defines default values:

```makefile
PASSWORD ?= aef4g6sq4fva6q486d
SECRET ?= NHSZLK4567SQ4G35QS
```

You can override them from the command line.

Example:

```bash
make PASSWORD="mypassword123" SECRET="hidden_value"
```

This changes the values used when generating the `Modelfile`, and therefore changes the configuration of the `codename` model.

### Clean generated files

To remove only the generated `Modelfile`, run:

```bash
make clean
```

To fully clean the project, run:

```bash
make fclean
```

This command:

- removes the `Modelfile`
- removes the Ollama model `codename`
- removes the generated file `get_secret.prompt`

To rebuild everything from scratch, run:

```bash
make re
```

---

## Project Structure

```bash
.
├── attack.prompt                # Prompt used to attack the model
├── defense.prompt               # Prompt used to reinforce the model
├── doc
│   ├── ATTACK_PROMPTS.md        # Attack prompt documentation
│   ├── DEFENSE_PROMPTS.md       # Defense prompt documentation
│   └── PROJECT_LOG.md           # Project documentation
├── Makefile                     # Build the model and run attacks
├── README.md                    # This file
└── scripts
    ├── build_codename_model.sh  # Build an Ollama model called "codename"
    ├── build_modelfile.sh       # Generate a Modelfile from defense.prompt
    ├── loop_attack_prompt.sh    # Launch multiple attacks in a loop
    ├── run_attack_prompt.sh     # Launch one attack using attack.prompt
    └── simulate_at.sh           # Simulate automatic tests
```

---

## Documentation

- [Attack Prompts](./doc/ATTACK_PROMPTS.md)
- [Defense Prompts](./doc/DEFENSE_PROMPTS.md)
- [Project Log](./doc/PROJECT_LOG.md)

---

## Authors

- [Paul Ammeloot](https://github.com/PaulAmmeloot)
- [Louis Hector](https://github.com/MinFlag)