#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>

//void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint32_t val);



class Matrix{
private:
    int matrix[25][10];     // matrix
    int integer;        //for ground output (rows)  usually 0b111111...111
    int *row;           // for plus output (columns) 

public:
  Matrix(void);                                 //constructor
  void print();                                 // print current matrix
  void print_plus(int*);                        // set plus output
  void print_ground(uint32_t);                  // set ground output
  int set_by_pos(int, int, int);                // set position 
  int get_integer() { return integer; };        //  get ground output
  int get_state_by_pos(int, int);
}; // class matrix

#endif