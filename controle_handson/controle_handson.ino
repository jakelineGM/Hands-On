/*
 * Autores: Pedro Mendes e Jakeline
 * Firmaware para gamepad - Projeto desenvolvido no Hands-On final do DevTITANS
 * 
 */

 /*Array do gamepad*/
 /*[ X, A, 1, Start, Baixo, Cima, Esquerda, Direita, Y, B]*/

volatile int arrayControle[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

/*portas dos botoes de movimentacao*/
int buttonBaixo = 19;
int buttonCima = 4;
int buttonEsq = 5;
int buttonDir = 18;

/*portas do acelerometro*/
int acelX = 32;
int acelY = 35;
int acelZ = 34;

/*portas dos botoes de acao*/
int buttonX = 27;
int buttonY = 33;
int buttonA = 26;
int buttonB = 25;

/*portas de outros botoes*/
//int buttonSelect = ?;
int buttonStart = 21;

/*portas SNES*/
int pinDados = 13;
int pinClock = 12;
int pinLatch = 14;

/*variáveis de leitura do acelerômetro*/
int readX = 0;
int readY = 0;
int readZ = 0;

int countClock = 0;
volatile bool processandoClock = false; // Controle para evitar múltiplas leituras do clock

volatile bool ver = false;
volatile bool ver_clock = false;

int clocked = 0;
int latched = 0;

void setup()
{
  /*Setup dos botões de movimentação*/
  pinMode(buttonBaixo, INPUT_PULLUP);
  pinMode(buttonCima, INPUT_PULLUP);
  pinMode(buttonEsq, INPUT_PULLUP);
  pinMode(buttonDir, INPUT_PULLUP);

  /*Setup dos botões de ação*/
  pinMode(buttonX, INPUT_PULLUP);
  pinMode(buttonY, INPUT_PULLUP);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);
  //pinMode(buttonSelect, INPUT_PULLUP);

  /*Setup do acelerômetro*/
  pinMode(acelX, INPUT);
  pinMode(acelY, INPUT);
  pinMode(acelZ, INPUT);

  /*Setup do SNES*/
  pinMode(pinLatch, INPUT_PULLUP);
  pinMode(pinClock, INPUT_PULLUP);
  pinMode(pinDados, OUTPUT);

//  attachInterrupt(pinLatch, func_latch, HIGH);  // Função para interrupção externa latch
//  attachInterrupt(pinClock, func_clock, HIGH);  // Função para interrupção externa clock

  Serial.begin(115200);
}



void loop()
{
  ver = digitalRead(pinLatch);
  ver_clock = digitalRead(pinClock);

   /*[ X, A, 1, Start, Baixo, Cima, Esquerda, Direita, Y, B]*/

  /*Processamento do controle SNES*/
  /*************LATCH*************/
  if (ver == 1 && !latched){
    
//    Serial.println("Latch");
    countClock = 0;
    
    //readY = analogRead(acelY);
    //readX = analogRead(acelX);

    /*Leitura e verificação dos botões de movimentação e acelerômetro*/
    
    arrayControle[4] = digitalRead(buttonBaixo);
//    if (readY > 2000) {
//      arrayControle[4] = 0;
//      //Serial.println("Baixo");
//    }

    arrayControle[5] = digitalRead(buttonCima);
//    if (readY < 1600) {
//      arrayControle[5] = 0;
//      //Serial.println("Cima");
//    }

    arrayControle[6] = digitalRead(buttonEsq);
//    if (readX < 1600) {
//      arrayControle[6] = 0;
//      //Serial.println("Esquerda");
//    }

    arrayControle[7] = digitalRead(buttonDir);
//    if (readX > 2000) {
//      arrayControle[7] = 0;
//      //Serial.println("Direita");
//    }
    

    /*Leitura dos botões de ação*/
    arrayControle[0] = digitalRead(buttonX);
    arrayControle[8] = digitalRead(buttonY);
    arrayControle[1] = digitalRead(buttonA);
    arrayControle[9] = digitalRead(buttonB);
    arrayControle[3] = digitalRead(buttonStart);
    //arrayControle[2] = digitalRead(buttonSelect);

    /*resetar o flag de verificação*/ 
    latched = 1; 
  }

  if(ver == 0){
    latched = 0;
  }

  //*************CLOCK*************/
  if (ver_clock == 1 && !clocked){
    
    //Serial.println("Clock");
    
    digitalWrite(pinDados, arrayControle[countClock]);
    
    if(countClock < 9){
      countClock++;
    }
    clocked = 1;
  }

  if(ver_clock == 0){
    clocked = 0;
  }
}
