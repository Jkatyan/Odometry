#include "main.h"

using namespace pros;

//Sensors
Imu imu (IMU_PORT);

ADIEncoder backEncoder (BACK_A, BACK_B, BACK_REVERSED);
ADIEncoder sideEncoder (SIDE_A, SIDE_B, SIDE_REVERSED);

//Tasks
Task *tracking = nullptr;
