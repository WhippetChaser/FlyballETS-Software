// LightsController.h
// Copyright (C) 2015  Alex Goris
// This file is part of FlyballETS-Software
// FlyballETS-Software is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <http://www.gnu.org/licenses/>

#ifndef _LIGHTSCONTROLLER_h
#define _LIGHTSCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class LightsControllerClass
{
protected:

public:
	void init(uint8_t iLatchPin, uint8_t iClockPin, uint8_t iDataPin);

   //Overal state of this class
   enum OverallStates{
      STOPPED,
      STARTING,
      STARTED
   };
   OverallStates byOverallState = STOPPED;

   //Decimal values of lights connected to 74HC595
   enum Lights {
      WHITE = 128,
      RED = 64,
      YELLOW1 = 32,
      BLUE = 16,
      YELLOW2 = 8,
      GREEN = 4
   };
   enum LightStates {
      OFF,
      ON,
      TOGGLE
   };
   LightStates CheckLightState(Lights byLight);
   void Main();
   void HandleStartSequence();
   void InitiateStartSequence();
   void ToggleLightState(Lights byLight, LightStates byLightState = TOGGLE);
   void ResetLights();
   void DeleteSchedules();
   void ToggleFaultLight(uint8_t iDogNumber, LightStates byLightState);
   
private:
   //Pin connected to ST_CP of 74HC595
   uint8_t _iLatchPin = 12;
   //Pin connected to SH_CP of 74HC595
   uint8_t _iClockPin = 13;
   //Pin connected to DS of 74HC595
   uint8_t _iDataPin = 11;

   //This byte contains the combined states of all ligths at any given time
   byte _byCurrentLightsState = 256;
   byte _byNewLightsState = 0;

   bool _bStartSequenceStarted = 0;

   unsigned long _lLightsOnSchedule[6];
   unsigned long _lLightsOutSchedule[6];

   Lights _byLightsArray[6] = {
      WHITE,
      RED,
      YELLOW1,
      BLUE,
      YELLOW2,
      GREEN
   };

   Lights _byDogErrorLigths[4] = {
      RED,
      BLUE,
      YELLOW2,
      GREEN
   };

};

extern LightsControllerClass LightsController;

#endif

