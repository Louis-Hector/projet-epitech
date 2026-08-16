##
## EPITECH PROJECT, 2026
## G-CNA-400-LIL-4-1-interstonar-7
## File description:
## core
##

import sys
import os
import math
import tomllib

GRAVITATION = 6.674e-11
ROCK = 1000

def print_help():
    print("USAGE")     
    print("    ./interstonar [--global | --local] CONFIG_FILE [-d TIME | --delta=TIME] Px Py Pz Vx Vy Vz\n")
    print("DESCRIPTION")
    print("    --global")
    print("\tLaunch program in global scene mode. The CONFIG_FILE will describe a scene containing")
    print("\tmassive spherical moving bodies.")
    print("    --local")
    print("\tLaunch program in local scene mode. The CONFIG_FILE will describe a scene containing")
    print("\tmassless motionless shapes.")
    print("    -d TIME, --delta=TIME")
    print("\tGLOBAL mode only. Sets the delta time (in SI base unit) for which every position is updated.")
    print("    CONFIG_FILE")
    print("\tTOML configuration file describing a scene.")
    print("    Pi")
    print("\tInitial position coordinates of the rock")
    print("    Vi")
    print("\tInitial velocity vector of the rock")
    sys.exit(0)

def parse_args():
    type_file = sys.argv[1]
    file = sys.argv[2]
    if (type_file != "--global" and type_file != "--local"):
        sys.exit(84)
    _, extension = os.path.splitext(file)
    if (extension != ".toml"):
        sys.exit(84)
    time = 0
    index = 3
    if type_file == "--local":
        if len(sys.argv) != 9:
            sys.exit(84)
    elif type_file == "--global":
        if len(sys.argv) == 9:
            index = 3
        elif len(sys.argv) == 10:
            arg = sys.argv[3]
            if not arg.startswith("--delta="):
                sys.exit(84)
            try:
                time = float(arg.split("=")[1])
            except:
                sys.exit(84)
            index = 4
        elif len(sys.argv) == 11:
            if sys.argv[3] != "-d":
                sys.exit(84)
            try:
                time = float(sys.argv[4])
            except:
                sys.exit(84)
            index = 5
        else:
            sys.exit(84)
    tab_pi_vi = []
    for i in range(index, len(sys.argv)):
        try:
            value = float(sys.argv[i])
        except:
            sys.exit(84)
        tab_pi_vi.append(value)
    if len(tab_pi_vi) != 6:
        sys.exit(84)
    return type_file, file, time, tab_pi_vi

def move_celestial(celestials, time):
    for celestial in celestials:
        celestial['position']['x'] += celestial['direction']['x'] * time
        celestial['position']['y'] += celestial['direction']['y'] * time
        celestial['position']['z'] += celestial['direction']['z'] * time

def add_vectors(vi1, vi2):
    return [vi1[0] + vi2[0], vi1[1] + vi2[1], vi1[2] + vi2[2]]

def sub_vectors(vi1, vi2):
    return [vi1[0] - vi2[0], vi1[1] - vi2[1], vi1[2] - vi2[2]]

def mult_vectors(vi1, force):
    return [vi1[0] * force, vi1[1] * force, vi1[2] * force]