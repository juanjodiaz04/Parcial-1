// C++ code
//
int latchPin=11;
int clockPin=12;
int dataPin=9;

//Funciones
void verificacion();
void X_patt();
void rect_patt();
void alt_patt();
void arr_patt();

  
void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:

  verificacion();
  //rect_patt();
  //X_patt();
  //alt_patt();
  //arr_patt();

}

void verificacion(){
  
  for (int i = 0; i < 5; i++){
    
    shiftOut(dataPin,clockPin,MSBFIRST,0B00000000); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B11111111); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
    delay(3000);
    
    shiftOut(dataPin,clockPin,MSBFIRST,0B11111111); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00000000);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
    delay(3000);
  }
}

void rect_patt(){
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11100111); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B10000001); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11000011); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B01000010); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B00000000); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00011000); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
  	shiftOut(dataPin,clockPin,MSBFIRST,0B10000001); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00100100); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);

}

void X_patt(){
  
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,0B01111110); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B10000001); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B10111101); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B01000010); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11011011); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00100100); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11100111); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00011000); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
}

void alt_patt(){
    shiftOut(dataPin,clockPin,MSBFIRST,0B00110011); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B01101101); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11001100); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B11011011); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
}

void arr_patt(){
  
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,0B01111110); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B11110000); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B10111101); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B01111000); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11011011); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00111100); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  
    shiftOut(dataPin,clockPin,MSBFIRST,0B11100111); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00011110); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
}
