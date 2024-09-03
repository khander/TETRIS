

#include "includes.h"


LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long high_score;       //fix
//byte high_score[8];
//unsigned long high;
unsigned long score;
unsigned int level;
unsigned int levels_cleared;

int current_tick_rate;


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
   
void pause_page(){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("PAUSE");
}

void game_over_page(){
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(0, 1);
    lcd.print("SCORE:");
    lcd.print(score);
    usleep(3000000);
    lcd.setCursor(0, 0);
    lcd.print("             ");
    lcd.setCursor(0, 0);
    lcd.print("H_SCORE:");
    lcd.print(high_score);

}

void score_page(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SCORE:");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print("LVL:");
    lcd.print(level);
}

int lastStatePause = HIGH;
int currentStatePause;
unsigned long lastCheckedTimePause = 0;

void start_btn(){
    while(true){
        currentStatePause = digitalRead(PAUSEBTN);
        if(lastStatePause == LOW && currentStatePause == HIGH) {
            lastStatePause = currentStatePause;
            return;
        }
            
        lastStatePause = currentStatePause;
    }
}

void pause_btn(Matrix& m){
    currentStatePause = digitalRead(PAUSEBTN);

    if(lastStatePause == LOW && currentStatePause == HIGH ){
       
        lastStatePause = currentStatePause;
        pause_page();
        while(true){
            m.print();
            
            currentStatePause = digitalRead(PAUSEBTN);
            if(lastStatePause == LOW && currentStatePause == HIGH) {
                lastCheckedTimePause = millis();
                lastStatePause = currentStatePause;
                return;
            }
            lastStatePause = currentStatePause;

        }
    }
    lastStatePause = currentStatePause;
    
}

void setup() {
    pinMode( LEFTBTN, INPUT_PULLUP);
    pinMode( RIGHTBTN, INPUT_PULLUP);
    pinMode( ROTATEBTN, INPUT_PULLUP);
    pinMode( DOWNBTN, INPUT_PULLUP);
    pinMode( PAUSEBTN, INPUT_PULLUP);

    EEPROM.begin(EEPROM_SIZE);
   // EEPROM.writeULong(0, 0);
    high_score = EEPROM.readULong(0);
    level = 0;
    score = 0;
    levels_cleared = 0;
    
    lcd.init();
    lcd.backlight();
    hello_page();
    start_btn();
    score_page();



    
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
        score++;            //1 point for each skipped row
        lastCheckedTimeDown = millis();
        isChangedDown = 0;
    }
    else if(lastStateDown == LOW && currentStateDown == HIGH){
        isChangedDown = 1;
       
    }
    lastStateDown = currentStateDown;

    if(currentStateDown == LOW && isChangedDown == 0 && ((millis() - lastCheckedTimeDown) > BOUNCE_TIME_DOWN)){
        fig->down(m);
        score++;         //1 point for each skipped row
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

void game_over(){
    if(score > high_score){
        high_score = score;
        EEPROM.writeULong(0, high_score);
        EEPROM.commit();
    }
    game_over_page();

    score = 0;
    level = 0;
    levels_cleared = 0;
    start_btn();
    m.reset_matrix();

    
}

void points_to_add(int rows_points){
    int temp_score = 0;
    switch(rows_points){
        case 1: 
            temp_score = 40;
            break;
        case 2:
            temp_score = 100;
            break;
        case 3:
            temp_score = 300;
            break;
        case 4:
            temp_score = 1200;
            break;
        default:
            break;
    }
    temp_score *=(level + 1);
    score += temp_score;
    levels_cleared+=rows_points;
    if(levels_cleared >=10){
        level++;
        levels_cleared -=10;
    }
}

void loop() {
    
    
    
    m.print();
    ticks++;
    
    rightButton();
    leftButton();
    rotateButton();
    downButton();
    pause_btn(m);

    if(ticks == TICKRATE_LEVEL_KILLZONE){

        fig->put_figure(m, 0);
        if(!(fig->down(m))){
            fig->put_figure(m, 1);
            int rows_points = m.check_rows_to_delete();
            if(rows_points > 0)
                m.delete_chosen_rows();
            points_to_add(rows_points);
            score_page();
            if(fig->is_game_over())
                game_over();
            delete fig;
            
            fig = random_figure();
        }
        fig->put_figure(m, 1); 
        ticks = 0;      
    }
    
}   //loop