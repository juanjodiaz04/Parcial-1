// C++ code
//
int latchPin = 12;  //Pin connected to ST_CP of 1st 74595
int clockPin = 13;  //Pin connected to SH_CP of 1st 74595
int dataPin = 11;   //Pin connected to DS of 1st 74595

int latchPin2 = 6;  //Pin connected to ST_CP of 2nd 74595
int clockPin2 = 7;  //Pin connected to SH_CP of 2nd 74595
int dataPin2 = 5;   //Pin connected to DS of 2nd 74595

int j=0;
int anode_decimal[8]={1, 128,64,32,16,8,4,2};
int cathode_decimal[8]={254, 253, 251, 247, 239, 223, 191, 127};
void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
}

void loop() {
    for(j=0;j<8;j++)
    {
      /************To increase the ON time of LEDs five times more than 
      OFF time to increase the brightness of LEDs*************/
 
      /*************************  TURN ON DIAGONAL LEDs ONLY  ***************************/  
   
      // take the latchPin low so the LEDs don't change while you're sending in bits:  
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, cathode_decimal[j]);
      // shift out the bits:    
      digitalWrite(latchPin, HIGH);
  
      // take the latchPin low so the LEDs don't change while you're sending in bits:    
      digitalWrite(latchPin2, LOW);
      shiftOut(dataPin2, clockPin2, MSBFIRST, anode_decimal[j]);
      // shift out the bits:  
      digitalWrite(latchPin2, HIGH);
        
      delay(1000);                   
   }
}
