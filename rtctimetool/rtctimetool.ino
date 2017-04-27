#include <RtcDS3231.h>
#include <Wire.h>

RtcDS3231 rtcModule;

void setup () {
  
  Wire.begin();

  RtcDateTime compiled = RtcDateTime(__DATE__,__TIME__);
  rtcModule.SetDateTime(compiled);
  
}
void loop(void)
{
  
}

