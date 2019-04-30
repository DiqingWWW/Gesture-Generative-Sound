#include <AccelStepperFirmata.h>
#include <SerialFirmata.h>
#include <FirmataFeature.h>
#include <DigitalInputFirmata.h>
#include <ServoFirmata.h>
#include <I2CFirmata.h>
#include <OneWireFirmata.h>
#include <FirmataExt.h>
#include <AnalogOutputFirmata.h>
#include <AnalogInputFirmata.h>
#include <Encoder7Bit.h>
#include <DigitalOutputFirmata.h>
#include <AnalogFirmata.h>
#include <EthernetClientStream.h>
#include <StepperFirmata.h>
#include <FirmataReporting.h>
#include <FirmataScheduler.h>
#include <ConfigurableFirmata.h>
#include <AnalogWrite.h>

#include <Wire.h>

#include <AccelStepperFirmata.h>
#include <SerialFirmata.h>
#include <FirmataFeature.h>
#include <DigitalInputFirmata.h>
#include <ServoFirmata.h>
#include <I2CFirmata.h>
#include <OneWireFirmata.h>
#include <FirmataExt.h>
#include <AnalogOutputFirmata.h>
#include <AnalogInputFirmata.h>
#include <Encoder7Bit.h>
#include <DigitalOutputFirmata.h>
#include <AnalogFirmata.h>
#include <EthernetClientStream.h>
#include <StepperFirmata.h>
#include <FirmataReporting.h>
#include <FirmataScheduler.h>
#include <ConfigurableFirmata.h>
#include <AnalogWrite.h>

/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.
   See the bottom of this file for license terms.
*/

/*
   This sketch example demonstrates how the BMI160 accelerometer on the
   Intel(R) Curie(TM) module can be used to detect motion events
*/

#include "CurieIMU.h"

boolean blinkState = false;          // state of the LED
unsigned long loopTime = 0;          // get the time since program started
unsigned long interruptsTime = 0;    // get the time when motion event is detected

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial) ;   // wait for serial port to connect. Makes the board pause until you open the serial port

  /* Initialise the IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Enable Motion Detection */
  CurieIMU.setDetectionThreshold(CURIE_IMU_MOTION, 20); // 20mg, setup threshold for detection, acceleration 20 mg.
  //2G: 0 to 997.05 mg, in steps of 3.91 mg
  //4G: 0 to 1991.55 mg, in steps of 7.81 mg
  //8G: 0 to 3985.65 mg, in steps of 15.63 mg
  //16G: 0 to 7968.75 mg, in steps of 31.25 mg
  CurieIMU.setDetectionDuration(CURIE_IMU_MOTION, 10);  // trigger times of consecutive slope data points
  CurieIMU.interrupts(CURIE_IMU_MOTION);

  Serial.println("IMU initialisation complete, waiting for events...");
}

void loop() {
  // if motion is detected in 1000ms, LED will be turned up
  loopTime = millis();
  if (abs(loopTime - interruptsTime) < 1000 )
    blinkState = true;
  else
    blinkState = false;
  digitalWrite(13, blinkState);
}


static void eventCallback(void) {
  if (CurieIMU.getInterruptStatus(CURIE_IMU_MOTION)) {
    if (CurieIMU.motionDetected(X_AXIS, POSITIVE))
      Serial.println("6"); //Negative motion detected on X-axis
    if (CurieIMU.motionDetected(X_AXIS, NEGATIVE))
      Serial.println("5");  //Positive motion detected on X-axis
    if (CurieIMU.motionDetected(Y_AXIS, POSITIVE))
      Serial.println("4");  //Negative motion detected on Y-axis
    if (CurieIMU.motionDetected(Y_AXIS, NEGATIVE))
      Serial.println("3");  //Positive motion detected on Y-axis
    if (CurieIMU.motionDetected(Z_AXIS, POSITIVE))
      Serial.println("2");  //Negative motion detected on Z-axis
    if (CurieIMU.motionDetected(Z_AXIS, NEGATIVE))
      Serial.println("1");  //Positive motion detected on Z-axis
    interruptsTime = millis();
    //if (CurieIMU.getInterruptStatus(CURIE_IMU_MOTION)) {
    //if (CurieIMU.motionDetected(X_AXIS, POSITIVE))
    // Serial.println("Negative motion detected on X-axis");
    // if (CurieIMU.motionDetected(X_AXIS, NEGATIVE))
    //  Serial.println("Positive motion detected on X-axis");
    // if (CurieIMU.motionDetected(Y_AXIS, POSITIVE))
    //   Serial.println("Negative motion detected on Y-axis");
    // if (CurieIMU.motionDetected(Y_AXIS, NEGATIVE))
    //   Serial.println("Positive motion detected on Y-axis");
    // if (CurieIMU.motionDetected(Z_AXIS, POSITIVE))
    //   Serial.println("Negative motion detected on Z-axis");
    // if (CurieIMU.motionDetected(Z_AXIS, NEGATIVE))
    //   Serial.println("Positive motion detected on Z-axis");
    // interruptsTime = millis();
  }
}

/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/
