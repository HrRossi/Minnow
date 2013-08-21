/*
 Minnow Pacemaker client firmware.
    
 Copyright (C) 2013 Robert Fairlie-Cuninghame

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHIN ANY WARRANTY; within even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// Interface for input switch devices
//

#include "Device_InputSwitch.h"

uint8_t Device_InputSwitch::input_switch_pins[MAX_INPUT_SWITCHES];

//
// Methods
//

void Device_InputSwitch::Init()
{
  memset(input_switch_pins, 0xFF, sizeof(input_switch_pins));
}

uint8_t Device_InputSwitch::GetNumDevices()
{
  for (int8_t i=MAX_INPUT_SWITCHES-1; i>=0; i--)
  {
    if (input_switch_pins[i] != 0xFF)
      return i+1;
  }    
  return 0;
}


bool Device_InputSwitch::SetPin(uint8_t device_number, uint8_t pin)
{
  if (device_number >= MAX_INPUT_SWITCHES)
    return false;
  
  input_switch_pins[device_number] = pin;
  
  if (pin != 0xFF)
    pinMode(pin, INPUT);

  return true;
}


    