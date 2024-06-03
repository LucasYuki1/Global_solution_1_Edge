#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Inicializa o display LCD com o endereço I2C 0x27 (pode variar, consulte seu módulo)
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc; // Objeto do RTC

unsigned long relogioMilis = 0; // Marca a última vez que o relógio foi atualizado
const long relogioIntervalo = 1000; // Intervalo para atualizar o relógio (1 segundo)
int baixo = 54;
int medio = 61;
unsigned long pHUltimaleitura = 0; // Marca a última vez que o pH foi lido
const long intervaloPH = 5000; // Intervalo para calcular a média do pH (5 segundos)
int rPin = 12;
int gPin = 7;
int yPin = 6;
const int sensorPin = A0; // Pino analógico onde o sensor de pH está conectado
int buzzerPin = 8; // Pino onde o buzzer está conectado
float somaPH = 0; // Soma dos valores de pH lidos
int contagemPH = 0; // Contagem de leituras de pH
float ultimoPH = -1; // Valor anterior de pH para detectar mudanças abruptas
float phMudanca = 0.5; // Limite para detectar mudança abrupta de pH

byte interrogar[] = { B01110, B10001, B10001, B00001, B00110, B00100, B00000, B00100 };
byte terceiro[] = { B00000, B00011, B00110, B01111, B00111, B00011, B00000, B11111 };
byte quarto[] = { B00000, B11110, B11111, B11111, B11111, B11110, B00000, B11111 };
byte quinto[] = { B00000, B00100, B01100, B11100, B01100, B00100, B00000, B11111 };
byte exclamacao[] = { B00100, B00100, B00100, B00100, B00100, B00100, B00000, B00100 };
byte check[] = { B00000, B00000, B00001, B00010, B10100, B01000, B00000, B00000 };
byte segundo[] = { B00001, B00001, B00001, B00001, B00001, B00001, B00001, B00001 };
byte sexto[] = { B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000 };

void setup() {
  lcd.begin(16, 2);
  lcd.backlight(); // Liga a luz de fundo do LCD
  Serial.begin(9600); // Inicia a comunicação serial
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(yPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC não está funcionando!");
    while (1);
  }

  lcd.createChar(0, segundo);
  lcd.createChar(1, terceiro);
  lcd.createChar(2, quarto);
  lcd.createChar(3, quinto);
  lcd.createChar(4, sexto);
  lcd.createChar(5, exclamacao);
  lcd.createChar(6, interrogar);
  lcd.createChar(7, check);
  lcd.setCursor(10, 1); // Posição para exibir o caractere "segundo"
  lcd.write(0);
  lcd.setCursor(11, 0); // Posição para exibir o caractere "quarto"
  lcd.write(1);
  lcd.setCursor(12, 0); // Posição para exibir o caractere "quinto"
  lcd.write(2);
  lcd.setCursor(13, 0); // Posição para exibir o caractere "sexto"
  lcd.write(3);
  lcd.setCursor(14, 1); // Posição para exibir o caractere "oitavo"
  lcd.write(4);
  delay(1000);
  // Configure o RTC com a hora atual se necessário
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Descomente e ajuste se necessário
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - relogioMilis >= relogioIntervalo) {
    relogioMilis = currentMillis;
    updateClockDisplay();
  }

  if (currentMillis - pHUltimaleitura >= intervaloPH) {
    pHUltimaleitura = currentMillis;
    updatePHDisplay();
  }

  readPH(); // Leia o valor de pH constantemente
}

void updateClockDisplay() {
  DateTime now = rtc.now();
  
  // Formata a hora, minuto e segundo com dois dígitos
  char buffer[9];
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  lcd.setCursor(0, 0); // Define o cursor na primeira coluna da primeira linha
  lcd.print(buffer);   // Exibe o horário formatado no LCD
}

void readPH() {
  int sensorValue = analogRead(sensorPin); // Lê o valor do sensor
  int sensorMapeado = map(sensorValue, 0, 1023, 0, 1400); // map para 0 a 1400 para permitir precisão de duas casas decimais
  float valorPH = sensorMapeado / 100.0; // Convertendo para pH com duas casas decimais
  int porcentagemPH = map(sensorValue, 0, 1023, 0, 99); //define um limite de porcentagem para até 99% para não quebrar os caracteres, é possível alterar com um display maior
  
  somaPH += valorPH;
  contagemPH++;
  lcd.setCursor(11,1);
  lcd.print(porcentagemPH);
  lcd.print("%");
  lcd.setCursor(15, 1); // Define o cursor na segunda linha

  if (porcentagemPH < baixo) {
    lcd.write(5); // Exibe o caractere para intervalo baixo
    digitalWrite(rPin, HIGH);
    digitalWrite(gPin, LOW);
    digitalWrite(yPin, LOW);
    tone(buzzerPin, 1000); // Buzzer toca com 1000 Hz
  } else if (porcentagemPH < medio) {
    lcd.write(7); // Exibe o caractere para intervalo médio
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, HIGH);
    digitalWrite(yPin, LOW);
    noTone(buzzerPin); // Buzzer para de tocar
  } else {
    lcd.write(6); // Exibe o caractere para intervalo alto
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
    digitalWrite(yPin, HIGH);
    noTone(buzzerPin); // Buzzer para de tocar
  }

  // Verifica se houve uma mudança abrupta no pH
  if (ultimoPH != -1 && abs(valorPH - ultimoPH) >= phMudanca) {
    DateTime now = rtc.now();
    Serial.print("Mudança abrupta no PH: ");
    Serial.print(now.timestamp(DateTime::TIMESTAMP_FULL));
    Serial.print(" | Ultimo valor do PH: ");
    Serial.print(ultimoPH, 2);
    Serial.print(" | Valor atual do PH: ");
    Serial.println(valorPH, 2);
  }

  ultimoPH = valorPH;
}

void updatePHDisplay() {
  float pHMedio = somaPH / contagemPH;

  // Exibe a média de pH no Serial Monitor
  Serial.print("pH médio: ");
  Serial.println(pHMedio, 2);

  // Exibe o valor no LCD
  lcd.setCursor(0, 1); // Define o cursor na primeira coluna da segunda linha
  lcd.print("PH: ");
  lcd.print(pHMedio, 2); // Exibe o valor de pH com duas casas decimais

  // Reseta os valores para a próxima média
  somaPH = 0;
  contagemPH = 0;
}
