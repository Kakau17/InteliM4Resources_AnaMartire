const int pin25out = 25;
const int pin32out = 32;
const int pin27out = 27;
void setup() {
  // Define o pino 25 como SAIDA
  pinMode(pin25out,OUTPUT);
  pinMode(pin32out,OUTPUT);
  pinMode(pin27out,OUTPUT);

  // Inicializa a porta serial de com. com o ESP32
  Serial.begin(115200);
  Serial.println("Iniciando a serial");
}
void loop() {
  // Envia 0V. para o pino 25
  digitalWrite(pin25out, HIGH);
  digitalWrite(pin32out, LOW);
  digitalWrite(pin27out, LOW);
  delay(500);

  digitalWrite(pin25out, LOW);
  digitalWrite(pin32out, HIGH);
  digitalWrite(pin27out, LOW);
  delay(500);

  digitalWrite(pin25out, LOW);
  digitalWrite(pin32out, LOW);
  digitalWrite(pin27out, HIGH);
  delay(500);

}