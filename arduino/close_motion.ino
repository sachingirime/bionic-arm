  // rock 180,30,180,10,145

#include <Servo.h>

Servo Servo2; //thumb push pull servo (min = 0, max = 180 // 9
Servo Servo3; //index finger servo (min = 140, max = 30)
Servo Servo4; //middle finger servo (min = 44, max = 180)
Servo Servo5; //ring finger servo (min = 140, max = 10)
Servo Servo6; //little finger servo (min = 25, max 145)

int increment = 8; //icrement value for the servo's
int pos2; //position Servo2
int pos3; //position Servo3
int pos4; //position Servo4
int pos5; //position Servo5x
int pos6; //position Servo6

//int rock = 1;
//int paper=2;
//int scissors = 3;
//int ok = 4;

int hand_gesture = 0; //2 paper, 3 scissors

void setup() {
  // put your setup code here, to run once:

  Servo2.attach(8); //attach Servo2 to pin 3
  Servo3.attach(9); //attach Servo3 to pin 4  index
  Servo4.attach(10); //attach Servo4 to pin 5 middle
  Servo5.attach(11); //attach Servo5 to pin 6 ring
  Servo6.attach(12); //attach Servo6 to pin 7 little
  // rock 180,30,180,10,145
  Servo2.write(180); //startposition Servo2 (thumb push pull servo)
  Servo3.write(30); //startposition Servo3 (index finger servo)
  Servo4.write(180); //startposition Servo4 (middle finger servo)
  Servo5.write(10); //startposition Servo5 (ring finger servo)
  Servo6.write(145); //startposition Servo6 (little finger servo)

  pos2 = 0; //position Servo2
  pos3 = 140; //position Servo3
  pos4 = 44; //position Servo4
  pos5 = 140; //position Servo5
  pos6 = 25; //position Servo6

  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  //code to detect serial from python


    if (Serial.available() > 0) {

     //Serial.println(hand_gesture);


      char signal_1 = Serial.read();

//     Serial.println("signal_1---");
//      Serial.println(signal_1);

      switch (signal_1) {
      case '1':
        // code for rock gesture
        hand_gesture = 1;
       // Serial.println("hand gesture to ---1");

        break;

      case '2':
        // code for paper gesture
        hand_gesture = 2;
        break;

      case '3':
        // code for scissors gesture
        hand_gesture = 3;
        break;

      case '4':
        // code for another gesture
        hand_gesture = 4;
        break;

      default:
        // code to handle an unknown gesture
        break;
    }
    }



  // code for different hand gestures

  if (hand_gesture == 1){   // rock
    
    if(pos3>=30){ // closing index
      index_close();
    }

    if  (pos4<=180){  // closing middle
      middle_close(); 
    }

    if(pos5 >= 10 ){  // ring close
      ring_close();
    }

    if(pos6 <= 145){  // little close
      little_close();
    }

    if(pos2 <= 180){  // thumb close
      thumb_close();
    }

    if((pos3<=30) && (pos4>=180)&&(pos5<=10)&&(pos6>=145)&&(pos2>=180)){ // initial state
      delay(100);
      //rock = 0;
      hand_gesture = 0;
      delay(5000);
      start_position();
     
    }

    Serial.print("pos2-----");
    Serial.println(pos2);
    Serial.print("pos3-----");
    Serial.println(pos3);
    Serial.print("pos4-----");
    Serial.println(pos4);
    Serial.print("pos5-----");
    Serial.println(pos5);
    Serial.print("pos6-----");
    Serial.println(pos6);
    
  }


 if (hand_gesture ==2){  //paper

  if(pos2 >= 0){  // thumb open
    thumb_open();
  }

  if (pos3 <= 140){ // index open
    index_open();
  }

  if(pos4 >= 44){   // middle open
    middle_open();
  }

  if(pos5<= 140){ // ring open
    ring_open();
  }

  if(pos6 >= 25){ // little open
    little_open();
  }

  if((pos2 <= 0)&&(pos3 >= 140)&&(pos4 <= 44)&&(pos5 >= 140)&&(pos6 <= 25)){ //initial state
    //paper = 0;
    hand_gesture = 0;
    delay(5000);
    start_position();
  }

  
    Serial.print("pos2-----");
    Serial.println(pos2);
    Serial.print("pos3-----");
    Serial.println(pos3);
    Serial.print("pos4-----");
    Serial.println(pos4);
    Serial.print("pos5-----");
    Serial.println(pos5);
    Serial.print("pos6-----");
    Serial.println(pos6);

 }


 if(hand_gesture == 3){ //scissors


  if (pos3 <= 140){ // index open
    index_open();
  }

  if(pos4 >= 44){   // middle open
    middle_open();
  }

    
    if((pos3 >= 140) && (pos4 <= 44) ){  //initial state
      //scissors = 0;
      hand_gesture = 0;
      delay(5000);
      start_position();
    }

    
    Serial.print("pos2-----");
    Serial.println(pos2);
    Serial.print("pos3-----");
    Serial.println(pos3);
    Serial.print("pos4-----");
    Serial.println(pos4);
    Serial.print("pos5-----");
    Serial.println(pos5);
    Serial.print("pos6-----");
    Serial.println(pos6);
    
 }

 if(hand_gesture == 7){//mid finger

  
  if(pos4 >= 44){   // middle open
    middle_open();
  }

   if( (pos4 <= 44) ){  //initial state
      //scissors = 0;
      hand_gesture = 0;
      delay(5000);
      start_position();
    }
 }


 if (hand_gesture == 4){  // ok motion //open = 0,140,44,140,25

     if(pos2 <= 180){ // closing thumb
      thumb_close();
    }
    
    if(pos3>=30){ // closing index
      index_close();
    }

    if((pos2>= 180)&&(pos3<=30)){ // initial state
      //ok = 0;
      hand_gesture = 0;
      delay(5000);
      start_position();
    }

    
    Serial.print("pos2-----");
    Serial.println(pos2);
    Serial.print("pos3-----");
    Serial.println(pos3);
    Serial.print("pos4-----");
    Serial.println(pos4);
    Serial.print("pos5-----");
    Serial.println(pos5);
    Serial.print("pos6-----");
    Serial.println(pos6);
    
 

    }


  

}

void index_close(){
    pos3 -= increment;
    Servo3.write(pos3); // index finger
}

void middle_close(){
    pos4 += increment;
    Servo4.write(pos4); // middle finger
}

void ring_close(){
    pos5 -= increment;
    Servo5.write(pos5); // ring finger
}

void little_close(){
  pos6 += increment;
  Servo6.write(pos6); // little finger
}

void thumb_close(){
   pos2 += increment;
   Servo2.write(pos2); // thumb push pull
}


void index_open(){
    pos3 += increment;
    Servo3.write(pos3); // index finger
}

void middle_open(){
    pos4 -= increment;
    Servo4.write(pos4); // middle finger
}

void ring_open(){
   pos5 += increment;
   Servo5.write(pos5); // ring finger
}

void little_open(){
   pos6 -= increment;
   Servo6.write(pos6); // little finger
}

void thumb_open(){
    pos2 -= increment;
    Servo2.write(pos2); // thumb push pull
}


void start_position(){
  // rock 180,30,180,10,145
  Servo2.write(180); //startposition Servo2 (thumb push pull servo)
  Servo3.write(30); //startposition Servo3 (index finger servo)
  Servo4.write(180); //startposition Servo4 (middle finger servo)
  Servo5.write(10); //startposition Servo5 (ring finger servo)
  Servo6.write(145); //startposition Servo6 (little finger servo)

  
}
