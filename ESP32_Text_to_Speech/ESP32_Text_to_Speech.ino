/*
    This is the code for Text to Speech conversion of
    String respose coming from other ESP32 board.

    To use this code succesfully:
      1. You need to downgrade your ESP32 Boards Package to version 1.0.6.
      2. You need to download and install the Audio.h library mentioned in this code itself and remove other
         Audio.h libraries if you have already installed.
      3. Add your Credentials like WiFi SSID Name, Password below to make this project
         connect with Internet


    If you still facing any issues, kindly watch out our video about this project on our YouTube channel
    YouTube channel - https://www.youtube.com/techiesms


*/

#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h" // Download this Library -> https://github.com/schreibfaul1/ESP32-audioI2S


#define uart_en 15
#define RXp2 16
#define TXp2 17
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26


// Your WiFi Credentials
const char *ssid = "SSID";       // WiFi SSID Name
const char *password = "PASS";// WiFi Password ( Keep it blank if your WiFi router is open )

Audio audio;


void setup()
{

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin( ssid, password);

  while (WiFi.status() != WL_CONNECTED)
    delay(1500);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  audio.connecttospeech("Starting", "en"); // Google TTS
}


void loop()

{
  if (Serial2.available()) {
    String Answer = Serial2.readString();
    Serial.println(Answer);
    audio.connecttospeech(Answer.c_str(), "en");
  }
  audio.loop();

}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}
