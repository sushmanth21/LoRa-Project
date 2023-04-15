#include <SoftwareSerial.h>
#include <RH_RF95.h>

SoftwareSerial ss(5, 6); //RX, TX
RH_RF95 rf95(ss);

const int total_height = 30;
const int hold_height = 25;

const int trigger = 13;
const int echo = 12;
long Time;
int distanceCM;
int resultCM;

int bin_lvl = 0;
int snsr_to_max = 0;

void setup() 
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  snsr_to_max = total_height - hold_height;
           
  Serial.begin(115200);
  Serial.println("Initializing...");
    if (!rf95.init())
    {
        Serial.println("init failed");
        while(1);
    }
    rf95.setFrequency(434.0);
}

void loop()
{
  delay(1000);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  Time = pulseIn(echo, HIGH);
  distanceCM = Time * 0.034;
  resultCM = distanceCM / 2;

  bin_lvl = map(resultCM, snsr_to_max, total_height, 100, 0);
  if (bin_lvl > 100) bin_lvl = 100;
  if (bin_lvl < 0) bin_lvl = 0;
  
  Serial.println("");
  Serial.println("");
  Serial.println("Sending to LoRa BASE STATION..");
  rf95.send((uint8_t *)&bin_lvl , sizeof(int));

  Serial.print("Present TrashBin Status: ");
  Serial.print(bin_lvl); 
  Serial.println(" % Filledup.");   
  rf95.waitPacketSent();
  delay(100);
}
