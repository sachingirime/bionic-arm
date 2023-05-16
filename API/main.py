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

csv_file = ''


#load model
model = joblib.load('paper_scissor.joblib')
result={
    1:'Paper',
    3:'scissor'
}
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
 

@app.get("/")
async def root():

    return {"message": "Hello World"}

@app.post("/uploadcsv/")
async def file_upload(file: UploadFile = File(...)):
    with open(f"{file.filename}", "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)
    csv_file = file.filename

    

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
    


        


