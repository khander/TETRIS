#include <Arduino.h>
#include <stdio.h>
#include "matrix.h"
#include "figure.h"
#include "figures.cpp"


#define TIME 0



Matrix m;
//_J_ j_;
//Figure *fig = new j_figure();
//j_figure figr;
Figure *fig = new j_figure();

void setup() {

    //m.set_by_pos(5, 5, 1);
    //m.set_by_pos(15, 2, 1);
    /*
    for(int i = 0; i < 15 ; i ++){
        for(int j = 0; j < 10 ; j++){
            m.set_by_pos(i, j , 1);
            if( j > 3 && j < 7 || (i > 5 && i < 7))
                m.set_by_pos(i, j, 0);
        }
    }
    m.set_by_pos(20, 5, 1);

    */
    //fig->put_figure(m, 1);

    //figs[1] = new _J_();
    //fig->set_base_pos(5, 1);
    fig->put_figure(m, 1);

}   //setup

static int ticks = 0;
int l = 0;
int r = 0;




void loop() {
    
    m.print();
    ticks++;
    if(ticks == 20){
        fig->put_figure(m, 0);
        if(fig->check_if_able_down(m)){
            fig->down(m);
        }
        else{
            fig->put_figure(m, 1);
            delete fig;
            fig = new o_figure;
            fig->set_base_pos(4, 1);
        }
        fig->put_figure(m, 1);

        /*
        m.set_by_pos(21 - l + 1, r, 0);
        m.set_by_pos( 21 - l, r, 1);

        l++;
        */
        ticks = 0;
        if(l > 21){
            l = 0;
            r++;
        }

    }
    

}   //loop