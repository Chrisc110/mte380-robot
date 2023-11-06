#ifndef MPU6050_H
#define MPU6050_H

typedef struct
{
    float accX;
    float accY;
    float accZ;

    float gyroX;
    float gyroY;
    float gyroZ;
} MPU6050Data;

class MPU6050 {

    public:

    MPU6050();
    ~MPU6050();

    void init();

    void getAll(MPU6050Data* data);


    private:

    float accCalibrationX;
    float accCalibrationY;
    float accCalibrationZ;


    float gyroCalibrationX;
    float gyroCalibrationY;
    float gyroCalibrationZ;


};

#endif