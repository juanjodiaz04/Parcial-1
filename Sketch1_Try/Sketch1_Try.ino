//C++ code
//
int latchPin=11; //Pin de Latch
int clockPin=12; //Pin del Reloj	
int dataPin=9;	//Pin de datos

char receivedChar; //Para almacenar el valor del puerto serial

unsigned long durat = 3000;
unsigned long timestart;


//Funciones
void verificacion();
void X_patt();
void rect_patt();
void alt_patt();
void arr_patt();

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  
  Serial.println("Escoge la opcion");
}
void loop() {
  // put your main code here, to run repeatedly:

  //verificacion();
  //rect_patt();
  //X_patt();
  //alt_patt();
  //arr_patt();

 if (Serial.available() > 0) {  
    	receivedChar = Serial.read();
   
   		if (receivedChar == 'A'){
     		Serial.println("Verificacion");
        	timestart = millis();
          	Serial.print("Tiempo de inicio: ");
          	Serial.println(timestart);
     		verificacion(3, 2000); //Iteraciones y tiempo de delay
   		}
   		else if(receivedChar == 'B'){
     		Serial.println("Patron 1");
        	timestart = millis();
          	Serial.print("Tiempo de inicio: ");
          	Serial.println(timestart);
     		rect_patt(durat, timestart); //Duración del patrón y tiempo al que empieza
        }
   		else if(receivedChar == 'C'){
     		Serial.println("Patron 2");
        	timestart = millis();
          	Serial.print("Tiempo de inicio: ");
          	Serial.println(timestart);
     		X_patt(durat, timestart); //Duración del patrón y tiempo al que empieza
        }
   		else if(receivedChar == 'D'){
     		Serial.println("Patron 3");
        	timestart = millis();
          	Serial.print("Tiempo de inicio: ");
          	Serial.println(timestart);
     		alt_patt(durat, timestart); //Duración del patrón y tiempo al que empieza
        }
   		else if(receivedChar == 'E'){
     		Serial.println("Patron 4");
        	timestart = millis();
          	Serial.print("Tiempo de inicio: ");
          	Serial.println(timestart);
     		arr_patt(durat, timestart); //Duración del patrón y tiempo al que empieza
        }
   		else {
   		}
   
 } //Cierre if puerto serial
  
} //Cierre void loop

void verificacion(int iter , int delays){
  
  for (int i = 0; i < iter; i++){
    
    shiftOut(dataPin,clockPin,MSBFIRST,0B00000000); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B11111111); 
  	digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
    delay(delays);
    
    shiftOut(dataPin,clockPin,MSBFIRST,0B11111111); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00000000);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
    delay(delays);
  }
}

void rect_patt(unsigned long dur , unsigned long inicio){
  	
  	while(millis() - inicio <= dur){
      
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

      shiftOut(dataPin,clockPin,MSBFIRST,0B11111111); 
      shiftOut(dataPin,clockPin,MSBFIRST,0B00000000);
      digitalWrite(latchPin,HIGH);
      digitalWrite(latchPin,LOW);
 
    }

}

void X_patt(unsigned long dur, unsigned long inicio) {
  
  byte* led_array = new byte[8];
  
  led_array[0] = 0B01111110;
  led_array[1] = 0B10000001;
  led_array[2] = 0B10111101;
  led_array[3] = 0B01000010;
  led_array[4] = 0B11011011;
  led_array[5] = 0B00100100;
  led_array[6] = 0B11100111;
  led_array[7] = 0B00011000;
  
  while(millis() - inicio <= dur){
   
    for(int i = 0; i < 8; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,led_array[i]); 
      digitalWrite(latchPin,HIGH);
      digitalWrite(latchPin,LOW);
    }
  
  }
}

void alt_patt(unsigned long dur, unsigned long inicio) {

  byte* led_array = new byte[6];
  
  led_array[0] = 0B00110011;
  led_array[1] = 0B10110110;
  led_array[2] = 0B11001100;
  led_array[3] = 0B11011011;
  led_array[4] = 0B11111111;
  led_array[5] = 0B00000000;
  
  while(millis() - inicio <= dur){
  
    for(int i = 0; i < 6; i++){
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,led_array[i]); 
      digitalWrite(latchPin,HIGH);
      digitalWrite(latchPin,LOW);
    }
    
  }
}

void arr_patt(unsigned long dur , unsigned long inicio){
  
  while(millis() - inicio <= dur){
  
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
  
  	shiftOut(dataPin,clockPin,MSBFIRST,0B11111111); 
    shiftOut(dataPin,clockPin,MSBFIRST,0B00000000);
    digitalWrite(latchPin,HIGH);
    digitalWrite(latchPin,LOW);
  }
}

  // Codigo para seleccionar opciones y que se ejecuten hasta que la entrada del puerto serial cambie
  /*
   if (Serial.available() > 0) {  
    receivedChar = Serial.read();
    
    if (receivedChar == 'A') { 
      while (receivedChar == 'A') {
        rect_patt();
        if (Serial.available() > 0) {
          receivedChar = Serial.read();
        }
      }
    }
    else if (receivedChar == 'B') { 
      while (receivedChar == 'B') {
        X_patt();
        if (Serial.available() > 0) {
          receivedChar = Serial.read();
        }
      }
    }
    else if (receivedChar == 'C') { 
      while (receivedChar == 'C') {
        alt_patt();
        if (Serial.available() > 0) {
          receivedChar = Serial.read();
        }
      }
    }
    else if (receivedChar == 'D') { 
      while (receivedChar == 'D') {
        arr_patt();
        if (Serial.available() > 0) {
          receivedChar = Serial.read();
        }
      }
    }
  }
  */

