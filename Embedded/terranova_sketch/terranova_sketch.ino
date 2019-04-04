#include <Servo.h>

#include "PinDefine.hpp"
#include "DriveMotor.hpp"
#include "SuspensionMotor.hpp"
#include "WirelessCommunication.hpp"

DriveMotor FrontLeft(FLDIRA, FLDIRB, FLPWM, FLMF, FLCS, FLENCA, FLENCB, 48 * 99);
DriveMotor RearLeft(RLDIRA, RLDIRB, RLPWM, RLMF, RLCS, RLENCA, RLENCB, 48 * 99);
DriveMotor FrontRight(FRDIRB, FRDIRA, FRPWM, FRMF, FRCS, FRENCA, FRENCB, 48 * 99);
DriveMotor RearRight(RRDIRB, RRDIRA, RRPWM, RRMF, RRCS, RRENCA, RRENCB, 48 * 99);

SuspensionMotor LeftSuspension(SMLSERIAL);
SuspensionMotor RightSuspension(SMRSERIAL);

Servo SSL_serv; // 90 to 180 - 110 is straight
Servo SSR_serv; // 0 to 100 - 90 is straight
int ssl_nom = 80;
int ssr_nom = 130;

WirelessCommunication wc(&(XBESERIAL));

uint8_t buffer[5];

void setup() {
  Serial.begin(9600);

  
  wc.init();

  wc.setDataValue(1,1.2);
  wc.setFaultValue(1, true);
  
  FrontLeft.init();
  RearLeft.init();
  FrontRight.init();
  RearRight.init();
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  LeftSuspension.setPidConstants(300, 0, 0);
  RightSuspension.setPidConstants(300, 0, 0);
  while(!LeftSuspension.setCurrentAngle());
  while(!RightSuspension.setCurrentAngle());
  LeftSuspension.setPid();
  RightSuspension.setPid();
  
  SSL_serv.attach(SSL);
  SSR_serv.attach(SSR);
  SSL_serv.write(ssl_nom);
  SSR_serv.write(ssr_nom);
}

void loop() {
  /*wc.sendMessages();
  int index = random(0, MAX_DATA_LENGTH - 1);
  float value = random(0, 100) * 0.3465f;
  wc.setDataValue(index, value);
  delay(500);*/

  Serial.println(millis());
  delay(20);
  
  if(wc.receiveMessages(buffer)) {
    if(wc.buttonState(Button::X, ButtonState::PRESSED)) {
      LeftSuspension.coast();
      RightSuspension.coast();
    }
    if(wc.buttonState(Button::X, ButtonState::RELEASED)) {
      LeftSuspension.setPidConstants(300, 0, 0);
      RightSuspension.setPidConstants(300, 0, 0);
      while(!LeftSuspension.setCurrentAngle());
      while(!RightSuspension.setCurrentAngle());
      LeftSuspension.setPid();
      RightSuspension.setPid();
    }
    
    if(buffer[0] < 110 && buffer[0] > 90) {
      FrontLeft.setSpeed(0);
      RearLeft.setSpeed(0);
      FrontRight.setSpeed(0);
      RearRight.setSpeed(0);
    }
    else {
      int spd = buffer[0] - 100;
      FrontLeft.setSpeed(spd);
      RearLeft.setSpeed(spd);
      FrontRight.setSpeed(spd);
      RearRight.setSpeed(spd);
    }

    if(buffer[1] <= 50) {
      SSL_serv.write(ssl_nom - 20);
      SSR_serv.write(ssr_nom - 20);
    }
    else if(buffer[1] >= 150) {
      SSL_serv.write(ssl_nom + 20);
      SSR_serv.write(ssr_nom + 20);
    }
    else {
      SSL_serv.write(ssl_nom);
      SSR_serv.write(ssr_nom);
    }
  }
}
