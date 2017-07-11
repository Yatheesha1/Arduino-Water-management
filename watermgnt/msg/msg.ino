#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
void setup()
{
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  mySerial.begin(9600);
  Serial.begin(9600);

  mySerial.println("AT+CMGF=1");
  delay(100);
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(100);

}


void loop()
{

  String msg = mySerial.readString();
  Serial.print(msg);
  delay(1000);

  if (msg.substring(51, 54) >= "1")
  {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(1000);
  }

  if (msg.substring(51, 54) >= "2")
  {
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    delay(1000);
  }
  
}
