/*CODIGO PARA UN ZUMOBOT AUTONOMO USANDO ARDUINO Y HARDWARE LIBRE

CREADO POR DEYBYSTIVEN GARCIA MONTES & IVAN JOSE DIAZ MORALES
estudiantes de ingenieria de sistemas de la universidad de cordoba Colombia sede Monteria

REQUERIMIENTOS

  *Kit Sumo from Pololu
  http://www.pololu.com/product/2509
  
  *Sensor de Reflectancia from Pololu
  http://www.pololu.com/product/1419
  
  *Arduino Leonardo o Arduino uno R3
  
  * Librerias 
  https://github.com/pololu/zumo-shield
  https://github.com/ivajo26/Ultrasonido-HC-SR06
  
  *Sensor de ultrasonido 
  http://didacticaselectronicas.com/index.php?page=shop.product_details&flypage=flypage.tpl&product_id=1244&category_id=45&option=com_virtuemart&Itemid=141
  
*/

// Incluimos las librerias necesarias
#include <Ultrasonido.h>
#include <Pushbutton.h>
#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>

//Declaramos los pines de Trigger y Echo
Ultrasonido Sensor=Ultrasonido(2,3);

//creamos un objeto de tipo ZumoMotors
ZumoMotors motores;
#define QTR_THRESHOLD 1500

//Definimos una matriz de 6 posisciones
#define matriz_sensores 6

//asignamos la matriz a una variable VALORES
unsigned int valores[matriz_sensores];

//Declaramos el arreglo sensor de reflectancia
ZumoReflectanceSensorArray sensores(QTR_NO_EMITTER_PIN);

// Definimos el el pin del boton
Pushbutton boton(ZUMO_BUTTON);
int inicio=0;
int distancia;
void setup()
{
  //Se invierte la polaridad del motor derecho esto es opcional solo cuestiones de armado
motores.flipRightMotor(true);
}
void loop()
{
  // preguntamos si el boton esta presionado
  if(boton.isPressed()){
    
    // retraso de 5 segundos
    delay(5000);
  inicio=1;
  }
  
  // Si el boton esta precionado
  if(inicio==1){
    // se leen los valores de la matriz del sensor de reflectancia
  sensores.read(valores);
  
  // si los valores detenctados por el arrglo en la posicion 0 y 5 estan entre < 0 y < 800
  // siginifica que esta detenctando una linea blanca
  if (valores[0]<=800 || valores[5]<=800)
  {
    // Si los valores de la posicion 0 del arreglo es menor a la de la posicion 5
    // significa que se detecto una linea blanca la posicion 0 por tanto se retrocede girando hacia el lado contrario
    if (valores[0]<valores[5])
    {
      motores.setSpeeds(-400,-200);
    }
    else{
      // el sensor el la posicio 5 detecto la linea blanca asi que se retrocede girando hacia el lado contrario del sensor en la posicion 5
    motores.setSpeeds(-200,-400);
    }
    delay(700);
  }
  else{
  distancia= Sensor.Distancia();
    
    // si la distancia registrada es menor a 120cm
    // significa que hay un obstaculo
    if(distancia<=120){
      //motores hacia adelante
      motores.setSpeeds(400,400);
    }
    else{
      // no ha encontrado ningun obstaculo 
      // el robot gira sobre su propio eje para buscar
    motores.setSpeeds(400,-400);
    }
  }
  }
}
  
  
  
    
    
  






