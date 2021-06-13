#include "api.h"

#pragma once

using namespace pros;

//Sensors
extern Imu imu;
extern ADIEncoder backEncoder, sideEncoder;

  //IMU
  const int IMU_PORT = 1;

  //Back Tracking Wheel
  const int BACK_A = 2;
  const int BACK_B = 3;
  const bool BACK_REVERSED = false;

  //Side Tracking Wheel
  const int SIDE_A = 2;
  const int SIDE_B = 3;
  const bool SIDE_REVERSED = false;

//Robot Constants
  const float sideDistance = 10.00,  // Distance in inches from tracking center to center of side tracker
              backDistance = -4.125, // Distance in inches from tracking center to center of back tracker
              sideDiameter = 2.75,   // Side tracker diameter in inches
              backDiameter = 2.75;   // Back tracker diameter in inches

//Tasks
extern Task *tracking;
