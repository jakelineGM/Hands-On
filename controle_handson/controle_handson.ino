// Autor: Pedro Mendes

// Array do controle
// [ Baixo, Cima, Esquerda, Direita, X, Y, A, B, Start]

volatile bool arrayControle[9] = {true, true, true, true, true, true, true, true, true};

//Botoes de Movimentacao
int buttonBaixo = 19; // declara o button Baixo na porta 19
int buttonCima = 4; // declara o button Cima na porta 4
int buttonEsq = 5; // declara o button Esquerda na porta 5
int buttonDir = 18; // declara o button Direita na porta 18

//Botoes de acao
int buttonX = 27; // declara o button X na porta 27
int buttonY = 33; // declara o button Y na porta 33
int buttonA = 26; // declara o button A na porta 26
int buttonB = 25; // declara o button B na porta 25

//Botao de Pause
int buttonStart = 21; // declara o button Pause na porta 21

//Direcoes do Acelerometro
int acelX = 32;
int acelY = 35;
int acelZ = 34;

// Pinos de SNES
volatile int pinDados = 12; // declara o pino de dados na porta 12
volatile int pinClock = 14; // declara o pino de clock na porta 14
volatile int pinLatch = 13; // declara o pino de dados na porta 13

volatile int countClock = 0; // Count do clock

//variaveis de leitura acelerometro
int readX = 0;
int readY = 0;
int readZ = 0;

// Funcao para o latch
void IRAM_ATTR func_latch()
{
  countClock = 0;

  arrayControle[0] = digitalRead(buttonBaixo);
  readY = analogRead(acelY);
  if(readY > 2000){
    arrayControle[0] = false;
  }
  arrayControle[1] = digitalRead(buttonCima);
  readY = analogRead(acelY);
  if(readY < 1600){
    arrayControle[1] = false;
  }
  arrayControle[2] = digitalRead(buttonEsq);
  readX = analogRead(acelX);
  if(readX < 1600){
    arrayControle[2] = false;
  }
  arrayControle[3] = digitalRead(buttonDir);
  readX = analogRead(acelX);
  if(readX > 2000){
    arrayControle[3] = false;
  }
  
  
  arrayControle[4] = digitalRead(buttonX);
  arrayControle[5] = digitalRead(buttonY);
  arrayControle[6] = digitalRead(buttonA);
  arrayControle[7] = digitalRead(buttonB);
  arrayControle[8] = digitalRead(buttonStart);
  
}

// Funcao para o clock
void IRAM_ATTR func_clock()
{
  if(digitalRead(pinClock)){
    
    // Array do controle
    // [ Baixo, Cima, Esquerda, Direita, X, Y, A, B, Start]
    
    if(countClock==0){ // Baixo
      digitalWrite(pinDados,arrayControle[0]);
    }
    if(countClock==1){ // Cima
      digitalWrite(pinDados,arrayControle[1]);
    }
    if(countClock==2){ // Esquerda
      digitalWrite(pinDados,arrayControle[2]);
    }
    if(countClock==3){ // Direita
      digitalWrite(pinDados,arrayControle[3]);
    }
    if(countClock==4){ // X
      digitalWrite(pinDados,arrayControle[4]);
    }
    if(countClock==5){ // Y
      digitalWrite(pinDados,arrayControle[5]);
    }
    if(countClock==6){ // A
      digitalWrite(pinDados,arrayControle[6]);
    }
    if(countClock==7){ // B
      digitalWrite(pinDados,arrayControle[7]);
    }
    if(countClock==8){ // Start
      digitalWrite(pinDados,arrayControle[8]);
    }
    
    countClock++;
  }
  
}


void setup()
{
  //Setup botoes movimentacao
  pinMode(buttonBaixo, INPUT_PULLUP); // define o pino do botao baixo como entrada
  pinMode(buttonCima, INPUT_PULLUP); // define o pino do botao cima como entrada
  pinMode(buttonEsq, INPUT_PULLUP); // define o pino do botao esquerda como entrada
  pinMode(buttonDir, INPUT_PULLUP); // define o pino do botao direita como entrada

  //Setup botoes acao
  pinMode(buttonX, INPUT_PULLUP); // define o pino do botao X como entrada
  pinMode(buttonY, INPUT_PULLUP); // define o pino do botao Y como entrada
  pinMode(buttonA, INPUT_PULLUP); // define o pino do botao A como entrada
  pinMode(buttonB, INPUT_PULLUP); // define o pino do botao B como entrada

  pinMode(buttonStart, INPUT_PULLUP); // define o pino do botao Start como entrada

  //Setup acelerometro
  pinMode(acelX, INPUT);
  pinMode(acelY, INPUT);
  pinMode(acelZ, INPUT);

  pinMode(pinLatch, INPUT_PULLUP); // define o pino Latch como entrada
  pinMode(pinClock, INPUT_PULLUP); // define o pino Clock como entrada

  attachInterrupt(pinLatch, func_latch, HIGH); //Funcao para interrupcao externa latch
  attachInterrupt(pinClock, func_clock, HIGH); //Funcao para interrupcao externa clock
  
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(buttonBaixo) == false){
    Serial.println("Botao Baixo");
  }
  if(digitalRead(buttonCima) == false){
    Serial.println("Botao Cima");
  }
  if(digitalRead(buttonEsq) == false){
    Serial.println("Botao Esq");
  }
  if(digitalRead(buttonDir) == false){
    Serial.println("Botao Dir");
  }
  if(digitalRead(buttonX) == false){
    Serial.println("Botao X");
  }
  if(digitalRead(buttonY) == false){
    Serial.println("Botao Y");
  }
  if(digitalRead(buttonA) == false){
    Serial.println("Botao A");
  }
  if(digitalRead(buttonB) == false){
    Serial.println("Botao B");
  }
  if(digitalRead(buttonStart) == false){
    Serial.println("Botao Start");
  }
  
  readY = analogRead(acelY);
  if(readY > 2150){
    Serial.println("Acel. Baixo");
  }
  readY = analogRead(acelY);
  if(readY < 1450){
    Serial.println("Acel. Cima");
  }
  readX = analogRead(acelX);
  if(readX < 1450){
    Serial.println("Acel. Esq");
  }
  readX = analogRead(acelX);
  if(readX > 2150){
    Serial.println("Acel. Dir");
  }
}
