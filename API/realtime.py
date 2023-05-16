from fastapi import FastAPI, UploadFile, File
from keras.models import load_model

import joblib
import pandas as pd
import numpy as np
import serial
import struct
import time
import asyncio





import shutil
from fastapi.middleware.cors import CORSMiddleware
import os









app = FastAPI()



origins = ["*"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=False,
    allow_methods=["*"],
    allow_headers=["*"],
)


async def arm_motion(gesture):
    #arduino uno - /dev/cu.usbmodem101
    # nano - /dev/cu.usbserial-110
    ser = serial.Serial('/dev/cu.usbmodem101', 9600)  # replace 'COM3' with the appropriate port name
    time.sleep(2)  # add a delay of 2 seconds
    print("gesture in arm motion ------- ", gesture)
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

async def collect_data():
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
    

@app.get("/")
async def root():

    

    #collect realtime data
    collect_data()

    # load created csv file

    csv_file = 'input.csv'

      # Load the saved model
    model = load_model('sequential.h5',compile=False)
    model.compile()
    df = pd.read_csv(csv_file, header = None)
    y_pred_encoded = model.predict(df)
    y_pred = np.argmax(y_pred_encoded, axis=1)

    # Decode the predicted labels
    gesture = 'paper' if str(y_pred[0]) == '0' else 'scissors'
    print("prediction---",y_pred)


    loop = asyncio.get_event_loop()
    loop.create_task(arm_motion(gesture=gesture))

    os.remove(csv_file)  # Remove the CSV file


    return {"prediction class":str(y_pred[0])}



  