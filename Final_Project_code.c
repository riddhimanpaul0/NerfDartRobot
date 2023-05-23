/*
Name(s): Matthew Bridger, Riddhiman Paul, Khushmeet Kaur, Ishan Sahu
Desc: robots detects Nerf darts and picks it up
Date: Nov 25 2022
Version: 1.2
*/


void configureAllSensors();
void driveDist(int distCm,int powerM);
void drive(int motor_power);
void drive(int motor_power_A, int motor_power_D);//powers both motors independently
void waitButton(TEV3Buttons button_name);
void resetClaw();
void depositBlue();
void depositGreen();
void stuckBullet(int floorVal);

#include "EV3Servo-lib-UW.c"

const int SV_SERVO_S = 1;
const int SV_SERVO_U = 2;
const int SV_GRIPPER = 3;
const int TOP_HEIGHT = 2200;
const int BOT_HEIGHT = 950;
const int GRIP_CLOSE = 1000;
const int GRIP_OPEN = 2400;
const int DART_LOC = 750;
const int BLUE_HEIGHT = 1700;
const int BLUE_LOC = 1500;
const int GREEN_HEIGHT = 1600;
const int GREEN_LOC = 1200;


task main()
{
	int floorVal = 0;
	int countBlue = 0;
	int countGreen = 0;
	configureAllSensors();
	waitButton(buttonEnter);
	floorVal = SensorValue[S4] - 1;
	resetClaw();
	time1[T1] = 0;
	time1[T2] = 0;
	while(time1[T1] <= 40000 && (!getButtonPress(buttonEnter)) && (countBlue + countGreen) < 8)
	{
		if(SensorValue[S3] >= floorVal && SensorValue[S3] <= floorVal + 2)
		{
			time1[T2] = 0;
		}
		if(SensorValue[S2] == 0)
		{
			drive(30);
		}
		if(SensorValue[S2] < 0)
		{
			drive(20, 40);
		}
		if(SensorValue[S2] > 0)
		{
			drive(40, 20);
		}
		if(SensorValue[S4] < floorVal)
		{
			drive(0);
			NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, BOT_HEIGHT);
			driveDist(6,30);
			depositBlue();
			resetClaw();
			countBlue++;
			time1[T1] = 0;
			time1[T2] = 0;
		}
		if(SensorValue[S4] > floorVal + 2)
		{
			drive(0);
			NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, BOT_HEIGHT);
			driveDist(6,30);
			depositGreen();
			resetClaw();
			countGreen++;
			time1[T1] = 0;
			time1[T2] = 0;
		}
		if(time1[T2] >= 1000)
		{
			stuckBullet(floorVal);
		}

	}
}


void configureAllSensors()
{
	SensorType[S2] = sensorEV3_Gyro;
	SensorType[S3] = sensorEV3_Color; //stuck
	SensorType[S4] = sensorEV3_Color; //funnel
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Reflected;
	SensorMode[S4] = modeEV3Color_Reflected;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}

void driveDist(int distCm,int powerM)
{
	nMotorEncoder[motorD]=0;
	drive(powerM);
	while (abs(nMotorEncoder[motorD])<distCm*180/(PI*2.75))
	{ }
	drive(0);
	return;
}

void waitButton(TEV3Buttons button_name)
{
	while(!getButtonPress(button_name))
	{}
	while(getButtonPress(button_name))
	{}
}

void drive(int motor_power)//powers both drive motors with the same power
{
	motor[motorA] = motor[motorD] = motor_power;
}

void drive(int motor_power_A, int motor_power_D)//powers both motors independently
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
}

void resetClaw()
{
	int i = 1;
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, TOP_HEIGHT);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_GRIPPER, GRIP_CLOSE);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_S, DART_LOC);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	while(i <= 10 && (!getButtonPress(buttonEnter)))
	{
		time1[T1] = 0;
		NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, TOP_HEIGHT - 110*i);
		while(time1[T1] <= 200 && (!getButtonPress(buttonEnter)))
		{
		}
		i++;
	}
	NXTServo_SetPosition(S1, I2C_ADDR, SV_GRIPPER, GRIP_OPEN);
	time1[T1] = 0;
	while(time1[T1] <= 1000 && (!getButtonPress(buttonEnter)))
	{
	}
}

void depositBlue()
{
	time1[T1] = 0;
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_GRIPPER, GRIP_CLOSE);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, TOP_HEIGHT);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_S, BLUE_LOC);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, BLUE_HEIGHT);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	NXTServo_SetPosition(S1, I2C_ADDR, SV_GRIPPER, GRIP_OPEN);
	time1[T1] = 0;
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
}

void depositGreen()
{
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_GRIPPER, GRIP_CLOSE);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, TOP_HEIGHT);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_S, GREEN_LOC);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	time1[T1] = 0;
	NXTServo_SetPosition(S1, I2C_ADDR, SV_SERVO_U, GREEN_HEIGHT);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	NXTServo_SetPosition(S1, I2C_ADDR, SV_GRIPPER, GRIP_OPEN);
}

void stuckBullet(int floorVal)
{
	drive(10);
	while(time1[T1] <= 400 && (!getButtonPress(buttonEnter)))
	{
	}
	while(SensorValue[S3] > floorVal && SensorValue[S3] < floorVal + 2)
	{
	}
	time1[T1] = 0;
	drive(0);
	while(time1[T1] <= 500 && (!getButtonPress(buttonEnter)))
	{
	}
	drive(-20, 20);
	while(abs(SensorValue[S2]) <= 45)
	{
	}
	drive(20);
	while(SensorValue[S3] > floorVal && SensorValue[S3] < floorVal + 2)
	{
	}
	drive(0);
}
