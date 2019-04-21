#include <Servo.h>

#include "PinDefine.hpp"
#include "JumpMotor.hpp"
#include "DriveMotor.hpp"
#include "SuspensionMotor.hpp"
#include "WirelessCommunication.hpp"
#include "ImuSensor.hpp"

//JumpMotor Jump(JMPWM, JMDIR, JMSLP, JMFLT, JMCS, JMHAL, JMENC, 100);

DriveMotor FrontLeft(FLDIRA, FLDIRB, FLPWM, FLMF, FLCS, FLENCA, FLENCB, 48 * 99);
DriveMotor RearLeft(RLDIRA, RLDIRB, RLPWM, RLMF, RLCS, RLENCA, RLENCB, 48 * 99);
DriveMotor FrontRight(FRDIRB, FRDIRA, FRPWM, FRMF, FRCS, FRENCA, FRENCB, 48 * 99);
DriveMotor RearRight(RRDIRB, RRDIRA, RRPWM, RRMF, RRCS, RRENCA, RRENCB, 48 * 99);

SuspensionMotor LeftSuspension(SMLSERIAL);
SuspensionMotor RightSuspension(SMRSERIAL);

ImuSensor IMU;

Servo SSL_serv; // 90 to 180 - 110 is straight
Servo SSR_serv; // 0 to 100 - 90 is straight
//Servo Jump_serv;

int ssl_nom = 845;
int ssl_left_diff = 100;
int ssl_right_diff = 100;
int ssr_nom = 75;
float inner = 15;
float outter = 17;

WirelessCommunication wc(&(XBESERIAL));

uint8_t buffer[5];
uint8_t data[100];
bool fault = false;

void setup() {
  Serial.begin(9600);

  wc.init();

  //Jump.init();
  
  FrontLeft.init();
  RearLeft.init();
  FrontRight.init();
  RearRight.init();
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  LeftSuspension.setPidConstants(300, 0, 0);
  RightSuspension.setPidConstants(300, 0, 0);
  LeftSuspension.setCurrentAngle();
  RightSuspension.setCurrentAngle();
  LeftSuspension.setPid();
  RightSuspension.setPid();

  
  SSL_serv.attach(SSL);
  SSR_serv.attach(SSR);
  //Jump_serv.attach(JS);
  SSL_serv.write(ssl_nom);
  SSR_serv.write(ssr_nom);
  //Jump_serv.write(90);

  IMU.init();
}

void readSensors() {
  float holder1, holder2;

  if(LeftSuspension.getVoltage(holder1) || RightSuspension.getVoltage(holder2)) {
    float supply = holder2; //(holder1 + holder2) / 2.0f;
    wc.setDataValue(D_SUPPLY_VOLTAGE, supply);
    fault = supply < 10.5;
    wc.setFaultValue(F_REGULATOR_POWER_GOOD, fault);
    wc.setFaultValue(F_UNDER_VOLTAGE, fault);
  }
  if(LeftSuspension.getAngle(holder1))
    wc.setDataValue(D_LEFT_ROCKER_ANGLE, holder1 - LeftSuspension.getSetAngle());
  if(RightSuspension.getAngle(holder1))
    wc.setDataValue(D_RIGHT_ROCKER_ANGLE, holder1 - RightSuspension.getSetAngle());

  ImuData data = IMU.getData();
  wc.setDataValue(D_ROLL, data.roll);
  wc.setDataValue(D_PITCH, data.pitch);
  wc.setDataValue(D_YAW, data.heading);
  wc.setDataValue(D_X_ACCELERATION, data.accel_x);
  wc.setDataValue(D_Y_ACCELERATION, data.accel_y);
  wc.setDataValue(D_Z_ACCELERATION, data.accel_z);
}

int misses = 0;

void loop() {
  readSensors();
  wc.sendMessages();

  float voltage = 0;

  FrontLeft.setSpeed(130);
  
  FrontLeft.updateSpeed(voltage);
  RearLeft.updateSpeed(voltage);
  FrontRight.updateSpeed(voltage);
  RearRight.updateSpeed(voltage);

  if(fault) {
    FrontLeft.setSpeed(100);
    RearLeft.setSpeed(100);
    FrontRight.setSpeed(100);
    RearRight.setSpeed(100);
  }

  if(wc.receiveMessages(buffer) && !fault) {
    misses = 0;

    if(wc.buttonState(Button::B, ButtonState::DOWN)) {
      fault = true;
      return;
    }

    /*
    if(wc.buttonState(Button::RT, ButtonState::PRESSED))
      Jump.setSpeed(100);
    else if(wc.buttonState(Button::RT, ButtonState::RELEASED))
      Jump.setSpeed(0);*/

    if(wc.buttonState(Button::X, ButtonState::PRESSED)) {
      LeftSuspension.coast();
      RightSuspension.coast();
    }
    if(wc.buttonState(Button::X, ButtonState::RELEASED)) {
      LeftSuspension.setPidConstants(300, 0, 0);
      RightSuspension.setPidConstants(300, 0, 0);
      LeftSuspension.setCurrentAngle();
      RightSuspension.setCurrentAngle();
      LeftSuspension.setPid();
      RightSuspension.setPid();
    }
    
    int spd = buffer[0];
    FrontLeft.setSpeed(spd);
    RearLeft.setSpeed(spd);
    FrontRight.setSpeed(spd);
    RearRight.setSpeed(spd);

    int servo = buffer[1] - 100;
    if(servo < 1) {
      float scale = servo / -100.0f;
      SSL_serv.writeMicroseconds(ssl_nom - (ssl_left_diff * scale));
      SSR_serv.write(ssr_nom - (outter * scale));
    }
    else if(servo > 1) {
      float scale = servo / 100.0f;
      SSL_serv.writeMicroseconds(ssl_nom + (ssl_right_diff * scale));
      SSR_serv.write(ssr_nom + (outter * scale));
    }
    else {
      SSL_serv.writeMicroseconds(ssl_nom);
      SSR_serv.write(ssr_nom);
    }
  }
  else {
    misses++;
    if(misses > 5) {
      FrontLeft.setSpeed(100);
      RearLeft.setSpeed(100);
      FrontRight.setSpeed(100);
      RearRight.setSpeed(100);
    }
  }

  delay(20);
}
