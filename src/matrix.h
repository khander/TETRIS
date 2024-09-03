#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>

//void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint32_t val);



class Matrix{
private:
    int matrix[25][10];     // matrix
    int integer;        //for ground output (rows)  usually 0b111111...111
    int *row;           // for plus output (columns) 
    int array_to_delete[4];
    int rows_to_clear;
public:
  Matrix(void);                                 //constructor
  void print();                                 // print current matrix
  void print_plus(int*);                        // set plus output
  void print_ground(uint32_t);                  // set ground output
  int set_by_pos(int, int, int);                // set position 
  int get_integer() { return integer; };        //  get ground output
  int get_state_by_pos(int, int);
  int check_rows_to_delete();
  void delete_chosen_rows();
  void reset_matrix();
}; // class matrix

#endif