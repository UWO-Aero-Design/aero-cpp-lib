// File for testing communication protocol
#include <gtest/gtest.h>
#include <iostream>

#include "../src/Message.cpp"

class AeroMessageTest : public ::testing::Test
{

protected:

    // Test suite pre-test construction
    void SetUp ( void ) override
    {
        /* do nothing */
    }

    // Test suite post-test destruction
    void TearDown ( void ) override 
    {
        /* do nothing */
    }

    // Unit under test
    aero::Message msg_handler;

};

// What to test
    // 1. Check the checksum result ( Can use validate function )
    // 2. Check empty build creates an empty buffer and empty signature and correct link
    // 3. Check non-empty build sets the correct signature, correct buffer, and correct link
    // 4. Check parse handles properly
    // 5. Check validate functions
    // 6. Check all add functions? 

// Check to see appropriate behavior for when Message is built with adding anything
TEST_F( AeroMessageTest, EmptyMessage)
{
    using namespace ::testing;
    using namespace aero::def;

    /* Check proper building */
    RawMessage_t message = msg_handler.build( ID::Gnd, ID::G1 );

    ASSERT_EQ( message.start,     0x0A ) << " Unexpected value for start byte ";
    ASSERT_EQ( message.end,       0x0F ) << " Unexpected value for end byte ";
    ASSERT_EQ( message.length,    0 )    << " Length of empty message is not zero ";
    ASSERT_EQ( message.signature, 0 )    << " Signature of empty message should be 0 ";
    ASSERT_EQ( message.link,      2 )    << " Link from Gnd->G1 should be 2 ";

    /* Check proper parsing */
    // Valid message
    bool valid = msg_handler.validate( (uint8_t *) &message );
    ASSERT_EQ( valid, true );

    // Valid parse result
    ParsedMessage_t parsed_message = msg_handler.parse( (uint8_t *) &message  );

    for( int i = 0; i < 12; ++i )
        ASSERT_EQ( parsed_message.segments[ i ] == NULL, true ) << "All buffer elements should be NULL for empty message";

    ASSERT_EQ( parsed_message.m_from, ID::Gnd );
    ASSERT_EQ( parsed_message.m_to, ID::G1 );
}

TEST_F( AeroMessageTest, HalfMessage )
{
    using namespace ::testing;
    using namespace aero::def;

    // Structs to add
    IMU_t imu_data; 
    imu_data.ax = 5; 
    imu_data.ay = 10; 
    imu_data.az = 15;

    Enviro_t env_data; 
    env_data.humidity = 10; 
    env_data.pressure = 20;
    env_data.temperature = 25;
    
    Battery_t bat_data;
    bat_data.current = 12;
    bat_data.voltage = 25;

    Commands_t cmd_data;
    cmd_data.drop = 99;
    cmd_data.pitch = 1;
    cmd_data.servos = 8;


    /* Check proper building */
    msg_handler.add_imu( imu_data ).add_enviro( env_data ).add_battery( bat_data )
               .add_cmds( cmd_data );

    RawMessage_t message = msg_handler.build( ID::Gnd, ID::G1 );

    int length = sizeof( struct IMU_t ) +  sizeof( struct Enviro_t ) 
                 + sizeof( struct Battery_t ) + sizeof( struct Commands_t );

    ASSERT_EQ( message.start,     0x0A ) << " Unexpected value for start byte ";
    ASSERT_EQ( message.end,       0x0F ) << " Unexpected value for end byte ";
    ASSERT_EQ( message.length,    length )    << " Length of empty message is not zero ";
    ASSERT_EQ( message.signature, ((1 << 1) | (1 << 3) | (1 << 4 ) | (1 << 9)) )    << " Signature of empty message should be 0 ";
    ASSERT_EQ( message.link,      2 )    << " Link from Gnd->G1 should be 2 ";

    /* Check proper parsing */
    // Valid message
    bool valid = msg_handler.validate( (uint8_t *) &message );
    ASSERT_EQ( valid, true );

    // Valid parse result
    ParsedMessage_t parsed_message = msg_handler.parse( (uint8_t *) &message  );

    // Valid data
    for( int i = 0; i < 12; ++i )
    {
        if( i != 1 && i != 3 && i != 4 && i != 9)
            ASSERT_EQ( parsed_message.segments[ i ] == NULL, true ) << std::to_string(i) + " All buffer elements that wererent added should be NULL ";
    }

    IMU_t *imu = ( IMU_t* ) parsed_message.segments[ 1 ]; 
    Enviro_t *enviro = ( Enviro_t* ) parsed_message.segments[ 3 ]; 
    Battery_t *batt = ( Battery_t* ) parsed_message.segments[ 4 ]; 
    Commands_t *cmds = ( Commands_t* ) parsed_message.segments[ 9 ]; 

    ASSERT_EQ( imu_data.ax, imu->ax );
    ASSERT_EQ( imu_data.ay, imu->ay );
    ASSERT_EQ( imu_data.az, imu->az );

    ASSERT_EQ( env_data.temperature, enviro->temperature );
    ASSERT_EQ( env_data.humidity, enviro->humidity );
    ASSERT_EQ( env_data.pressure, enviro->pressure );

    ASSERT_EQ( bat_data.current, batt->current );
    ASSERT_EQ( bat_data.voltage, batt->voltage );

    ASSERT_EQ( cmd_data.drop, cmds->drop );
    ASSERT_EQ( cmd_data.servos, cmds->servos );
    ASSERT_EQ( cmd_data.pitch, cmds->pitch );
    
    ASSERT_EQ( parsed_message.m_from, ID::Gnd );
    ASSERT_EQ( parsed_message.m_to, ID::G1 );

    // If i build again, the same contents should be there because we didnt clear the buffer
    // Next time around though, it should fail
    message = msg_handler.build( ID::Gnd, ID::G1, true );
    parsed_message = msg_handler.parse( (uint8_t *) &message  );

        // Valid data
    for( int i = 0; i < 12; ++i )
    {
        if( i != 1 && i != 3 && i != 4 && i != 9)
            ASSERT_EQ( parsed_message.segments[ i ] == NULL, true ) << std::to_string(i) + " All buffer elements that wererent added should be NULL ";
        else
            ASSERT_EQ( parsed_message.segments[ i ] == NULL, false );
    }

    message = msg_handler.build( ID::Gnd, ID::G1, true );
    parsed_message = msg_handler.parse( (uint8_t *) &message  );

    for( int i = 0; i < 12; ++i )
        ASSERT_EQ( parsed_message.segments[ i ] == NULL, true ) << "All buffer elements should be NULL for empty message";
}

