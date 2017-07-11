void Reset()
{  
   pulseCount        = 0;
   flowRate          = 0.0;
   flowMilliLitres   = 0;
   totalMilliLitres  = 0;
   oldTime           = 0;
   value=0;
   digitalWrite(valvePin1,LOW);
   digitalWrite(valvePin2,LOW);
   digitalWrite(valvePin3,LOW);
   //digitalWrite(flowPin,LOW);
   if(z=0)
   {
    Serial.println("Stopped");
    z=1;
   } 
}   
