#include "ChessDisplay.h"

#define LCD_COLUMNS 20

void ChessDisplay::display_message_at(String message, int column, int row){
  setCursor(column, row);
  print(message);
}

void ChessDisplay::print_top_left(String message){
  if(message.length() > 7){
    Serial.println("Message too big to be written at position");
    return;
  }

  display_message_at(message, 0, 0);
}

void ChessDisplay::print_top_right(String message){
  if(message.length() > 7){
    Serial.println("Message too big to be written at position");
    return;
  }
  
  display_message_at(message, LCD_COLUMNS - message.length(), 0);
}

void ChessDisplay::print_middle(String message){
  if(message.length() > 20){
    Serial.println("Message too big to be written at position");
    return;
  }

  display_message_at(message, 0, 2);
}

void ChessDisplay::clear_middle(){
  display_message_at("                   ", 0, 2);
}

void ChessDisplay::print_bottom(String message){
  if(message.length() > 20){
    Serial.println("Message too big to be written at position");
    return;
  }
  
  display_message_at(message, 0, 3);
}

void ChessDisplay::clear_bottom(){
  display_message_at("                   ", 0, 3);
}
