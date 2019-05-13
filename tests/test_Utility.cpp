// File for testing utility functions
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include "../include/Utility.hpp"

// Test swap endian function in aero library
TEST( UtilityTest, BitSwapEndian )
{
    using namespace aero;

    // Check unsigned byte representations
    uint8_t ui_byte = 0xAF;
    uint16_t ui_word = 0x1234, ui_word_swapped = 0x3412;
    uint32_t ui_long = 0x12345678, ui_long_swapped = 0x78563412;

    ASSERT_EQ( bit::swap_endian<uint8_t>( ui_byte ), ui_byte );
    ASSERT_EQ( bit::swap_endian<uint16_t>( ui_word ), ui_word_swapped );
    ASSERT_EQ( bit::swap_endian<uint32_t>( ui_long ), ui_long_swapped );

    // Check signed byte representations
    int8_t si_byte = 0xAF;
    int16_t si_word = 0x1234, si_word_swapped = 0x3412;
    int32_t si_long = 0x12345678, si_long_swapped = 0x78563412;

    ASSERT_EQ( bit::swap_endian<int8_t>( si_byte ), si_byte );
    ASSERT_EQ( bit::swap_endian<int16_t>( si_word ), si_word_swapped );
    ASSERT_EQ( bit::swap_endian<int32_t>( si_long ), si_long_swapped );
    
}


// Test bit set function in aero library
TEST( UtilityTest, BitSet )
{
    using namespace aero;

    // Check setting all bits of a 0x00000000 uint32_t value
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::set( (uint32_t)0, i ), (int)pow(2, i));

    // Check setting all bits of a 0xFFFFFFFF uint32_t value
    // Value should not change cause all bits set are
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::set( (uint32_t)0xFFFFFFFF, i ), 0xFFFFFFFF);
}

// Test bit read function in aero library
TEST( UtilityTest, BitRead )
{
    using namespace aero;

    // Check reading all bits of a 0x00000000 uint32_t value
    // All values should return 0
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::read( (uint32_t)0x00000000, i ), 0);

    // Check reading all bits of a 0xFFFFFFFF uint32_t value
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::read( (uint32_t)0xFFFFFFFF, i ), 1);
}

// Test bit clear function in aero library
TEST( UtilityTest, BitClear )
{
    using namespace aero;

    // Check clearing all bits of a 0x00000000 uint32_t value
    // All values should return 0
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::clear( (uint32_t)0x00000000, i ), 0);

    // Check clearing all bits of a 0xFFFFFFFF uint32_t value
    // All values should return 0xFFFFFFFF - 2^index
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::clear( (uint32_t)0xFFFFFFFF, i ), (uint32_t)( 0xFFFFFFFF - pow(2,i) ) );
}

// Test bit toggle function in aero library
TEST( UtilityTest, BitToggle )
{
    using namespace aero;

    // Check toggling all bits of a 0x00000000 uint32_t value
    // All values should return 2^index
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::toggle( (uint32_t)0x00000000, i ), pow(2,i) );

    // Check toggling all bits of a 0xFFFFFFFF uint32_t value
    // All values should return 0xFFFFFFFF - 2^index
    for( size_t i = 0; i < 31; ++i )
        ASSERT_EQ( bit::toggle( (uint32_t)0xFFFFFFFF, i ), (uint32_t)( 0xFFFFFFFF - pow(2,i) ) );
}

// Test function to convert metric units in aero library
TEST( UtilityTest, ConvertMetric )
{
    using namespace aero::convert;

    float value = 1.0f;

    // Convert from base to kilo which would result in divide by 1000f
    ASSERT_FLOAT_EQ( metric( value, Unit::base, Unit::k ), value / 1000.0f );
    // Convert from base to milli which would result in mulitply by 1000f
    ASSERT_FLOAT_EQ( metric( value, Unit::base, Unit::m ), value * 1000.0f );
    // Convert from base to kilo which would result in divide by 1000000f
    ASSERT_FLOAT_EQ( metric( value, Unit::m, Unit::k ), value / 1000.0f / 1000.0f );
    // Convert from base to milli which would result in mulitply by 1000000f
    ASSERT_FLOAT_EQ( metric( value, Unit::k, Unit::m ), value * 1000.0f * 1000.0f );
}

// Use EXCEL sheet to generate test points
// Negative number, 0, positive number
TEST( UtilityTest, ConvertIndAs )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertEqAs )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertTrAs )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertPresAlt )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertAboveGndAlt )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertAltMSL )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertDensityAlt )
{
    using namespace aero::convert;
}

TEST( UtilityTest, ConvertApproxTemp )
{
   using namespace aero::convert; 
}

TEST( UtilityTest, ConvertApproxDensity )
{
    using namespace aero::convert;
}