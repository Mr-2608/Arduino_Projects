#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <TinyGPS++.h>

SoftwareSerial GSMserial(3,4); // Rx = 3 , Tx = 4
MPU6050 mpu6050(Wire);
TinyGPSPlus GPS;

String gps_latitude;
String gps_longitude;
float Angle_X;

void setup() {
  mpu6050_intailazion();
  Gps_intailazion();
  Gsm_intailazion(); 
}

void loop() {
  Gps_Data();
  AngleX();
  Condition_sendMSG();
}

void mpu6050_intailazion(){
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  }

void Gsm_intailazion(){
   delay(1000);
   GSMserial.begin(9600);
   GSMserial.println("AT+CMGF=1");
   delay(1000);
  }
  
void Gps_intailazion(){
  Serial.begin(9600); // Serial Monitor use for GPS module
  }

void Gps_Data(){
  while(Serial.available())
  {
    GPS.encode(Serial.read());
  }
  if(GPS.location.isUpdated()) 
  {
    gps_latitude = String(GPS.location.lat());
    gps_longitude = String(GPS.location.lng());
    
 }
}

void AngleX(){
  mpu6050.update();
  Angle_X = mpu6050.getAngleX();
}

void Condition_sendMSG(){
  if(Angle_X > 40.0 or Angle_X < -40.0){
    GSMserial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
    delay(1000);
    GSMserial.println("Your Vechical No. RJ14XXXXXX met with an accident at location:");
    delay(1000);
    GSMserial.println("https://www.google.com/maps/@"+gps_latitude+","+gps_longitude+",14z");
    delay(1000);
    GSMserial.println((char)26);
    delay(1000);
    }
  }
