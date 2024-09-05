

#include "includes.h"

TaskHandle_t Task1;

void Task1code( void * pvParameters );

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long high_score;
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
                score_page();
                return;
            }
            lastStatePause = currentStatePause;

        }
    }
    lastStatePause = currentStatePause;
    
}

void setup() {


    xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */       



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
    current_tick_rate = TICKRATE_LEVEL_BASE;
    
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

    if(ticks == current_tick_rate){

        fig->put_figure(m, 0);
        if(!(fig->down(m))){
            fig->put_figure(m, 1);
            int rows_points = m.check_rows_to_delete();
            if(rows_points > 0){
                m.delete_chosen_rows();
                points_to_add(rows_points);
                if(level >= 13 && level < 16){
                    current_tick_rate = TICKRATE_LEVEL_1;
                }
                else if(level >= 16 && level < 19){
                    current_tick_rate = TICKRATE_LEVEL_2;
                }
                else if(level >= 19 && level < 29){
                    current_tick_rate = TICKRATE_LEVEL_3;
                }
                else if(level >= 29){
                    current_tick_rate = TICKRATE_LEVEL_KILLZONE;
                }
                else{
                    current_tick_rate = TICKRATE_LEVEL_BASE - level * 2;
                }
            }
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


void Task1code( void * pvParameters ){              //music function


    //author:https://github.com/robsoncouto/arduino-songs/blob/master/tetris/tetris.ino


  // change this to make the song slower or faster
int tempo=144; 

// change this to whichever pin you want to use
int buzzer = SPEAKER;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
  

  NOTE_E5,2,  NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,2,   NOTE_A4,2,
  NOTE_GS4,2,  NOTE_B4,4,  REST,8, 
  NOTE_E5,2,   NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,4,   NOTE_E5,4,  NOTE_A5,2,
  NOTE_GS5,2,

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes=sizeof(melody)/sizeof(melody[0])/2; 

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

  for(;;){
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  } 
}