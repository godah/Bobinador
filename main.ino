#include <LiquidCrystal.h>

//Tela
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Sensor
int sens = 8;
long count = 0;
int detect = 0;
int button =  9;
boolean flag = 0;
long nowMillis = millis();
long lastMillis = millis();
long lastCount = 0;

void setup() {
  lcd.begin(16,2);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sens, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  showGreetings();
}

void loop() {
  if (digitalRead(button) == HIGH) {
    resetCounter();
  }

  detect = digitalRead(sens);
  if (detect) flag = 1;

  if(detect == LOW && flag) {
    flag = 0;
    count++;
    digitalWrite(LED_BUILTIN, HIGH);
    printWithMask(count);
  } else if(detect == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
  }

  nowMillis = millis();
  if((nowMillis - lastMillis) > 1000 && count > 0){
    int cpm = (count - lastCount) * 60; 
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("RPM: ");
    lcd.print(cpm);
    lastMillis = nowMillis;
    lastCount = count;
  }
}

void printWithMask(long count){
  char buff[6];
  sprintf(buff, "%.5ld", count); // buff will be "01238"
  char withDot[7];
  withDot[0] = buff[0];
  withDot[1] = buff[1];
  withDot[2] = '.';
  withDot[3] = buff[2];
  withDot[4] = buff[3];
  withDot[5] = buff[4];
  withDot[6] = '\0'; // The terminating NULL
  
  Serial.print("Voltas: ");
  Serial.println(withDot);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Voltas: ");
  lcd.print(withDot);
}

void resetCounter(){
  count =0;
    Serial.println(count);
    lcd.clear();
    lcd.setCursor(0,0);    
    lcd.print("Contador");
    lcd.setCursor(0,1);
    lcd.print("Restado");
    delay(2000);
    showGreetings();
}

void  showGreetings(){
  lcd.setCursor(0,0);
  lcd.print("Bobinador V1.0");
  lcd.setCursor(0,1);
  lcd.print("20/12/2023");
}
