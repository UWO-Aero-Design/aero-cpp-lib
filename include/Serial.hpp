#pragma once

// This code should only compile for teensy and arduino boards
#if defined(ARDUINO) || defined(CORE_TEENSY)

#include "Arduino.h"
#include "Message.hpp"
#include "Utility.hpp"

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

/*!
 *  \addtogroup serial
 *  @{
 */

//! Serial helper functions for arduino/teensy
namespace serial
{
    
namespace
{
    const size_t BUFFER_SPACE = 256;

    // This is currently the size from python. If message size changes, change this const
    const int MSG_SIZE = 181;

    char buffer[BUFFER_SPACE];
    int buf_index = 0;
}

// Copy message contents into new buffer
inline int msg_contents(char* buf) {

    for(int i = 0; i < BUFFER_SPACE; i++) {
        buf[i] = buffer[i];
    }
    
    return buf_index;
}

/**
 * @brief Read a message
 * 
 * @details This code is blocking while their is serial port activity
 *          and designed for Arduino/Teensy. If their is no serial port activity
 *          the returned message while contain all null parsed segments
 * 
 * @param port Reference to serial port you want to read from
 * @param debug Default false. Set to true if you want function to print debug messages
 * @return true if msg valid else false
 */
inline bool check_for_msg( Stream& port, bool debug = false )
{
    Message messageHandler;
    // Boolean flags for reading data
    bool started = false, ended = false, filled = false;
    // Reset buffer index
    buf_index = 0;

    // Read from buffer only when available
    while( port.available() )
    {
        char in_byte = port.read();

        // If byte is start byte and we havent reached the start byte yet
        if( in_byte == def::START_BYTE && started == false )
        {
            buffer[ buf_index++ ] = in_byte;
            started = true;
        }

        // If byte is end byte and we have reached the start but not the end
        else if( in_byte == def::END_BYTE && buf_index == MSG_SIZE - 1 && started == true && ended == false )
        {
            buffer[ buf_index++ ] = in_byte;
            ended = true;
        }
        // If the byte is not the end byte
        else if( started == true && ended == false )
        {
            if( buf_index < BUFFER_SPACE - 1)
            {
                buffer[ buf_index++ ] = in_byte;
            }
        }

        // We have gotten a full message if both started and ended are true
        if( started == true && ended == true )
        {
            return true;
        }
    }
    
    
    return false;
}

/**
 * @brief Used to monitor a serial port connection
 * 
 * @details Will write all src port activity to the target port and vice versa.
 *          This can be used to monitor a port connection and print it to the
 *          serial monitor in Arduino.
 * 
 * @param src Serial port to provide data from the source
 * @param target Serial port to provide data from the target
 */
inline void monitor( Stream& src, Stream& target )
{
    if( src.available() )
    {
        target.write( src.read() );
    }

    if( target.available() )
    {
        src.write( target.read() );
    }
}
   
} // End of namespace serial

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/

#endif
