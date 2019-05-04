#pragma once

// Aero Communication Protocol V1.0 -- 2019 / 2020

#if defined(ARDUINO)
    #include "Arduino.h"
#else
    #include <cstdint>
#endif

// Groundstation --> Aircraft 
    // Message 
        // Config, Status, Actuators, Commands
// Aircraft --> Groundstation
    // Message
        // PitotTube, IMU, GPS, EnviroSensor, Battery, Status


enum class Signature{   Pitot, IMU, GPS, Enviro, Batt, Config, 
                        Status, Actuators, AData, Cmds, Drop };

enum class ID{ Gnd, Plane, G1, G2 };

// Overview Message
struct __attribute__((__packed__)) RawMessage
{
    

    uint8_t start;       // Start byte for serial transfer
    uint16_t link;       // Link describes the connection the message is trying to bridge. Sender --> Recipient
    uint16_t signature;  // Bits for determining what data is being sent

    uint8_t buffer[256]; // Actual data. Max size
    uint8_t length;

    uint16_t crc;        // Try fast crc
    uint8_t end;         // End byte for serial transfer
};

struct __attribute__((__packed__)) ParsedMessage
{
    ParsedMessage()
    {
        for(int i = 0; i < 12; ++i)
            segments[i] = NULL;
    } 

    ~ParsedMessage()
    {
        for(int i = 0; i < 12; ++i)
            delete segments[i]; 
    }

    ID m_from, m_to;
    uint8_t* segments[12];
};

struct __attribute__((__packed__)) Pitot
{
    int16_t differential_pressure;
};

struct __attribute__((__packed__)) IMU
{
    int16_t ax;
    int16_t ay;
    int16_t az;
};

struct __attribute__((__packed__)) GPS
{
    int32_t coordinates[2];
};

struct __attribute__((__packed__)) Enviro
{
    uint16_t pressure;
    uint16_t humidity;
    uint16_t temperature; 
};

struct __attribute__((__packed__)) Battery
{
    uint16_t voltage;
    uint16_t current;
};

struct __attribute__((__packed__)) Config
{

};

struct __attribute__((__packed__)) Status
{
    int16_t rssi;        // Signal strength
    uint32_t state;      // State bit fields
};

struct __attribute__((__packed__)) Actuators
{
    int16_t servo_min[16];
    int16_t servo_max[16];
};

struct __attribute__((__packed__)) AirData
{
    float ias;
    float eas;
    float tas;
    float agl;
    float pressure_alt;
    float msl;
    float density_alt;
    float approx_temp;
    float density;
};

struct __attribute__((__packed__)) Commands
{
    uint8_t drop;
    uint16_t servos;
    uint8_t pitch;
};

struct __attribute__((__packed__)) DropAlgo
{
    int16_t heading;
    uint16_t distance;
};
