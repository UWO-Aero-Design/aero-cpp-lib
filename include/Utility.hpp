#pragma once

#include <climits>
#include <cstddef>

#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <iostream>
    #include <climits>
    #include <cstddef>
    #include <cmath>
#endif

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

/*!
 *  \addtogroup bit
 *  @{
 */

//! Binary-level helper functions
namespace bit
{
    /**
     * Taken from stackoverflow from some brilliant person
     * 
     * @brief Used to swap endian order of a value
     * 
     * @tparam T data type of value you want to swap
     * @param to_swap value you want to swap endian value of
     * @return T swapped endian order value
     */
    template <typename T>
    T swap_endian( T to_swap )
    {
        union
        {
            T to_swap;
            unsigned char u8[ sizeof( T) ];
        } source, dest;

        // Apply union to input value
        source.to_swap = to_swap;

        for( size_t k = 0; k < sizeof( T ); ++k)
            dest.u8[k] = source.u8[ sizeof( T ) - k - 1];

        return dest.to_swap;
    }

    /**
     * @brief Set a bit
     * 
     * @param value Value to set a bit in
     * @param index Position of bit you want to set
     * @return int Value with bit at index set
     */
    int set( int value, unsigned int index )
    {
        return ( value | ( 1 << index ) );
    }

    /**
     * @brief Read a bit
     * 
     * @param value Value to read a bit from
     * @param index Position of bit you want to read
     * @return uint8_t Value of bit at position index in value
     */
    uint8_t read( int value, unsigned int index )
    {
        return ( ( value >> index ) & 0x01 );
    }

    /**
     * @brief Clear a bit
     * 
     * @param value Value to clear a bit in
     * @param index Position of bit you want to clear
     * @return int Value with bit at index cleared
     */
    int clear( int value, unsigned int index )
    {
        return ( value & ~( 1 << index ) );
    }

    /**
     * @brief Toggle a bit
     * 
     * @param value Value to toggle a bit in
     * @param index Position of bit you want to toggle
     * @return int Value with bit at index toggled
     */
    int toggle( int value, unsigned int index )
    {
        return ( value ^ ( 0x01 << index ) );
    }
} // End of namespace bit

/*! @} End of Doxygen Groups*/

/*!
 *  \addtogroup convert
 *  @{
 */

//! Data conversion helper functions
namespace convert // Credit goes to github.com/bolderflight/AirData
{
    // Namespace constants
    namespace
    {
        const static float gravity = 9.807f;            // Acceleration caused by gravity       [ m/s^2 ]
        const static float sl_sound_speed = 340.29f;    // Standard speed of sound at sea level [ m/s ]
        const static float sl_pressure = 101325.0f;     // Standard temperature at sea level    [ Pa ]
        const static float sl_temperature = 288.15f;    // Standard sea level temperature       [ K ]
        const static float lapse = 0.0065f;             // Standard lapse rate                  [ K/m ]
        const static float gas_const = 8.314f;          // Gas constant                         [ J/kg*mol ]
        const static float air_mass = 0.02895f;          // Molecular mass of air                [ kg/mol ]
    }

    /**
     * @brief Units for metric conversion
     */
    enum class Unit { n, u, m, base, k, M, G };

    /**
     * @brief Convert a value to a new metric prefix
     * 
     * @details A metric prefix is like centi or milli or kilo. So use this function
     *          to change from, for example, metres to kilometres, very easily
     * 
     * @param value Value you want to change
     * @param src Unit the value currently has
     * @param dest Unit you want the value to have
     * @return float Value with new metric prefix
     */
    float metric( float value, Unit src, Unit dest )
    {
        int exponent = static_cast< int >( dest ) - static_cast< int >( src );
        return value * powf( 1000.0f, exponent );
    }

    /**
     * @brief Calculates indicated airspeed in m/s 
     * 
     * @param diff_pressure Differential pressure in Pa
     * @return float Resulting indicated air speed
     */
    float ind_as( float diff_pressure )
    {
        return (sl_sound_speed * sqrtf( 5.0f * ( powf( ( ( sl_pressure / sl_pressure ) + 1.0f ), ( 2.0f/7.0f ) ) - 1.0f ) ) );
    }

