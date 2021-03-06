#include "main.h"

float x, y, angle, diff = 0;
bool trackenabled = true;

//Math
double radToDeg(double rad){
  return rad/M_PI * 180.0;
}

double degToRad(double deg){
  return deg * M_PI / 180.0;
}

//IMU Filter
double filter(const double& currentVal, const double& lastVal){
  double filteredVal = currentVal - lastVal;
  if(fabs(filteredVal) < 0.01){
    filteredVal = 0;
  }
  return filteredVal;
}

//Tracking
void track(){

  backEncoder.reset();
  sideEncoder.reset();

  float Ss = sideDistance,
        Sb = backDistance,
        wheelDiameter = sideDiameter,
        trackingDiameter = backDiameter;

  float deltaTheta = 0,
        thetaFiltered = 0,
        thetaNew = 0,
        thetaAvg = 0,
        curRotation = 0,
        lastRotation = 0,

        curSide = 0,
        curBack = 0,
        lastSide = 0,
        lastBack = 0,
        deltaSide = 0,
        deltaBack = 0,
        sideChord = 0,
        backChord = 0,
        i, Ri = imu.get_rotation();

  while(trackenabled){

    i = (imu.get_rotation() - Ri - diff);

    curRotation = i;

    thetaFiltered += filter(curRotation, lastRotation);
    lastRotation = curRotation;
    thetaNew = degToRad(thetaFiltered);
    deltaTheta = thetaNew - angle;

    curSide = sideEncoder.get_value() * M_PI/360;
    curBack = backEncoder.get_value() * M_PI/360;
    deltaSide = (curSide - lastSide)*(wheelDiameter);
    deltaBack = (curBack - lastBack)*(trackingDiameter);
    lastSide = curSide;
    lastBack = curBack;

    if(deltaTheta != 0){
      backChord = (2*sin(deltaTheta/2))*(deltaBack/deltaTheta + Sb);
      sideChord = (2*sin(deltaTheta/2))*(deltaSide/deltaTheta + Ss);
    }
    else{
       sideChord = deltaSide;
       backChord = deltaBack;
    }

    thetaAvg = angle + deltaTheta/2;

    x += sideChord * sin(thetaAvg);
    y += sideChord * cos(thetaAvg);
    x += backChord * -cos(thetaAvg);
    y += backChord *  sin(thetaAvg);

    angle += deltaTheta;

    pros::delay(10);
  }
}

//Tasks
void stopTracking(){
  if(tracking != nullptr){
    tracking->remove();
    delete tracking;
    tracking = nullptr;
  }
}
