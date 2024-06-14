#include "includes.h"
#include "matrix.h"

int rows[] = {23, 22, 32, 33, 25, 26, 27, 14, 12, 13}; 
 

void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint32_t val) {
    uint32_t i;

    for(i = 0; i < 24; i++) {
        if(bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}   //_shiftOut

Matrix::Matrix(){
    
    pinMode(DATAPIN1, OUTPUT);
    pinMode(LATCHPIN1, OUTPUT);
    pinMode(CLOCKPIN1, OUTPUT);

  for (int i = 0; i < 20; i++){
    for (int j = 0; j < 10; j++){
      matrix[i][j] = 0;
    }
  }
  integer = 0b1;
  for (int i = 0; i < 24; i++){
    integer = integer << 1;
    integer++;
  }
  row = rows;
  for (int i = 0; i < 10; i++){
      pinMode(row[i], OUTPUT);
  }
}; // matrix::matrix

int Matrix::get_state_by_pos(int x, int y){
    y += 4;
    return matrix[y][x];
}   //matrix::get_state_by_pos

void Matrix::print(){
    int integ_copy = integer;
    for (int i = 0; i <= 24 ; i++){
        print_plus(matrix[i]);
        usleep(500);            //for correct output
        print_ground(integer - (1 << i));
  }
}   //matrix::print

void Matrix::print_plus(int* x){
    for (int i = 0; i < 10; i++){
        digitalWrite(row[i], x[i] == 1 ? HIGH : LOW);
        //usleep(10);
    }
}   //print_plus

void Matrix::print_ground(uint32_t x){
    digitalWrite(LATCHPIN1, LOW);
    _shiftOut(DATAPIN1, CLOCKPIN1, LSBFIRST, x);
    digitalWrite(LATCHPIN1, HIGH);
}   //print_ground

int Matrix::set_by_pos(int y, int x, int num){
    y += 4;
    if(y > 24 || y < 0 || x < 0 || x > 9 )
        return -1;
    matrix[y][x] = num > 0 ? 1 : 0;
    return 1;
}   //matrix::set_by_pos