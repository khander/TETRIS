#include "figure.h"
//#include "matrix.h"

Figure::Figure(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            fig[i][j] = 0;
        }
    }
    base_pos_x = 5;     // x position of main matrix
    base_pos_y = 5;    // y position of main matrix
    inner_pos_x = 1;    
    inner_pos_y = 1;
};  //Figure::Figure

int check_if_correct(int x, int y){
    return (x > -1 && x < 10 && y > 0 && y < 21);
}   //check if correct

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
}