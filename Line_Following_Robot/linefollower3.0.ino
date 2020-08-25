int ir1=4;        // we put 12v batteri in vin (arduino input) and connect all ir sensor with 5v (ardunio input):
int ir2=5;        // all ir sensor readings in ardunio output pin 4,5,6,7,8 and connect motor driver in1,in2,in3 and in4 to pin in arduino 9,10,11,12:
int ir3=6;        // we connect red wire of right dc motor to out1 in motor driver and black in out2: 
int ir4=7;        // we connect red wire of left dc motor to out4 in motor driver and black in out3:
int ir5=8;        
int motor1=9;       //                                         ir b                           :
int motor2=10;      //                                  ir a         ir c                     :
int motor3=11;     //     our ir sensors positioning     -------------                        :
int motor4=12;      //                                  ir d         ir e                     : 
int led =13;         
int a,b,c,d,e;

void setup() {
  
 pinMode (ir1,INPUT);
 pinMode (ir2,INPUT);
 pinMode (ir3,INPUT);
 pinMode (ir4,INPUT);
 pinMode (ir5,INPUT);
 pinMode (motor1,OUTPUT );
 pinMode (motor2,OUTPUT );
 pinMode (motor3,OUTPUT );
 pinMode (motor4,OUTPUT );
 pinMode ( led,OUTPUT);
 Serial.begin(9600);

}

void loop() {

  a= digitalRead (ir1 );
  b= digitalRead (ir2 ); 
  c= digitalRead (ir3 );
  d= digitalRead (ir4 );
  e= digitalRead (ir5 );
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d);
  Serial.println(e);
 if (a==0&&b==1&&c==0)              // move forvard:
{ digitalWrite (motor1,HIGH);
 digitalWrite (motor2,LOW);
 digitalWrite (motor4,HIGH);
 digitalWrite (motor3,LOW);
 digitalWrite (led, LOW);}
 
 else if (a==1&&b==0&&c==0)         // move left:
 {digitalWrite (motor1,HIGH);
 digitalWrite (motor2,LOW);
 digitalWrite (motor3,LOW);
 digitalWrite (motor4,LOW);
 digitalWrite (led, LOW);}

 else if (a==0&&b==0&&c==1)        // move right(sharp turn):
 {digitalWrite (motor1,LOW);
 digitalWrite (motor2,LOW);
 digitalWrite (motor4,HIGH);
 digitalWrite (motor3, LOW);
 digitalWrite (led, LOW);}
 
 else if (a==1&&b==0&&c==1)          // t shape path:
{ digitalWrite (motor1,LOW);
 digitalWrite (motor2,LOW);
 digitalWrite (motor3,LOW);
 digitalWrite (motor4,HIGH);
 digitalWrite (led, LOW);}

 else if (a==1&&b==1&&c==1&&d==1&&e==1)  // stop condition and switch on led:
 {digitalWrite (motor1,LOW);
 digitalWrite (motor2,LOW);
 digitalWrite (motor3,LOW);
 digitalWrite (motor4,LOW);
 digitalWrite (led , HIGH);}

 else if (a==0&&b==0&&c==0&&d==0&&e==0)          // u turn(turn left ):
 {digitalWrite (motor1,HIGH);
 digitalWrite (motor2, LOW);
 digitalWrite (motor3,HIGH);
 digitalWrite (motor4, LOW);
 digitalWrite (led , LOW);}

 else if (a==1&&b==1&&c==1&&d==0&&e==0)  // + shape path (turn right):
 {digitalWrite (motor1,LOW);
  digitalWrite (motor2,HIGH);
  digitalWrite (motor3,LOW);
  digitalWrite (motor4,HIGH);
  digitalWrite (led, LOW);}

 else if (a==1&&b==1&&c==0&&d==0&&e==0)  //       in a t shape if this condition is not applied boat moves in previous path( move forward):
 {digitalWrite (motor1,HIGH);
  digitalWrite (motor2,LOW);
  digitalWrite (motor4,HIGH);
  digitalWrite (motor3,LOW);
  digitalWrite (led ,LOW);}

 else if (a==0&&b==1&&c==1&&d==0&&e==0)  // move right (useful for squre condition):
 {digitalWrite (motor1,LOW);
  digitalWrite (motor2,LOW);
  digitalWrite (motor3,LOW);
  digitalWrite (motor4,HIGH);
  digitalWrite (led, LOW);}
}
