#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x3A, 0xDC};
IPAddress server(192, 168, 1, 7); // system ip address
IPAddress ip(192, 168, 1, 8); //  ethernet ip address
EthernetClient client;

byte sensorInterrupt = 0; 
byte flowPin = 7;//flow sensor pin
int valvePin1=4;//relay pin
int valvePin2=5;
int valvePin3=6;
int value=0;
byte z=0;
int wait=0;
String id="",msg="";

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;



void setup() 
{
  pinMode(flowPin, INPUT);
  pinMode(valvePin1, OUTPUT);
  pinMode(valvePin2, OUTPUT);
  pinMode(valvePin3, OUTPUT);
  Serial.begin(9600);
  while (!Serial) 
  {;}

  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  delay(1000);



  if (client.connect(server, 80)) 
  {
    client.println("GET /Smart_Water/Admin/sendcode.php");
    client.println("Host:192.168.1.8");
    client.println("Connection: close");
    client.println();
  }
  else 
  {
    Serial.println("connection failed");
  }
}


void loop()
{
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  if (client.available()) 
  {
    String c = client.readString();

    Serial.print(c.substring(2,5));
    id=c.substring(0,2);
    msg=c.substring(2,5);
    value=c.toInt();
    if(value>0)
    {
    Serial.println("Started");
    if(id=="03")
    {
     while(value>totalMilliLitres)
     {   
       digitalWrite(valvePin1,HIGH);           
       if((millis() - oldTime) > 1000)    // Only process counters once per second
        {                          
          detachInterrupt(sensorInterrupt);
          flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
          oldTime = millis();
          flowMilliLitres = (flowRate / 60) * 1000;
          totalMilliLitres += flowMilliLitres;            
          pulseCount = 0;
          attachInterrupt(sensorInterrupt, pulseCounter, FALLING);                                  
        }
        Serial.print("Quantity: ");        
        Serial.print(totalMilliLitres);
        Serial.println(" mL");
        if(totalMilliLitres<20)
            {
              wait++;
              if(wait>100)
              { 
                wait=0;         
                break;  
              }   
            }  
      }
     digitalWrite(valvePin1,LOW);
     }
     if(id=="01")
     {
       digitalWrite(valvePin2,HIGH);
       delay(5000);
       digitalWrite(valvePin2,LOW);
     }
     if(id=="02")
     {
       digitalWrite(valvePin3,HIGH);
       delay(5000);
       digitalWrite(valvePin3,LOW);
     }
     Serial.println("Stopped");
     z=0;
     client.println(id); 
    }

  }

  if (!client.connected()) 
  {
    Serial.println(); 
    client.println(id); 
     client.println("Unsuccess!"); 
    client.stop();
    while (true);
  }

}

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
