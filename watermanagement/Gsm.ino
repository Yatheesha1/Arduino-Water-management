void gsm()
{
  if (mySerial.available())
  { 
    id=0;
    message="";
    num="";
    String msg=mySerial.readString();
    Serial.println(msg);
    num=msg.substring(9,22);
    Serial.print("Number:");   
    Serial.println(num);   
    message=msg.substring(51,msg.length()-2);
    if(num==number1)
        id=1;
    if(num==number2)
        id=2;
    if(num==number3)
        id=3;
    if(num!="" && value>0 && id!=0)
    {
      SendMessage(state[1],num);
      delay(1000);
      process(); 
      SendMessage(state[0],num);
      delay(1000);
    } 
  } 
}

void SendMessage(String st,String nu)
{
  mySerial.println("AT+CMGF=1\r\n"); //Sets the GSM Module in Text Mode
  delay(1000); // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\""+nu+"\"\r\n"); // Replace x with mobile number
  delay(1000);
  mySerial.println(st);
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
