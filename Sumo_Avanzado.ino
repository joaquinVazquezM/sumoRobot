/******************************************************************************/
/*La programación realizada para el minisumo ha sido de carácter básico, 
diseñada para asegurar el funcionamiento adecuado de cada uno de sus componentes. 
Esta base nos permite controlar sus movimientos, sensores y respuestas de manera efectiva, 
pero también deja espacio para futuras mejoras y optimizaciones.

Es importante destacar que el sistema estará en constante actualización. 
A medida que avancemos en nuestra comprensión y experimentación, 
podremos implementar nuevas funciones y optimizar el código existente. 
Esto no solo mejorará el rendimiento del minisumo, sino que también facilitará 
la incorporación de nuevas tecnologías y técnicas que surjan en el campo de la robótica.

En resumen, aunque la programación actual es un buen punto de partida, 
estamos comprometidos con la mejora continua para maximizar el potencial del minisumo y adaptarlo a nuevos desafíos.*/
/******************************************************************************/

#include <HCSR04.h> Libreria Sensor Ultrasonico

HCSR04 hc(9, 8); //Definicion de pines para Ultasonico (trig pin , echo pin)

// Pines para nuestro motor, pulsador y LEDs
const int bPin = 10;     // Definimos PIN de entrada para nuestro pulsador 
const int ledPin =  11;      // Definimos PIN de entrada para nuestro led
int bestado = 1; // Definimos el estado inicial de nuestro boton 
int x=0; // Variable bandera modo de batalla 

//Definicion de pines para control de motores //
int STBY = 12; //PIN de activacion
//Motor A
int PWMA = 6; //PIN de control de velocidad
int AIN1 = 4; //PIN sentido de giro motor a
int AIN2 = 5; //PIN sentido de giro motor a
//Motor B
int PWMB = 7; //PIN de control de velocidad
int BIN1 = 3; //PIN sentido de giro motor b
int BIN2 = 2; //PIN sentido de giro motor b
// Salidas de pines de control
boolean inPin1 = LOW;
boolean inPin2 = LOW;
//Variables para sensores infrarrojos
int s1=0;
int s2=0;
int s3=0;
int s4=0;
//Variables para control de sensores infrarrojos
int fi= 0;
int fd = 0;
int ti= 0;
int td = 0; 
//Variable para intermitencia 
 int y=0;

