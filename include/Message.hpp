#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#if defined(ARDUINO) || defined(CORE_TEENSY)
    #include "Arduino.h"
#else
    #include <cstddef>
#endif

#include "Data.hpp"

namespace aero
{

/**
 * @brief Enum class for IDs of possible send and target recipients
 */
enum class ID{ Gnd, Plane, G1, G2 };

/** @brief Start byte definition for serial communications */
const uint16_t START_BYTE = 0x0A; 
/** @brief Stop byte definition for serial communications */
const uint16_t END_BYTE = 0x0F;   

/**
 * @brief Raw message struct used to represent a unparsed message
 */
struct __attribute__((__packed__)) RawMessage_t
{
    uint8_t start;       // Start byte for serial transfer
    uint16_t link;       // Link describes the connection the message is trying to bridge. Sender --> Recipient
    uint16_t signature;  // Bits for determining what data is being sent

    uint8_t buffer[256]; // Actual data. Max size
    uint8_t length;

    uint16_t crc;        // Try fast crc
    uint8_t end;         // End byte for serial transfer
};

/**
 * @brief Parsed message
 */
struct __attribute__((__packed__)) ParsedMessage_t
{
    ParsedMessage_t()
    {
        for(int i = 0; i < 12; ++i)
            segments[i] = NULL;
    } 

    ~ParsedMessage_t()
    {
        for(int i = 0; i < 12; ++i)
            delete segments[i]; 
    }

    ID m_from, m_to;
    uint8_t* segments[12];

    // Data accessors
    def::MsgPitot_t* pitot( void ) const
    {
        int index = static_cast<int>(def::Signature::Pitot);
        return reinterpret_cast<def::MsgPitot_t*>( segments[ index ] );
    }

    def::IMU_t* imu( void ) const
    {
        int index = static_cast<int>(def::Signature::IMU);
        return reinterpret_cast<def::IMU_t*>( segments[ index ] );
    }

    def::GPS_t* gps( void ) const
    {
        int index = static_cast<int>(def::Signature::GPS);
        return reinterpret_cast<def::GPS_t*>( segments[ index ] );
    }

    def::Enviro_t* enviro( void ) const
    {
        int index = static_cast<int>(def::Signature::Enviro);
        return reinterpret_cast<def::Enviro_t*>( segments[ index ] );
    }

    def::Battery_t* battery( void ) const
    {
        int index = static_cast<int>(def::Signature::Batt);
        return reinterpret_cast<def::Battery_t*>( segments[ index ] );
    }

    def::SystemConfig_t* config( void ) const
    {
        int index = static_cast<int>(def::Signature::Config);
        return reinterpret_cast<def::SystemConfig_t*>( segments[ index ] );
    }

    def::Status_t* status( void ) const
    {
        int index = static_cast<int>(def::Signature::Status);
        return reinterpret_cast<def::Status_t*>( segments[ index ] );
    }

    def::Servos_t* servos( void ) const
    {
        int index = static_cast<int>(def::Signature::Actuators);
        return reinterpret_cast<def::Servos_t*>( segments[ index ] );
    }

    def::AirData_t* air_data( void ) const
    {
        int index = static_cast<int>(def::Signature::AData);
        return reinterpret_cast<def::AirData_t*>( segments[ index ] );
    }

    def::DropAlgo_t* drop_algo( void ) const
    {
        int index = static_cast<int>(def::Signature::Drop);
        return reinterpret_cast<def::DropAlgo_t*>( segments[ index ] );
    }
};

/**
 * @brief Class used to build and parse buffer-based messages
 */
class Message
{

public:
    /**
     * @brief Construct a new Message object
     */
    Message( void );
    
    /**
     * @brief Add pitot data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_pitot( const def::MsgPitot_t& data );
    
    /**
     * @brief Add IMU data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_imu( const def::IMU_t& data );

    /**
     * @brief Add GPS data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_gps ( const def::GPS_t& data );

    /**
     * @brief Add environmental sensor data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_enviro( const def::Enviro_t& data );

    /**
     * @brief Add battery data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_battery( const def::Battery_t& data );

    /**
     * @brief Add config data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_config( const def::SystemConfig_t& data );

    /**
     * @brief Add status information to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_status( const def::Status_t& data );

    /**
     * @brief Add actuator definition to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_actuators( const def::Servos_t& data );

    /**
     * @brief Add air data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_airdata( const def::AirData_t& data );

    /**
     * @brief Add commands to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_cmds( const def::Commands_t& data );

    /**
     * @brief Add drop algorithm results to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_drop( const def::DropAlgo_t& data );

    /**
     * @brief Used to build a message with data buffer based on builder functions
     * 
     * @param from who the message is from
     * @param to who the message is for
     * @param clear true if you want to clear the old message buffer after building
     * @return RawMessage built message
     */
    RawMessage_t build( ID from, ID to, bool clear = false);

    /**
     * @brief Check if a uint8_t* buffer is a valid message based on size and check sum
     * 
     * @param message unvalidated buffer
     * @return true if buffer is a valid message
     * @return false if buffer is an invalid message
     */
    bool validate( const uint8_t* message );

    /**
     * @brief Takes a valid buffer and parses the data into a struct
     * 
     * @param message valid buffer to be parsed
     * @return ParsedMessage parsed message 
     */
    ParsedMessage_t parse( const uint8_t* message );

protected:
private:
    // Private helper functions
    void set( def::Signature buf_segment, uint8_t* data );
    uint8_t segment_size( def::Signature buf_segment );
    uint16_t chk_sum( const RawMessage_t& message );

    // Array to store each struct as buffer segments
    uint8_t* buffer_segments[12];
};

} // End of namespace aero

#endif // MESSAGE_HPP