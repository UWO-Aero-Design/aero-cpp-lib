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

    /** @brief types of IMUs that can be made by factory pattern */
    enum class Model { };
    /**
     * @brief Make an IMU object
     * 
     * @param choice which IMU child to make
     * @return IMU* newly created object of selected type
     */
    static IMU* make_imu( Model choice );

    /**
     * @brief Destructor
     */
    virtual ~IMU();

protected:
    // Hidden constructor that only children can redefine
    IMU(){}

    // Member variables
    def::IMU_t m_data;      // For imu data
    IMU::Config_t m_config; // For imu configuration
};

} // End of namespace sensor

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/