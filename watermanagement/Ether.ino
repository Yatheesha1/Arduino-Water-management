void ether()
{
  String readString;
  client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {   
      id=0;
      if (client.available()) 
      {
         char c = client.read(); 
         //read char by char HTTP request
         if (readString.length() < 100) 
         {
          //store characters to string
          readString += c;
         }


         //if HTTP request has ended
         if (c == '\n') 
         {              
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           
           client.println();  
              
           client.println("<HTML>");
           
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Arduino Project</TITLE>");
           client.println("</HEAD>");
           
           client.println("<BODY>");  
                  
           client.println("<br/>");  
           client.println("<H2>Water Management</H2>");
                      
           client.println("<FORM ACTION='/' method=get >"); //uses IP/port of web page
           client.println("Enter User Number: <INPUT TYPE=TEXT NAME='nm' VALUE='' SIZE='25' MAXLENGTH='13'>");
           client.println("<br />");
           client.println("<br />");
           client.println("Enter Liter   : <INPUT TYPE=TEXT NAME='ML' VALUE='' SIZE='25' MAXLENGTH='13'>");
           client.println("<br />");
           client.println("<br />");
           client.println("<INPUT TYPE=SUBMIT NAME='submit' VALUE='SUBMIT'>");
           client.println("</FORM>");  
           client.println("<br />");

           client.println("</BODY>");
           
           client.println("</HTML>");
           client.stop();
           //clearing string for next read
     
           //stopping client
           
           //controls the Arduino if you press the buttons

           num="+";
           message="";  
           if (readString.length() >0) 
            {
            //Serial.println(readString); //prints string to serial port out
            int pos1 = readString.indexOf("nm=");
            int pos2 = readString.indexOf("&ML=");
            int pos3 = readString.indexOf("&submit");
            if(pos1>0 && pos2 >pos1)
            {
            num += readString.substring(pos1+6, pos2);
            message = readString.substring(pos2+4, pos3); 
            int temp=message.toInt();//convert to integer
            value=temp*1000;//////////////////////////////////////////////////////in liter
            Serial.print("User: ");
            Serial.println(num);
            Serial.print("Required ML: ");
            Serial.println(value);
            readString=""; //clears variable for new input  
            if(num==number1)
              id=1;
            if(num==number2)
              id=2;
            if(num==number3)
              id=3; 
            if(num!="" && value>0)
            {
              SendMessage(state[1],num);
              delay(1000);
              process(); 
              SendMessage(state[0],num);
              delay(1000);
            } 
            } 
            num="";
            message="";           
           }      
           readString="";            
        }
      }
    }
  }
}

