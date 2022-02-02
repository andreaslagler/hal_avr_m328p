/*
Copyright (C) 2020 Andreas Lagler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

/**
@brief Test for INT0 class
Connect a push-button switch to PD3
Connect a LED to PD0

LED should react to push-button switch
PD3 toggles PD0

@note Prerequisites: GPIO Test passed
*/

#include "m328p_Int1.h"
#include "m328p_GPIO.h"
#include <stdbool.h>

/// Output pin definition
typedef m328p::GPIOPin<m328p::Port::D, 0> OutputPin;

/// main method
int main(void)
{
    OutputPin::setAsOutput();
    OutputPin::low();
    
    m328p::Int1::init();
      
    sei();    
    
    while (1) 
    {
    }
}    

/// ISR for Int1
void m328p::Int1::handleInterrupt()
{
    static bool pinState = 1;
    OutputPin::write(pinState);
    pinState = !pinState;
}
