#include "MPU6050.h"
#include "Arduino.h"
#include "Wire.h"

MPU6050::MPU6050(){}
MPU6050::~MPU6050(){}

void MPU6050::init()
{
    Wire.setClock(400000);
    Wire.begin();
    delay(250);
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();

    for (uint32_t i = 0; i < 2000; i++) {
        MPU6050Data data;
        getAll(&data);
        gyroCalibrationX+=data.gyroX;
        gyroCalibrationY+=data.gyroY;
        gyroCalibrationZ+=data.accZ;
        delay(1);
    }

    gyroCalibrationX/=2000;
    gyroCalibrationY/=2000;
    gyroCalibrationZ/=2000;
}

void MPU6050::getAll(MPU6050Data* data)
{
    Wire.beginTransmission(0x68);
    Wire.write(0x1A);
    Wire.write(0x05);
    Wire.endTransmission();
    Wire.beginTransmission(0x68);
    Wire.write(0x1C);
    Wire.write(0x10);
    Wire.endTransmission();
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission(); 
    Wire.requestFrom(0x68,6);
    int16_t AccXLSB = Wire.read() << 8 | Wire.read();
    int16_t AccYLSB = Wire.read() << 8 | Wire.read();
    int16_t AccZLSB = Wire.read() << 8 | Wire.read();

    Wire.beginTransmission(0x68);
    Wire.write(0x1B); 
    Wire.write(0x8);
    Wire.endTransmission();     
    Wire.beginTransmission(0x68);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(0x68,6);
    int16_t GyroX=Wire.read()<<8 | Wire.read();
    int16_t GyroY=Wire.read()<<8 | Wire.read();
    int16_t GyroZ=Wire.read()<<8 | Wire.read();

    data->gyroX = (float)GyroX/65.5 - accCalibrationX;
    data->gyroY = (float)GyroY/65.5 - accCalibrationY;
    data->gyroZ = (float)GyroZ/65.5 - accCalibrationZ;
    data->accX = (float)AccXLSB/4096;
    data->accY = (float)AccYLSB/4096;
    data->accZ = (float)AccZLSB/4096;
}