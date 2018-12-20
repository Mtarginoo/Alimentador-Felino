//Programa: Sistema de Registro do horário da alimentação das gatas
//Autor: Matheus Targino Barbosa
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <DS1307.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

DS1307 rtc(A5, A4);
//Define os pinos que serão usados para controle do sistema
#define btn1 10
#define btn2 9
#define btn3 8
#define btnEnter 7
#define btnCorrige 6
//#define ledred A5

//Declarando as variáveis a serem usados no programa
bool b1 = false, b2 = false, b3 = false;
 
void setup()
{
  rtc.halt(false);

  
  
  rtc.setDOW(MONDAY);      //Define o dia da semana
  rtc.setTime(17, 50, 0);     //Define o horario
  rtc.setDate(17, 12, 2018);  //Define o dia, mes e ano
  lcd.begin(16, 2);
  
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(A5, OUTPUT);

  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  Serial.begin(9600); 
  
}
 
void loop()
{ 
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Aperte 1, 2 ou 3");
  Serial.println("Estou aqui 1");
  Serial.println(b1);
  Serial.println(b2);
  Serial.println(b3);
  digitalWrite(btn1, LOW);
  b1 = false;
  delay(1000);
  
  if(digitalRead(btn1) == HIGH){
    b1 = true;
  }
  else if(digitalRead(btn2) == HIGH && digitalRead(btn1) == LOW && digitalRead(btn3) == LOW){
    b2 = true;
  }
  else if(digitalRead(btn3) == HIGH && digitalRead(btn2) == LOW && digitalRead(btn1) == LOW){
    b3 = true;
  }
       while(b1 == true ){
        Serial.println("Estou aqui 2");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Salvar Mia?");
        delay(1000);
          if(digitalRead(btnEnter) == HIGH){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Horario Mia");
            lcd.setCursor(0,1);
            lcd.print("Salvando...");
            Serial.print("Hora : ");
            Serial.print(rtc.getTimeStr());
            delay(1000);
            Serial.print(" ");
            delay(2000);
            b1 = false;
            digitalWrite(btnEnter, LOW);
           
          }
         else if(digitalRead(btnCorrige) == HIGH){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Corrigindo...");
          Serial.print("Corrigindo...");
          b1 = false;
          digitalWrite(btnCorrige, LOW);
         }
         
      }
 
 
   while(b2 == true){
      Serial.println("Estou aqui 3");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Salvar Ada?");
      delay(1000);
      if(digitalRead(btnEnter) == HIGH){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Horario Ada");
        lcd.setCursor(0,1);
        lcd.print("Salvando...");
        Serial.print("Hora : ");
        Serial.print(rtc.getTimeStr());
        delay(1000);
        Serial.print(" ");
        delay(2000);
        b2 = false;
      }
      else if(digitalRead(btnCorrige) == HIGH){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Corrigindo...");
        Serial.println("Corrigindo...");
        b2 = false;
      }
    }
  
  delay(1000);
  
}
