import csv
import os
import matplotlib.pyplot as plt

# === CONFIGURARE CALE ===
# Fișierul e în Semnale_test
base_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../Semnale_test'))

# ← Înlocuiește cu numele fișierului salvat ultima oara
filename = "semnale_2025-06-30_14-51-27.csv"  
filepath = os.path.join(base_dir, filename)

if not os.path.exists(filepath):
    print(f"[Eroare] Fișierul nu există: {filepath}")
    exit()

# === CITIRE DATE ===
timestamps = []
env_data = []
raw_data = []
rect_data = []

with open(filepath, newline='') as csvfile:
    reader = csv.reader(csvfile)
    header = next(reader)  # Sare peste antet
    for row in reader:
        try:
            timestamps.append(row[0])
            env_data.append(int(row[1]))
            raw_data.append(int(row[2]))
            rect_data.append(int(row[3]))
        except (IndexError, ValueError):
            continue  # Ignoră liniile corupte

print(f"[INFO] Date încărcate: {len(env_data)} eșantioane")

# === PLOTARE ===
fig, axs = plt.subplots(3, 1, figsize=(10, 8), sharex=True)

axs[0].plot(env_data, label='Env', color='blue')
axs[0].set_title("Semnal ENV")
axs[0].set_ylabel("Valoare")
axs[0].set_ylim(0, 1023)

axs[1].plot(raw_data, label='Raw', color='red')
axs[1].set_title("Semnal RAW")
axs[1].set_ylabel("Valoare")
axs[1].set_ylim(0, 1023)

axs[2].plot(rect_data, label='Rect', color='green')
axs[2].set_title("Semnal RECT")
axs[2].set_ylabel("Valoare")
axs[2].set_ylim(0, 1023)
axs[2].set_xlabel("Eșantion")

plt.tight_layout()
plt.show()
