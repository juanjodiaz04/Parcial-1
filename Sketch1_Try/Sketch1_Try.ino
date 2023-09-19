// C++ code
//
int latchPin = 12;  //Pin conectado a ST_CP del primer 74595
int clockPin = 13;  //Pin conectado a SH_CP del primer 74595
int dataPin = 11;   //Pin conectado a DS del primer 74595

int latchPin2 = 6;  //Pin conectado a ST_CP del segundo 74595
int clockPin2 = 7;  //Pin connected to SH_CP del segundo 74595
int dataPin2 = 5;   //Pin connected to DS del segundo 74595

int j=0;
int anode_decimal[8]={1, 128,64,32,16,8,4,2};
int cathode_decimal[8]={254, 253, 251, 247, 239, 223, 191, 127};

//Funciones
void verificacion();

void setup() {
  
  //Iniciar el puerto serial para poder pedir entradas
  Serial.begin(9600);
  
  //Los pines conectados al 74595 son de salida para controlar el integrado
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
}

void loop() {
  verificacion();
  
  /*
    for(j=0;j<8;j++)
    {
      
      //latchPin en bajo para poder modificar la trama de bits a enviar  
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, cathode_decimal[j]);
      // shift out the bits:    
      digitalWrite(latchPin, HIGH);
  
      //latchPin en bajo para poder modificar la trama de bits a enviar   
      digitalWrite(latchPin2, LOW);
      shiftOut(dataPin2, clockPin2, MSBFIRST, anode_decimal[j]);
      // shift out the bits:  
      digitalWrite(latchPin2, HIGH);
        
      delay(1000);                   
   }
   */
  
}


void verificacion(){
  
  for (int i = 0; i < 5; i++){
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, MSBFIRST, 255);
    digitalWrite(latchPin2, HIGH);
    delay(3000);
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 255);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, MSBFIRST, 0);
    digitalWrite(latchPin2, HIGH);
    delay(3000);
  }
}
