/*
 * Autores: Pedro Mendes e Jakeline
 * Firmaware para gamepad - Projeto desenvolvido no Hands-On final do DevTITANS
 * 
 */

 /*Array do gamepad*/
 /*[ X, A, 1, Start, Baixo, Cima, Esquerda, Direita, Y, B]*/

volatile int arrayControle[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

/*portas dos botoes de movimentacao*/
int buttonBaixo = 19;
int buttonCima = 4;
int buttonEsq = 5;
int buttonDir = 18

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
int pinDados = 12;
int pinClock = 14;
int pinLatch = 13;

/*variáveis de leitura do acelerômetro*/
int readX = 0;
int readY = 0;
int readZ = 0;

volatile int countClock = 0;
volatile bool processandoClock = false; // Controle para evitar múltiplas leituras do clock

volatile bool ver = false;
volatile bool ver_clock = false;

/*funções de interrupção externa*/
void IRAM_ATTR func_latch(){ver = true;}
void IRAM_ATTR func_clock(){ver_clock = true;}

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

  attachInterrupt(pinLatch, func_latch, FALLING);  // Função para interrupção externa latch
  attachInterrupt(pinClock, func_clock, FALLING);  // Função para interrupção externa clock

  Serial.begin(115200);
}



void loop()
{
  /*Processamento do controle SNES*/
  /*************LATCH*************/
  if (ver == true){
    
    Serial.println("Latch");
    countClock = 0;

    readY = analogRead(acelY);
    readX = analogRead(acelX);

    /*Leitura e verificação dos botões de movimentação e acelerômetro*/
    arrayControle[4] = digitalRead(buttonBaixo);
    if (readY > 2000) {
      arrayControle[4] = 0;
      Serial.println("Baixo");
    }

    arrayControle[5] = digitalRead(buttonCima);
    if (readY < 1600) {
      arrayControle[5] = 0;
      Serial.println("Cima");
    }

    arrayControle[6] = digitalRead(buttonEsq);
    if (readX < 1600) {
      arrayControle[6] = 0;
      Serial.println("Esquerda");
    }

    arrayControle[7] = digitalRead(buttonDir);
    if (readX > 2000) {
      arrayControle[7] = 0;
      Serial.println("Direita");
    }

    /*Leitura dos botões de ação*/
    arrayControle[0] = digitalRead(buttonX);
    arrayControle[8] = digitalRead(buttonY);
    arrayControle[1] = digitalRead(buttonA);
    arrayControle[9] = digitalRead(buttonB);
    arrayControle[3] = digitalRead(buttonStart);
    //arrayControle[2] = digitalRead(buttonSelect);

    /*resetar o flag de verificação*/
    ver = false;  
  }

  //*************CLOCK*************/
  if (ver_clock == true){
    
    Serial.println("Clock");

    if(countClock < 9){
      digitalWrite(pinDados, arrayControle[countClock]);
      Serial.print(countClock);
      Serial.print(" : ");
      Serial.println(arrayControle[countClock]);
    }

    countClock++;
    ver_clock = false;

    /*Após enviar todos os dados, resetamos as variáveis*/
    if (countClock >= 9){
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
