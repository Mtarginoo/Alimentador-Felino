//Programa: Sistema de Registro do horário da alimentação das gatas
//Autor: Matheus Targino Barbosa

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <DS1307.h>
#include <Wire.h>

#define DS1307_ADDRESS 0x68

byte zero = 0x00;

int minute;
int Hour;
int dayWeek;
int day;
int month;
int Year;

int lastDiaMia, lastMesMia, lastAnoMia, lastMinutoMia, lastHoraMia;
int lastDiaAda, lastMesAda, lastAnoAda, lastMinutoAda, lastHoraAda;


//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//DS1307 rtc(A5, A4);

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

  Wire.begin();
  setDateTime();

  lcd.begin(16, 2);

  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(A5, OUTPUT);

  //Definicoes do pino SQW/Out
  // rtc.setSQWRate(SQW_RATE_1);
  //rtc.enableSQW(true);
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
  digitalWrite(btn1, LOW);
  b1 = false;
  delay(1000);

  if (digitalRead(btn1) == HIGH && digitalRead(btn2) == LOW && digitalRead(btn3) == LOW) {
    b1 = true;
    Serial.println("Botao 1 apertado");
  }
  else if (digitalRead(btn2) == HIGH && digitalRead(btn1) == LOW && digitalRead(btn3) == LOW) {
    b2 = true;
    Serial.println("Botao 2 apertado");
  }
  else if (digitalRead(btn3) == HIGH && digitalRead(btn2) == LOW && digitalRead(btn1) == LOW) {
    b3 = true;
  }
  while (b1 == true ) {
    Serial.println("Estou aqui 2");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Salvar Mia?");
    delay(1000);
    if (digitalRead(btnEnter) == HIGH && digitalRead(btnCorrige) == LOW) {
      Serial.println("Botao enter apertado");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Salvando...");
      // Serial.print("Hora : ");
      // Serial.print(rtc.getTimeStr());
      printDate();
      salvaHoraMia();
      delay(1000);
      Serial.print(" ");
      delay(2000);
      b1 = false;
      //digitalWrite(btnEnter, LOW);

    }
    else if (digitalRead(btnCorrige) == HIGH && digitalRead(btnEnter) == LOW) {
      Serial.println("Botao corrige apertado");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Corrigindo...");
      Serial.print("Corrigindo...");
      b1 = false;
      //digitalWrite(btnCorrige, LOW);
    }

  }


  while (b2 == true) {
    Serial.println("Estou aqui 3");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Salvar Ada?");
    delay(1000);
    if (digitalRead(btnEnter) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Horario Ada");
      lcd.setCursor(0, 1);
      lcd.print("Salvando...");
      printDate();
      salvaHoraAda();
      delay(1000);
      Serial.print(" ");
      delay(2000);
      b2 = false;
    }
    else if (digitalRead(btnCorrige) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Corrigindo...");
      Serial.println("Corrigindo...");
      b2 = false;
    }
  }

  while (b3 == true) {

    bool c1 = false, c2 = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1: Horario Mia");
    lcd.setCursor(0, 1);
    lcd.print("2: Horario Ada");
    delay(1000);
    if (digitalRead(btn1) == HIGH && digitalRead(btn2) == LOW && digitalRead(btn3) == LOW) {
      c1 = true;
    }
    else if (digitalRead(btn2) == HIGH && digitalRead(btn1) == LOW && digitalRead(btn3) == LOW) {
      c2 = true;
    }


   while(c1 == true){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Horario Mia?");
    delay(1000);
    if (digitalRead(btnEnter) == HIGH && digitalRead(btnCorrige) == LOW) {
      printLastMia();
      delay(5000);
      b3 = false;
      c1 = false;
   }
    else if (digitalRead(btnCorrige) == HIGH && digitalRead(btnEnter) == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Corrigindo...");
      b3 = false;
      c1 = false;
    }
    delay(1000);
   }

   while(c2 == true){
   lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Horario Ada?");
    delay(1000);
    if (digitalRead(btnEnter) == HIGH && digitalRead(btnCorrige) == LOW) {
      printLastAda();
      delay(5000);
      b3 = false;
      c2 = false;
   }
    else if (digitalRead(btnCorrige) == HIGH && digitalRead(btnEnter) == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Corrigindo...");
      b3 = false;
      c2 = false;
    }
    delay(1000);
   }
  }
  delay(1000);

}

void setDateTime() {

  byte segundo =      00;  //0-59
  byte minuto =        14;  //0-59
  byte hora =           23;  //0-23
  byte diasemana =    5;  //1-7
  byte dia =               20;  //1-31
  byte mes =            12; //1-12
  byte ano  =            18; //0-99

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);

  Wire.write(decToBcd(segundo));
  Wire.write(decToBcd(minuto));
  Wire.write(decToBcd(hora));
  Wire.write(decToBcd(diasemana));
  Wire.write(decToBcd(dia));
  Wire.write(decToBcd(mes));
  Wire.write(decToBcd(ano));

  Wire.write(zero);

  Wire.endTransmission();

}

byte decToBcd(byte val) {
  // Conversão de decimal para binário
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val)  {
  // Conversão de binário para decimal
  return ( (val / 16 * 10) + (val % 16) );
}

void printDate() {

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemana = bcdToDec(Wire.read());             //0-6 -> Domingo - Sábado
  int dia = bcdToDec(Wire.read());
  int mes = bcdToDec(Wire.read());
  int ano = bcdToDec(Wire.read());

  minute = minuto;
  Hour = hora;
  dayWeek = diasemana;
  day = dia;
  month = mes;
  Year = ano;

  //Exibe a data e hora. Ex.:   3/12/13 19:00:00

  lcd.setCursor(0, 1);
  lcd.print(dia);
  lcd.print("/");
  lcd.print(mes);
  lcd.print("/");
  lcd.print(ano);
  lcd.print(" ");
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minuto);
  lcd.print(":");
  lcd.println(segundo);

}

void salvaHoraMia() {
  lastMinutoMia = minute;
  lastHoraMia = Hour;
  lastDiaMia = day;
  lastMesMia = month;
  lastAnoMia = Year;
}

void salvaHoraAda() {
  lastMinutoAda = minute;
  lastHoraAda = Hour;
  lastDiaAda = day;
  lastMesAda = month;
  lastAnoAda = Year;
}

void printLastMia() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lastDiaMia);
  lcd.print("/");
  lcd.print(lastMesMia);
  lcd.print("/");
  lcd.print(lastAnoMia);
  lcd.print(" ");
  lcd.print(lastHoraMia);
  lcd.print(":");
  lcd.print(lastMinutoMia);
 
}

void printLastAda() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lastDiaAda);
  lcd.print("/");
  lcd.print(lastMesAda);
  lcd.print("/");
  lcd.print(lastAnoAda);
  lcd.print(" ");
  lcd.print(lastHoraAda);
  lcd.print(":");
  lcd.print(lastMinutoAda);
  
}



