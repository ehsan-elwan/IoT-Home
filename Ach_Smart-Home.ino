/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc



  1:100011011100111000001000 293  dec:9293320 volet ch2
  2:100011011100111000000000 292  dec:9293312
  3:100011011100111000001100 302  dec:9293324
  4:100011011100111000000010 301  dec:9293314
  5:100011011100111000001010 301  dec:9293322
  6:100011011100111000000110 299  dec:9293318
  7:100011011100111000001110 300  dec:9293326 pare-soliel
  8:100011010000000000000000 297  dec:9240576
  9:100011011100111000001001 300  dec:9293321
  10:100011011100111000000000 301 dec:9293312
  11:100011011100111000001101 302 dec:9293325
  12:100011011100111000000011 299 dec:9293315   V16
  portail: 100000110000000000000000 288 dec:8585216   || 111110100010000011101000 284 dec:16392424
  Clio A:111110100010000011100001 285 dec:16392417
  Clio B:111110100010000011100010 286 dec:16392418
  Fiat ouv:110110100010010011101001 285 dec:14296297
  Fiat ferm:111010101010001001101001 286 dec:15377001
  Fiat ouvFen:100100101011010001100101 285 dec:9614437
  Fiat fermFen:111011111000101100111001 286 dec:15698745
  B button: 100000111111110011010100 dec:8649940
  Mouvement Sensor: 000111010101010111111000 353 dec:1922552  z-10   chambre
                    100110100001110111111000     dec:10100216 z-2-4  salon tv
                    010001000101010001010000     dec:4478032  z-2-2   entree
                    111001011101100111111000     dec:15063544 z-2-3  salle a manger
                    000100000001100111111000     dec:1055224 z-3-1   garage portail
                    000011110110001011111000     dec:1008376  z-3-2 garage porte

  http://139.59.206.133/8f8e430dabe94c53b4b3f18d610abd87/update/D35

  http://139.59.206.133/8f8e430dabe94c53b4b3f18d610abd87/update/V14?value=1

*/

int pulse[15] = {290, 292, 302, 301, 301, 299,
                 300, 297, 300, 301, 302, 299, 284, 285, 286
                };

long code[15] = {
  "100000111111110011010100",
  "100011011100111000000000",
  "100011011100111000001100",
  "100011011100111000000010",
  "100011011100111000001010",
  "100011011100111000000110",
  "100011011100111000001110",
  "100011010000000000000000",
  "100011011100111000001001",
  "100011011100111000000000",
  "100011011100111000001101",
  "100011011100111000000011",
  "111110100010000011101000",
  "111110100010000011100001",
  "111110100010000011100010",
};


#define Sen_Z_1_0 1922552
#define Sen_Z_2_4 10100216
#define Sen_Z_2_2 4478032
#define Sen_Z_2_3 15063544
#define Sen_Z_3_1 1055224
#define Sen_Z_3_2 1008376

#define R1 9293320
#define R2 9293312
#define R3 9293324
#define R4 9293314
#define R5 9293322
#define R6 9293318
#define R7 9293326
#define R8 9240576
#define R9 9293321
#define R10 9293312
#define R11 9293325
#define R12 9293315
#define portail1 8585216
#define portail2 16392424
#define clioA 16392417
#define clioB 16392418
#define buttonB 8649940
#define fiatOuv 14296297
#define fiatFerm 15377001

#define BLYNK_PRINT Serial
#define DATA_TX433 51
#define VINRF433 53
#define DATA_RX433 3
#define VINRX433 11
#define GNDRX433 8
#define DATA_TX315 50
#define VINRF315 48
#define GNDRF315 46
#define VINDH A0
#define DHTPIN A1
#define GNDDH A2
#define DHTTYPE DHT11   // DHT 11 
#define timeSpace 1500
#define AlarmState 52

#include <RCSwitch.h>
#include "DHT.h"




#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";//"";
char pass[] = "";//"";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial3
BlynkTimer timer;
// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);
RCSwitch tx433 = RCSwitch();
RCSwitch tx315 = RCSwitch();
RCSwitch rx433 = RCSwitch();
DHT dht(DHTPIN, DHTTYPE, 6);


BLYNK_WRITE(V0)
{
  int pinData = param.asInt();

  if (pinData)
  {

    tx433.setPulseLength(284);
    tx433.send("111110100010000011101000");
    Blynk.virtualWrite(0, LOW);
  }
}

