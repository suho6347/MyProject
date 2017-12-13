#include "Altino.h"

#include <stdio.h>
#include<time.h>
void turn(){

    int i4,input;
    SensorData dat;


    Go(-300,-300);

    delay(1200);

    Go(0,0);
    delay(100);

    Steering(1);

    Go(220,450);

    delay(2200);

    Steering(2);

    Go(300,300);

    delay(100);


    Go(0,0);

    return;

}

void music(){
    Sound(41);
    delay(500);
    Sound(41);
    delay(500);
    Sound(37);
    delay(500);
    Sound(37);
    delay(500);
    Sound(45);
    delay(500);
    Sound(41);
    delay(500);
    Sound(0);
    return;
}

void heart(){
    DisplayLine(0x42,0xe7,0xff,0xff,0xff,0x7e,0x3c,0x18);
    delay(3000);
    Display(0);
}



void ledcycle(){
    Led(0x0001);
    delay(500);
    Led(0);
    Led(0x0010);
    delay(500);
    Led(0);
    Led(0x0040);
    delay(500);
    Led(0);
    Led(0x0004);
    delay(500);
    Led(0);
    Led(0x8000);
    delay(500);
    Led(0);
    Led(0x4000);
    delay(500);
    Led(0);
    Led(0x0008);
    delay(500);
    Led(0);
    Led(0x0080);
    delay(500);
    Led(0);
    Led(0x0020);
    delay(500);
    Led(0);
    Led(0x0002);
    delay(500);
    Led(0);
    return;
    }



void backgear(){

    Go(0,0);
    delay(100);
    Steering(2);
    Go(-300,-300);
    delay(100);
    Steering(1);

    Go(-220,-450);

    delay(1900);

    Steering(2);

    Go(300,300);

    delay(4000);


    return;

}



void backgearR(){
    int i5;
    SensorData dat;
    printf("R\n");
while(1){
    dat=Sensor(10);
    i5=dat.IRSensor[5];
    Steering(2);

    Go(-400,-400);
    if(i5>100){
        break;
    }

}
    Go(0,0);

    delay(5000);
    return;

}



int main(void)

{
 double time_cal;
 time_t start, end;
 int i=0,input,num;
 int i0,i1,i2,i3,i4,i5,j=0,cd=1000;

 SensorData dat;

 Open(szPort);
 start=clock();


    dat=Sensor(10);

  i0=dat.IRSensor[0];

  i1=dat.IRSensor[1];

  i2=dat.IRSensor[2];

  i3=dat.IRSensor[3];

  i4=dat.IRSensor[4];

  i5=dat.IRSensor[5];

  cd=dat.CDSSensor;
  printf("i0 : %d, i1 : %d, i2 : %d, i4 : %d, cd : %d\n",i0,i1,i2,i4,cd);

  scanf("%d",&input);
   Sound(40);
 delay(1000);
 Sound(0);


 while(1)
 {

  dat=Sensor(10);

  i0=dat.IRSensor[0];

  i1=dat.IRSensor[1];

  i2=dat.IRSensor[2];

  i3=dat.IRSensor[3];

  i4=dat.IRSensor[4];

  i5=dat.IRSensor[5];

  cd=dat.CDSSensor;
    printf("i0 : %d, i1 : %d, i2 : %d, i4 : %d, cd : %d\n",i0,i1,i2,i4,cd);
  Steering(2);

  Go(300,300);
  delay(300);
  Go(0,0);

  //좁은공간에서 막혀있을때 Steering2 로 빠져나가도록 해야함 , 아니면 측면센서 값을 받아서 빠져나가도록 해야될듯?

  if(i0>20 || i1>20 || i2>20) // 값을 조금더 키워야함

  {

   if(i0>i2)

   {

    Steering(2);

    Go(-300,-300);

    delay(1000);

    Steering(3);

    Go(300,300);

    delay(1000);

   }



   else

   {

    Steering(2);

    Go(-300,-300);

    delay(1000);

    Steering(1);

    Go(300,300);

    delay(1000);

   }

   dat=Sensor(10);

   i0=dat.IRSensor[0];

   i1=dat.IRSensor[1];

   i2=dat.IRSensor[2];

  }

    if(i4<20 && cd>200 && i2<20)//좌회전
        {
    printf("turn left\n");
    turn();
        if(i==0){

            printf("first turn\n");
            Go(0,0);
            music();

            backgear();

            i++;
            dat=Sensor(10);
            i4=dat.IRSensor[4];
            cd=dat.CDSSensor;
            continue;

        }

        if(i==1){

            printf("second turn\n");
            heart();

            backgear();

            i++;
            dat=Sensor(10);
            i4=dat.IRSensor[4];
            cd=dat.CDSSensor;
            continue;
        }

        if(i==2){

            printf("third turn\n");
            ledcycle();

            backgearR();
            i++;
            dat=Sensor(10);
            i4=dat.IRSensor[4];
            cd=dat.CDSSensor;
            continue;
        }
            dat=Sensor(10);
            i4=dat.IRSensor[4];
            cd=dat.CDSSensor;
    continue;
    }

 /*   if(cd<100){

        if(i==0){
            printf("first turn\n");
            Go(0,0);
            delay(1000);
            //music();

            backgear();

            i++;
            dat=Sensor(10);
            cd=dat.CDSSensor;
            continue;

        }

        if(i==1){
            printf("second turn\n");
            heart();

            backgear();

            i++;
            dat=Sensor(10);
            cd=dat.CDSSensor;
            continue;
        }

        if(i==2){
            printf("third turn\n");
            ledcycle();

            backgearR();
            i++;
            dat=Sensor(10);
            cd=dat.CDSSensor;
            continue;
        }

    }*/
    if(i0<0 && i1<0 && i2<0 && i3<0 && i4<0){
        scanf("%d",num);
    }
    if(num==1){
        break;
    }
}
end=clock();
time_cal=(double)(end-start)/CLK_TCK;
printf("\n\n We spent %f clock time",time_cal);
Close();

}
