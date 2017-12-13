#include "Altino.h"
#include <stdio.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNNIGS
void LedOn()
{
	Led(0x0033);
	delay(1000);
	Led(0);
	delay(500);
}

int main(void)
{
	int i0, i1, i2, i3, sp, cd, cnt = 1;
	SensorData dat;

	int input;


	double time_cal;      // process ���� clock����, ���������� clock���� ���̸�  ���� �ð��� ����
	time_t start, end;      // process ����, �շ����� ������ clock�� ���Խ�ų ����


	Open(szPort);         //<3>
	start = clock();      // ���۽� clock ����



						  //<4>
						  //scanf("%d", &input);   //ǥ�� �Է� ���, ��� ���̱� ������ �Է��� �ޱ� ������ clock���� �����ϰ� �ִ�.
						  //ǥ�� �Է� �Ϸ���� code_line�� ���� ��



	LedOn();
	LedOn();
	LedOn();

	sp = 660;
	while (1)
	{
		dat = Sensor(10);
		i0 = dat.IRSensor[0];
		i1 = dat.IRSensor[1];
		i2 = dat.IRSensor[2];
		i3 = dat.IRSensor[3];

		cd = dat.CDSSensor;

		printf("%d %d %d %d %d\n", i0, i1, i2, i3, cd);


		Steering(2);
		Go(sp, sp);
		//delay(500);

		if (i0 > 20 || i1 > 20 || i2 > 20)
		{
			if (i0 >= i2)
			{
				Steering(1);
				Go(-sp, -sp);
				delay(500);
				Steering(3);
				Go(sp, sp);
				delay(500);

				dat = Sensor(10);
				i0 = dat.IRSensor[0];
				i1 = dat.IRSensor[1];
				i2 = dat.IRSensor[2];
				cd = dat.CDSSensor;
			}

			else
			{
				Steering(3);
				Go(-sp, -sp);
				delay(500);
				Steering(1);
				Go(sp, sp);
				delay(500);

				dat = Sensor(10);
				i0 = dat.IRSensor[0];
				i1 = dat.IRSensor[1];
				i2 = dat.IRSensor[2];
				cd = dat.CDSSensor;

			}
			dat = Sensor(10);
			i0 = dat.IRSensor[0];
			i1 = dat.IRSensor[1];
			i2 = dat.IRSensor[2];
			cd = dat.CDSSensor;
		}
		/*if (i0 > 20 || i1 > 20 || i2 > 20)
		Go(sp, sp);*/

		if ((cd > 10) && (cd < 200) && (cnt == 1))
		{
			Go(0, 0);
			Sound(47);
			delay(2000);

			Sound(0);
			sp = sp / 2;
			Go(sp, sp);
			cnt++;
		}

		if (i0 > 200 && i1 > 200 && i2 > 200 && i3 > 20)
		{
			Go(0, 0);
			Display('B');
			delay(1000);
			Display('O');
			delay(1000);
			Display('Y');
			delay(1000);
			break;
		}
	}

	end = clock();         //���� ������ clocküũ
						   // clock�� ���̸� ���� �ҿ� �ð� ����
	time_cal = (double)(end - start) / CLK_TCK;
	Close();
	printf("\n\nWe Spent %f Clock Time", time_cal);
	system("pause");
	return 0;
}