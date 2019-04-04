#ifndef PIN_DEFINE_HPP
#define PIN_DEFINE_HPP

// XBEE
// connector : C1
// Serial1
#define XBESERIAL Serial1
#define XBERX 0 // blue
#define XBETX 1 // white

// JUMPING MOTOR
// connector: C2
#define JMFLT 2   // blue
#define JMSLP 3   // white
#define JMDIR 4   // brown
#define JMPWM 5   // green
#define JMCS  A10 // grey

// JUMPING MOTOR ENCODE
// connector: C11
#define JMENC 6   // blue
#define JMHAL A11 // white

// TODO : what the fuck are those
// connector: C13 (triple pins)
#define SSR 7 // grey
// connector: C14 (triple pins)
#define SSL 8 // bridge
// connector: C15 (triple pins)
#define JS  9 // grey

// FORWARD LEFT MOTOR
// connector: C3
#define FLPWM  10 // green
#define FLMF   11 // blue
#define FLDIRA 12 // white
#define FLDIRB 24 // brown
#define FLCS   32 // grey

// VOLTAGE REGULATOR
// connnector: C20 (single pin)
#define VR 25 // grey

// REAR LEFT MOTOR
// connecttor: C4
#define RLMF   27 // white cable with blue written on it
#define RLDIRA 28 // blue cable with white written on it
#define RLDIRB 29 // brown
#define RLPWM  30 // green
#define RLCS   31 // grey

// TEMPERATURE SENSOR
// connector: C12
#define TSF 23 // blue 
#define TSR 24 // white

// IMU, Time of flight
// connector: C10
// I2c 0
#define IMUTOFSCL 19 // white
#define IMUTOFSDA 18 // blue

// FORWARD RIGHT DRIVE MOTOR
// connector: C9
#define FRMF   16  // blue
#define FRDIRA 15  // white
#define FRPWM  14  // green
#define FRDIRB 21  // brown
#define FRCS   A21 // grey

// REAR RIGHT DRIVE MOTOR
// connector: C8
#define RRMF   35 // blue
#define RRDIRA 36 // white
#define RRDIRB 37 // brown 
#define RRPWM  38 // green
#define RRCS   39 // grey

// SUSPENSION MOTOR RIGHT
// connector: C7
// Serial5
#define SMRSERIAL Serial5
#define SMRRX 34 // blue
#define SMRTX 33 // white

// SUSPENSION MOTOR LEFT
// connector: C6
// Serial6
#define SMLSERIAL Serial6
#define SMLRX 47 // blue 
#define SMLTX 48 // white

// REVERSE RIGHT DRIVE MOTOR ENCODER
// connector: C19
#define RRENCB 52 // green
#define RRENCA 53 // brown

// FORWARD RIGHT DRIVE MOTOR ENCODER
// connector: C18
#define FRENCB 54 // green
#define FRENCA 55 // brown

// TIME OF FLIGHT2
// connector: C5
#define TOFSDA 56 // blue
#define TOFSCL 57 // white

// REVERSE LEFT DRIVE MOTOR ENCODER
// connector: C17
#define RLENCA 46 // brown 
#define RLENCB 45 // green

// FORWARD LEFT DRIVE MOTOR ENCODER
// connector: C16
#define FLENCA 44 // brown
#define FLENCB 43 // green

#endif // PIN_DEFINE_HPP