    /**
     * @brief Calculates equivalent air speed in m/s
     * 
     * @param diff_pressure Differential pressure in Pa
     * @param pressure Static pressure in Pa
     * @return float Resulting equivalent air speed
     */
    float equiv_as( float diff_pressure, float pressure ) 
    {
        return sl_sound_speed * sqrtf(5.0f*pressure/sl_pressure*(powf((diff_pressure/pressure + 1.0f),(2.0f/7.0f)) - 1.0f));
    }

    /**
     * @brief Calculates true air speed in m/s
     * 
     * @param airspeed Either indicated or equivalent airspeed in m/s 
     * @param temperature Air temperature in Celsuis
     * @return float Resulting equivalent true air speed 
     */
    float true_as( float airspeed, float temperature ) 
    {
        return airspeed * sqrtf((temperature+273.15f)/sl_temperature);
    }

    /**
     * @brief Calculates pressure altitude in m
     * 
     * @param pressure Static Pressure in Pa
     * @return float Resulting pressure altitude
     */
    float pressure_altitude( float pressure ) 
    {
        return (sl_temperature/lapse)*(1.0f - powf((pressure/sl_pressure),((lapse*gas_const)/(air_mass*gravity))));
    }

    /**
     * @brief Calculates above ground level in m given an offet
     * 
     * @param pressure Static pressure in Pa
     * @param offset Level offset in m
     * @return float Resulting above ground level altitude in m
     */
    float above_gnd_altitude( float pressure, float offset ) 
    {
        return pressure_altitude( pressure ) - offset;
    }

    /**
     * @brief Calcualtes altitude above mean sea level in m
     * 
     * @param agl above ground level altitude in m
     * @param start_alt Start altitude of flight in m
     * @return float Resulting mean sea level altitude
     */
    float mean_sl_altitude( float agl, float start_alt ) 
    {
        return agl + start_alt;
    }

    /**
     * @brief Calculates density altitude in m which is based on standard atmosphere
     * 
     * @param pressure Static pressure in Pa
     * @param temperature Temperature in Celsius
     * @return float Resulting density altitude
     */
    float density_altitude( float pressure, float temperature ) 
    {
        return (sl_temperature/lapse)*(1.0f - powf(((pressure/sl_pressure)*(sl_temperature/(temperature+273.15f))),((lapse*gas_const)/(air_mass*gravity - lapse*gas_const))));
    }

    /**
     * @brief Calculate approximate temperature based on altitude in Celsius
     * 
     * @param temperature Current temperature in Celsuis
     * @param altitude Altitude in m
     * @return float Approximate temperature at altitude
     */
    float approx_temp( float temperature, float altitude ) 
    {
        return temperature - lapse*altitude;
    }

    /**
     * @brief Calculate air density in kg/m^3
     * 
     * @param pressure Static pressure in Pa
     * @param temperature Temperature in Celsius
     * @return float Resulting air density
     */
    float approx_density( float pressure, float temperature ) 
    {
        return (air_mass*pressure)/(gas_const*(temperature+273.15f));
    }
} // End of namespace convert

/*! @} End of Doxygen Groups*/

/*!
 *  \addtogroup print
 *  @{
 */

//! Printing helper functions to output data to serial monitor/terminal
namespace print
{
    /**
     * @brief Print buffer in HEX
     * 
     * @param buf char buffer of bytes
     * @param len Length of buffer to print
     */
    void print_hex( char* buf, int len )
    {
        for( size_t i = 0; i < len; ++i )
        {
            char _byte = buf[i] & 0xFF;

            #if defined (__AVR__)
                // Arduino streaming library
                #ifdef ARDUINO_STREAMING
                    Serial << _HEX(_byte) << " ";
                // Regular serial print
                #else
                    Serial.print( _byte, HEX );
                    Serial.print( " " );
                #endif
            #else
                std::cout << std::hex << " ";
            #endif
        }
    }
} // End of namespace print

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/