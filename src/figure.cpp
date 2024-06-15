#include "figure.h"
//#include "matrix.h"

int check_if_correct(int x, int y){
    return (x > -1 && x < 10 && y > 0 && y < 22);
}   //check if correct

    int fig_copy[4][4];


Figure::Figure(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            fig[i][j] = 0;
        }
    }
    base_pos_x = 5;     // x position of main matrix
    base_pos_y = 1;    // y position of main matrix
    inner_pos_x = 1;    
    inner_pos_y = 1;
};  //Figure::Figure

int Figure::rotate(Matrix &m){

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            fig_copy[i][j] = 0;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            fig_copy[i][j] = fig[2 - j][i];
        }
    }
    if(check_if_able_rotate(m)){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                fig[i][j] = fig_copy[i][j];
            }
        }
        //fig = fig_copy;
        return 1;
    }
    else{
        return 0;
    }

}   //Figure::rotate

int Figure::check_if_able_rotate(Matrix& m){
    int x, y;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            x = base_pos_x + (i - inner_pos_x);
            y = base_pos_y + (j - inner_pos_y);
            if(!(check_if_correct(x, y)) && fig_copy[j][i] == 1){
                if(m.get_state_by_pos(x, y) == 1)
                    return 0;
            }
        }
    }
    return 1;
}   //Figure::check_if_able_rotate


//Figure::~Figure(){};

void Figure::put_figure(Matrix& m, int val){
    int x, y;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            x = base_pos_x + (i - inner_pos_x);
            y = base_pos_y + (j - inner_pos_y);
            if(check_if_correct(x, y) && fig[j][i] == 1){
                if(val == 0){
                    m.set_by_pos(y, x, 0);
                }
                else{
                    m.set_by_pos(y, x, fig[j][i]);
                }
            }
        }
    }

}   //Figure::put_figure

void Figure::set_base_pos(int x, int y){
    base_pos_x = x;
    base_pos_y = y;
}   //Figure::set_base_pos

int Figure::down(Matrix& m){
    if(check_if_able_down(m)){
        base_pos_y++;
        return 1;
    }
    return 0;
}   //Figure::down

int Figure::left(Matrix& m){
    if(check_if_able_left(m)){
        base_pos_x--;
        return 1;
    }
    return 0;
}   //Figure::left

int Figure::right(Matrix& m){
    if(check_if_able_right(m)){
        base_pos_x++;
        return 1;
    }
    return 0;
}   //Figure::right

int Figure::check_if_able_right(Matrix& m){
    int cur_x = base_pos_x + 1;
    int x, y;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            x = cur_x + (i - inner_pos_x);
            y = base_pos_y + (j - inner_pos_y);
            if(!(check_if_correct(x, y)) && fig[j][i] == 1){
                if(m.get_state_by_pos(x, y) == 1 || x > 9)
                    return 0;
            }
        }
    }
    return 1;
}   //Figure::check_if_able_right

int Figure::check_if_able_left(Matrix& m){
    int cur_x = base_pos_x - 1;
    int x, y;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            x = cur_x + (i - inner_pos_x);
            y = base_pos_y + (j - inner_pos_y);
            if(!check_if_correct(x, y) && fig[j][i] == 1){
                if(m.get_state_by_pos(x, y) == 1 || x < 0)
                    return 0;
            }
        }
    }
    return 1;
}   //Figure::check_if_able_left

int Figure::check_if_able_down(Matrix& m){
    int cur_y = base_pos_y + 1;
        int x, y;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            x = base_pos_x + (i - inner_pos_x);
            y = cur_y + (j - inner_pos_y);
            if(check_if_correct(x, y) && fig[j][i] == 1){
                if(m.get_state_by_pos(x, y) == 1 || y > 20)
                    return 0;
            }
        }
    }
    return 1;
}   //Figure::check_if_able_down