
extern "C" int rom_phy_get_vdd33();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Chip Revesion: ");
  Serial.println(ESP.getChipRevision());  //1
  Serial.print("Chip Model: ");
  Serial.println(ESP.getChipModel());     //ESP32-D0WDQ6
  Serial.print("Chip core: ");
  Serial.println(ESP.getChipCores());     //2
  Serial.print("SDK version: ");
  Serial.println(ESP.getSdkVersion());    //v4.4.1-472-gc9140caf8c
  float flashChipSize = (float)ESP.getFlashChipSize() / 1024.0 / 1024.0;
  Serial.print("Flash size: ");
  Serial.println(flashChipSize);          //4MB
  float temp = temperatureRead();
  Serial.print("Tempature: ");
  Serial.println(temp);
  float Vcc = ((float)rom_phy_get_vdd33())/100;   //3.26
  Serial.print("Vcc: ");
  Serial.println(Vcc);
//--ESP8266
//  Serial.println(ESP.getChipId());          //4038641
//  Serial.println(ESP.getCoreVersion());     //2_7_4
//  Serial.println(ESP.getSdkVersion());      //2.2.2-dev(38a443e)  
  delay(1000);
}
