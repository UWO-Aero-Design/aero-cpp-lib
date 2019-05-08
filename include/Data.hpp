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
 * @brief Enum class for data signatures of each struct that can be sent
 */
enum class Signature{ Pitot, IMU, GPS, Enviro, Batt, Config, Status, Actuators, AData, Cmds, Drop };

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
};

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
    uint16_t pressure;
    uint16_t humidity;
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
 * @brief Command data
 */
struct __attribute__((__packed__)) DropAlgo_t
{
    int16_t heading;
    uint16_t distance;
};

} // End of namespace def

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/
