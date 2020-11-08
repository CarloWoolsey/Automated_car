 #include <ArxContainer.h>
 arx:: vector<int>myVector1;
 arx:: vector<int>myVector2;
 bool autoState = false;
 int switchState;
 int index = 0; 
 

 const int vry = A0;
 const int vrx = A1;
 const int enA = 5;
 const int enB = 6; 
 const int ln1 = 7;
 const int ln2 = 8;
 const int ln3 = 9;
 const int ln4 = 11;
 int motorSpeedRight;
 int motorSpeedLeft;




void setup() {
  pinMode(ln1, OUTPUT);
  pinMode(ln2, OUTPUT);
  pinMode(ln3, OUTPUT);
  pinMode(ln4, OUTPUT);
  pinMode(16, INPUT_PULLUP);
  digitalWrite(ln1, HIGH);
  digitalWrite(ln2, LOW);
  digitalWrite(ln3, LOW);
  digitalWrite(ln4, HIGH);
  Serial.begin(9600);
  


}

void loop() {
  int switchState = digitalRead(16);
  if(switchState == LOW&& !autoState){
    autoState = true;
  }
//  else if(switchState == LOW && autoState){
//    autoState = false;
//    index = 0;
//  }
  if(autoState == false){
    record();   
  }
  if(autoState == true){
    if(index < myVector1.size()){
      analogWrite(enA, myVector1[index]);
      analogWrite(enB, myVector2[index]);
      Serial.print("myVector1: ");
      Serial.print(myVector1[index]);
      Serial.print("myVector2: ");
      Serial.println(myVector2[index]);
      index++;
      delay(5);      
    }    
  }
}

void record(){  
    int yAxisSpeed = analogRead(vry);
    int xAxisSpeed = analogRead(vrx);
    if (yAxisSpeed > 550){
    motorSpeedRight = map(yAxisSpeed, 550, 1023, 0, 255);
    motorSpeedLeft = map(yAxisSpeed, 550, 1023, 0, 255);
    }
    else{
      motorSpeedRight = 0;
      motorSpeedLeft = 0;
    }
     if (xAxisSpeed <470){
      int xMapped = map(xAxisSpeed, 470,0,0,255);
      motorSpeedRight = motorSpeedRight - xMapped;
      motorSpeedLeft = motorSpeedLeft + xMapped;
      if(motorSpeedRight >255){
       motorSpeedRight = 255;
      }
      if(motorSpeedLeft < 0){
       motorSpeedLeft = 0;
      }
    } 
    if(xAxisSpeed >550){
      int xMapped = map(xAxisSpeed, 550, 1023, 0, 255);
      motorSpeedRight = motorSpeedRight + xMapped;
      motorSpeedLeft = motorSpeedLeft - xMapped;
      if(motorSpeedRight < 0){
        motorSpeedRight = 0;
      }
     if(motorSpeedLeft > 255){
      motorSpeedLeft = 255;
     }
    }
    analogWrite(enA, motorSpeedRight);
    analogWrite(enB, motorSpeedLeft);
    myVector1.push_back(motorSpeedRight);
    myVector2.push_back(motorSpeedLeft);
    Serial.print("myVector1: ");
    Serial.print(myVector1.back());
    Serial.print("myVector2: ");
    Serial.println(myVector2.back());
    delay(5);
    
}