BLYNK_WRITE(V1)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(292);
    tx315.send("100011011100111000000000");
    Blynk.virtualWrite(1, LOW);
  }
}


BLYNK_WRITE(V2)
{

  if (param.asInt())
  {
    digitalWrite(AlarmState, HIGH);
  } else {
    digitalWrite(AlarmState, LOW);
  }
}



BLYNK_WRITE(V5)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    actionRelays();

  }
}

BLYNK_WRITE(V6)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001110");
  }
}


BLYNK_WRITE(V7)
{
  int pinData = param.asInt();

  if (pinData)
  {
    tx433.setPulseLength(285);
    tx433.send("111110100010000011100001");
    Blynk.virtualWrite(7, LOW);
  }
}


BLYNK_WRITE(V8)
{
  int pinData = param.asInt();

  if (pinData)
  {
    tx433.setPulseLength(286);
    tx433.send("111110100010000011100010");
    Blynk.virtualWrite(8, LOW);
  }
}

BLYNK_WRITE(V9)
{
  int pinData = param.asInt();

  if (pinData)
  {
    tx433.setPulseLength(286);
    tx433.send("110110100010010011101001");
    Blynk.virtualWrite(9, LOW);
  }
}


BLYNK_WRITE(V10)
{
  int pinData = param.asInt();

  if (pinData)
  {
    tx433.setPulseLength(286);
    tx433.send("111010101010001001101001");
    Blynk.virtualWrite(10, LOW);
  }
}



BLYNK_WRITE(V11)
{
  int pinData = param.asInt();

  if (pinData)
  {
    tx433.setPulseLength(286);
    tx433.send("100100101011010001100101");
    Blynk.virtualWrite(11, LOW);
  }
}

BLYNK_WRITE(V12)
{
  int pinData = param.asInt();

  if (pinData)
  {
    tx433.setPulseLength(286);
    tx433.send("111011111000101100111001");
    Blynk.virtualWrite(12, LOW);
  }
}

BLYNK_WRITE(V13)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001100");
  }
}

BLYNK_WRITE(V14)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000000010");
  }
}


BLYNK_WRITE(V15)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001010");
  }
}

BLYNK_WRITE(V16)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000000011");
  }
}

BLYNK_WRITE(V17)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001110");
  }
}

BLYNK_WRITE(V18)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011010000000000000000");
  }
}

BLYNK_WRITE(V19)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001001");
  }
}

BLYNK_WRITE(V20)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000000000");
  }
}

BLYNK_WRITE(V21)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001101");
  }
}



BLYNK_WRITE(V22)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(22, LOW);
  }
}


BLYNK_WRITE(V23)
{
  int pinData = param.asInt();

  if (pinData == 0)
  { digitalWrite(23, LOW);
  }

}


BLYNK_WRITE(V24)
{
  int pinData = param.asInt();

  if (pinData == 0)
  { digitalWrite(24, LOW);
  }
}


BLYNK_WRITE(V25)
{
  int pinData = param.asInt();

  if (pinData == 0)
  { digitalWrite(25, LOW);
  }
}


BLYNK_WRITE(V26)
{
  int pinData = param.asInt();

  if (pinData == 0)
  { digitalWrite(26, LOW);
  }
}



BLYNK_WRITE(V27)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(27, LOW);
  }
}

BLYNK_WRITE(V28)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(28, LOW);
    tx315.setPulseLength(300);
    tx315.send("100011011100111000001000");
  }
}

BLYNK_WRITE(V29)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(29, LOW);
  }
}

BLYNK_WRITE(V30)
{
  int pinData = param.asInt();

  if (pinData == 1)
  {
    digitalWrite(30, LOW);
  } else {
    digitalWrite(30, HIGH);
  }
}

BLYNK_WRITE(V31)
{
  int pinData = param.asInt();

  if (pinData == 1)
  {
    digitalWrite(31, LOW);
  } else {
    digitalWrite(31, HIGH);
  }
}

BLYNK_WRITE(V32)
{
  int pinData = param.asInt();

  if (pinData == 1)
  {
    digitalWrite(32, LOW);
  } else {
    digitalWrite(32, HIGH);
  }
}

