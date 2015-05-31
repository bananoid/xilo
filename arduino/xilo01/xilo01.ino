#define ANALOG_PORT 0
#define NUM_PIEZO 16

int selectorPins[4]  = {4,5,6,7};
int piezoValues[NUM_PIEZO];
char piezoChars[16] =   {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
bool piezoEnabled[16] = { 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };


void setup(){
  Serial.begin(115200);

  for(int i=0; i < NUM_PIEZO; i++){
    pinMode(selectorPins[i],OUTPUT);
    digitalWrite(selectorPins[i],LOW);
    piezoValues[i] = 0;
  }
}

// int readPort = -1;

void loop(){

  // if (Serial.available() > 0) {
  //   char incomingByte = Serial.read();
  //   readPort =  int(incomingByte);
  //   Serial.print("readPort :: ");
  //   Serial.println(readPort);
  // }
  readSensors();
  printSensors();

}

void readSensors(){
  for(int i=0; i < NUM_PIEZO; i++){
      if(!piezoEnabled[i]) continue;
      piezoValues[i] = muxAnalogRead(i);
  }
}

void printSensors(){
  int v;
  for(int i=0; i < NUM_PIEZO; i++){
    if(!piezoEnabled[i]) continue;
    if(piezoValues[i] < 50) continue;
    // printValue(piezoValues[i] / 10, piezoChars[i] );
    Serial.print(i);
    Serial.print(":: [");
    Serial.print(piezoValues[i]);
    Serial.println(" ]");
  }
}

int muxAnalogRead(int port){
  for(int k=0; k < 4; k++){
    digitalWrite(selectorPins[k], bitRead(port,k) );
  }
  return analogRead(ANALOG_PORT);
}

void printValue(int val,char c){
  for(int i=0; i<val ; i++){
    Serial.print(c);
  }
  Serial.println("");
}
