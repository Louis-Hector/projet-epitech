# NANOTEKSPICE
***
**NANOTEKSPICE** is a project from the OOP module, aimed at reproducing a server with the file transfer protocol(FTP).

## TABLE OF CONTENTS

- [Summary](#summary)
- [Usage](#usage)
- [Implementation](#implementation)
- [Project Structure](#project-structure)
- [Authors](#authors)

---

## Summary

NanoTekSpice is a logic simulator that builds a graph (the nodes of which will be simulated digital elec-
tronic components, inputs or outputs) from a configuration file, and injects values into that graph to get results.

There are many programming languages: C, Lisp, Basic, APL, Intercal... Each has its specificities and may
be efficient in a different way. They generally rely on a compiler to work. The compiler transforms code
written in something similar to human language into a more primitive form. This primitive form is called
assembly language when displayed in a human-readable format, or machine language when displayed
under the format read by the microprocessor.

Much like there are many programming languages, there are many assembly languages: at least one per
processor family, sometimes even one per single processor. Of course, knowing an assembly language for
a microprocessor may not be enough to be efficient : processors aren't the only components in machines

## Usage

### Launch the project

```bash
make re
./nanotekspice file
```

## Implementation

### Add New Component

### 1. Register the component in the Factory

Go to the file `Factory.cpp`.  
In the function `create_component`, add a new entry:

```cpp
{ "name_component", [] { return std::make_unique<nts::name_component_file>(); }},
```
Example:

```cpp
{ "and", [] { return std::make_unique<nts::And>(); }},
```

### 2. Define the pins

Still in Factory.cpp, in the function isPinValid, add your component in typePin:

```cpp
{"name_component", {1, 1}}
```

Example:

```cpp
{"and", {1, 1}}
```

This step defines the component and its pin configuration.

#### 3. Create the component files

Create two files for your component:

name_component.cpp
name_component.hpp

And add the functions need as compute.

## Project Structure

```bash
.
├── src/               # main folder
├── .gitignore         # For clean files
├── main.cpp           # Main source
├── Makefile           # Compilation)
└── README.md          # This file
```

## Authors

- Paul A.
- Louis H.