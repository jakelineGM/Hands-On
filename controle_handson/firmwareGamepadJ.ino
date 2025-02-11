/*
 * Autores: Pedro Mendes e Jakeline
 * Firmware de gamepad contendo 9/10 botões e acelerômetro
 */

/*portas dos botoes de movimentacao*/
const int buttonDown = 19;
const int buttonUp = 4;
const int buttonLeft = 5;
const int buttonRight = 18;

/*portas do acelerometro*/
const int acelX = 32;
const int acelY = 35;
const int acelZ = 34;

/*portas dos botoes de acao*/
const int buttonX = 27;
const int buttonY = 33;
const int buttonA = 26;
const int buttonB = 25;

/*portas de outros botoes*/
//const int buttonSelect = ?;
const int buttonStart = 21;

/*portas SNES*/
const int pinData = 12;
const int pinClock = 14;
const int pinLatch = 13;

/*variáveis de leitura do acelerômetro*/
int readX = 0;
int readY = 0;
int readZ = 0;

/*status dos botoes*/
/*volatile bool StateButtonDown = true;
volatile bool StateButtonUp = true;
volatile bool StateButtonLeft = true;
volatile bool StateButtonRight = true;
volatile bool StateButtonX = true;
volatile bool StateButtonY = true;
volatile bool StateButtonA = true;
volatile bool StateButtonB = true;
volatile bool StateButtonStart = true;
//volatile bool StateButtonSelect = true;*/

volatile int StateButtonDown = 1;
volatile int StateButtonUp = 1;
volatile int StateButtonLeft = 1;
volatile int StateButtonRight = 1;
volatile int StateButtonX = 1;
volatile int StateButtonY = 1;
volatile int StateButtonA = 1;
volatile int StateButtonB = 1;
volatile int StateButtonStart = 1;
//volatile int StateButtonSelect = 1;

/*Array DATA*/
//static int arrayData[10] = {StateButtonDown, StateButtonUp, StateButtonLeft, StateButtonRight, StateButtonX, StateButtonY, StateButtonA, StateButtonB, StateButtonStart, StateButtonSelect};
volatile static int arrayData[9] = {StateButtonDown, StateButtonUp, StateButtonLeft, StateButtonRight, StateButtonX, StateButtonY, StateButtonA, StateButtonB, StateButtonStart};

volatile int countClock = 0;
volatile bool callLatch = true;
volatile bool callClock = true;

/*funções de interrupção externa
 *No momento que há mudança do sinal de alto para baixo o processamento do sinal correspondente ocorre.
*/
void IRAM_ATTR func_latch(){callLatch = true;}//Serial.println("LATCH");}
void IRAM_ATTR func_clock(){callClock = true;}//Serial.println("CLOCK");}

void setup(){

  Serial.begin(115200);
  Serial.println("Iniciando firmware...");
  
  /*setup dos botões de movimentação*/
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  
  /*setup do acelerômetro*/
  pinMode(acelX, INPUT);
  pinMode(acelY, INPUT);
  pinMode(acelZ, INPUT);

  /*setup dos botões de ação*/
  pinMode(buttonX, INPUT_PULLUP);
  pinMode(buttonY, INPUT_PULLUP);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);

  /*setup outros botoes*/
  //pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);
  
  /*setup dos pinos SNES*/
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, INPUT_PULLUP);
  pinMode(pinClock, INPUT_PULLUP);

  /*setup das funções de interrupção externa*/
  attachInterrupt(pinLatch, func_latch, HIGH);
  attachInterrupt(pinClock, func_clock, HIGH);
  
  Serial.print("Estado inicial buttonDown: "); Serial.println(digitalRead(buttonDown));
}