void setup() {
 Serial.begin(9600); //Frecuencia de comunicacion de arduino NO MODIFICAR
  
  //Configuramos el tipo de salida para nuestro pulsador y nuestro led
  pinMode(ledPin, OUTPUT);
  pinMode(bPin, INPUT_PULLUP);
  
  //Definir como salida los pines del controlador de motores o puente H
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  //Configurar pines del motor como salida en OFF
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  
  // Configurar pines de los sensores infrarrojos
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

}
void loop() {

/*/<-/////////////////////////// Volver como comentario una vez calibrado /////////
 ////Lectura de Sensores para identificar DOJO
 s1= analogRead(A0);
 s2= analogRead(A1);
 s3= analogRead(A2);
 s4= analogRead(A3);
 /////////////Vista de valores///////////////// 
    Serial.print("Sensor 1=");
    Serial.println(s1);
    delay(1000);
    Serial.print("Sensor 2=");
    Serial.println(s2);
    delay(1000);
    Serial.print("Sensor 3=");
    Serial.println(s3);
    delay(1000);
    Serial.print("Sensor 4=");
    Serial.println(s4);
    delay(1000);
//////////////////////////////////////////////////////////////////////////////->*/
  
  //Lectura del estado de nuestro boton para iniciar programacion 
  bestado = digitalRead(bPin);
   
////////////////////Preguntamos si iniciamos la lucha o estamos en espera ///////////////////////////       
if(bestado==LOW){
  if(x==1){
    x=0;
  }else{
  x=x+1;
 for(int i = 0; i<4; i++){
      digitalWrite(ledPin, HIGH);
 delay(100);
    digitalWrite(ledPin, LOW);
     delay(100);} 
   delay(5000);
  }
     
}else{
     Serial.println("En espera");
      Serial.println(hc.dist());
}
///////////////////////////////////////////////////////////////////////////////////////////////////     
  
///////////////Si nuestro boton fue precionado entraremos en la siguiente decision////////////////

if(x == 1){ //Preguntamos si nuestro boton fue precionado para iniciar el combate//

  Serial.println("Buscando oponente");
  digitalWrite(ledPin, HIGH);
  
 ////Lectura de Sensores para identificar DOJO
 s1= analogRead(A0);
 s2= analogRead(A1);
 s3= analogRead(A2);
 s4= analogRead(A3);
/////////Definimos nuestros valores para ajustar nuestro sensores y saber si esta en el dojo//////
//La comparacion dependera de nuestros valores calibrando los sensores en el dojo //
 
if(s1<20){ //Preguntamos si nuestro sensor delantero izquierdo esta dentro del dojo 
  fd = 1;
}else{
  fd=0;
}
if(s2<20){ //Preguntamos si nuestro sensor delantero derecho esta dentro del dojo 
  fi = 1;
}else{
  fi=0;
}
if(s3<20){ //Preguntamos si nuestro sensor trasero derecho esta dentro del dojo 
  td = 1;
}else{
  td=0;
}
if(s4<20){ //Preguntamos si nuestro sensor trasero izquierdo esta dentro del dojo 
  ti = 1;
}else{
  ti=0;
}


 
  if (fi == 1) {  // Sumo lado delantero Izquierdo Dentro de dojo
      if (fd == 1){  // Sumo lado delantero Derecho Dentro de dojo
        if(td==1){  // Sumo lado trasero Derecho Dentro de dojo
          if(ti==1){ // Sumo lado trasero Izquierdo Dentro de dojo
 if (hc.dist()<25){
   //Serial.println(hc.dist());//Presentamos nuestra distancia en el puerto serial Comentar una vez calibrado
  ///Ataque de frente (motres 1 y 2 a maxima potencia de frente ////
move (1, 255, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
move (2, 255, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
 
 Serial.println("Ataquee definido");
 }//Fin pregunta de distancia
 else{// La distancia de nuestro oponente no es mayor a 25
  Serial.println("No hay nadie :(");
   if (y==0){//nuestro numero aleatorio es menor a 5
    y=1;
    Serial.println("Giro Izquierda Busqueda");
     stop();
      move (1, 160, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
      move (2, 160, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
      delay(500);
      stop();
      delay(1000);
   }//Fin de valor aleatorio 
   else{//nuestro numero aleatorio no es menor a 50
    y=2;
              Serial.println("Giro Derecha Busqueda");
              stop();
              move (1, 160, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
              move (2, 160, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
              delay(500);
              stop();
              delay(1000);
            } //Fin pregunta numero aleatorio
      if(y==2){
        y=0;
          Serial.println("PaLante compa");
              stop();
              move (1, 180, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
              move (2, 180, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
              delay(500);
              stop();
              delay(1000);      
      }
 }//Fin pregunta distancia 
          }//Fin lado trasero izquierdo
          else{
            stop();
            move (1, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(200);
            move (1, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(500); 
            stop();         
            }//Fin lado trasero izquierdo movimiento
        }//Fin lado trasero derecho
                  else{
            stop();
            move (1, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(200);
            move (1, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(500); 
            stop();  
            }//Fin lado trasero derecho movimiento
      }//Fin lado delantero derecho
            else{
            stop();
            move (1, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(200);
            move (1, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(500); 
            stop();  
            }//Fin lado delantero derecho movimiento
       }//Fin lado delantero izquierdo
           else{
            stop();
            move (1, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(200);
            move (1, 200, 2); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            move (2, 200, 1); //Ingreso de variables para la funcion de control de motore (Motor,Velocidad,sentido de giro)
            delay(500); 
            stop();  
            }  //Fin lado delantero izquierdo  movimiento
            }else{
    digitalWrite(ledPin, HIGH);
 delay(500);
    digitalWrite(ledPin, LOW);
     delay(500);
     stop(); 
}  
}



void move(int motor, int speed, int direction){ //Funcion de conttol de motores //////
digitalWrite(STBY, HIGH); 

if(direction == 1){ //Preguntamos si nuestra direccion va a la derecha
inPin1 = HIGH;
inPin2 = LOW;
}else{              //Al no ser asi giramos a la izquierda
inPin1 = LOW;
inPin2 = HIGH;
}

if(motor == 1){    //Preguntamos si la orden es para nuestro motor 1
digitalWrite(AIN1, inPin1);
digitalWrite(AIN2, inPin2);
analogWrite(PWMA, speed);
}else{             //Al no ser asi mandamos la orden para motor 2
digitalWrite(BIN1, inPin1);
digitalWrite(BIN2, inPin2);
analogWrite(PWMB, speed);
}

}

 

void stop(){      //En esta funcion detenemos nuestro controlador para evitar el giro de cualquier motor
digitalWrite(STBY, LOW);
}
