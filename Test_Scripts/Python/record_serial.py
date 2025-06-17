import serial
import time
import os
import csv
from datetime import datetime
import matplotlib.pyplot as plt
from collections import deque

# === CONFIGURARE SERIALĂ ===
PORT = 'COM7'  
BAUD = 115200
ser = serial.Serial(PORT, BAUD)

# === CONFIGURARE FIȘIER ===
base_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../Semnale_test'))
if not os.path.exists(base_dir):
    print(f"[Eroare] Folderul 'Semnale_test' nu a fost găsit.")
    exit()

timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
filename = f"semnale_{timestamp}.csv"
filepath = os.path.join(base_dir, filename)

# === CONFIGURARE PLOT ===
MAX_POINTS = 200
x_vals = deque(maxlen=MAX_POINTS)
env_vals = deque(maxlen=MAX_POINTS)
raw_vals = deque(maxlen=MAX_POINTS)
rect_vals = deque(maxlen=MAX_POINTS)

plt.ion()
fig, ax = plt.subplots()
env_line, = ax.plot([], [], label='Env', color='blue')
raw_line, = ax.plot([], [], label='Raw', color='red')
rect_line, = ax.plot([], [], label='Rect', color='green')

ax.set_ylim(0, 1023)
ax.set_xlim(0, MAX_POINTS)
ax.set_xlabel('Timp (eșantion)')
ax.set_ylabel('Valoare')
ax.legend(loc='upper right')
plt.title("Semnale EMG Live")

# === START LOGARE ȘI PLOTARE ===
print(f"[INFO] Salvare în: {filepath}")
print("[START] Înregistrare + Plotare... Ctrl+C pentru oprire.")

with open(filepath, mode='w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(["Timestamp", "Env", "Raw", "Rect"])

    try:
        index = 0
        while True:
            line = ser.readline().decode().strip()
            if not line or len(line.split(",")) < 3:
                continue
            try:
                values = list(map(int, line.split(",")))
                now = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
                writer.writerow([now] + values)

                # Adaugă în plot
                x_vals.append(index)
                env_vals.append(values[0])
                raw_vals.append(values[1])
                rect_vals.append(values[2])
                index += 1

                # Actualizează graficele
                env_line.set_data(x_vals, env_vals)
                raw_line.set_data(x_vals, raw_vals)
                rect_line.set_data(x_vals, rect_vals)
                ax.set_xlim(max(0, index - MAX_POINTS), index)

                plt.pause(0.001)

            except ValueError:
                print(f"[Avertisment] Linie nevalidă: {line}")
                continue

    except KeyboardInterrupt:
        print("\n[STOP] Înregistrare oprită de utilizator.")
        ser.close()
