#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include "SparkFunLSM9DS1.h"

#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

// Earth's magnetic field varies by location. Add or subtract 
// a declination to get a more accurate heading. Calculate 
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION 12

struct ImuData
{
  float gyro_x = NAN;
  float gyro_y = NAN;
  float gyro_z = NAN;

  float accel_x = NAN;
  float accel_y = NAN;
  float accel_z = NAN;

  float mag_x = NAN;
  float mag_y = NAN;
  float mag_z = NAN;

  float pitch   = NAN;
  float roll    = NAN;
  float heading = NAN;
};

class ImuSensor
{
  public:
    ImuSensor():imu_(new LSM9DS1()){};
    ~ImuSensor(){delete imu_;};

    bool init();

    ImuData getData();

  private:
    LSM9DS1 *imu_;

    float pitch_;
    float roll_;
    float heading_;

    void calculateAttitude(const float &ax, const float &ay, const float &az, float mx, float my, float mz);
};