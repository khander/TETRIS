#include <Arduino.h>
#include <stdio.h>
#include "includes.h"
#include "matrix.h"
#include "figure.h"
#include "figures.cpp"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows




Matrix m;
//_J_ j_;
//Figure *fig = new j_figure();
//j_figure figr;
Figure *fig = new i_figure();

void setup() {
    pinMode( LEFTBTN, INPUT_PULLUP);
    pinMode( RIGHTBTN, INPUT_PULLUP);
    pinMode( ROTATEBTN, INPUT_PULLUP);
    pinMode( DOWNBTN, INPUT_PULLUP);
    pinMode( PAUSEBTN, INPUT_PULLUP);

    lcd.init(); // initialize the lcd
    lcd.backlight();

    lcd.clear();              // clear display
    lcd.setCursor(0, 0);      // move cursor to   (0, 0)
    lcd.print("TETRIS BY KHANDER");       // print message at (0, 0)

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


int lastStateRight = HIGH;
int currentStateRight;
unsigned long lastCheckedTimeRight = 0;
bool isChangedRight = 0;

void rightButton(){
    currentStateRight = digitalRead(RIGHTBTN);
    fig->put_figure(m, 0);
    
    if(lastStateRight == HIGH && currentStateRight == LOW){
        fig->right(m);
        
        lastCheckedTimeRight = millis();
        isChangedRight = 0;
    }
    else if(lastStateRight == LOW && currentStateRight == HIGH){
        isChangedRight = 1;
       
    }
    lastStateRight = currentStateRight;

    if(currentStateRight == LOW && isChangedRight == 0 && ((millis() - lastCheckedTimeRight) > BOUNCE_TIME)){
        fig->right(m);
        lastCheckedTimeRight = millis();
    }
    fig->put_figure(m, 1);
}

int lastStateLeft = HIGH;
int currentStateLeft;
unsigned long lastCheckedTimeLeft = 0;
bool isChangedLeft = 0;

void leftButton(){
    currentStateLeft = digitalRead(LEFTBTN);
    fig->put_figure(m, 0);
    
    if(lastStateLeft == HIGH && currentStateLeft == LOW){
        fig->left(m);
        
        lastCheckedTimeLeft = millis();
        isChangedLeft = 0;
    }
    else if(lastStateLeft == LOW && currentStateLeft == HIGH){
        isChangedLeft = 1;
       
    }
    lastStateLeft = currentStateLeft;

    if(currentStateLeft == LOW && isChangedLeft == 0 && ((millis() - lastCheckedTimeLeft) > BOUNCE_TIME)){
        fig->left(m);
        lastCheckedTimeLeft = millis();
    }
    fig->put_figure(m, 1);
}

int lastStateDown = HIGH;
int currentStateDown;
unsigned long lastCheckedTimeDown = 0;
bool isChangedDown = 0;

void downButton(){
    currentStateRight = digitalRead(DOWNBTN);
    fig->put_figure(m, 0);
    
    if(lastStateDown == HIGH && currentStateDown == LOW){
        fig->down(m);
        
        lastCheckedTimeDown = millis();
        isChangedDown = 0;
    }
    else if(lastStateDown == LOW && currentStateDown == HIGH){
        isChangedDown = 1;
       
    }
    lastStateDown = currentStateDown;
/*
    if(currentStateDown == LOW && isChangedDown == 0 && ((millis() - lastCheckedTimeDown) > BOUNCE_TIME)){
        fig->down(m);
        lastCheckedTimeDown = millis();
    }
    */
    fig->put_figure(m, 1);
}

int lastStateRotate = HIGH;
int currentStateRotate;
unsigned long lastCheckedTimeRotate = 0;
bool isChangedRotate = 0;

void rotateButton(){
    currentStateRotate = digitalRead(ROTATEBTN);
    fig->put_figure(m, 0);
    
    if(lastStateRotate == HIGH && currentStateRotate == LOW){
        fig->rotate(m);
        
        lastCheckedTimeRotate = millis();
        isChangedRotate = 0;
    }
    else if(lastStateRotate == LOW && currentStateRotate == HIGH){
        isChangedRotate = 1;
       
    }
    lastStateRotate = currentStateRotate;

    if(currentStateRotate == LOW && isChangedRotate == 0 && ((millis() - lastCheckedTimeRotate) > BOUNCE_TIME)){
        fig->rotate(m);
        lastCheckedTimeRotate = millis();
    }
    fig->put_figure(m, 1);
}


static int ticks = 0;
int l = 0;
int r = 0;

int lastStatePause = HIGH;
int currentStatePause;



void loop() {
    
    currentStatePause = digitalRead(PAUSEBTN);
    
    m.print();
    ticks++;
    
    rightButton();
    leftButton();
    rotateButton();
    downButton();


    


    if(ticks == 20){
        fig->put_figure(m, 0);
//        if(fig->check_if_able_down(m)){
//            fig->down(m);
        if(!(fig->down(m))){
            fig->put_figure(m, 1);
            delete fig;
            fig = new z_figure;
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