#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
//#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

int percent=91;
//LiquidCrystal lcd(D2, D3, D5, D6, D7, D8);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int blueled=D0;
const int redled=9;
const int orangeled=10;
const int greenled=A0;

const char* ssid = "MUDDU KRISHNA";
const char* password = "SUSHMANTH";

#define BOTtoken "5052094109:AAFFMhsKkhV2DUN6reItlZvBAhBmSa490ho"
#define CHAT_ID "918847542"

AsyncWebServer server(80); 

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#include <SoftwareSerial.h>
#include <RH_RF95.h>

SoftwareSerial ss(14,2);
RH_RF95 rf95(ss);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  
<style>
html {display: inline-block; margin: 0px auto; text-align: center}
  
h1 { font-family: Arial; color: #FF1493; display: inline-block; margin: 0px auto; text-align: center; font-size: 1.5rem; }
h2 {font-family: Calibri; color: #006400; display: inline-block; margin: 0px auto; text-align: center; font-size: 1.5rem;}
h3 { font-family: Arial; color: #800080; display: inline-block; margin: 0px auto; text-align: center; font-size: 1.5rem; }
h4 { font-family: Arial; color: black; display: inline-block; margin: 0px auto; text-align: left ; font-size: 1.0rem; }
h5{ font-family: Arial; color: #800080; display: inline-block; margin: 0px auto; text-align: center; font-size: 1.1rem; }

 p1 {font-size: 1.5rem; color: darkgreen; font-family: Arial;} 
    .units{font-size: 1.5rem; vertical-align:top;}
    .percentlabels{font-size: 1.5rem; vertical-align:top;}
 p2 {font-size: 1.5rem; color: darkgreen; font-family: Arial;}   
 p3 {font-size: 1.5rem; color: darkgreen; font-family: Arial;}   
 p4 {font-size: 1.5rem; color: darkgreen; font-family: Arial;}   
 
</style>
</head>
<body>
<img src="http://sietk.org/images/sietk-logo.png" width="140" height="135" text-align= right;>
<img src="http://sietk.org/images/header-image-clgname.png " width="670" height="120" text-align= center;>
<img src="http://sietk.org/images/header-image-naac-aicte.png " width="380"  height="120" text-align= left;>
<br><hr>

<h1><b>DEPARTMENT OF ELECTRONICS AND COMMUNICATION ENGINEERING</b></h1>
<br>
<h2>ECE-4  &nbsp BATCH-01 &nbsp 2022 </h2>
<br>
<p2>
<div style="background: lightyellow;            
            padding-top: 10px; padding-right: 10px; padding-left: 10px; padding-bottom: 25px;
            border: 5px solid purple; 
            margin: 35px;">

<h3><b> LONG RANGE (LoRa) BASED GARBAGE MONITORING SYSTEM OVER INTERNET OF THINGS (IoT) </b></h3>
<br>
<br>
<b>
    <i class="fas fa-trash-alt" style="color:#00add6;"></i> 
    <span class="percentlabels">Trash Bin is filled up : </span> 
    <span id="percent">%PERCENT%</span>
    <span class="units">&percnt;</span>
</b>
</div>
</p1>

<p3> 
<div style="background: #FFF0F5; 
           float:left;
           padding-top: 27px; padding-right: 15px; padding-left: 10px; padding-bottom: 29px;
           text-align=left;
           border: 5px solid purple; 
           margin: 35px;">
<h5><b><u>UNDER THE ESTEEMED GUIDANCE OF: </u> </b></h5>
<br>
<br>
<h4>  Dr. R PREM KUMAR M.E.,Ph.D. </h4>
<br>
<h4>PROFESSOR</h4>
<br>
<h4>(DEPT. OF ECE, SIETK.)</h4>
</div>
</p3>

<p3>
<div style="background: #FFF0F5; 
           float:right;
            padding-top: 10px; padding-right: 29px; padding-left: 28px; padding-bottom: 10px;
            border: 5px solid purple; 
            margin: 35px;">
<h5><b><u> PROJECT MEMBERS: </u></b></h5>
<br>
<br>
<h4> C SUSHMANTH (18F61A04N1) </h4><br>
<h4> G SANDEEP (18F61A04J9) </h4><br>
<h4> B SRAVANI (18F61A04M3) </h4><br>
<h4> C KRISHNA VAMSI (19F65A0413) </h4><br>
<h4> C GIRISH (19F65A0408) </h4><br>
</div>
</p3>

<p3>
<div style="background: #FFF0F5; 
           float:left;
           padding: 10px; 
           border: 5px solid purple; 
           margin: 35px;">
<h5> The Location of the Trash Bin: </h5><br>
<iframe width="572.9" height="200" frameborder="0" style="border:0"
src="https://www.google.com/maps/embed/v1/place?q=Siddharth+Institute+of+Engineering+and+Technology&key=AIzaSyDn5BgYvMnG8SAXXuLO74w-1o9rxnWfrww" allowfullscreen></iframe>
</div>
</p3>
</body>

<script>
setInterval(function ( )
 {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      document.getElementById("percent").innerHTML = this.responseText;
     }
  };
  xhttp.open("GET", "/percent", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

String processor(const String& var)
{
 if(var == "PERCENT")
   {
    return String(percent);
   }
  return String();
}

void setup(){
configTime(0,0,"pool.ntp.org");
client.setTrustAnchors(&cert);

Serial.begin(115200);
pinMode(blueled,OUTPUT);
pinMode(redled,OUTPUT);
pinMode(orangeled,OUTPUT);
pinMode(greenled,OUTPUT);

//lcd.begin(16,2);
//lcd.clear();

  lcd.init();
  Wire.begin(D2,D1);
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Our Guide:      ");
  lcd.setCursor(0,1);
  lcd.println("Dr. R PREM KUMAR ");
  delay(2500);

  lcd.setCursor(0,0);
  lcd.clear();
  lcd.println("C SUSHMANTH,     ");
  lcd.setCursor(0,1);
  lcd.print("C KRISHNA VAMSI,   ");
  delay(2500);

  lcd.setCursor(0,0);
  lcd.clear();
  lcd.println("B SRAVANI, G SAN");
  lcd.setCursor(0,1);
  lcd.print("DEEP, C GIRISH.      ");
  delay(2000);
  
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Connecting.....    ");
  lcd.setCursor(0,1);
  lcd.print("Please Wait!!!    ");
  
  lcd.print(WiFi.localIP());
  lcd.println(" ");

 WiFi.begin(ssid, password); 
 Serial.println("");

 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Welcome to LoRa BASE STATION..");
  Serial.println("");

  if(!rf95.init())
    {
        Serial.println("init failed");
        while(1);
    } 
     rf95.setFrequency(434.0); 

    digitalWrite(blueled, HIGH);
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
    });

    server.on("/percent", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(percent).c_str());
    });

   server.begin(); 
 }
 
void loop(){ 
if(rf95.available())
  {  
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if(rf95.recv(buf, &len))
    {
     percent = buf[0] | (buf[1] << 12);

     if (percent<=50){
      digitalWrite(greenled,HIGH);
     }
     if ((percent>50) && (percent<=90)){
      digitalWrite(orangeled,HIGH);
     }
      if (percent>90){
      digitalWrite(redled,HIGH);
      bot.sendMessage(CHAT_ID, "Hi! The TrashBin at following Location is filled up: \n\nLatitude: 13.427547 \nLongitude: 79.573817 \n\nhttps://goo.gl/maps/M5E4zDkwDZVCBHJU8 \n\nPlease Segregate it fast!!!","");
      delay(500);
     }

     Serial.print("The TrashBin is filled up: ");
     Serial.print(percent);
     Serial.println(" %");
     Serial.println("At Location:");
     Serial.println("Latitude: 13.427547");
     Serial.println("Longitude: 79.573817");
     Serial.println("");
     
     lcd.setCursor(0,0);
     lcd.clear();
     //lcd.print("IP");
     lcd.print(WiFi.localIP());
     lcd.println("      ");
  
     lcd.setCursor(0,1);
     lcd.print("TrashBin: ");
     lcd.print(percent); 
     lcd.print(" %     ");
     
    }
    else
    {
        Serial.println("recv failed");
    }
  }
}
