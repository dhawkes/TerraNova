#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <iq_module_communicaiton.hpp>


class SuspensionMotor
{
  public:
    SuspensionMotor(HardwareSerial &my_serial):
      iq_(new IqSerial(my_serial)),
      mult_(new MultiTurnAngleControlClient(0)),
      mot_(new BrushlessDriveClient(0))
    {
      iq_->begin(115200);
    };

    ~SuspensionMotor()
    {
      delete iq_;
      delete mult_;
    };

    void setPid()
    {
      iq_->set(mult_->angle_Kp_,Kp_);
      iq_->set(mult_->angle_Ki_,Kd_);
      iq_->set(mult_->angle_Kd_,Ki_);
    };

    void setPidConstants(const float &Kp = 0, const float &Kd = 0, const float &Ki = 0)
    {
      Kp_ = Kp;
      Kd_ = Kd;
      Ki_ = Ki;
      return;
    };

    bool getAngle(float &current_angle)
    {
      if(iq_->get(mult_->obs_angular_displacement_, current_angle))
      {
        return 1;
      }
      return 0;
    };

    void setAngle(const float &angle)
    {
      iq_->set(mult_->ctrl_angle_, angle);
    };

    bool setCurrentAngle()
    {
      float current_angle;
      if(!getAngle(current_angle))
      {
        return 0;
      }
      setAngle(current_angle);
      return 1;
    };

    bool getVoltage(float &obs_volts)
    {
      if(iq_->get(mot_->obs_supply_volts_, obs_volts))
      {
        return 1;
      }
      return 0;
    }

    void coast()
    {
      iq_->set(mult_->ctrl_coast_);
    }

    void increaseKp(const float &increase)
    {
      Kp_ += increase;
      setPid();
    }


  private:
    IqSerial                    *iq_;
    MultiTurnAngleControlClient *mult_;
    BrushlessDriveClient        *mot_;

    float Kp_ = 10;
    float Kd_ = 0;
    float Ki_ = 0;
};