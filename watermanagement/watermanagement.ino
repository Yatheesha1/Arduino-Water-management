#include <SoftwareSerial.h>
#include<String.h>
#include <SPI.h>
#include <Ethernet.h>

String number1="+918495897091";
String number2="+917019244463";
String number3="+918848337736";

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//MAC address

IPAddress ip(192,168,137,20);//
EthernetServer server(80);

SoftwareSerial mySerial(2,3);//(Rx,Tx)

byte sensorInterrupt = 0; 
byte flowPin = 7;//flow sensor pin
int valvePin1=4;//relay pin
int valvePin2=5;
int valvePin3=6;
int value=0;
byte z=0;
int wait=0;
int id=0;

const char *state[]={"STARTED","STOPPED"};
String num="";
String message="";

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  server.begin();
  mySerial.begin(9600);
  Serial.begin(9600);
  
  pinMode(flowPin, INPUT);
  pinMode(valvePin1, OUTPUT);
  pinMode(valvePin2, OUTPUT);
  pinMode(valvePin3, OUTPUT);
  
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  Serial.println(mySerial.readString());
  
  Serial.println("...........................................................");
  Serial.println("Enter input in ML");
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  Reset();
}

void loop()
{
   Reset();
   gsm();
   ether();
   serial();
}   

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
