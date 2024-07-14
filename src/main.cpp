#include <Arduino.h>
#include <stdio.h>
#include "includes.h"
#include "matrix.h"
#include "figure.h"
#include "figures.cpp"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows


#define TIME 0



Matrix m;
//_J_ j_;
//Figure *fig = new j_figure();
//j_figure figr;
Figure *fig = new j_figure();

void setup() {
    pinMode( LEFTBTN, INPUT_PULLUP);
    pinMode( RIGHTBTN, INPUT_PULLUP);
    pinMode( ROTATEBTN, INPUT_PULLUP);


    pinMode(DATAPIN2, OUTPUT);
    pinMode(LATCHPIN2, OUTPUT);
    //pinMode(CLOCKPIN2, OUTPUT);
    unsigned test = 10101010;
    digitalWrite(LATCHPIN2, LOW);
    shiftOut(DATAPIN2, CLOCKPIN1, LSBFIRST, test);
    digitalWrite(LATCHPIN2, HIGH);



    lcd.init(); // initialize the lcd
    lcd.backlight();

    lcd.clear();              // clear display
    lcd.setCursor(0, 1);      // move cursor to   (0, 0)
    lcd.print("TETRIS");       // print message at (0, 0)

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

int lastStateLeft = HIGH;
int currentStateLeft;

int lastStateRight = HIGH;
int currentStateRight;

int lastStateRotate = HIGH;
int currentStateRotate;


void loop() {
    currentStateLeft = digitalRead(LEFTBTN);
    currentStateRight = digitalRead(RIGHTBTN);
    currentStateRotate = digitalRead(ROTATEBTN);    
    
    m.print();
    ticks++;

    if(ticks % 3 == 0){
        fig->put_figure(m, 0);
        
        if(lastStateLeft == LOW && currentStateLeft == HIGH)
            fig->left(m);
        lastStateLeft = currentStateLeft;

        if(lastStateRight == LOW && currentStateRight == HIGH)
            fig->right(m);
        lastStateRight = currentStateRight;

        if(lastStateRotate == LOW && currentStateRotate == HIGH)
            fig->rotate(m);
        lastStateRotate = currentStateRotate;

        fig->put_figure(m, 1);
    }

    if(ticks == 20){
        fig->put_figure(m, 0);
//        if(fig->check_if_able_down(m)){
//            fig->down(m);
        if(!(fig->down(m))){
            fig->put_figure(m, 1);
            delete fig;
            fig = new t_figure;
            fig->left(m);
            fig->rotate(m);
            //fig->set_base_pos(4, 1);
        }
        //fig->right(m);
        


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