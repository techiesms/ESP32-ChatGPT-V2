/*
    This is the code for Speech to Text conversion and
    Requesting OpenAi API to ask any questions.

    To use this code succesfully:
      1. You need to downgrade your ESP32 Boards Package to version 1.0.6.
      2. Keep all the files attached with this zip in one single folder named ESP32_Speech_to_Text.
      3. Add all your Credentials like WiFi SSID Name, Password, Google Cloud Key &
         OpenAI API Key into Credentials.h Header File


    If you still facing any issues, kindly watch out our video about this project on our YouTube channel
    YouTube channel - https://www.youtube.com/techiesms


*/

//IR Sensor acting as WakeUp Button
#define button 23

// RGB LEDs for status indication
#define led_1 15
#define led_2 2
#define led_3 4

// UART Pins of Other ESP32 for Text to Speech
#define RXp2 16
#define TXp2 17

// Necessary Libraries
#include "Audio.h"
#include "CloudSpeechClient.h"


int i = 0;
void setup()
{
  pinMode(button, INPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
  Serial2.println("Intialising");
  //  Serial.println(My_Data);
}

void loop()
{

  digitalWrite(led_1, 0);
  digitalWrite(led_2, 0);
  digitalWrite(led_3, 0);

  if (i == 0) {
    Serial.println("Press button");
    i = 1;
  }
  //  if(i==1){delay(1);}

  delay(500);
  if (digitalRead(button) == 0)
  {
    Serial2.println("\r\nPlease Ask!\r\n");
    // Green LED ON
    digitalWrite(led_1, 1);
    digitalWrite(led_2, 0);
    digitalWrite(led_3, 0);
    delay(2100);
    Serial.println("\r\nRecord start!\r\n");
    Audio* audio = new Audio(ADMP441);
    audio->Record();
    Serial.println("Processing your Audio File");
    // Blue LED ON
    digitalWrite(led_1, 0);
    digitalWrite(led_2, 1);
    digitalWrite(led_3, 0);

    CloudSpeechClient* cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
    cloudSpeechClient->Transcribe(audio);
    delete cloudSpeechClient;
    delete audio;
    i = 0;
  }
  if (digitalRead(button) == 1)
  {
    delay(1);   
  }
}
