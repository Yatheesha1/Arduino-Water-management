void serial()
{
   if(Serial.available()>0)
   {
     value=Serial.parseInt();
     Serial.print("Required ML: ");
     Serial.println(value);
     process();
   }
}   
