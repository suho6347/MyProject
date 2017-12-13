#include <stdio.h>
#include <time.h>
#include "Altino.h"
#define SPEED 300

void turn()
{
	SensorData dat;
	int i0, i1, i2, i3, i4, cd;

	dat = Sensor(10);
	cd = dat.CDSSensor;

	if (cd < 200) return;
	else {
		i0 = dat.IRSensor[0];
		i1 = dat.IRSensor[1];
		i2 = dat.IRSensor[2];

		if (i0>30 || i1>30 || i2>30)
		{
			if (i0 >= i2)
			{
				Steering(2);
				Go(-SPEED, -SPEED);
				Display('R');
				delay(1000);
				Steering(3);
				Go(SPEED, SPEED);
				Display('D');
				delay(1000);
			}
			else
			{
				Steering(2);
				Go(-SPEED, -SPEED);
				Display('R');
				delay(1000);
				Steering(1);
				Go(SPEED, SPEED);
				Display('D');
				delay(1000);
			}
			dat = Sensor(10);
			i0 = dat.IRSensor[0];
            i1 = dat.IRSensor[1];
            i2 = dat.IRSensor[2];
		}
		else {
			Steering(2);
			Go(SPEED, SPEED);
			Display('D');
		}

		return turn();
	}
}

void turn2()
{
	SensorData dat;
	int i0, i1, i2, i3, i4, cd;

	dat = Sensor(10);
	i0 = dat.IRSensor[0];
	i1 = dat.IRSensor[1];
	i2 = dat.IRSensor[2];

	if (i0>30 || i1>30 || i2>30)
	{
		if (i0 > 300 && i1 > 500 && i2 > 300) {
                Steering(2);
                Go(0,0);
                return;
		}

		if (i0 >= i2)
		{
			Steering(2);
			Go(-SPEED*2, -SPEED*2);
			Display('R');
			delay(1000);
			Steering(3);
			Go(SPEED*2, SPEED*2);
			Display('D');
			delay(1000);
		}
		else
		{
			Steering(2);
			Go(-SPEED*2, -SPEED*2);
			Display('R');
			delay(1000);
			Steering(1);
			Go(SPEED*2, SPEED*2);
			Display('D');
			delay(1000);
		}
	}
	else {
		Steering(2);
		Go(SPEED*2, SPEED*2);
		Display('D');
	}

	return turn2();

}

void sound()
{
    int cd;
    SensorData dat;
    dat = Sensor(10);
    cd = dat.CDSSensor;

	Steering(2);
	Go(0, 0);
	DisplayLine(0, 0, 0, 0, 0, 0, 0, 0);
	Sound(41);
	delay(500);
	Sound(0);
	delay(500);

	Sound(41);
	delay(500);
	Sound(0);
	delay(500);
}

void Rdrive()
{
    int cd;
    SensorData dat;
    dat = Sensor(10);
    cd = dat.CDSSensor;

    Steering(2);
	Go(-SPEED, -SPEED);
    Display('R');
    delay(1200);

	Steering(3);
	Go(-SPEED, -SPEED);
	Display('R');
	delay(1300);

	Steering(1);
	Go(-SPEED, -SPEED);
	Display('R');
	delay(1300);

	Steering(3);
	Go(SPEED, SPEED);
	Display('D');
	delay(1300);


    dat = Sensor(10);
    cd = dat.CDSSensor;
}

void stop()
{
	Steering(2);
	Go(0, 0);
	delay(5000);
}

int main()
{
	int i0, i1, i2, i3, i4, cd;
	SensorData dat;

	double time_cal;
	time_t start, end;

	Open(szPort);

	dat = Sensor(10);
	i0 = dat.IRSensor[0];
	i1 = dat.IRSensor[1];
	i2 = dat.IRSensor[2];
	cd = dat.CDSSensor;

	while (1) {
		dat = Sensor(10);
		cd = dat.CDSSensor;
		if (cd > 200) break;
	}
	Led(0xC0FF);

	start = clock();


	printf("start!\n\n");
	turn();
	printf("in 1st block\n\n");
	sound();
	Rdrive();

	printf("2nd start!\n\n");
	turn();
	printf("in 2nd block\n\n");
	stop();

	printf("3rd start!\n\n");
	//turn2();

	Steering(2);
	Go(SPEED*2,SPEED*2);
	delay(700);
	Steering(3);
	Go(SPEED*2,SPEED*2);
	delay(1400);
	Steering(1);
	Go(SPEED*2,SPEED*2);
	delay(600);
	Steering(2);
	Go(0,0);
	printf("in finish\n\n");

	end = clock();

	time_cal = (double)(end - start) / CLK_TCK;
	printf("\n\nWe Spent %f Clock Time\n\n", time_cal);

    Led(0x0000);
	Close();

	return 0;
}
