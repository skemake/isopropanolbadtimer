#include <RtcDS3231.h>
#include "U8glib.h"
#include <Button.h>

#include "pitches.h"
#include "melody.h"
#include "skemakelogo.h"

#define BUTTONPIN 13
#define BUZZERPIN 10

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
  running=false;
  //pinMode(BUZZERPIN, OUTPUT);
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
void playmelody(){
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++){

    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    */
    int noteDuration = 1000/noteDurations[thisNote];
    tone(BUZZERPIN, melody[thisNote],noteDuration);
    
    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZERPIN); //stop the tone playing:
  }
  
}

