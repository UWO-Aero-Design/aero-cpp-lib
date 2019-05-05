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

struct __attribute__((__packed__)) GPS
{
    int32_t lat;
    int32_t lon;
    uint16_t speed;
    uint8_t satellites;
    uint16_t altitude;
    uint32_t time;  // 4 BYTES. XX HR MIN SEC
    uint32_t date;  // 4 BYTES. XX YR MNTH DAY
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

// HIGH BYTE is MAX, LOW BYTE is MIN. 
struct __attribute__((__packed__)) Servos
{
    uint16_t servo0;
    uint16_t servo1;
    uint16_t servo2;
    uint16_t servo3;
    uint16_t servo4;
    uint16_t servo5;
    uint16_t servo6;
    uint16_t servo7;
    uint16_t servo8;
    uint16_t servo9;
    uint16_t servo10;
    uint16_t servo11;
    uint16_t servo12;
    uint16_t servo13;
    uint16_t servo14;
    uint16_t servo15;
};

// Pretty much all we need to send back is AirData in terms of telemetry
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
