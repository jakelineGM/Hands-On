
int pinDados = 22; // declara o pino de dados na porta 12
int pinClock = 1; // declara o pino de clock na porta 14
int pinLatch = 23; // declara o pino de dados na porta 13


void setup() {
  pinMode(pinLatch, OUTPUT); // define o pino Latch como entrada
  pinMode(pinClock, OUTPUT); // define o pino Clock como entrada
  pinMode(pinDados, INPUT); // define o pino data como saída
  
  Serial.begin(115200);

  delay(5000);
  Serial.println("Comecou");


  digitalWrite(pinLatch, LOW);
  digitalWrite(pinClock, LOW);
  digitalWrite(pinLatch, HIGH);
  digitalWrite(pinLatch, LOW);
  digitalWrite(pinClock, HIGH);
  digitalWrite(pinClock, LOW);
  Serial.println(digitalRead(pinLatch));
  Serial.println(digitalRead(pinClock));
  Serial.println(digitalRead(pinDados));
  digitalWrite(pinLatch, LOW);
  digitalWrite(pinClock, LOW);
  

}

void loop() {
  

}
