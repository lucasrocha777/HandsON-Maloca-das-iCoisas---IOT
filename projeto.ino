#include <LiquidCrystal.h>

// Pinos do LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define TRIG_PIN 8
#define ECHO_PIN 9
#define LED_PIN 12
#define BUZZER_PIN 11

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Inicializa o LCD
  lcd.begin(16, 2); // Configura o LCD 16x2
  lcd.print("Distance:"); // Texto inicial no LCD
  
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Enviando pulso para o TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lendo o tempo do pulso no ECHO
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculando a distância (em cm)
  distance = duration * 0.034 / 2;

  // Exibindo a distância no Monitor Serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Atualizando o LCD
  lcd.setCursor(0, 1); // Segunda linha, posição inicial
  lcd.print("    ");   // Apaga valores antigos
  lcd.setCursor(0, 1); // Segunda linha, posição inicial
  lcd.print(distance);
  lcd.print(" cm");

  // Lógica para o alerta
  if (distance > 0 && distance < 50) { // Distância menor que 50 cm
    digitalWrite(LED_PIN, HIGH);      // Acende o LED
    digitalWrite(BUZZER_PIN, HIGH);   // Ativa o buzzer
  } else {
    digitalWrite(LED_PIN, LOW);       // Desliga o LED
    digitalWrite(BUZZER_PIN, LOW);    // Desativa o buzzer
  }

  delay(500); // Atualiza a cada meio segundo
}
