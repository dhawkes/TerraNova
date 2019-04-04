#include "ImuSensor.hpp"

bool ImuSensor::init()
{
  imu_->settings.device.commInterface = IMU_MODE_I2C;
  imu_->settings.device.mAddress = LSM9DS1_M;
  imu_->settings.device.agAddress = LSM9DS1_AG;

  if(imu_->begin())
  {
    return 1;
  }
  
  return 0;
}

ImuData ImuSensor::getData()
{
  imu_->readGyro();
  imu_->readAccel();
  imu_->readMag();
  calculateAttitude(imu_->ax, imu_->ay, imu_->az, imu_->mx, imu_->my, imu_->mz);

  ImuData imud;

  imud.gyro_x = imu_->calcGyro(imu_->gx);
  imud.gyro_y = imu_->calcGyro(imu_->gy);
  imud.gyro_z = imu_->calcGyro(imu_->gz);

  imud.accel_x = imu_->calcGyro(imu_->ax);
  imud.accel_y = imu_->calcGyro(imu_->ay);
  imud.accel_z = imu_->calcGyro(imu_->az);

  imud.mag_x = imu_->calcGyro(imu_->mx);
  imud.mag_y = imu_->calcGyro(imu_->my);
  imud.mag_z = imu_->calcGyro(imu_->mz);

  imud.pitch   = pitch_;
  imud.roll    = roll_;
  imud.heading = heading_;

  return imud;
}

void ImuSensor::calculateAttitude(const float &ax, const float &ay, const float &az, float mx, float my, float mz)
{
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  
  float heading;
  mx *= 180 / PI;
  my *= 180 / PI;
  mz *= 180 / PI;

  if(my > 0)
    heading = 90 - (atan2(mx,my))*(180/PI);
  else if(my < 0)
    heading = 270 - (atan2(mx,my))*(180/PI);
  else if(my == 0 && mx < 0)
    heading = 180.0;
  else
    heading = 0.0;
        
  // Convert everything from radians to degrees:
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;

  heading_ = heading;
  pitch_   = pitch;
  roll_    = roll;
}