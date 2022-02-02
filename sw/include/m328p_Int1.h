/*
Copyright (C) 2022  Andreas Lagler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef M328P_INT1_H
#define M328P_INT1_H

#include <avr/interrupt.h>
#include "register_access.h"
#include "m328p_gpio.h"

namespace m328p
{
    /**
    @brief Register-level driver for external interrupt INT1
    */
    class Int1
    {
        public:

        ///@brief Interrupt Sense Control
        enum class InterruptSenseControl : uint8_t
        {
            PIN_LOW = 0b00,
            PIN_CHANGE = 0b01,
            FALLING_EDGE = 0b10,
            RISING_EDGE = 0b11
        } ;

        /**
        @brief Initialization
        @param interruptSenseControl Interrupt sense control. Default is interrupt on rising edge
        @param enable Interrupt enable flag. Default is interrupt enabled
        */
        static void init(
        const InterruptSenseControl interruptSenseControl = InterruptSenseControl::RISING_EDGE,
        const bool enable = true)
        {
            Pin::setAsInput();
            ISC::write(interruptSenseControl);
            INT::write(enable);
        }
        
        /**
        @brief Enable Interrupt
        */
        static void enableInterrupt() __attribute__((always_inline))
        {
            // Set interrupt enable flag
            INT::set();
        }
        
        /**
        @brief Disable Interrupt
        */
        static void disableInterrupt() __attribute__((always_inline))
        {
            // Clear interrupt enable flag
            INT::clear();
        }
        
        private:

        // Interrupt Sense Control
        typedef BitGroupInRegister<EICRA, ISC10, ISC11, InterruptSenseControl> ISC;

        // External Interrupt Request Enable
        typedef BitInRegister<EIMSK, INT1> INT;

        // INT1 Pin PD3
        typedef GPIOPin<Port::D, 3> Pin;

        /**
        @brief INT1 interrupt handler
        @note This method has to be defined in a separate cpp file. Otherwise, interrupt vector table won't be populated
        */
        static void handleInterrupt() asm("__vector_2") __attribute__((signal, used, externally_visible));
    };
}

#endif