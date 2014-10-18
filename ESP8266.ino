//passthrough code

char serialbuffer[100];//serial buffer for request url


void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200); 
}

void loop()
{
  if (Serial.available() > 0) {

     //read from serial until terminating character
     int len = Serial.readBytesUntil('\n', serialbuffer, sizeof(serialbuffer));
  
     //trim buffer to length of the actual message
     String message = String(serialbuffer).substring(0,len);
     
     //find the dividing marker between domain and path
     int slash = message.indexOf('/');
     
     //grab the domain
     String domain = message.substring(0,slash);
     
     //get the path
     String path;
     if(slash>0){  
       path = message.substring(slash + 1);   
     }else{
       path = "";          
     }
     
     //output domain and path to verify
     Serial.println(domain);
     Serial.println(path);     
     
     //create start command
     String startcommand = "AT+CIPSTART=\"TCP\",\"" + domain + "\",80";
     Serial1.println(startcommand);
     Serial.println(startcommand);
     
     
     //test for a start error
     if(Serial1.find("Error")){
       Serial.println("error on start");
       return;
     }
     
     //create the request command
     String sendcommand = "GET /" + path + " HTTP/1.0\r\n\r\n";//works for most cases
  
     
     
     //send 
     Serial1.print("AT+CIPSEND=");
     Serial1.println(sendcommand.length());
     
     Serial.print("AT+CIPSEND=");
     Serial.println(sendcommand.length());
     
     
     
     if(Serial1.find(">"))
     {
       Serial.println(">");
     }else
     {
       Serial1.println("AT+CIPCLOSE");
       Serial.println("connect timeout");
       delay(1000);
       return;
     }
     
     //Serial.print(getcommand);
     Serial1.print(sendcommand);
  }
  
  //output everything from ESP8266 to the Serial output
  if (Serial1.available() > 0) {
    Serial.write(Serial1.read());
  }
}
