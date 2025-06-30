import serial
import matplotlib.pyplot as plt

ser = serial.Serial('COM7', 115200)
angles = []
pwms = []

while True:
    line = ser.readline().decode().strip()
    if "Unghi:" in line:
        try:
            parts = line.split(',')
            angle = float(parts[0].split(':')[1])
            pwm = float(parts[1].split(':')[1])
            angles.append(angle)
            pwms.append(pwm)
        except:
            continue

    if len(angles) > 100:
        plt.plot(angles, label='Unghi')
        plt.plot(pwms, label='PWM')
        plt.legend()
        plt.show()
        break
