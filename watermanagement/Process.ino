void process()
   {
     pulseCount        = 0;
     flowRate          = 0.0;
     flowMilliLitres   = 0;
     totalMilliLitres  = 0;
     oldTime           = 0;
     Serial.println("Started");
     if(id==1)
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
              if(wait>500)
              { 
                wait=0;         
                break;  
              }   
            }  
      }
     digitalWrite(valvePin1,LOW);
     }
     if(id==2)
     {
       digitalWrite(valvePin2,HIGH);
       delay(5000);
       digitalWrite(valvePin2,LOW);
     }
     if(id==3)
     {
       digitalWrite(valvePin3,HIGH);
       delay(5000);
       digitalWrite(valvePin3,LOW);
     }
     Serial.println("Stopped");
     Serial.println("...........................................................");
     Serial.println("Enter input in ML");
     z=0;
     id=0;
	 }
