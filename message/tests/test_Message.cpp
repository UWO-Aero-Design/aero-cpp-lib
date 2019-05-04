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
    aero::Message msgHandler;

};

// What to test
    // 1. Check the checksum result
    // 2. Check empty build creates an empty buffer and empty signature and correct link
    // 3. Check non-empty build sets the correct signature, correct buffer, and correct link
    // 4. Check parse handles properly
    // 5. Check validate function
    // 6. Check all add functions? 
