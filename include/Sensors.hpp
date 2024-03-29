#pragma once

#if defined(ARDUINO) || defined(CORE_TEENSY)
    #include "Arduino.h"
#else
    #include <cstddef>
#endif

#include "Data.hpp"

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

/*!
 *  \addtogroup sensor
 *  @{
 */

//! Sensor interfaces
namespace sensor
{

/**
 * @brief Abstract IMU definition
 */
class IMU
{
public: 

    /** @brief Defines configuration data for the IMU */
    struct Config_t
    {
        // Can add things like offsets here
        // Make sure to include defaults here
    };

    /**
     * @brief Initializes the IMU
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Initializes the IMU with user configuration
     * 
     * @param config user selected IMU configuration
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    bool init( IMU::Config_t config )
    {
        m_config = config;
        init();
    }

    /**
     * @brief Update the IMU data
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update( ) = 0;

    /**
     * @brief Get imu data
     * 
     * @return const def::IMU_t& reference to IMU's data struct
     */
    const def::IMU_t& data(void) { return m_data; }

    /**
     * @brief Destructor
     */
    virtual ~IMU(){}

protected:
    // Hidden constructor that only children can redefine
    IMU(){}

    // Member variables
    def::IMU_t m_data;      // For imu data
    IMU::Config_t m_config; // For imu configuration
};

/**
 * @brief Abstract GPS definition
 */
class GPS
{
public:
    /** @brief Defines configuration data for the GPS */
    struct Config_t
    {
        uint32_t baud_rate;
        uint16_t poll_time_ms;
        // Can add things like offsets here
        // Make sure to include defaults here
    };

    /**
     * @brief Initializes the GPS
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Initializes the GPS with user configuration
     * 
     * @param config user selected GPS configuration
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    bool init( GPS::Config_t config )
    {
        m_config = config;
        init();
    }

    /**
     * @brief Update the GPS data
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update( ) = 0;

    /**
     * @brief Get GPS data
     * 
     * @return const def::GPS_t& reference to GPS's data struct
     */
    const def::GPS_t& data(void) { return m_data; }

    /**
     * @brief Destructor
     */
    virtual ~GPS(){}

protected:
    // Hidden constructor that only children can redefine
    GPS(){}

    // Member variables
    def::GPS_t m_data;      // For gps data
    GPS::Config_t m_config; // For gps configuration
};

/**
 * @brief Abstract Pitot Tube definition aka differential pressure sensor
 */
class Pitot
{
public:
    /** @brief Defines configuration data for the pitot tube */
    struct Config_t
    {
        // Can add things like offsets here
        // Make sure to include defaults here
    };

    /**
     * @brief Initializes the pitot tube
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Initializes the pitot tube with user configuration
     * 
     * @param config user selected pitot tube configuration
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    bool init( Pitot::Config_t config )
    {
        m_config = config;
        init();
    }

    /**
     * @brief Update the pitot tube data
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update( ) = 0;

    /**
     * @brief Get pitot tube data
     * 
     * @return const def::Pitot_t& reference to pitot tube's data struct
     */
    const def::Pitot_t& data(void) { return m_data; }

    /**
     * @brief Destructor
     */
    virtual ~Pitot(){}

protected:
    // Hidden constructor that only children can redefine
    Pitot(){}

    // Member variables
    def::Pitot_t m_data;      // For pitot tube data
    Pitot::Config_t m_config; // For pitot tube configuration
};

/**
 * @brief Abstract environmental sensor definition
 */
class EnviroSensor
{
public:
    /** @brief Defines configuration data for the environmental sensor */
    struct Config_t
    {
        // Can add things like offsets here
        // Make sure to include defaults here
    };

    /**
     * @brief Initializes the environmental sensor
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Initializes the environmental sensor with user configuration
     * 
     * @param config user selected environmental sensor configuration
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    bool init( EnviroSensor::Config_t config )
    {
        m_config = config;
        init();
    }

    /**
     * @brief Update the environmental sensor data
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update( ) = 0;

    /**
     * @brief Get environmental sensor data
     * 
     * @return const def::Enviro_t& reference to environmental sensor's data struct
     */
    const def::Enviro_t& data(void) { return m_data; }

    /**
     * @brief Destructor
     */
    virtual ~EnviroSensor(){}

protected:
    // Hidden constructor that only children can redefine
    EnviroSensor(){}

    // Member variables
    def::Enviro_t m_data;      // For environmental sensor data
    EnviroSensor::Config_t m_config; // For environmental sensor configuration
};

/**
 * @brief Abstract radio sensor definition
 */
class Radio
{
public:
    /**
     * @brief Initializes the radio 
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Update the radio data for messages
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update() = 0;

    /**
     * @brief Check if there is a new message
     * 
     * @return true if there is a message
     * @return false if there are no new messages
     */
    virtual bool ready() = 0;

    /**
     * @brief Receive a new message if ready
     * 
     * @param buf the buffer to receive into
     * @param len the number of bytes received
     * 
     * @return true if successful read
     * @return false if unsuccessful read
     */
    virtual bool receive(uint8_t* buf, uint8_t *len) = 0;

    /**
     * @brief Send a message over the radio 
     * 
     * @param buf the buffer to send
     * @param len the size of the buffer
     * 
     * @return true if packet send was successful
     * @return false if packet send was unsuccessful
     */
    virtual bool send(uint8_t* buf, uint8_t len) = 0;

    /**
     * @brief Get radio sensor data
     * 
     * @return const def::Radio_t& reference to radio's data struct
     */
    const def::Radio_t& data(void) { return m_data; }

    /**
     * @brief Destructor
     */
    virtual ~Radio(){}

protected:
    // Hidden constructor that only children can redefine
    Radio(){}

    // Member variables
    def::Radio_t m_data;      // For environmental sensor data
    size_t RECEIVE_BUFFER_SIZE;
};

} // End of namespace sensor

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/