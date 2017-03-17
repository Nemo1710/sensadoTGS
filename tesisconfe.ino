//Inicializar variables
float tgs822_superior=0;
float tgs822_inferior=0;
float tgs2610_superior=0;
float tgs2610_inferior=0;
int bomba=13;
int j=0;
int i=10;
int reset=4;
int electrovalvula1=12;
int electrovalvula2=11;
unsigned long previo = 0;
unsigned long previo1 = 0;
unsigned long previo2 = 0;
unsigned long previo3 = 0;


void setup() {
  digitalWrite(reset,HIGH);
  Serial.begin(115200);  
  pinMode(reset,OUTPUT);
  
  pinMode(bomba,OUTPUT);
  pinMode(electrovalvula1,OUTPUT);
  pinMode(electrovalvula2,OUTPUT);
  digitalWrite(bomba,HIGH);
  digitalWrite(electrovalvula1,LOW);
  digitalWrite(electrovalvula2,HIGH);
  delay(5000);
  
}

void loop() {
  unsigned long actual = millis();
  if (Serial.available()){
    int var=Serial.read();
    if(var==97){
      Serial.println("siii");
      digitalWrite(reset,LOW);
    }
    if(var==98){
      Serial.println("si");
      previo3=actual;      
      //delay(1000);
      i=3;
    }
  }

  //tiempo de muestreo a 50ms : 20 muestras por segundo
  if(actual-previo1>=50){
                   
  tgs822_superior=analogRead(A4);
  tgs822_inferior=analogRead(A2);  
  tgs2610_superior=analogRead(A3);
  tgs2610_inferior=analogRead(A1);

  //S4
  tgs822_superior = (5.0 * tgs822_superior )/1024.0; 
  //S2
  tgs822_inferior = (5.0 * tgs822_inferior )/1024.0; 
  //S3
  tgs2610_superior = (5.0 * tgs2610_superior )/1024.0; 
  //S1
  tgs2610_inferior = (5.0 * tgs2610_inferior )/1024.0; 
  
  Serial.print(tgs2610_inferior);
  Serial.print(",");
  Serial.print(tgs822_inferior);
  Serial.print(",");
  Serial.print(tgs2610_superior);
  Serial.print(",");
  Serial.println(tgs822_superior);
  previo1=actual;   
        }
        
//Tiempo respiracion
  switch(i){
    case 3:
        //Serial.println("no enctri");
        
        
        if(actual-previo3>=(2000)){
          i=0;
          
          previo2=actual;   
        }
//Tiempo limpieza       
    break;
    case 0:
        //Serial.println("no enctri");
        
        digitalWrite(electrovalvula1,HIGH);
        digitalWrite(electrovalvula2,LOW);
        if(actual-previo2>=(10+1000)){
          i++;
          
          previo=actual;   
        }
//Tiempo limpieza       
    break;
    case 1:
    
        //Serial.println("no enctri");
        digitalWrite(electrovalvula1,LOW);
        digitalWrite(electrovalvula2,HIGH);
        //digitalWrite(electrovalvula1,HIGH);
        if(actual-previo>=30000){
          i=0;
          
          previo2=actual;   
        }
    
    break;  
    
  }
  
/*  //delay(500);
  if(actual-previo>=500){
      
      Serial.println("Millis");
      if(digitalRead(electrovalvula1)==HIGH){
        Serial.println("bajo");
        //digitalWrite(bomba,LOW);
        digitalWrite(electrovalvula1,LOW);
      }else {
        Serial.println("alto");
        //digitalWrite(bomba,HIGH);
        digitalWrite(electrovalvula1,HIGH);
      }
      
      previo=actual;  
   }*/
  
}
