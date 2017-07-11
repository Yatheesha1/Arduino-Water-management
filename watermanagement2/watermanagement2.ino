byte sensorInterrupt = 0; 
byte flowPin = 7;//flow sensor pin
int valvePin1=4;//relay pin
int value=0;
byte z=0;
int wait=0;

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
  Serial.begin(9600);
  
  pinMode(flowPin, INPUT);
  pinMode(valvePin1, OUTPUT);
  
  Serial.println("...........................................................");
  Serial.println("Enter input in ML");
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop()
{
   pulseCount        = 0;
   flowRate          = 0.0;
   flowMilliLitres   = 0;
   totalMilliLitres  = 0;
   oldTime           = 0;
   value=0;
   digitalWrite(valvePin1,LOW);
   if(z=0)
   {
    Serial.println("Stopped");
    z=1;
   } 
   if(Serial.available()>0)
   {
     value=Serial.parseInt();
     Serial.print("Required ML: ");
     Serial.println(value);
     pulseCount        = 0;
     flowRate          = 0.0;
     flowMilliLitres   = 0;
     totalMilliLitres  = 0;
     oldTime           = 0;
     Serial.println("Started");
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
     digitalWrite(valvePin1,LOW);
     }   
     Serial.println("Stopped");
     Serial.println("...........................................................");
     Serial.println("Enter input in ML");
     z=0;
   }
}   
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
