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


namespace aero
{

// Binary-level helper functions
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
        source.to_swap = to_swap

        for( size_t k = 0; k < sizeof( T ); ++k)
            desk.u8[k] = source.u8[ sizeof( T ) - k - 1];

        return dest.to_swap;
    }

    // Set bit index in value bit
    int set( int bit, unsigned int index )
    {
        return ( bit | ( 1 << index ) );
    }

    // Read bit at index in value bit
    uint8_t read( int bit, unsigned int index )
    {
        return ( ( bit >> index ) & 0x01 );
    }

    // Clear bit at index in value bit
    // Returns the value with the bit cleared
    int clear( int bit, unsigned int index )
    {
        return ( bit & ~( 1 << index ) );
    }

    // Toggle bit at index
    int toggle( int bit, unsigned int index )
    {
        return ( bit ^ ( 0x01 << index ) );
    }
} 

// Data conversion helper functions
namespace convert
{
    // Credit for most of the conversion functions comes from github.com//bolderflight/AirData

    // Anonymous namespace to keep these constants hidden
    // May need to move these to a place where they are more accessible cause could be needed in other modules
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

    enum class Unit { n, u, m, base, k, M, G };
    float metric( float value, Unit src, Unit dest )
    {
        int exponent = static_cast< int >( dest ) - static_cast< int >( src );
        return value * powf( 1000.0f, exponent );
    }

    enum class Temperature { K, C, F };
    // Very lazy solution to this problem
    // Problaby best to convert all inputs to SI then convert to destination
    float temperature( float t, Temperature src, Temperature dest )
    {
        if ( src == dest )
            return t;

        switch (src)
        {
            case Temperature::K:
            {
                if( dest == Temperature::C )
                    return ( t - 273.15 );
                if( dest == Temperature::F )
                    return ( t - 459.67 );
            } break;
            case Temperature::C:
            {
                if( dest == Temperature::K )
                    return ( t + 273.15 );
                if( dest == Temperature::F )
                    return ( ( t * ( 9.0f/5.0f ) ) + 32.0f );
            } break;
            case Temperature::F:
            {
                if( dest == Temperature::K )
                    return ( t + 459.67 );
                if( dest == Temperature::C )
                    return ( ( t - 32.0f ) * ( 5.0f/9.0f ) );
            } break;        
        }
    }

    // Calcultes indicated air speed. diff_pressure in Pa
    float ind_as( float diff_pressure )
    {
        return (sl_sound_speed * sqrtf( 5.0f * ( powf( ( ( sl_pressure / sl_pressure ) + 1.0f ), ( 2.0f/7.0f ) ) - 1.0f ) ) );
    }

    // Calculates equivalent air speed given. pressure in Pa
    float equiv_as( float qc, float p ) 
    {
        return sl_sound_speed * sqrtf(5.0f*p/sl_pressure*(powf((qc/p + 1.0f),(2.0f/7.0f)) - 1.0f));
    }

    // Calculate true air speed with IAS or EAS and temperature in Kelvin
    float true_as( float AS, float T ) 
    {
        return AS * sqrtf((T+273.15f)/sl_temperature);
    }

    // Calculate pressure altitude. pressure in Pa
    // Altitude is altitude based on standard atmosphere
    float pressure_altitude(float p) 
    {
        return (sl_temperature/lapse)*(1.0f - powf((p/sl_pressure),((lapse*gas_const)/(air_mass*gravity))));
    }

    // Calculates altitude Above Ground Level (AGL) given static pressure and a bias
    float above_gnd_altitude(float p, float c) 
    {
        return pressure_altitude(p) - c;
    }

    /* computes altitude above Mean Sea Level (MSL) given AGL and starting altitude */
    float mean_sl_altitude(float H, float h) 
    {
        return H + h;
    }

    /* computes density altitude given static pressure and temperature */
    float density_altitude(float p, float T) 
    {
        return (sl_temperature/lapse)*(1.0f - powf(((p/sl_pressure)*(sl_temperature/(T+273.15f))),((lapse*gas_const)/(air_mass*gravity - lapse*gas_const))));
    }

    /* approximates temperature as a fuction of altitude */
    float approx_temp(float T, float h) 
    {
        return T - lapse*h;
    }

    /* computes air density given temperature and pressure */
    float approx_density(float p, float T) 
    {
        return (air_mass*p)/(gas_const*(T+273.15f));
    }
} // End of namespace convert

// Printing helper functions to output data to serial monitor/terminal
namespace print
{
    void print_hex( char* buf, int len )
    {
        for( size_t i = 0; i < len; ++i )
        {
            char _byte = buf[i] & 0xFF;

            #if defined (__AVR__)
                #ifdef ARDUINO_STREAMING
                    Serial << _HEX(_byte) << " ";
                #else
                    Serial.print( _byte, HEX );
                    Serial.print( " " );
                #endif
            #else
                std::cout << std::hex << " ";
            #endif
        }
    }
}

} // End of namespace aero