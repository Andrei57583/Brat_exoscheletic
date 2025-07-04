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
filename = f"unghi_pwm_{timestamp}.csv"
filepath = os.path.join(base_dir, filename)

# === CONFIGURARE PLOT ===
MAX_POINTS = 200
x_vals = deque(maxlen=MAX_POINTS)
angle_vals = deque(maxlen=MAX_POINTS)
pwm_vals = deque(maxlen=MAX_POINTS)

plt.ion()
fig, ax = plt.subplots()
angle_line, = ax.plot([], [], label='Unghi (°)', color='blue')
pwm_line, = ax.plot([], [], label='PWM', color='red')

ax.set_ylim(0, 300)  # Valori maxime unghi & PWM
ax.set_xlim(0, MAX_POINTS)
ax.set_xlabel('Timp (eșantion)')
ax.set_ylabel('Valoare')
ax.legend(loc='upper right')
plt.title("Unghi & PWM în timp real")

# === START LOGARE ȘI PLOTARE ===
print(f"[INFO] Salvare în: {filepath}")
print("[START] Înregistrare + Plotare... Ctrl+C pentru oprire.")

with open(filepath, mode='w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(["Timestamp", "Unghi", "PWM"])

    try:
        index = 0
        while True:
            line = ser.readline().decode().strip()
            if "Unghi:" in line and "PWM:" in line:
                try:
                    # Extrage valorile
                    parts = line.split(',')
                    angle = float(parts[0].split(':')[1].strip())
                    pwm = float(parts[1].split(':')[1].strip())
                    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]

                    # Scrie în CSV
                    writer.writerow([now, angle, pwm])

                    # Adaugă în buffer pentru plotare
                    x_vals.append(index)
                    angle_vals.append(angle)
                    pwm_vals.append(pwm)
                    index += 1

                    # Actualizează graficul
                    angle_line.set_data(x_vals, angle_vals)
                    pwm_line.set_data(x_vals, pwm_vals)
                    ax.set_xlim(max(0, index - MAX_POINTS), index)
                    ax.set_ylim(0, max(300, max(angle_vals, default=0), max(pwm_vals, default=0) + 20))

                    plt.pause(0.001)

                except Exception as e:
                    print(f"[Avertisment] Linie nevalidă: {line}")
                    continue

    except KeyboardInterrupt:
        print("\n[STOP] Înregistrare oprită de utilizator.")
        ser.close()
