#pragma once

// File for converting msg data into raw data and raw into msg

#include "Data.hpp"

namespace aero
{

namespace msg
{

namespace
{
    // Scaling value for pitot tube differential pressure
    const float DIFF_PRESSURE_SCALAR = 1.0f;
}

def::RawPitot_t convert( def::MsgPitot_t input )
{
    def::RawPitot_t data;
    data.differential_pressure = ( 1.0f / DIFF_PRESSURE_SCALAR ) * input.differential_pressure;
    return data;
}

def::MsgPitot_t convert( def::RawPitot_t input )
{
    def::MsgPitot_t data;
    data.differential_pressure = ( DIFF_PRESSURE_SCALAR ) * input.differential_pressure;
    return data;
}

}

}

