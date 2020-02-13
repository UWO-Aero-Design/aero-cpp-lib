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
 * @brief Class used to build and parse buffer-based messages
 */
class Message
{

public:
    /**
     * @brief Construct a new Message object
     */
    Message( void );

    ~Message( void );
    
    /**
     * @brief Add pitot data to the message buffer
     * 
     * @param data struct object to add to the message buffer
     * @return Message& reference to self for builder pattern
     */
    Message& add_pitot( const def::Pitot_t& data );
    
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
    def::RawMessage_t build( def::ID from, def::ID to, bool clear = false);

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
    def::ParsedMessage_t* parse( const uint8_t* message );

protected:
private:
    // Private helper functions
    void set( def::Signature buf_segment, uint8_t* data );
    uint8_t segment_size( def::Signature buf_segment );
    uint16_t chk_sum( const def::RawMessage_t& message );


    def::ParsedMessage_t *result;

    


    // Array to store each struct as buffer segments
    uint8_t* buffer_segments[12];
};

} // End of namespace aero

#endif // MESSAGE_HPP