#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define RELAY 3 //connect the relay to number 3 pin
#define BUZZER 2 // connect the buzzer to 2 pin
#define PROXY 5 // Proxy output
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

int Reading ;
String cardReading;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup()
{
intailazation();
gsmIntailazion();
Serial.println("Put your card to the reader for scanning …");
Serial.println();

}

void loop()
{
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
//Show UID on serial monitor
Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
Serial.print("Message : ");
content.toUpperCase();
cardReading = content.substring(1);
if (content.substring(1) == "D3 7D 30 0D" || content.substring(1) == "5C 60 37 64" ) // enter your own card number after copying it from serial monitor
{
Serial.println("Authorized access");
tone(BUZZER,1000);
delay(500);
noTone(BUZZER);
Serial.println();
delay(500);
digitalWrite(RELAY, LOW);
delay(ACCESS_DELAY);
digitalWrite(RELAY, HIGH);
sendMSG();

}


else {
  Serial.println(" Access denied");
  tone(BUZZER, 300);
  sendMSG();
  delay(DENIED_DELAY);
  noTone(BUZZER);
  }
}

void intailazation(){
  
   Serial.begin(9600); // Initiate a serial communication
   SPI.begin(); // Initiate SPI bus
   mfrc522.PCD_Init(); // Initiate MFRC522
   pinMode(RELAY, OUTPUT);
   pinMode(BUZZER, OUTPUT);
   pinMode(7, OUTPUT);
   noTone(BUZZER);
   digitalWrite(RELAY, HIGH);
   digitalWrite(7,LOW);

  }

void gsmIntailazion(){
  
   delay(1000);
   Serial.begin(9600);
   Serial.println("AT+CMGF=1");
   delay(1000);
   
  }
  
void sendMSG(){
   if (cardReading == "D3 7D 30 0D" ){
    Serial.println("AT+CMGS=\"+918078621094\"\r");
    delay(1000);
    Serial.println("Shubham , enter in the house");
    delay(1000);
    Serial.println((char)26);
    delay(1000);}

    if (cardReading == "5C 60 37 64" ){
    Serial.println("AT+CMGS=\"+918078621094\"\r");
    delay(1000);
    Serial.println("Vishal , enter in the house");
    delay(1000);
    Serial.println((char)26);
    delay(1000);}
    
    
  }
