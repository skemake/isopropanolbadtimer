#include <RtcDS3231.h>
#include <Wire.h>

RtcDS3231 rtcModule;

void setup () {
  Serial.begin(9600);
  Wire.begin();

  //RtcDateTime compiled = RtcDateTime(__DATE__,__TIME__);
  //rtcModule.SetDateTime(compiled);
  
  Serial.println(rtcModule.GetDateTime());
}
void loop(void)
{
  
}

