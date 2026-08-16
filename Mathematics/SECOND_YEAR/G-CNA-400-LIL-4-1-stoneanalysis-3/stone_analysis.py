##
## EPITECH PROJECT, 2026
## G-CNA-400-LIL-4-1-stoneanalysis-3
## File description:
## stone_analysis
##

import sys
import os
from scipy.io import wavfile
import numpy as np

def print_help():
    print("USAGE")
    print("    ./stone_analysis [--analyze | -a] IN_FILE N")
    print("                     [--cypher | -c] IN_FILE OUT_FILE MESSAGE")
    print("                     [--decypher | -d] IN_FILE\n")
    print("DESCRIPTION")
    print("    IN_FILE An audio file to be analyzed")
    print("    OUT_FILE Output audio file of the cypher mode")
    print("    MESSAGE The message to hide in the audio file")
    print("    N Number of top frequencies to display")
    
def check_extension(file_args):
    _, file_extension = os.path.splitext(file_args)
    if (file_extension != ".wav"):
        sys.exit(84)
    return file_args

# def DFT(samples):
    # N = len(samples)
    # n = np.arange(N)
    # k = n.reshape(N)
    # exp = np.exp(-2j * np.pi * k * n / N)
    # return np.dot(exp, samples)
    
def DFT(samples):
    lenght = len(samples)
    values = []
    for i in range(lenght):
        #print(i)
        ampli = 0.0
        for j in range(lenght):
            ampli += samples[j] * np.exp(-2j * np.pi * i * j / lenght)
        values.append(ampli)
    return np.array(values)  
    
def search_frequencies(values, N, rate, samples):
    magni = np.abs(values)
    indices = np.argsort(magni)[::-1]
    max_indices = indices[:N]
    max_frequencies = max_indices * (rate / 10) / len(samples)
    return max_frequencies

def analyze_rock():
    if (len(sys.argv) != 4):
        sys.exit(84)
    input_file = check_extension(sys.argv[2])
    if (sys.argv[3].isdigit() == False):
        sys.exit(84)
    Num = (int)(sys.argv[3])
    if (Num == 0):
        sys.exit(84)
    rate, samples = wavfile.read(input_file)
    # print(rate)
    # print(samples)
    if samples.ndim > 1:
        samples = samples.mean(axis=1)
    samples = samples.astype(float)
    too_many_samples = samples[::10]
    values = DFT(too_many_samples)
    max_fr = search_frequencies(values, Num, rate, too_many_samples)
    print(f"Top {Num} frequencies:")
    for i in max_fr:
        print(f"{i:.2f} Hz")
    sys.exit(0)

def cypher_rock():
    if (len(sys.argv) != 5):
        sys.exit(84)
    input_file = check_extension(sys.argv[2])
    output_file = check_extension(sys.argv[3])
    message = sys.argv[4]
    for i in message:
        if ((i < 'a' or i > 'z') and (i < 'A' or i > 'Z') and i != " " and (i < '0' or i > '9')):
            sys.exit(84)
    message = message.upper()
    sys.exit(0)

def decypher_rock():
    if (len(sys.argv) != 3):
        sys.exit(84)
    input_file = check_extension(sys.argv[2])
    sys.exit(0)

def main():
    if (len(sys.argv) == 2 and sys.argv[1] == "--help"):
        print_help()
        sys.exit(0)
    if (len(sys.argv) < 3 or len(sys.argv) > 5):
        sys.exit(84)
    if (sys.argv[1] == "--analyze" or sys.argv[1] == "-a"):
        analyze_rock()
    elif (sys.argv[1] == "--cypher" or sys.argv[1] == "-c"):
        cypher_rock()
    elif (sys.argv[1] == "decypher" or sys.argv[1] == "-d"):
        decypher_rock()
    else:
        sys.exit(84)
    
if __name__ == '__main__':
    main()