#pragma once

#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <cstdint>
    #include <cstring>
    #include <iostream>
#endif

#include "Structures.hpp"

class MessageHandler
{
public:
    MessageHandler();

    // Building process
    MessageHandler& set_pitot( PitotTube );
    MessageHandler& set_imu( const IMU& data );
    MessageHandler& set_gps( GPS );
    MessageHandler& set_enviro( EnviroSensor );
    MessageHandler& set_battery( Battery );
    MessageHandler& set_config( Config );
    MessageHandler& set_status( Status );
    MessageHandler& set_actuators( Actuators );
    MessageHandler& set_adata( AirData );
    MessageHandler& set_cmds( Commands );
    MessageHandler& set_drop( DropAlgorithm );

    RawMessage build( ID start, ID end );

    // Parsing process
    bool validate( const uint8_t* message ); 
    ParsedMessage parse( const uint8_t* message);

private:
    void set( Signature segment, uint8_t* data);
    uint8_t packet_size( Signature segment );
    uint16_t chk_sum ( RawMessage message );

    uint8_t* buffer_segments[12];
};
MessageHandler::MessageHandler()
{   
    for(int i = 0; i < 12; ++i )
        buffer_segments[i] = NULL;
}

bool MessageHandler::validate( const uint8_t* message )
{
    // We are receiving message
    RawMessage* msg = ( RawMessage * ) message;
    uint16_t crc = chk_sum( *msg );

    if( msg->crc == crc )
        return true;
    else
        return false;
}

ParsedMessage MessageHandler::parse( const uint8_t* message )
{
    // We are receiving message
    RawMessage* msg = ( RawMessage * ) message;

    ParsedMessage result;

    result.m_from = ID::G2;
    result.m_to = ID::G1;

    int temp = msg->signature;
    int length = 0;

    for( int i = 0; i < 12; ++i )
    {   
        int bit = ( temp & 1 );
        temp >>= 1;

        if( bit )
        {
            int size = packet_size( static_cast<Signature>(i) );
            uint8_t temp[256];
            memcpy( temp, msg->buffer+length, size );
            result.segments[i] = temp;
            length += size;
        }
        else
            result.segments[i] = NULL;
    }

    return result;
}

uint16_t MessageHandler::chk_sum ( RawMessage message )
{
    return 1;
}

void MessageHandler::set( Signature segment, uint8_t* data )
{
    std::cout << "Set\n" ;
    int signature = static_cast< int >( segment );
    std::cout << "Index " << signature << std::endl;
    buffer_segments[ signature ] = data;
}

MessageHandler& MessageHandler::set_pitot( PitotTube data )
{
    this->set( Signature::Pitot, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_imu( const IMU& data )
{
    std::cout << "Data test " << data.ax << std::endl;
    // this->set( Signature::IMU, (uint8_t *) &data );

    buffer_segments[ 1 ] = (uint8_t *) &data;

    std::cout << "Data test " << ( (IMU *) buffer_segments[ 1 ] )->ax << std::endl;
    return *this;
}

MessageHandler& MessageHandler::set_gps( GPS data )
{
    this->set( Signature::GPS, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_enviro( EnviroSensor data )
{
    this->set( Signature::Enviro, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_battery( Battery data )
{
    this->set( Signature::Batt, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_config( Config data )
{
    this->set( Signature::Config, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_status( Status data )
{
    this->set( Signature::Status, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_actuators( Actuators data )
{
    this->set( Signature::Actuators, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_adata( AirData data )
{
    this->set( Signature::AData, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_cmds( Commands data )
{
    this->set( Signature::Cmds, (uint8_t *) &data );
    return *this;
}

MessageHandler& MessageHandler::set_drop( DropAlgorithm data )
{
    this->set( Signature::Drop, (uint8_t *) &data );
    return *this;
}

RawMessage MessageHandler::build( ID from, ID to )
{
    IMU *imu = ( reinterpret_cast<IMU*>(buffer_segments[ 1 ]) );
    
    std::cout << "Cast test " << ( (IMU * ) buffer_segments[ 1 ] )->ay << "\n"; 

    RawMessage message;
    
    // TODO: Start stop
    message.start = 0x0A;
    message.end   = 0x0F;

    //imu = ( (IMU * ) buffer_segments[ 1 ] );
    std::cout << "Cast test ay " << (imu)->ay << "\n"; 

    // uint8_t from_id = static_cast< int >( from );
    // uint8_t to_id = static_cast< int >( to );
    
    // message.link = ( ( (uint16_t) from_id << 8 ) | to_id );

    for( int i = 0; i < 12; ++i )
    {
        if( buffer_segments[i] != NULL )
        {
            
            std::cout << "Cast test Cast test " << ( (IMU * ) buffer_segments[ 1 ] )->az << "\n"; 
            

            message.signature |= ( 1 << (i) );
            // Copy in data to the buffer

            uint8_t size = packet_size( static_cast<Signature> (i) );
            memcpy( message.buffer + message.length, buffer_segments[i], size);
            message.length += size;
        }
    }

    // Calculate checksum
    message.crc = chk_sum( message );

    for( int i = 0; i < 12; ++i )
        buffer_segments[i] = NULL;

    return message;
}

// Large switch case with sizeof on structs
uint8_t MessageHandler::packet_size( Signature segment )
{
    switch( segment )
    {
        case Signature::Pitot:
        {
            return sizeof( struct PitotTube );
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
            return sizeof( struct EnviroSensor );
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
            return sizeof( struct DropAlgorithm );
        } break;
        default:
        {
            return 0;
        } break;
    }
}