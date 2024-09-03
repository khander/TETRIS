#include "includes.h"
#include "matrix.h"


int rows[] = {15, 18, 13, 12, 14, 27, 26, 25, 33, 32}; 
 

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

    for(int i = 0; i < 4; i++)      //array to delete init
        array_to_delete[i] = 0;
    rows_to_clear = 0;

}; // matrix::matrix

void Matrix::reset_matrix(){
    for (int i = 0; i < 25; i++){
    for (int j = 0; j < 10; j++){
      matrix[i][j] = 0;
    }
  }
}   //matrex::reset_matrix

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

int Matrix::check_rows_to_delete(){
    int counter_array = 0;
    for(int i = 0; i < 25; i++){
        int counter_of_row = 0;
        for(int j = 0; j < 10; j++){
            if(matrix[i][j] == 1)
                counter_of_row++;
            else   
                break;
        }
        if(counter_of_row == 10){       //not neccessary
            array_to_delete[counter_array++] = i;
        }
        rows_to_clear = counter_array;

    }
    return rows_to_clear;
}   //matrix::check_rows_to_delete

void Matrix::delete_chosen_rows(){
    int counter = 1;
    for(int i = 5; i < 10; i++){
        for(int j = 0; j < 4; j++){
            matrix[array_to_delete[j]][i] = 0;
            matrix[array_to_delete[j]][i-counter] = 0;
        }
        counter+=2;
        for(int m = 0; m < 8; m++){     //for normal output
            print();
        }
    }
    for(int i = 0; i < 4; i++){
        if(array_to_delete[i] != 0){
            for(int j = 0; j < 10; j++){
                for(int m = array_to_delete[i]; m > 3; m--){
                    matrix[m][j] = matrix[m-1][j];
                }  
            }
        }
    }
    for(int i = 0; i < 4; i++)      //array to delete init
        array_to_delete[i] = 0;

        //add score
    rows_to_clear = 0;
}   //matrix::delete_chosen_rows