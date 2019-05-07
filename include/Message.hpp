#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <cstddef>
#endif

#include "Data.hpp"

namespace aero
{

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
    Message& add_pitot( const Pitot& data );
    
    /**
     * @brief Add IMU data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_imu( const IMU& data );

    /**
     * @brief Add GPS data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_gps ( const GPS& data );

    /**
     * @brief Add environmental sensor data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_enviro( const Enviro& data );

    /**
     * @brief Add battery data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_battery( const Battery& data );

    /**
     * @brief Add config data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_config( const Config& data );

    /**
     * @brief Add status information to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_status( const Status& data );

    /**
     * @brief Add actuator definition to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_actuators( const Servos& data );

    /**
     * @brief Add air data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_airdata( const AirData& data );

    /**
     * @brief Add commands to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_cmds( const Commands& data );

    /**
     * @brief Add drop algorithm results to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_drop( const DropAlgo& data );

    /**
     * @brief Used to build a message with data buffer based on builder functions
     * 
     * @param from who the message is from
     * @param to who the message is for
     * @param clear true if you want to clear the old message buffer after building
     * @return RawMessage built message
     */
    RawMessage build( ID from, ID to, bool clear = false);

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
    ParsedMessage parse( const uint8_t* message );

protected:
private:
    // Private helper functions
    void set( Signature buf_segment, uint8_t* data );
    uint8_t segment_size( Signature buf_segment );
    uint16_t chk_sum( const RawMessage& message );

    // Array to store each struct as buffer segments
    uint8_t* buffer_segments[12];
};

} // End of namespace aero

#endif // MESSAGE_HPP