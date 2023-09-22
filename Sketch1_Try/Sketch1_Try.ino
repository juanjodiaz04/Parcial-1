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
void patt_print(int latchPin,int dataPin,int clockPin,int a, int b);
void off();

  
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
  
  int **pr; int a = 6;
  pr = (new int* [2]); //Filas
  
  pr[0] = new int [4]; pr[1] = new int [4]; //Reservar columnas
  
  pr[0][0] = 126; //Semilla para el register shifter de los cátodos
  pr[1][0] = 24;  //Semilla para el register shifter de los ánodos
  
  
  for (int j = 1; j<4 ;j++) //Llenar el array de las otras semillas
  {
    pr[0][j] = pr[0][j-1] + (ceil(pow(2,a)))-(ceil(pow(2,6-a))); //Forma 2**n - 2**a → n+a = 6
    pr[1][j] = pr[1][j-1] + (ceil(pow(2,j+4))) + (ceil(pow(2,7-(j+4)))); //Forma 2**n + 2**a → n+a = 7 
    a--;
   }
  
  	while(millis() - inicio <= dur){
      for (int i = 0; i <4; i++){
        patt_print(latchPin, dataPin ,clockPin, pr[0][i], pr[1][i]);
      }
      
	    
    }
  off();
  
  delete [] pr[0]; delete [] pr[1];  //Liberación de memoria
  delete [] pr;
  pr = NULL;

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
  
  while (millis() - inicio <= dur) {
  
    for (int i = 0; i < 8; i++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, led_array[i]);
      digitalWrite(latchPin, HIGH);
      digitalWrite(latchPin, LOW);
    }
  }

  delete[] led_array; // Liberar la memoria dinámica cuando ya no se necesita
}

void alt_patt(unsigned long dur, unsigned long inicio) {

  byte* led_array = new byte[6];
  
  led_array[0] = 0B00110011;
  led_array[1] = 0B10110110;
  led_array[2] = 0B11001100;
  led_array[3] = 0B11011011;
  led_array[4] = 0B11111111;
  led_array[5] = 0B00000000;
  
  while (millis() - inicio <= dur) {
  
    for (int i = 0; i < 6; i++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, led_array[i]);
      digitalWrite(latchPin, HIGH);
      digitalWrite(latchPin, LOW);
    }
  }

  delete[] led_array; // Liberar la memoria dinámica cuando ya no se necesita
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

