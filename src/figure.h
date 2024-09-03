#ifndef FIGURE_H
#define FIGURE_H

#include "matrix.h"

class Figure{
protected:
    int fig[4][4];
    int fig_copy[4][4];
    int base_pos_x;     //x position in main matrix
    int base_pos_y;     //y position in main matrix

    int inner_pos_x;
    int inner_pos_y;

public:
    Figure();
    virtual int rotate(Matrix &);       //was pure
    int check_if_able_rotate(Matrix &);
    void put_figure(Matrix &, int);
    void set_base_pos(int, int);
    int down(Matrix &);
    int right(Matrix &);
    int left(Matrix &);
    int check_if_able_down(Matrix &);
    int check_if_able_left(Matrix &);
    int check_if_able_right(Matrix &);
    int is_game_over();
    virtual ~Figure(){};
};

#endif