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
    // 1. Check the checksum result
    // 2. Check empty build creates an empty buffer and empty signature and correct link
    // 3. Check non-empty build sets the correct signature, correct buffer, and correct link
    // 4. Check parse handles properly
    // 5. Check validate functions
    // 6. Check all add functions? 

// Check to see appropriate behavior for when Message is built with adding anything
TEST_F( AeroMessageTest, EmptyMessage)
{
    using namespace ::testing;

    /* Check proper building */
    RawMessage message = msg_handler.build( ID::Gnd, ID::G1 );

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
    ParsedMessage parsed_message = msg_handler.parse( (uint8_t *) &message  );

    for( int i = 0; i < 12; ++i )
        ASSERT_EQ( parsed_message.segments[ i ] == NULL, true ) << "All buffer elements should be NULL for empty message";

    ASSERT_EQ( parsed_message.m_from, ID::Gnd );
    ASSERT_EQ( parsed_message.m_to, ID::G1 );
}

