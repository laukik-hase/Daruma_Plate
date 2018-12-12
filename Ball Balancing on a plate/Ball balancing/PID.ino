#include <SRA16.h>  //Basic library used for loops and some functions
#include<Servo.h>
int x,y,setpointx=123,setpointy=174,PIDx,PIDy;
int a[6],i;
int errorx,errory,pidflag=0,preverrory=0,preverrorx=0;
float Kpx=0.14,

      Kdx=-0.475,
      
      Kpy=0.17,
      
      Kdy=-0.22;

Servo myservo;
Servo yourservo;
void setup() 
{
 Serial.begin(115200); // set the baud rate
 myservo.attach(12);
 yourservo.attach(14);
 myservo.write(119);
 yourservo.write(55);
 
}
void loop()
{
while(Serial.available()>=6)
{
  for(i=0;i<6;i++)
  {
    a[i]=Serial.read()-'0';
  }
  x=100*a[0]+10*a[1]+a[2];
  y=100*a[3]+10*a[4]+a[5];
  
  errorx = setpointx - x;
  errory = setpointy - y;

  
  PIDx=Kpx*errorx + Kdx*(preverrorx-errorx) ;
  preverrorx=errorx;
  
  PIDy=Kpy*errory + Kdy*(preverrory-errory);
  preverrory=errory;
  

  if((errory<=15)&&(errory>=-15))
   {
     myservo.write(119);
     
   }
  else
   {
     PIDy=constrain(PIDy,-34,9);
     myservo.write(119-PIDy);
     delay(1);
     
   }
  
  
  if((errorx<=15)&&(errorx>=-15))
   {
     yourservo.write(55);
   } 
  else
   {
     yourservo.write(55+PIDx);
     delay(1);
   }
}
}