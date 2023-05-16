import serial
import time
#arduino uno - /dev/cu.usbmodem101
# nano - /dev/cu.usbserial-110
ser = serial.Serial('/dev/cu.usbmodem101', 9600)  # replace 'COM3' with the appropriate port name
time.sleep(2)  # add a delay of 2 seconds
gesture = 'paper'
# assume the output of the model is stored in the variable 'gesture'
if gesture == 'rock':
    ser.write(b'1')  # signal to move the prosthetic arm for rock gesture

elif gesture == 'paper':
    ser.write(b'2')  # signal to move the prosthetic arm for paper gesture
elif gesture == 'scissors':
    ser.write(b'3')  # signal to move the prosthetic arm for scissors gesture
elif gesture == 'ok':
    ser.write(b'4')  # signal to move the prosthetic arm for ok gesture

ser.close()
