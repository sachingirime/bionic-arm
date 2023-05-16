import serial
import struct
import pandas as pd
import time

# code to get the emg signal from
start_time = time.time()
# nano = /dev/cu.usbserial-110
#uno = /dev/cu.usbmodem101 (Arduino Uno)
ser = serial.Serial('/dev/cu.usbserial-10', 115200) # replace 'COM4' with the name of the serial port connected to Arduino

data = []
while True:
    arduino_data = ser.read(4) # read 4 bytes from the serial port
    analog_values = struct.unpack('>hh', arduino_data) # unpack the binary data into two 16-bit integers
    analog_values_scaled = [x/1023 for x in analog_values]
    data.append(analog_values_scaled)
    print(analog_values)
    
    if time.time() - start_time > 8:
        break

df = pd.DataFrame(data)
df.to_csv('input.csv', mode='w', index=True, header=False)
