// C++ code
//

#include <math.h>

int latchPin=11; //Pin de Latch
int clockPin=12; //Pin del Reloj	
int dataPin=9;	//Pin de datos

char receivedChar; //Para almacenar el valor del puerto serial

unsigned long durat = 3000;
unsigned long timestart;


//Funciones
void verificacion(int iter , int delays);
void imagen(unsigned long dur);
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

void verificacion(int iter , int delays){ //
  
  for (int i = 0; i < iter; i++){
    
    patt_print(latchPin, dataPin ,clockPin, 0, 255);
    delay(delays);
    
    off();
    delay(delays);
  }
}

void imagen(unsigned long dur) {
  
  //Recolección de datos
  int *im;
  im = new int [8]; // Array para almacenar los 8 valores decimales

  //Almacenar las cadenas de 8 bits como numeros enteros
  for (int j = 0; j < 8; j++) {
    Serial.print("Ingrese una linea de 8 numeros con 0 para apagado y 1 para encendido en la fila ");
    Serial.print(j);
    Serial.println(": ");
    
    while (Serial.available() < 8) {
      // Espera hasta que se reciban 8 caracteres
    }

    // Leer los 8 caracteres y convertirlos a un valor decimal
    int valorDecimal = 0;
    for (int i = 0; i < 8; i++) {
      char caracter = (char)Serial.read();
      valorDecimal = valorDecimal * 2 + (caracter - '0');
    }
    
    // Almacenar el valor decimal en el array
    im[j] = valorDecimal;
    
    Serial.println(im[j]);
  }
  
  //Valor para los cátodos
  int *cat;
  cat = new int [8];
  
  for (int j = 0; j <8 ; j++)
  {
    if (im[j] != 0) //Solo enciende las lineas cuyo valor entero es diferente de 0
    {
      cat[j] = 255-(ceil(pow(2,7-j))); 
    }
      else
      {
        cat[j] = 255;
        Serial.println(cat[j]);
      }
  }
  
  unsigned long inicio = millis();
  while(millis() - inicio <= dur){
    
    for(int k = 0; k<8; k++){
      
      patt_print(latchPin, dataPin ,clockPin, cat[k], im[k]);
      off();
    }
    
  }
  
  delete [] im; //Liberar memoria
  im = NULL;
  
  delete [] cat; //Liberar memoria
  cat = NULL;
    
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


void X_patt(unsigned long dur, unsigned long inicio){
  
  int *p; int a = 6;
  p = new int [4];
  
  p[0] = 126;  //0B01111110 → 126 Byte semilla para el register shifter de los cátodos
  
  for (int j = 1; j<4 ;j++) //Llenar el array de las otras semillas
  {
    p[j] = p[j-1] + (ceil(pow(2,a)))-(ceil(pow(2,6-a))); //Forma 2**n - 2**a → n+a = 6
    a--;
   }
    
  while (millis() - inicio <= dur) {
    for (int i = 0; i <4; i++){
      patt_print(latchPin, dataPin ,clockPin, p[i], 255-p[i]);
    }
    
  }
  
  off(); //Apaga los leds al final 
  
  delete [] p; //Liberar memoria
  p = NULL;
}



void alt_patt(unsigned long dur, unsigned long inicio) { 
  
  /* La solución trivial en este caso ahorra código enormemente*/

  while (millis() - inicio <= dur) {
    patt_print(latchPin, dataPin ,clockPin, 51, 219); //0B00110011,0B11011011)
  	patt_print(latchPin, dataPin ,clockPin, 204, 109); //0B11001100,0B01101101)
  	off();
  }

}

void arr_patt(unsigned long dur , unsigned long inicio){
  
  
  int **pa; int a = 6;
  pa = (new int* [2]); //Filas
  
  pa[0] = new int [4]; pa[1] = new int [4]; //Reservar columnas
  
  pa[0][0] = 126; //Semilla para el register shifter de los cátodos
  pa[1][0] = 240;  //Semilla para el register shifter de los ánodos
  
  
  for (int j = 1; j<4 ;j++) //Llenar el array de las otras semillas
  {
    pa[0][j] = pa[0][j-1] + (ceil(pow(2,a)))-(ceil(pow(2,6-a))); //Forma 2**n - 2**a → n+a = 6
    pa[1][j] = pa[1][j-1] - (ceil(pow(2,8-j))) + (ceil(pow(2,4-j))); //Suma un bit a la derecha y resta un bit a la izquierda
    a--;
   }
  
  	while(millis() - inicio <= dur){
      for (int i = 0; i <4; i++){
        patt_print(latchPin, dataPin ,clockPin, pa[0][i], pa[1][i]);
      }
      
	    
    }
  off();
  
  delete [] pa[0]; delete [] pa[1];  //Liberación de memoria
  delete [] pa;
  pa = NULL;
  
}


void off(){
  patt_print(latchPin, dataPin ,clockPin, 255, 0);
}

void patt_print(int latchPin,int dataPin,int clockPin,int a, int b){
  
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,a); 
    shiftOut(dataPin,clockPin,MSBFIRST,b);
    digitalWrite(latchPin,HIGH);
  
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

