#include <Arduino.h>
#include <FastLED.h>
#include "LedControl.h"

#define DATA_PIN 2;

LEDControl::LEDControl(CRGB *ledss){
  leds = ledss;
  NumLeds = 84;
  lastHouseLedLitIndex = 0;
}

/// <summary>
/// Converte coordenadas row e col que variam de 0 até 7 para uma 
/// única coordenada de 0 até 63, que representa as casas do tabuleiro.
/// </summary>
int LEDControl::ConvertRowAndPosToTabIndex(int row, int col){
  return row * 8 + col;
}

/// <summary>
/// Converte coordenadas row e col que variam de 0 até 7 para uma 
/// única coordenada de 0 até 84 (?), que corresponde ao led que está
/// naquela coordenada.
/// </summary>
int LEDControl::ConvertRowAndColToLedPos(int row, int col){
  int p;
  if (row % 2 > 0) {
    p = 7 + row * 11 - (col);

  } else {
    p = col + row * 11;
  }
  return p + 1;
}

/// <summary>
/// Converte index da casa do tabuleiro que varia de 0 até 63 para uma 
/// única coordenada de 0 até 84 (?), que corresponde ao led que está
/// naquela coordenada.
/// </summary>
int LEDControl::ConvertTabIndexToLedPos(int tabIndex){
  int row = tabIndex / 8;
  int col = tabIndex % 8;
  return ConvertRowAndColToLedPos(row, col);
}

void LEDControl::TurnLedOff(int ledPos){
  leds[ledPos] = CRGB::Black;
  FastLED.show();
}

void LEDControl::TurnLedOn(int ledPos, CRGB color){
  leds[ledPos] = color;
  FastLED.show();
}

void LEDControl::TurnEverythingOff(){
  for (int i = 0; i < NumLeds; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

/// <summary>
/// Funcao usada para mostrar a casa selecionada. Automaticamente apaga
/// a casa selecionada anterior.
/// </summary> 
void LEDControl::ShowHouseSelection(int row, int col){
  int ledPos = ConvertRowAndColToLedPos(row, col);
  
  if(lastHouseLedLitIndex == ledPos){
    return;
  }
  else {
    TurnLedOff(lastHouseLedLitIndex);
    TurnLedOn(ledPos, CRGB::Red);
    lastHouseLedLitIndex = ledPos;
  }
}

/// <summary>
/// Funcao usada para mostrar onde o jogador pode mover a peça.
/// Acende os leds das casas do tabuleiro que são válidas para mover uma peça.
/// Recebe uma lista de 0..63 posições indicando quais casas são válidas:
/// -1 é casa invalida, qlqr coisa diferente quer dizer que casa é valida (e deve ter seu led aceso).
/// </summary> 
void LEDControl::ShowPossibleMoves(int *validMoves){
  for (int i = 0; i < sizeof(validMoves)/sizeof(validMoves[0]); i++){
    if(validMoves[i] != -1){
      int ledPos = ConvertTabIndexToLedPos(validMoves[i]);
      leds[ledPos] = CRGB::Green;
    }
  }
  FastLED.show();
}
