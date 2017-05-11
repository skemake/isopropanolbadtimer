#include <RtcDS3231.h>
#include "U8glib.h"
#include <Button.h>

#include "pitches.h"
#include "melody.h"
#include "skemakelogo.h"

#define BUTTONPIN 12
#define BUZZER_PIN 10

//#define ALARM_TIME_IN_SECONDS 5
#define ALARM_TIME_IN_SECONDS 600

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE); //i2c twi

RtcDS3231 rtcModule;

Button btn(BUTTONPIN);

byte minutes;
byte seconds;

RtcDateTime alarm;
bool running;

void setup () 
{
  Serial.begin(9600);
  running=false;
  btn.begin();
}
void loop(void)
{
  oled.firstPage();
  do{
    draw();  
  }while(oled.nextPage());
  delay(20);
  if(running)
    updateTime();
    
  if(btn.released()){
    Serial.println(rtcModule.GetDateTime());
    if(running)
    {
      running = false;
    }else{
      alarm = rtcModule.GetDateTime();
      alarm+=ALARM_TIME_IN_SECONDS; // add alarmtime
      running=true;
    }
  } 
}
void updateTime() {
  RtcDateTime now = rtcModule.GetDateTime();
  if(alarm == now){
    running=false;
    oled.firstPage();
    do{
      draw();
    }while(oled.nextPage());
    
    playmelody();
  }
  else{
  RtcDateTime disp = alarm-now;
  minutes = disp.Minute();
  seconds = disp.Second();  
  }
}

void draw(void) {
  if(running){
    oled.setFont(u8g_font_helvB24);
    char timeString[10];
    sprintf(timeString, "%02u:%02u", minutes, seconds);
    oled.setPrintPos(22,45);
    oled.print(timeString);
  }
  else{
    oled.drawXBMP(0,0,SkeMake_width,SkeMake_height, SkeMake_bits);
  }
  
}
// for arduino melodies
/*
void playmelody(){
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++){

    
    // to calculate the note duration, take one second divided by the note type.
    //  e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    
    int noteDuration = 5000/noteDurations[thisNote];
    tone(BUZZERPIN, melody[thisNote],noteDuration);
        
    //  to distinguish the notes, set a minimum time between them.
    //  the note's duration + 30% seems to work well:
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZERPIN); //stop the tone playing:
  }
  
}*/
void playmelody(){
    //tone(pin, note, duration)
    tone(BUZZER_PIN,LA3,Q); 
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(BUZZER_PIN,LA3,Q);
    delay(1+Q);
    tone(BUZZER_PIN,LA3,Q);
    delay(1+Q);
    tone(BUZZER_PIN,F3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,LA3,Q);
    delay(1+Q);
    tone(BUZZER_PIN,F3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    tone(BUZZER_PIN,LA3,H);
    delay(1+H);
    
    tone(BUZZER_PIN,E4,Q); 
    delay(1+Q); 
    tone(BUZZER_PIN,E4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,E4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,F4,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,Ab3,Q);
    delay(1+Q);
    tone(BUZZER_PIN,F3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    tone(BUZZER_PIN,LA3,H);
    delay(1+H);
    
    tone(BUZZER_PIN,LA4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,LA3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,LA3,S);
    delay(1+S);
    tone(BUZZER_PIN,LA4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,Ab4,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,G4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,Gb4,S);
    delay(1+S);
    tone(BUZZER_PIN,E4,S);
    delay(1+S);
    tone(BUZZER_PIN,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(BUZZER_PIN,Bb3,E);
    delay(1+E);
    tone(BUZZER_PIN,Eb4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,D4,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,Db4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    tone(BUZZER_PIN,B3,S);
    delay(1+S);
    tone(BUZZER_PIN,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(BUZZER_PIN,F3,E);
    delay(1+E);
    tone(BUZZER_PIN,Ab3,Q);
    delay(1+Q);
    tone(BUZZER_PIN,F3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,LA3,S);
    delay(1+S);
    
    tone(BUZZER_PIN,C4,Q);
    delay(1+Q);
     tone(BUZZER_PIN,LA3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    tone(BUZZER_PIN,E4,H);
    delay(1+H);
    
     tone(BUZZER_PIN,LA4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,LA3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,LA3,S);
    delay(1+S);
    tone(BUZZER_PIN,LA4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,Ab4,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,G4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,Gb4,S);
    delay(1+S);
    tone(BUZZER_PIN,E4,S);
    delay(1+S);
    tone(BUZZER_PIN,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(BUZZER_PIN,Bb3,E);
    delay(1+E);
    tone(BUZZER_PIN,Eb4,Q);
    delay(1+Q);
    tone(BUZZER_PIN,D4,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,Db4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    tone(BUZZER_PIN,B3,S);
    delay(1+S);
    tone(BUZZER_PIN,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(BUZZER_PIN,F3,E);
    delay(1+E);
    tone(BUZZER_PIN,Ab3,Q);
    delay(1+Q);
    tone(BUZZER_PIN,F3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    
    tone(BUZZER_PIN,LA3,Q);
    delay(1+Q);
     tone(BUZZER_PIN,F3,E+S);
    delay(1+E+S);
    tone(BUZZER_PIN,C4,S);
    delay(1+S);
    tone(BUZZER_PIN,LA3,H);
    delay(1+H);
    
    delay(2*H);

}

