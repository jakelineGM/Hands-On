// Autores: Pedro Mendes e Jakeline

// Array do controle
// [ Baixo, Cima, Esquerda, Direita, X, Y, A, B, Start]

volatile int arrayControle[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Botoes de Movimentacao
int buttonBaixo = 19;  // Botão Baixo na porta 19
int buttonCima = 4;    // Botão Cima na porta 4
int buttonEsq = 5;     // Botão Esquerda na porta 5
int buttonDir = 18;    // Botão Direita na porta 18

// Botoes de acao
int buttonX = 27;      // Botão X na porta 27
int buttonY = 33;      // Botão Y na porta 33
int buttonA = 26;      // Botão A na porta 26
int buttonB = 25;      // Botão B na porta 25

// Botao de Pause
int buttonStart = 21;  // Botão Start na porta 21

// Direcoes do Acelerometro
int acelX = 32;
int acelY = 35;
int acelZ = 34;

// Pinos de SNES
int pinDados = 12;     // Pino de dados na porta 12
int pinClock = 14;     // Pino de clock na porta 14
int pinLatch = 13;     // Pino de latch na porta 13

volatile int countClock = 0;  // Contador de clock

// Variáveis de leitura do acelerômetro
int readX = 0;
int readY = 0;
int readZ = 0;

volatile bool ver = false;
volatile bool processandoClock = false; // Controle para evitar múltiplas leituras do clock

// Função para o latch
void IRAM_ATTR func_latch()
{
    ver = true;
}

// Função para o clock
volatile bool ver_clock = false;

void IRAM_ATTR func_clock()
{
  ver_clock = true;
}

void setup()
{
  // Setup dos botões de movimentação
  pinMode(buttonBaixo, INPUT_PULLUP);
  pinMode(buttonCima, INPUT_PULLUP);
  pinMode(buttonEsq, INPUT_PULLUP);
  pinMode(buttonDir, INPUT_PULLUP);

  // Setup dos botões de ação
  pinMode(buttonX, INPUT_PULLUP);
  pinMode(buttonY, INPUT_PULLUP);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);

  // Setup do acelerômetro
  pinMode(acelX, INPUT);
  pinMode(acelY, INPUT);
  pinMode(acelZ, INPUT);

  // Setup dos pinos SNES
  pinMode(pinLatch, INPUT_PULLUP);
  pinMode(pinClock, INPUT_PULLUP);
  pinMode(pinDados, OUTPUT);

  attachInterrupt(pinLatch, func_latch, FALLING);  // Função para interrupção externa latch
  attachInterrupt(pinClock, func_clock, FALLING);  // Função para interrupção externa clock

  Serial.begin(115200);
}



void loop()
{
  // Processamento do controle SNES
  if (ver == true)
  {
    Serial.println("Latch");
    countClock = 0;

    // Leitura e verificação dos botões e acelerômetro
    arrayControle[0] = digitalRead(buttonBaixo);
    readY = analogRead(acelY);
    if (readY > 2000) {
      arrayControle[0] = 0;
      Serial.println("Baixo");
    }

    arrayControle[1] = digitalRead(buttonCima);
    readY = analogRead(acelY);
    if (readY < 1600) {
      arrayControle[1] = 0;
      Serial.println("Cima");
    }

    arrayControle[2] = digitalRead(buttonEsq);
    readX = analogRead(acelX);
    if (readX < 1600) {
      arrayControle[2] = 0;
      Serial.println("Esquerda");
    }

    arrayControle[3] = digitalRead(buttonDir);
    readX = analogRead(acelX);
    if (readX > 2000) {
      arrayControle[3] = 0;
      Serial.println("Direita");
    }

    // Leitura dos botões de ação
    arrayControle[4] = digitalRead(buttonX);
    arrayControle[5] = digitalRead(buttonY);
    arrayControle[6] = digitalRead(buttonA);
    arrayControle[7] = digitalRead(buttonB);
    arrayControle[8] = digitalRead(buttonStart);

    ver = false;  // Resetar o flag de verificação
  }

  // Processamento do clock do protocolo SNES
  if (ver_clock == true)
  {
    Serial.println("Clock");

    if(countClock < 9){
      digitalWrite(pinDados, arrayControle[countClock]);
      Serial.print(countClock);
      Serial.print(" : ");
      Serial.println(arrayControle[countClock]);
    }
    
    countClock++;
    ver_clock = false;

    // Após enviar todos os dados, resetamos as variáveis
    if (countClock >= 9)
    {
        digitalWrite(pinDados, arrayControle[8]);
    }

    /*

    if (countClock == 0) { // Baixo
        digitalWrite(pinDados, arrayControle[0]);
        Serial.print("Baixo: ");
        Serial.println(arrayControle[0]);
    }
    else if (countClock == 1) { // Cima
        digitalWrite(pinDados, arrayControle[1]);
        Serial.print("Cima: ");
        Serial.println(arrayControle[1]);
    }
    else if (countClock == 2) { // Esquerda
        digitalWrite(pinDados, arrayControle[2]);
        Serial.print("Esquerda: ");
        Serial.println(arrayControle[2]);
    }
    else if (countClock == 3) { // Direita
        digitalWrite(pinDados, arrayControle[3]);
        Serial.print("Direita: ");
        Serial.println(arrayControle[3]);
    }
    else if (countClock == 4) { // X
        digitalWrite(pinDados, arrayControle[4]);
        Serial.print("X: ");
        Serial.println(arrayControle[4]);
    }
    else if (countClock == 5) { // Y
        digitalWrite(pinDados, arrayControle[5]);
        Serial.print("Y: ");
        Serial.println(arrayControle[5]);
    }
    else if (countClock == 6) { // A
        digitalWrite(pinDados, arrayControle[6]);
        Serial.print("A: ");
        Serial.println(arrayControle[6]);
    }
    else if (countClock == 7) { // B
        digitalWrite(pinDados, arrayControle[7]);
        Serial.print("B: ");
        Serial.println(arrayControle[7]);
    }
    else if (countClock == 8) { // Start
        digitalWrite(pinDados, arrayControle[8]);
        Serial.print("Start: ");
        Serial.println(arrayControle[8]);
    }
    

    countClock++;
    ver_clock = false;

    // Após enviar todos os dados, resetamos as variáveis
    if (countClock >= 9)
    {
        processandoClock = false;  // Liberar a interrupção para a próxima leitura
    }
    */
  }
}
