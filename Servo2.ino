#include <AccelStepper.h>
#include <MultiStepper.h>
#include "Mover.h"


#define motorInterfaceType 1

#define SETMICROSTEP      4
#define STEPREV           200
#define SCREWPITCH        8

long MMtoSTEP =          STEPREV * SETMICROSTEP / SCREWPITCH;
long coordToMM =         1;  //tamanho do lado (em mm) de uma casa do tabuleiro
long xi; //dist do canto efetivo do eletroima (0) até a borda do tabuleiro
long zi;

#define MAXPOSITIONX      136 //definido! (valor em mm)
#define MAXPOSITIONZ      136 //147 //definido!
#define MAXSPEED          1300 //1300 rapido ; 700 lento
#define SPEED             600
#define MAXACC            6*MMtoSTEP

#define ENABLE_PIN         8 // particularly useful when implementing an emergency stop or shutdown system

//pinos sugeitos a mudanças de acordo com o microcontrolador/montagem
//micro atual: MEGA2560
#define X_STEP_PIN         11
#define X_DIR_PIN          5
#define X_STOP_PIN         19

#define Z_STEP_PIN         13
#define Z_DIR_PIN          7
#define Z_STOP_PIN         20

#define ON                 HIGH
#define OFF                LOW

bool movingPiece = false; //comecando como true para testes!!!!
bool reseting = false;

int integerValue = 0;
char incomingByte;
int moves[64];
//{MAXPOSITIONX-1, MAXPOSITIONZ-1, MAXPOSITIONX-1, 0, 0, 0, 0, MAXPOSITIONZ-1, MAXPOSITIONX/2,MAXPOSITIONZ/2}; //vetor de testes
int INDMOVE = 0;//(sizeof(moves) / sizeof(moves[0])) - 1; //tamanho padrao = 4
int ind = 0;
char txt = ' ';

//variavel auxiliar para debounce das interrupçoes de stop
volatile unsigned long lastStopX;
volatile unsigned long lastStopZ;

//variaveis eletroima
int imaPin = 2;
bool imaState = LOW;

AccelStepper motorX(motorInterfaceType, X_STEP_PIN, X_DIR_PIN);
AccelStepper motorZ(motorInterfaceType, Z_STEP_PIN, Z_DIR_PIN);

Mover * mover;

void setup() {
  Serial.begin(9600);
  Stream * mainStream = (Stream *)&Serial;
  mover = Mover::GetMoverInstance(mainStream);
  motorsSetup();
  mover->deslocationByCoordinates(9,10);
}

void loop() {
  //motorX.run();
  //motorZ.run();

  if ((motorZ.distanceToGo() == 0) && (motorX.distanceToGo() == 0)) {

    if (reseting) {
      setIma(OFF);
      resetPosition();
    }
    else if (movingPiece) {
      motorMovementSet();
    }
    else {  //espera proximo input
      recvArray();
    }
  }
}

void moveMotorCoordinate(int x, int z) { //coordenada em mm (por hora, anda a distancia passada)

  x = (x * MMtoSTEP * coordToMM);
  if (reseting || (!reseting && (x <= MAXPOSITIONX * MMtoSTEP * coordToMM) && x >= 0)) {
    motorX.moveTo(x);
  }

  z = (z * MMtoSTEP * coordToMM);
  if (reseting || (!reseting && (z <= MAXPOSITIONZ * MMtoSTEP * coordToMM) && z >= 0)) {
    motorZ.moveTo(z);
  }

}

void resetPosition() {

  attachInterrupt(digitalPinToInterrupt(X_STOP_PIN), stopX, FALLING);
  attachInterrupt(digitalPinToInterrupt(Z_STOP_PIN), stopZ, FALLING);

  motorX.setCurrentPosition(0);
  motorZ.setCurrentPosition(0);

  moveMotorCoordinate(3, 3);
  while ((motorZ.distanceToGo() != 0) || (motorX.distanceToGo() != 0)) {
    motorX.run();
    motorZ.run();
  }

  moveMotorCoordinate(-(MAXPOSITIONX), -(MAXPOSITIONZ));
  while ((motorZ.distanceToGo() != 0) || (motorX.distanceToGo() != 0)) {
    motorX.run();
    motorZ.run();
  }

  detachInterrupt(digitalPinToInterrupt(X_STOP_PIN));
  detachInterrupt(digitalPinToInterrupt(Z_STOP_PIN));

  reseting = false;
}

void motorMovementSet() {  //chamado dentro da loop

  for (int i = 0; i < INDMOVE; i += 2) {

    moveMotorCoordinate(moves[i], moves[i + 1]); //move p/ proxima coordenada

    while ((motorZ.distanceToGo() != 0) || (motorX.distanceToGo() != 0)) {
      motorX.run();
      motorZ.run();
    }

    if (i == 0) {
      setIma(ON);
      delay(50);
    }
    else if (i == INDMOVE - 1) {
      //      setIma(OFF);
      //      delay(50);
    }
  }
  setIma(OFF);
  delay(50);

  movingPiece = false;

}

void stopX() {  //interrupçao pelo X_STOP_PIN -> para os motores
  unsigned long now = millis();
  if (now - lastStopX > 50) {
    motorX.stop();
    motorX.setCurrentPosition(0);
  }
  lastStopX = now;
}

void stopZ() {  //interrupçao pelo Z_STOP_PIN -> para o motor
  unsigned long now = millis();
  if (now - lastStopZ > 50) {
    motorZ.stop();
    motorZ.setCurrentPosition(0);
  }
  lastStopZ = now;
}

void setIma(bool state) {
  imaState = state;
  digitalWrite(imaPin, imaState);
}

void motorsSetup() {
  lastStopX = millis();
  lastStopZ = millis();

  pinMode(ENABLE_PIN, OUTPUT);

  //eletroima
  pinMode(imaPin, OUTPUT);
  digitalWrite(imaPin, imaState);

  //setup pinos de stop
  pinMode(X_STOP_PIN, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(X_STOP_PIN), stopX, FALLING);

  pinMode(Z_STOP_PIN, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(Z_STOP_PIN), stopZ, FALLING);

  //configurando parametros
  motorX.setMaxSpeed(MAXSPEED);
  motorX.setAcceleration(MAXACC);

  motorZ.setMaxSpeed(MAXSPEED);
  motorZ.setAcceleration(MAXACC);


  reseting = true;
  //resetPosition();  //coloca os motores na posiçao inicial (0,0)
}

void recvArray() {
  if (Serial.available() > 0) {   // something came across serial

    incomingByte = Serial.read(); //lê o valor da casa (entre 1 e 8, inclusivo)
    //txt = Serial.read();  //lê as possiveis virgulas/espaços

    //moves[ind] = incomingByte - 48;

    while (incomingByte != 'D') {
      moves[ind] = incomingByte - 48;
      incomingByte = Serial.read();

      while (incomingByte != ' ' && incomingByte != 'D') { //se n é ' ', é numero
        moves[ind] = (moves[ind] * 10) + (incomingByte - 48);
        incomingByte = Serial.read();
      }
      ind++;
      if (incomingByte != 'D') {
        incomingByte = Serial.read();
      }
    }

    char lixo = Serial.read(); //apenas para tirar o '\n' do buffer

    //define INDMOVE e ativa movimentaçao
    INDMOVE = ind;
    ind = 0;
    txt = ' ';
    movingPiece = true;

    //teste
    
  }
  else {
    delay(3000);
  }
}
