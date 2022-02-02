/*
Copyright (C) 2022 Andreas Lagler

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
@brief Test for GPIO class and associated classes
Connect push-button switches to PC2:3, PC5 and PD0:7
Connect LEDs to PC0:1, PC4 and PB0:7

LEDs should react to push-button switches
PC2:3 --> PC0:1
PC5 --> PC4
PD 0:7 --> PB0:7

@note Prerequisites: none
*/

#include "m328p_GPIO.h"

/// main function
int main(void)
{
    // I/O port definitions
    typedef m328p::GPIOPort<m328p::Port::B> OutputPort;
    typedef m328p::GPIOPort<m328p::Port::D> InputPort;
    typedef m328p::GPIOSubPort<m328p::Port::C, 0, 1> OutputSubPort;
    typedef m328p::GPIOSubPort<m328p::Port::C, 2, 3> InputSubPort;
    typedef m328p::GPIOPin<m328p::Port::C, 4> OutputPin;
    typedef m328p::GPIOPin<m328p::Port::C, 5> InputPin;

    // Set GPIO data direction
    OutputPort::setAsOutput();
    InputPort::setAsInput();
    OutputSubPort::setAsOutput();
    InputSubPort::setAsInput();
    OutputPin::setAsOutput();
    InputPin::setAsInput();
    
    while (1)
    {
        // Forward input port status to output port
        OutputPort::write(InputPort::read());
        OutputSubPort::write(InputSubPort::read());
        OutputPin::write(InputPin::read());
    }
}

