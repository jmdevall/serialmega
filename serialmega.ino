typedef struct{
  byte lastByte;
  boolean readed=false;
} SerialByte;


int serialAvailable(int numSerial){
  if(numSerial==0){
    return Serial.available();
  }
  if(numSerial==1){
    return Serial1.available();
  }
}

byte serialWrite(int numSerial, byte data){
  if(numSerial==0){
    Serial.write(data);
  }
  if(numSerial==1){
    Serial1.write(data);
  }
}

byte serialRead(int numSerial){
  if(numSerial==0){
    return Serial.read();
  }
  if(numSerial==1){
    return Serial1.read();
  }
}

int h1=30;
int h2=31;
int h3=32;
int alarma=22;
int boton=23;

int value = 0;
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(h1,OUTPUT);
  pinMode(h2,OUTPUT);
  pinMode(h3,OUTPUT);
  pinMode(alarma,OUTPUT);
  pinMode(boton,INPUT);
}


void loop() {
  digitalWrite(h2,HIGH);

  value=digitalRead(boton);
  if (value == HIGH) {
      digitalWrite(alarma,HIGH);
      //Serial.println("Encendido");
  }
  else {
    digitalWrite(alarma,LOW);
      //Serial.println("Apagado");
  }
  //Serial.println("hello world!\n");
  //delay(1000);
  
  //while(1) {
     SerialByte cncIn = recvSerial(1);
     writeSerial(0,cncIn);
     SerialByte inputIn=recvSerial(0);
     writeSerial(1,inputIn);
  //}

}

SerialByte recvSerial(int numSerial) {
  SerialByte bytecnc;

  if (serialAvailable(numSerial) > 0) {
    bytecnc.lastByte = serialRead(numSerial);
    bytecnc.readed = true;
  }
  return bytecnc;
}

void writeSerial(int numSerial,SerialByte &cncIn) {
 if (cncIn.readed == true) {
  serialWrite(numSerial,cncIn.lastByte);
  cncIn.readed = false;
 }
}
