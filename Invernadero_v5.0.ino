/*Invernadero inteligente 

_______________________________________________________________________________
HUMEDAD:

  000-300 Superficie seca
  300-500 Superficie humeda
  500-750 Superficie mojada 

  65% = 487.5
  70% = 525


LUMINOSIDAD

  00-20     Noche
  20-1024   Dia
________________________________________________________________________________ */

int humedad;
int timeBombeo=500;       //Tiempo que dura encendida la bomba
int Bomba=2;
int LED=3;
int Vent=4;
int temp;
int estado='e'; 
int iluminacion;
int sensorPin=A1;
int lightLevel=A0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Bomba, OUTPUT);
  pinMode (lightLevel, INPUT);
  pinMode (sensorPin, INPUT);
}

void loop() {
  if(Serial.available()>0){
    estado=Serial.read();
    digitalWrite(13, HIGH);
    delay(200);
    }else{
      digitalWrite(13, LOW);
      }
  if(estado=='a'){
    digitalWrite(LED, HIGH);
    }
  if(estado=='b'){
    digitalWrite(LED, LOW);
    }
  if(estado=='c'){
    digitalWrite(Bomba, HIGH);
    delay(timeBombeo);
    }
  if(estado=='d'){
    digitalWrite(Bomba, LOW);
    delay(timeBombeo);
    }

    
  if(estado=='f'){
    digitalWrite(Vent, HIGH);
    }
  if(estado=='g'){
    digitalWrite(Vent, LOW);
    }
    
  if(estado=='e'){
    /*______________________________ Humedad ___________________________________________________*/

    humedad=analogRead(sensorPin);
    if(humedad<487){
      digitalWrite(Bomba, HIGH);
      delay(timeBombeo);
               
      if(humedad>525){
        digitalWrite(Bomba, LOW);
        } else{
          delay(timeBombeo);
          digitalWrite(Bomba, LOW);
          }
      }else{
        digitalWrite(Bomba, LOW);
        delay(timeBombeo); 
        }

        
    /*_________________________________ Iluminaci�n ________________________________________________________________*/
        
        
        iluminacion=analogRead(lightLevel);
        if(iluminacion < 20){              
          digitalWrite(LED, HIGH);
          } else{
            digitalWrite(LED, LOW);
            }
   /*______________________________________Temperatura________________________________________________________________*/

      temp=analogRead(A2) / 10;
      if(temp>20){        //Generar un codigo que diga que hacer si esta por debajo de los 15 grados celsius
          digitalWrite(Vent, HIGH);
          } else{
            digitalWrite(Vent, LOW);
        }

   
    /*______________________________________________________________________________________________________*/
        Serial.print("Temperatura = ");
        Serial.print(temp);
        Serial.println("�C");
      

        
        Serial.print("Humedad= ");
        Serial.println(humedad);
        
        Serial.print("Iluminaci�n= ");
        Serial.println(iluminacion);
        Serial.print(" ");
        Serial.print("_____________________ ");
  
    }
}
