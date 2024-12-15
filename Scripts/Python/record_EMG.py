from pyfirmata import Arduino, util
import time

# Configurare placa Arduino
board = Arduino('COM7')

# Configurare iterator pentru a citi semnale analogice
it = util.Iterator(board)
it.start()

# Selectarea pinului analogic (de exemplu, A0)
analog_pin = board.get_pin('a:0:i')  # 'a' pentru analogic, '0' pentru pinul A0, 'i' pentru input

# Așteptare inițializare
time.sleep(1)

# Funcție pentru înregistrarea semnalelor în fișier
def record_signals(filename, duration):
    """
    Înregistrează semnalele EMG într-un fișier .txt.

    :param filename: Numele fișierului în care se salvează datele.
    :param duration: Durata înregistrării în secunde.
    """
    start_time = time.time()
    
    with open(filename, 'w') as file:
        file.write("Timp (s)\tValoare EMG\n")  # Scrie antetul fișierului
        print(f"Încep înregistrarea pentru {duration} secunde...")

        while time.time() - start_time < duration:
            emg_value = analog_pin.read()
            
            if emg_value is not None:
                # Transformă valoarea într-un interval de 0-1023
                emg_scaled = emg_value * 1023
                timestamp = time.time() - start_time
                file.write(f"{timestamp:.2f}\t{emg_scaled:.2f}\n")
                print(f"Timp: {timestamp:.2f}s, Semnal EMG: {emg_scaled:.2f}")
            else:
                print("Aștept semnal...")
            
            time.sleep(0.1)  # Pauză scurtă între citiri

    print(f"Înregistrare finalizată. Datele au fost salvate în {filename}.")

# Exemplu de utilizare a funcției de înregistrare
if __name__ == "__main__":
    try:
        # Setează durata înregistrării în secunde
        durata_inregistrare = 10  # Modifică durata după necesitate
        nume_fisier = "Semnale_test\\semnale_emg.txt"

        # Apelează funcția de înregistrare
        record_signals(nume_fisier, durata_inregistrare)

    except KeyboardInterrupt:
        print("Oprire manuală...")

    finally:
        board.exit()
