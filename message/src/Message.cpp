#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <cstddef>
    #include <cstring>
#endif

#include "Message.hpp"

namespace aero
{

// Default constructor
Message::Message( void )
{

    for( int i = 0; i < 12; ++i)
    {
        buffer_segments[i] = NULL;
    }
}

// Add pitot to buffer
Message& Message::add_pitot( const Pitot& data )
{
    this->set( Signature::Pitot, (uint8_t *) &data );
    return *this;
}

// Add imu to buffer
Message& Message::add_imu( const IMU& data )
{
    this->set( Signature::IMU, (uint8_t *) &data );
    return *this;
}

// Add gps to buffer
Message& Message::add_gps ( const GPS& data )
{
    this->set( Signature::GPS, (uint8_t *) &data );
    return *this;
}

// Add enviro to buffer
Message& Message::add_enviro( const Enviro& data )
{
    this->set( Signature::Enviro, (uint8_t *) &data );
    return *this;
}

// Add battery to buffer
Message& Message::add_battery( const Battery& data )
{
    this->set( Signature::Batt, (uint8_t *) &data );
    return *this;
}

// Add config to buffer
Message& Message::add_config( const Config& data )
{
    this->set( Signature::Config, (uint8_t *) &data );
    return *this;
}

// Add status to buffer
Message& Message::add_status( const Status& data )
{
    this->set( Signature::Status, (uint8_t *) &data );
    return *this;
}

// Add actuators to buffer
Message& Message::add_actuators( const Actuators& data )
{
    this->set( Signature::Actuators, (uint8_t *) &data );
    return *this;
}

// Add air data to buffer
Message& Message::add_airdata( const AirData& data )
{
    this->set( Signature::AData, (uint8_t *) &data );
    return *this;
}

// Add cmds to buffer
Message& Message::add_cmds( const Commands& data )
{
    this->set( Signature::Cmds, (uint8_t *) &data );
    return *this;
}

// Add drop algo to buffer
Message& Message::add_drop( const DropAlgo& data )
{
    this->set( Signature::Drop, (uint8_t *) &data );
    return *this;
}

// Build full message based on buffer
RawMessage Message::build( ID from, ID to, bool clear )
{
    // Blank message
    RawMessage message = {0, 0, 0, NULL, 0, 0, 0};

    // Set start and stop
    message.start = 0x0A;
    message.end = 0x0F;

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
    RawMessage* msg = ( RawMessage* ) message;
    
    // If the check sum sent in the message equals the check sum we calculate,
    // We have a valid message
    uint16_t crc = chk_sum( *msg );

    if( msg->crc == crc )
        return true;
    else
        return false;
}

// Parse valid buffer
ParsedMessage Message::parse( const uint8_t* message )
{
    // Message to parse
    RawMessage* msg = ( RawMessage* ) message;

    // Message to parse result into
    ParsedMessage result;

    // Set from and to values. TODO: Set these by extracting top byte and lower byte
    result.m_from = ID::G2;
    result.m_to = ID::G1;

    int signature = msg->signature;
    int length = 0;

    for( int i = 0; i < 12; ++i )
    {      
        // If LSB is set, parse out buffer element
        if( ( signature & 1 ) == 1)
        {
            // Grab size of struct to parse
            int size = segment_size( static_cast<Signature>(i) );
            // Allocate size for segment buffer
            result.segments[i] = new uint8_t[size];
            // Copy raw buffer into results
            memcpy( result.segments[i], msg->buffer+length, size );
            length += size;
        }
        else
            result.segments[i] = NULL;
        
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
uint16_t Message::chk_sum ( const RawMessage& message )
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
            return sizeof( struct Pitot );
        } break;
        case Signature::IMU:
        {
            return sizeof( struct IMU );
        } break;
        case Signature::GPS:
        {
            return sizeof( struct GPS );
        } break;
        case Signature::Enviro:
        {
            return sizeof( struct Enviro );
        } break;
        case Signature::Batt:
        {
            return sizeof( struct Battery );
        } break;
        case Signature::Config:
        {
            return sizeof( struct Config );
        } break;
        case Signature::Status:
        {
            return sizeof( struct Status );
        } break;
        case Signature::Actuators:
        {
            return sizeof( struct Actuators );
        } break;
        case Signature::AData:
        {
            return sizeof( struct AirData );
        } break;
        case Signature::Cmds:
        {
            return sizeof( struct Commands );
        } break;
        case Signature::Drop:
        {
            return sizeof( struct DropAlgo );
        } break;
        default:
        {
            return 0;
        } break;
    }
}

} // End of aero namespace