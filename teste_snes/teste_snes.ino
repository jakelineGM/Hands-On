int pinDados = 22; // declara o pino de dados na porta 22
int pinClock = 1; // declara o pino de clock na porta 1
int pinLatch = 23; // declara o pino de dados na porta 23

void sendLatchSignal() {
    digitalWrite(pinLatch, HIGH);
    delayMicroseconds(12);
    digitalWrite(pinLatch, LOW);
    Serial.println("Latch enviado");
}

void sendClockPulses() {
    for (int i = 0; i < 9; i++) {
        digitalWrite(pinClock, HIGH);
        delayMicroseconds(6); // Meio ciclo
        digitalWrite(pinClock, LOW);
        delayMicroseconds(6); // Meio ciclo

        delay(800);

        // Ler valor do pino de dados
        int bitValue = digitalRead(pinDados);
        Serial.printf("Bit %d lido: %d\n", i, bitValue);

    }
}


void setup() {
  pinMode(pinLatch, OUTPUT); // define o pino Latch como saída
  pinMode(pinClock, OUTPUT); // define o pino Clock como saída
  pinMode(pinDados, INPUT); // define o pino data como entrada
  
  Serial.begin(115200);
  Serial.println("Simulador SNES iniciado...");

   sendLatchSignal();
   sendClockPulses();
}

void loop() {
    
}