BLYNK_WRITE(V33)
{
  int pinData = param.asInt();

  if (pinData == 1)
  {
    digitalWrite(33, LOW);
  } else {
    digitalWrite(33, HIGH);
  }
}

BLYNK_WRITE(V34)
{
  int pinData = param.asInt();

  if (pinData == 1)
  {
    digitalWrite(34, LOW);
  } else {
    digitalWrite(34, HIGH);
  }
}

BLYNK_WRITE(V35)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(35, LOW);
  }
}

BLYNK_WRITE(V36)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(36, LOW);
  }
}

BLYNK_WRITE(V37)
{
  int pinData = param.asInt();

  if (pinData == 0)
  {
    digitalWrite(37, LOW);
  }
}

//ESP8266 wifi(Serial3,115200);
void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(VINRF433, OUTPUT);
  pinMode(VINRF315, OUTPUT);
  pinMode(GNDRF315, OUTPUT);
  pinMode(VINDH, OUTPUT);
  pinMode(GNDDH, OUTPUT);
  pinMode(VINRX433, OUTPUT);
  pinMode(GNDRX433, OUTPUT);

  for (int i = 22; i < 38; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(VINRF433, HIGH);
  digitalWrite(VINRF315, HIGH);
  digitalWrite(GNDRF315, LOW);
  digitalWrite(VINDH, HIGH);
  digitalWrite(GNDDH, LOW);
  digitalWrite(VINRX433, HIGH);
  digitalWrite(GNDRX433, LOW);

  tx433.enableTransmit(DATA_TX433);
  rx433.enableReceive(digitalPinToInterrupt(DATA_RX433));

  tx315.enableTransmit(DATA_TX315);

  // Start dht_temp
  dht.begin();
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);


  Blynk.begin(auth, wifi, ssid, pass);
  //Blynk.notify("Device started");
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8442);
  timer.setInterval(5000L, getEnvi);
  timer.setInterval(1500L, setRelays);
}

void loop()
{
  Blynk.run();
  timer.run();
  if (rx433.available()) {
    unsigned long dec = rx433.getReceivedValue();
    const char* bin = getBin(dec, rx433.getReceivedBitlength());
    Serial.print("Dec: ");
    Serial.println(dec);
    Serial.print("Bin: ");
    Serial.println(bin);

    if (digitalRead(AlarmState)) {
      switch (dec) {

        case portail1:
          Blynk.notify("Maison: Le portail est ouvert");
          break;
        case portail2:
          Blynk.notify("Maison: Le portail est ouvert");
          break;
        case clioA:
          Blynk.notify("Clio: la voiture est déverrouillée");
          break;
        case clioB:
          Blynk.notify("Clio: la voiture est verrouillée");
          break;
        case buttonB:
          Blynk.notify(bin);
          break;
        case Sen_Z_1_0:
          Blynk.notify("Alarme: Chambres");
          break;
        case Sen_Z_2_4:
          Blynk.notify("Alarme: Salon TV");
          break;
        case Sen_Z_2_2:
          Blynk.notify("Alarme: Entrée");
          break;
        case Sen_Z_2_3:
          Blynk.notify("Alarme: Salle à manger");
          break;
        case Sen_Z_3_1:
          Blynk.notify("Alarme: Garage portail");
          break;
        case Sen_Z_3_2:
          Blynk.notify("Alarme: Garage porte");
          break;
      }
    }

    rx433.resetAvailable();
  }
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

void getEnvi() {
  int humi = dht.readHumidity();
  // Read temperature as Celsius
  int temp = dht.readTemperature();
  Blynk.virtualWrite(V4, humi);
  Blynk.virtualWrite(V3, temp);
}

void setRelays() {
  for (int i = 22; i < 30; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(35, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(37, HIGH);
}

void relay2() {
  digitalWrite(23, LOW);
}

void relay3() {
  digitalWrite(24, LOW);
}

void relay4() {
  digitalWrite(25, LOW);
}
void relay5() {
  digitalWrite(26, LOW);
}

void actionRelays() {
  digitalWrite(22, LOW);
  timer.setTimeout(timeSpace, relay2);
  timer.setTimeout(timeSpace * 2, relay3);
  timer.setTimeout(timeSpace * 3, relay4);
  timer.setTimeout(timeSpace * 4, relay5);
}

