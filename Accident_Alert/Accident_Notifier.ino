#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <TinyGPS++.h>

SoftwareSerial GSMserial(2,3); // Rx = 2 , Tx = 3
MPU6050_tockn mpu6050(Wire);
TinyGPSPlus GPS;

float gps_latitude;
float gps_longitude;
float Angle_X;

void setup() {
  mpu6050_intailazion();
  Gps_intailazion();
  GSMserial.begin(9600);
}

void loop() {
  Gps_Data();
  AngleX();
  Condition_sendMSG()
}

void mpu6050_intailazion(){
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  }

void Gsm_intailazion(){
   delay(1000);
   GSMserial.begin(9600);
   GSMserial.write("AT+CMGF=1");
   delay(1000);
  }
  
void Gps_intailazion(){
  Serial.begin(115200); // Serial Monitor use for GPS module
  }

void Gps_Data(){
  while (Serial.available()){
  GPS.encode(GPS.read());
  if (GPS.location.isUpdated()){
    gps_latitude = GPS.location.lat();
    gps_longitude = GPS.location.lng();
   }
  }
 }

void AngleX(){
  mpu6050.update();
  Angle_X = mpu6050.getAngleX();
}

void Condition_sendMSG(){
  if(Angle_X > 75.0){
    GSMserial.println("AT+CMGS=\"+919694678634\"\r");
    delay(1000);
    GSMserial.println();
    delay(1000);
    GSMserial.println((char)26);
    delay(1000);
    }
  }
