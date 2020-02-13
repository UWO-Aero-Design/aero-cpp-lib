#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <cstddef>
    #include <cstring>
#endif

#include "../include/Message.hpp"

namespace aero
{

// Using namespace to clean up the code
using namespace def;

Message::~Message( void ) {
    for(int i = 0; i < 12; i++) {
        delete(result->segments[i]);
    }

    delete(result);
}

// Default constructor
Message::Message( void )
{

    for( int i = 0; i < 12; ++i)
    {
        buffer_segments[i] = NULL;
    }

    result = new ParsedMessage_t();

    for(int i = 0; i < 12; i++) {
        int size = segment_size( static_cast<Signature>(i) );
        result->segments[i] = new uint8_t[size];
    }
}

// Add pitot to buffer
Message& Message::add_pitot( const Pitot_t& data )
{
    this->set( Signature::Pitot, (uint8_t *) &data );
    return *this;
}

// Add imu to buffer
Message& Message::add_imu( const IMU_t& data )
{
    this->set( Signature::IMU, (uint8_t *) &data );
    return *this;
}

// Add gps to buffer
Message& Message::add_gps ( const GPS_t& data )
{
    this->set( Signature::GPS, (uint8_t *) &data );
    return *this;
}

// Add enviro to buffer
Message& Message::add_enviro( const Enviro_t& data )
{
    this->set( Signature::Enviro, (uint8_t *) &data );
    return *this;
}

// Add battery to buffer
Message& Message::add_battery( const Battery_t& data )
{
    this->set( Signature::Batt, (uint8_t *) &data );
    return *this;
}

// Add config to buffer
Message& Message::add_config( const SystemConfig_t& data )
{
    this->set( Signature::Config, (uint8_t *) &data );
    return *this;
}

// Add status to buffer
Message& Message::add_status( const Status_t& data )
{
    this->set( Signature::Status, (uint8_t *) &data );
    return *this;
}

// Add actuators to buffer
Message& Message::add_actuators( const Servos_t& data )
{
    this->set( Signature::Actuators, (uint8_t *) &data );
    return *this;
}

// Add air data to buffer
Message& Message::add_airdata( const AirData_t& data )
{
    this->set( Signature::AData, (uint8_t *) &data );
    return *this;
}

// Add cmds to buffer
Message& Message::add_cmds( const Commands_t& data )
{
    this->set( Signature::Cmds, (uint8_t *) &data );
    return *this;
}

// Add drop algo to buffer
Message& Message::add_drop( const DropAlgo_t& data )
{
    this->set( Signature::Drop, (uint8_t *) &data );
    return *this;
}

// Build full message based on buffer
RawMessage_t Message::build( ID from, ID to, bool clear )
{
    // Blank message
    RawMessage_t message = {0, 0, 0, NULL, 0, 0, 0};

    // Set start and stop
    message.start = def::START_BYTE;
    message.end = def::END_BYTE;

    // Determine from and to for link
    uint8_t from_id = static_cast< int >( from );
    uint8_t to_id = static_cast< int >( to );
    
    message.link = ( ( (uint16_t) from_id << 8 ) | to_id );

    // Set the signature for non-null buffers and copy in the buffer to the raw message
    for( int i = 0; i < 12; ++i )
    {
        if( buffer_segments[i] != NULL )
        {
            // Set signature bit
            message.signature |= ( 1 << (i) );

            // Copy in data to the buffer
            uint8_t size = segment_size( static_cast<Signature> (i) );
            memcpy( message.buffer + message.length, buffer_segments[i], size);
            message.length += size;
        }
    }

    // Calculate checksum
    message.crc = chk_sum( message );

    // Reset buffer if asked
    if( clear == true)
    {
        for( int i = 0; i < 12; ++i )
        {
            buffer_segments[i] = NULL;
        }
    }

    // Return data
    return message;
}

// Validate buffer as message
bool Message::validate( const uint8_t* message )
{
    // We are receiving message
    RawMessage_t* msg = ( RawMessage_t* ) message;
    
    // If the check sum sent in the message equals the check sum we calculate,
    // We have a valid message
    uint16_t crc = chk_sum( *msg );

    if( msg->crc == crc )
        return true;
    else
        return false;
}

// Parse valid buffer
ParsedMessage_t* Message::parse( const uint8_t* message )
{
    // Message to parse
    RawMessage_t* msg = ( RawMessage_t* ) message;

    // Message to parse result into
    // ParsedMessage_t result;

    // Set from and to values.
    result->m_from = (static_cast< ID >( ( msg->link >> 8)  ) ); // Extract upper byte
    result->m_to = (static_cast< ID >( msg->link & 0xFF ) );     // Extract lower byte

    int signature = msg->signature;
    int length = 0;

    for( int i = 0; i < 12; ++i )
    {      
        // If LSB is set, parse out buffer element
        if( ( signature & 1 ) == 1)
        {
            // Grab size of struct to parse
            int size = segment_size( static_cast<Signature>(i) );
            // Copy raw buffer into results
            memcpy( result->segments[i], msg->buffer+length, size );
            length += size;
        }
        else
            result->segments[i] = NULL;
        
        // Shift signature over to keep checking LSBs
        signature >>= 1;
    }

    return result;
}

// Set correct buffer segment
void Message::set( Signature buf_segment, uint8_t* data )
{
    int signature = static_cast< int >( buf_segment );
    buffer_segments[ signature ] = data;
}

// Calculate check sum
uint16_t Message::chk_sum ( const RawMessage_t& message )
{
    // TODO: Implement check sum
    return 1;
}


// Get size of struct based on Signature enum
uint8_t Message::segment_size( Signature segment )
{
    switch( segment )
    {
        case Signature::Pitot:
        {
            return sizeof( struct Pitot_t );
        } break;
        case Signature::IMU:
        {
            return sizeof( struct IMU_t );
        } break;
        case Signature::GPS:
        {
            return sizeof( struct GPS_t );
        } break;
        case Signature::Enviro:
        {
            return sizeof( struct Enviro_t );
        } break;
        case Signature::Batt:
        {
            return sizeof( struct Battery_t );
        } break;
        case Signature::Config:
        {
            return sizeof( struct SystemConfig_t );
        } break;
        case Signature::Status:
        {
            return sizeof( struct Status_t );
        } break;
        case Signature::Actuators:
        {
            return sizeof( struct Servos_t );
        } break;
        case Signature::AData:
        {
            return sizeof( struct AirData_t );
        } break;
        case Signature::Cmds:
        {
            return sizeof( struct Commands_t );
        } break;
        case Signature::Drop:
        {
            return sizeof( struct DropAlgo_t );
        } break;
        default:
        {
            return 0;
        } break;
    }
}

} // End of aero namespace