
// SKETCH: MSA (MECANISMO DE SENSORIAMENTO AUTOMÁTICO)
//  O projeto MSA foi desenvolvido e pensado no intuito de melhora em processos na indústria e do bem estar do indivíduo em seu dia-a-dia, utilizando os sensores de obstáculos: infravermelho e ultrassônico, com um auxílio de um Display LED.  

#include <LiquidCrystal.h>
#include <Servo.h>
//#include <HCSR04.h>

LiquidCrystal lcd (7,6,5,4,3,2);
Servo serv;
 
//#define p_trigger 9 
//#define p_echo 8
// UltraSonicDistanceSensor distanceSensor(p_trigger, p_echo);  

float distancia, dis[] = {}, meupos, menorDistancia = 0,d=0;
float menordist = 400.0;  
int sensor = 10;
int pos = 0, cont;

// tinkercad---------------
int trig = 9;
int echo = 8;
//----------------------

void setup() {

 lcd.begin (16,2);  //indicando quantas colunas e linhas o lcd possúi 
 lcd.clear ();  //limpando lcd de um possível resquicio 

  //PARA O TINKER------------------------------------------------------
   pinMode (trig,OUTPUT);
   pinMode (echo,INPUT);
  //----------------------------------------------------------
  
 pinMode (sensor,INPUT);
 serv.attach(11);
 Serial.begin(9600);

}

void loop() {

int estado;
estado = digitalRead(sensor);

if (estado == 0) {
 lcd.clear ();
 lcd.setCursor(2,0);
 lcd.print("VARREDURA DE");
 lcd.setCursor(4,1);
 lcd.print("AMBIENTE");
 
//varredura do servomotor
  for (cont = 0; cont<1; cont++){
   
    for (pos = 0; pos <= 180; pos += 5)  { 

  serv.write(pos);              
  delay(5);

  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
 

  distancia = pulseIn (echo, HIGH);
  distancia = distancia/58;
  Serial.println (distancia);
  
   //Verificar a menor distância, desprezando leituras inválidas
if ((distancia > 0) && (distancia < 400) && (distancia < menordist)) {
 menordist = distancia;


    }
    }
    delay(500);
    lcd.noDisplay();
    delay(500); 
    lcd.display();
    
  for (pos = 180; pos >= 0; pos -= 1) { 
    serv.write(pos);              
    delay(5);                  
    }
    
    lcd.noDisplay();
    delay(500); 
    lcd.display();
    } 
 
  lcd.clear ();
  lcd.setCursor(0,0);
  lcd.print("OB. LOCALIZADO");
  lcd.setCursor(0,1);
  lcd.print("DIST: ");
  lcd.setCursor(7,1);
  lcd.print(menordist);
  lcd.setCursor(12,1);
  lcd.print("cm");

Serial.print("[2J");    // comando para limpar a tela
   
}
}

