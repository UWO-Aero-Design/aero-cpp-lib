#pragma once

// Aero Communication Protocol V1.0 -- 2019 / 2020

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
struct Pitot_t
{
    float differential_pressure;
};

/**
 * @brief Raw IMU data
 */
struct IMU_t
{
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float mx;
    float my;
    float mz;
    float yaw;
    float pitch;
    float roll;
};

/**
 * @brief Raw GPS data
 */
struct GPS_t
{
    bool fix;
    float lat;
    float lon;
    float speed;
    uint32_t satellites;
    float altitude;
    uint32_t time;
    uint32_t date;
    uint32_t HDOP;
    uint32_t quality;
};

/**
 * @brief Raw environmental sensor data 
 */
struct Enviro_t
{
    float altitude;
    float temperature; 
    float pressure; 
};

/**
 * @brief Raw battery status data
 */
struct Battery_t
{
    float voltage;
    float current;
};

/**
 * @brief Raw radio data
 */
struct Radio_t
{
    float rssi;
    int32_t frequencyError;
    int32_t snr;
};

/**
 * @brief Configuration data
 */
struct SystemConfig_t
{

};

/**
 * @brief System status data
 */
struct Status_t
{
    float rssi;        // Signal strength
    uint32_t state;      // State bit fields
};

/**
 * @brief Servo data. High bytes are MAX, Low bytes are MIN 
 */
struct Servos_t
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
struct AirData_t
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
struct Commands_t
{
    uint8_t drop;
    uint16_t servos;
    uint8_t pitch;
};

/**
 * @brief Drop Algorithm data
 */
struct DropAlgo_t
{
    int16_t heading;
    uint16_t distance;
};

} // End of namespace def

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/
