char serialbuffer[1000];//serial buffer for request url






void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200); 
  
  Serial1.println("AT+RST");
  Serial1.println("AT+CWMODE=1");
  delay(500);
  Serial1.println("AT+RST");

  Serial1.println("AT+CWJAP=\"YOUR_WIFI_NETWORK\",\"YOUR_WIFI_PASSWORD\"");


  
}

void loop()
{
  //output everything from ESP8266 to the Arduino Micro Serial output
  while (Serial1.available() > 0) {
    Serial.write(Serial1.read());
  }
  
  if (Serial.available() > 0) {

     //read from serial until terminating character
     int len = Serial.readBytesUntil('\n', serialbuffer, sizeof(serialbuffer));
  
     //trim buffer to length of the actual message
     String message = String(serialbuffer).substring(0,len-1);
     Serial.println("message: " + message);
     
     
     
     if(message.substring(0,2)=="AT"){
       //make command request
       Serial.println("COMMAND REQUEST");
       Serial1.println(message); 
     }else{
      //make webrequest
       Serial.println("WEB REQUEST");
       WebRequest(message);
     }
     
     
     
     

     
     
  }
  

}




void WebRequest(String request){
 //find the dividing marker between domain and path
     int slash = request.indexOf('/');
     
     //grab the domain
     String domain;
     if(slash>0){  
       domain = request.substring(0,slash);
     }else{
       domain = request;
     }

     //get the path
     String path;
     if(slash>0){  
       path = request.substring(slash);   
     }else{
       path = "/";          
     }
     
     //output domain and path to verify
     Serial.println("domain: |" + domain + "|");
     Serial.println("path: |" + path + "|");     
     
     //create start command
     //String startcommand = "AT+CIPSTART=\"TCP\",\"signalvehicle.com\",80";
     String startcommand = "AT+CIPSTART=\"TCP\",\"" + domain + "\", 80"; //443 is HTTPS
     
     Serial1.println(startcommand);
     Serial.println(startcommand);
     
     
     //test for a start error
     if(Serial1.find("Error")){
       Serial.println("error on start");
       return;
     }
     
     //create the request command
     String sendcommand = "GET http://"+ domain + path + " HTTP/1.0\r\n\r\n\r\n";//works for most cases
     
     Serial.print(sendcommand);
     
     //send 
     Serial1.print("AT+CIPSEND=");
     Serial1.println(sendcommand.length());
     
     Serial.print("AT+CIPSEND=");
     Serial.println(sendcommand.length());
     
     //delay(5000);
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
