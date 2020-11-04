 #include <ArxContainer.h>
 arx:: vector<int>myVector1;
 arx:: vector<int>myVector2;
 bool autoState = false;
 int switchState;
 int index; 
 

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
  


}

void loop() {
  if(autoState == false){
    int dataForRightMotor = getMotorSpeedRight();
    int dataForLeftMotor = getMotorSpeedLeft();
    analogWrite(enA, dataForRightMotor);
    analogWrite(enB, dataForLeftMotor);
    myVector1.push_back(dataForRightMotor);
    myVector2.push_back(dataForLeftMotor);
    delay(5);
    switchState = digitalRead(16);
    if(switchState == LOW){
      autoState = true;
    }
    
  }
  if(autoState == true){
    index = 0;
  
    if (index < myVector1.size()){
      analogWrite(enA, myVector1[index]);
      analogWrite(enB, myVector2[index]);
      index++;
      delay(5);
     
//    for(size_t i = 0; i < myVector1.size(); i ++){
//      analogWrite(enA, myVector1[i]);     
//    }
//    for(size_t j = 0; j < myVector2.size(); j++){
//      analogWrite(enB, myVector2[j]);
//    }
//    if(switchState == LOW){
//      autoState = false;
//    }
  }
}
  
  


}

int getMotorSpeedRight(){  
    int yAxisSpeed = analogRead(vry);
    int xAxisSpeed = analogRead(vrx);
    if (yAxisSpeed > 550){
    motorSpeedRight = map(yAxisSpeed, 550, 1023, 0, 255);
    }
    else{
      motorSpeedRight = 0;
    }
     if (xAxisSpeed <470){
      int xMapped = map(xAxisSpeed, 470,0,0,255);
      motorSpeedRight = motorSpeedRight - xMapped;
      if(motorSpeedRight >255){
       motorSpeedRight = 255;
      }
    } 
    if(xAxisSpeed >550){
      int xMapped = map(xAxisSpeed, 550, 1023, 0, 255);
      motorSpeedRight = motorSpeedRight + xMapped;
      if(motorSpeedRight < 0){
        motorSpeedRight = 0;
      }
    }
    return motorSpeedRight;
}
int getMotorSpeedLeft(){
  int yAxisSpeed = analogRead(vry);
  int xAxisSpeed = analogRead(vrx);
  if (yAxisSpeed > 550){
   motorSpeedLeft = map(yAxisSpeed, 550, 1023, 0, 255);
  }
  else{
    motorSpeedLeft = 0;
  }
  if (xAxisSpeed <470){
    int xMapped = map(xAxisSpeed, 470,0,0,255);
    motorSpeedLeft = motorSpeedLeft + xMapped;
    if(motorSpeedLeft < 0){
      motorSpeedLeft = 0;
    }
  }
  if(xAxisSpeed >550){
    int xMapped = map(xAxisSpeed, 550, 1023, 0, 255);
    motorSpeedLeft = motorSpeedLeft - xMapped;
    if(motorSpeedLeft > 255){
      motorSpeedLeft = 255;
    }
  }
  return motorSpeedLeft;
  
}

