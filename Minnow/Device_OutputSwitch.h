/*
 Minnow Pacemaker client firmware.
    
 Copyright (C) 2013 Robert Fairlie-Cuninghame

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// Interface for output switch devices
//

#ifndef DEVICE_OUTPUTSWITCH_H
#define DEVICE_OUTPUTSWITCH_H

#include "Minnow.h"

class Device_OutputSwitch
{
public:
#define OUTPUT_SWITCH_STATE_LOW       0
#define OUTPUT_SWITCH_STATE_HIGH      1
#define OUTPUT_SWITCH_STATE_DISABLED  2

  static uint8_t Init(uint8_t num_output_switches);
  
  FORCE_INLINE static uint8_t GetNumDevices()
  {
    return num_output_switches;
  }
  
  FORCE_INLINE static bool IsInUse(uint8_t device_number)
  {
    return (device_number < num_output_switches 
      && output_switch_pins[device_number] != 0xFF);
  }

  FORCE_INLINE static uint8_t GetEnableState(uint8_t device_number)
  {
    return !output_switch_disabled[device_number];
  }
  
  FORCE_INLINE static uint8_t GetPin(uint8_t device_number)
  {
    return output_switch_pins[device_number];
  }
  
  static uint8_t SetPin(uint8_t device_number, uint8_t pin);
  
  // These are applied to/from NVConfigStore.
  static uint8_t SetInitialState(uint8_t device_number, uint8_t initial_state);
  static uint8_t GetInitialState(uint8_t device_number);

  // Note: this write method is not used for time-critical output pins
  // such as stepper or heater pins or for queued commands executed in the ISR.
  FORCE_INLINE static void WriteState(uint8_t device_number, uint8_t state)
  {
    if (state < OUTPUT_SWITCH_STATE_DISABLED)
    {
      if (output_switch_disabled[device_number])
      {
        pinMode(output_switch_pins[device_number], OUTPUT);
        output_switch_disabled[device_number] = false;
      }
      digitalWrite(output_switch_pins[device_number], state);
    }
    else
    {
      pinMode(output_switch_pins[device_number], INPUT);
      output_switch_disabled[device_number] = true;
    }
  }

private:

  friend bool handle_queue_command();

  static uint8_t num_output_switches;
  static uint8_t *output_switch_pins;
  static bool *output_switch_disabled; // TODO store full set state for GetDeviceStatus
  
};

#endif


    