void loop(){
  /*processamento do protocolo SNES*/
  /********* LATCH *********/
  /*
    if (callLatch == true){
    //Serial.println("LATCH");
    countClock = 0;

    readY = analogRead(acelY);
    readX = analogRead(acelX);
    
    StateButtonDown = digitalRead(buttonDown);
    if (readY > 2000){StateButtonDown = 0;}

    StateButtonUp = digitalRead(buttonUp);
    if (readY < 1600){StateButtonUp = 0;}

    StateButtonLeft = digitalRead(buttonLeft);
    if (readX < 1600) {StateButtonLeft = 0;}

    StateButtonRight = digitalRead(buttonRight);
    if (readX > 2000) {StateButtonRight = 0;}

    StateButtonX = digitalRead(buttonX);
    StateButtonY = digitalRead(buttonY);
    StateButtonA = digitalRead(buttonA);
    StateButtonB = digitalRead(buttonB);
    StateButtonStart = digitalRead(buttonStart);
    //StateButtonSelect = digitalRead(buttonSelect);
    */

    if (callLatch == true){
    //Serial.println("LATCH");
    countClock = 0;

    readY = analogRead(acelY);
    readX = analogRead(acelX);
    
    StateButtonDown = digitalRead(buttonDown);
    /*teste de botao
    if (StateButtonDown == 0){
      Serial.println("buttondown");
    }*/
    if (readY > 2000){StateButtonDown = 0;}

    StateButtonUp = digitalRead(buttonUp);
    if (readY < 1600){StateButtonUp = 0;}

    StateButtonLeft = digitalRead(buttonLeft);
    if (readX < 1600) {StateButtonLeft = 0;}

    StateButtonRight = digitalRead(buttonRight);
    if (readX > 2000) {StateButtonRight = 0;}

    StateButtonX = digitalRead(buttonX);
    StateButtonY = digitalRead(buttonY);
    StateButtonA = digitalRead(buttonA);
    StateButtonB = digitalRead(buttonB);
    StateButtonStart = digitalRead(buttonStart);
    //StateButtonSelect = digitalRead(buttonSelect);

    /*atualizacao do array com valoes atuais*/
    arrayData[0] = StateButtonDown;
    arrayData[1] = StateButtonUp;
    arrayData[2] = StateButtonLeft;
    arrayData[3] = StateButtonRight;
    arrayData[4] = StateButtonX;
    arrayData[5] = StateButtonY;
    arrayData[6] = StateButtonA;
    arrayData[7] = StateButtonB;
    arrayData[8] = StateButtonStart;
    delay(1000);

    /*reseta o flag de verificação*/
    //callLatch = false; 
  }

  /********* CLOCK *********/
  if (callClock == true){
    //Serial.println("CLOCK");

    /*//teste do array
    Serial.print("<");
    Serial.print(arrayData[0]);
    Serial.print(" ");
    Serial.print(arrayData[1]);
    Serial.print(" ");
    Serial.print(arrayData[2]);
    Serial.print(" ");
    Serial.print(arrayData[3]);
    Serial.print(" ");
    Serial.print(arrayData[4]);
    Serial.print(" ");
    Serial.print(arrayData[5]);
    Serial.print(" ");
    Serial.print(arrayData[6]);
    Serial.print(" ");
    Serial.print(arrayData[7]);
    Serial.print(" ");
    Serial.print(arrayData[8]);
    Serial.print(" ");
    Serial.print(">");
    Serial.println();
    delay(1000);*/

    Serial.println("{b c e d X Y A B S}");
    
    if (countClock == 0) {
        digitalWrite(pinData, arrayData[0]);
        Serial.print("<");
        Serial.print(arrayData[0]);
        Serial.print(" ");
    }
    else if (countClock == 1) {
        digitalWrite(pinData, arrayData[1]);
        Serial.print(arrayData[1]);
        Serial.print(" ");
    }
    else if (countClock == 2) {
        digitalWrite(pinData, arrayData[2]);
        Serial.print(arrayData[2]);
        Serial.print(" ");
    }
    else if (countClock == 3) {
        digitalWrite(pinData, arrayData[3]);
        Serial.print(arrayData[3]);
        Serial.print(" ");
    }
    else if (countClock == 4) {
        digitalWrite(pinData, arrayData[4]);
        Serial.print(arrayData[4]);
        Serial.print(" ");
    }
    else if (countClock == 5) {
        digitalWrite(pinData, arrayData[5]);
        Serial.print(arrayData[5]);
        Serial.print(" ");
    }
    else if (countClock == 6) {
        digitalWrite(pinData, arrayData[6]);
        Serial.print(arrayData[6]);
        Serial.print(" ");
    }
    else if (countClock == 7) {
        digitalWrite(pinData, arrayData[7]);
        Serial.print(arrayData[7]);
        Serial.print(" ");
    }
    else if (countClock == 8) {
        digitalWrite(pinData, arrayData[8]);
        Serial.print(arrayData[8]);
        Serial.print(" ");
    }
    countClock++;
    callClock = false;
  }

  
}
