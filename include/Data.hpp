#pragma once

// Aero Communication Protocol V1.0 -- 2019 / 2020

#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <cstdint>
#endif

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

/*!
 *  \addtogroup def
 *  @{
 */

//! Definitions for the library such as usable structs, constants, etc
namespace def
{

/**
 * @brief Raw pitot tube data 
 */
struct __attribute__((__packed__)) Pitot_t
{
    int16_t differential_pressure;
};

/**
 * @brief Raw IMU data
 */
struct __attribute__((__packed__)) IMU_t
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
    int16_t mx;
    int16_t my;
    int16_t mz;
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
};

/**
 * @brief Raw GPS data
 */
struct __attribute__((__packed__)) GPS_t
{
    int32_t lat;
    int32_t lon;
    uint16_t speed;
    uint8_t satellites;
    uint16_t altitude;
    uint32_t time;  // 4 BYTES. XX HR MIN SEC
    uint32_t date;  // 4 BYTES. XX YR MNTH DAY
};

/**
 * @brief Raw environmental sensor data 
 */
struct __attribute__((__packed__)) Enviro_t
{
    uint16_t altitude;
    uint16_t temperature; 
};

/**
 * @brief Raw battery status data
 */
struct __attribute__((__packed__)) Battery_t
{
    uint16_t voltage;
    uint16_t current;
};

/**
 * @brief Configuration data
 */
struct __attribute__((__packed__)) SystemConfig_t
{

};

/**
 * @brief System status data
 */
struct __attribute__((__packed__)) Status_t
{
    int16_t rssi;        // Signal strength
    uint32_t state;      // State bit fields
};

/**
 * @brief Servo data. High bytes are MAX, Low bytes are MIN 
 */
struct __attribute__((__packed__)) Servos_t
{
    uint32_t servo0;
    uint32_t servo1;
    uint32_t servo2;
    uint32_t servo3;
    uint32_t servo4;
    uint32_t servo5;
    uint32_t servo6;
    uint32_t servo7;
    uint32_t servo8;
    uint32_t servo9;
    uint32_t servo10;
    uint32_t servo11;
    uint32_t servo12;
    uint32_t servo13;
    uint32_t servo14;
    uint32_t servo15;
};

/**
 * @brief Processed flight data from raw sensor sources
 */
struct __attribute__((__packed__)) AirData_t
{
    uint32_t ias;
    uint32_t eas;
    uint32_t tas;
    uint32_t agl;
    uint32_t pressure_alt;
    uint32_t msl;
    uint32_t density_alt;
    uint32_t approx_temp;
    uint32_t density;
};

/**
 * @brief Command data
 */
struct __attribute__((__packed__)) Commands_t
{
    uint8_t drop;
    uint16_t servos;
    uint8_t pitch;
};

/**
 * @brief Drop Algorithm data
 */
struct __attribute__((__packed__)) DropAlgo_t
{
    int16_t heading;
    uint16_t distance;
};

/**
 * @brief Enum class for data signatures of each struct that can be sent
 */
enum class Signature{ Pitot, IMU, GPS, Enviro, Batt, Config, Status, Actuators, AData, Cmds, Drop };

/**
 * @brief Enum class for IDs of possible send and target recipients
 */
enum class ID{ Gnd, Plane, G1, G2 };

/** @brief Start byte definition for serial communications */
const uint8_t START_BYTE = 0xAA; 
/** @brief Stop byte definition for serial communications */
const uint8_t END_BYTE = 0xFF;   

/**
 * @brief Raw message struct used to represent a unparsed message
 */
struct __attribute__((__packed__)) RawMessage_t
{
    uint8_t start;       // Start byte for serial transfer
    uint16_t link;       // Link describes the connection the message is trying to bridge. Sender --> Recipient
    uint16_t signature;  // Bits for determining what data is being sent

    uint8_t length;
    uint8_t buffer[200]; // Actual data. Max size
    

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
    Pitot_t* pitot( void ) const
    {
        int index = static_cast<int>(Signature::Pitot);
        return reinterpret_cast<Pitot_t*>( segments[ index ] );
    }

    IMU_t* imu( void ) const
    {
        int index = static_cast<int>(Signature::IMU);
        return reinterpret_cast<IMU_t*>( segments[ index ] );
    }

    GPS_t* gps( void ) const
    {
        int index = static_cast<int>(Signature::GPS);
        return reinterpret_cast<GPS_t*>( segments[ index ] );
    }

    Enviro_t* enviro( void ) const
    {
        int index = static_cast<int>(Signature::Enviro);
        return reinterpret_cast<Enviro_t*>( segments[ index ] );
    }

    Battery_t* battery( void ) const
    {
        int index = static_cast<int>(Signature::Batt);
        return reinterpret_cast<Battery_t*>( segments[ index ] );
    }

    SystemConfig_t* config( void ) const
    {
        int index = static_cast<int>(Signature::Config);
        return reinterpret_cast<SystemConfig_t*>( segments[ index ] );
    }

    Status_t* status( void ) const
    {
        int index = static_cast<int>(Signature::Status);
        return reinterpret_cast<Status_t*>( segments[ index ] );
    }

    Servos_t* servos( void ) const
    {
        int index = static_cast<int>(Signature::Actuators);
        return reinterpret_cast<Servos_t*>( segments[ index ] );
    }

    AirData_t* air_data( void ) const
    {
        int index = static_cast<int>(Signature::AData);
        return reinterpret_cast<AirData_t*>( segments[ index ] );
    }

    DropAlgo_t* drop_algo( void ) const
    {
        int index = static_cast<int>(Signature::Drop);
        return reinterpret_cast<DropAlgo_t*>( segments[ index ] );
    }
};

} // End of namespace def

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/
