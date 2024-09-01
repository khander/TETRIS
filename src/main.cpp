

#include "includes.h"
//#include "lcd.cpp"

LiquidCrystal_I2C lcd(0x27, 16, 2);


Figure *random_figure();

Matrix m;
Figure *fig = random_figure();

void hello_page(){
    lcd.clear();              // clear display
    lcd.setCursor(0, 0);      // move cursor to   (0, 0)
    lcd.print("TETRIS BY");
    lcd.setCursor(0, 1);
    lcd.print("KHANDER");
    usleep(1000000);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("PRESS START");
    lcd.setCursor(5,1);
    lcd.print("BUTTON");
}
   
int lastStatePause = HIGH;
int currentStatePause;

void start_btn(){
    while(true){
        currentStatePause = digitalRead(PAUSEBTN);
        if(lastStatePause == LOW && currentStatePause == HIGH) 
            return;
        lastStatePause = currentStatePause;
    }
}

void setup() {
    pinMode( LEFTBTN, INPUT_PULLUP);
    pinMode( RIGHTBTN, INPUT_PULLUP);
    pinMode( ROTATEBTN, INPUT_PULLUP);
    pinMode( DOWNBTN, INPUT_PULLUP);
    pinMode( PAUSEBTN, INPUT_PULLUP);

    
    lcd.init();
    lcd.backlight();
    hello_page();
    start_btn();
   



    
    fig->put_figure(m, 1);

}   //setup

Figure *random_figure(){
    int seed = esp_random() % 7;
    Figure *figure;
    switch(seed){
        case 1:
            figure = new j_figure();
            break;
        case 2:
            figure = new l_figure();
            break;
        case 3:
            figure = new t_figure();
            break;    
        case 4:
            figure = new s_figure();
            break;
        case 5:
            figure = new z_figure();
            break;
        case 6:
            figure = new o_figure();
            break;
        case 0:
            figure = new i_figure();
            break;    
    }
    return figure;
}


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
    currentStateDown = digitalRead(DOWNBTN);
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

    if(currentStateDown == LOW && isChangedDown == 0 && ((millis() - lastCheckedTimeDown) > BOUNCE_TIME_DOWN)){
        fig->down(m);
        lastCheckedTimeDown = millis();
    }
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
        if(!(fig->down(m))){
            fig->put_figure(m, 1);
            m.check_rows_to_delete();
            m.delete_chosen_rows();
            delete fig;
            fig = random_figure();
        }
        fig->put_figure(m, 1); 
        ticks = 0;      
    }
    
}   //loop