import numpy as np
from scipy.io import wavfile

# Paramètres du signal
rate = 48000          # Fréquence d'échantillonnage 48 kHz
duration = 2          # Durée en secondes
frequency = 440       # Fréquence du signal en Hz (La4)
amplitude = 10000     # Amplitude (16 bits PCM = ±32767 max)

# Créer un vecteur de temps
t = np.arange(0, duration, 1/rate)

# Générer la sinusoïde
signal = amplitude * np.sin(2 * np.pi * frequency * t)

# Convertir en int16 pour WAV 16 bits
signal = signal.astype(np.int16)

# Sauvegarder en WAV
wavfile.write("test_sine.wav", rate, signal)

print("Fichier test_sine.wav créé !")