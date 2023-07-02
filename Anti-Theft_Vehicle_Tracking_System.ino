#include <SoftwareSerial.h>
    #include <TinyGPS.h>
    
    int state = 0;
    const int pin = 9;  
    float gpslat, gpslon;
    
    TinyGPS gps;
    SoftwareSerial sgps(5,4);//tx=5,rx=4,Software Serial Library is used to allow serial communication on pin 5 and 4
    SoftwareSerial sgsm(2,3);//tx=2,rx=3    
    
    void setup()
    {
      sgsm.begin(9600);
      sgps.begin(9600);
    }
    
    void loop()
    {
    sgps.listen();
      while (sgps.available())
      {
        int c = sgps.read();
        if (gps.encode(c))
        {
          gps.f_get_position(&gpslat, &gpslon);
        }
      }
        if (digitalRead(pin) == HIGH && state == 0) 
        { //state = 1; 
          sgsm.listen();
          sgsm.print("\r");
          delay(1000);
          sgsm.print("AT+CMGF=1\r");
          delay(1000);
          sgsm.print("AT+CMGS=\"+91**********\"\r"); //Receiver's Phone Number
          delay(1000);
            sgsm.println("Your Vehicle is ON now, at the location:");
            sgsm.print("https://www.google.com/maps/?q=");
          sgsm.print(gpslat, 6);
          sgsm.print(",");
          sgsm.print(gpslon, 6);
          delay(1000);
          sgsm.write(0x1A);
          delay(1000);
          state = 1;
          
        }
      if (digitalRead(pin) == LOW && state == 1) {
          state = 0;
          sgsm.listen();
          sgsm.print("\r");
          delay(1000);
          sgsm.print("AT+CMGF=1\r");
          delay(1000);
          sgsm.print("AT+CMGS=\"+91**********\"\r"); //Receiver's Phone Number
          delay(1000);
          
          sgsm.println("Your Vehicle is OFF now, at the location:");
            sgsm.print("https://www.google.com/maps/?q=");
          sgsm.print(gpslat, 6);
          sgsm.print(",");
          sgsm.print(gpslon, 6);
          delay(1000);
          sgsm.write(0x1A);
          delay(1000);
        }
          delay(100);
    }    
