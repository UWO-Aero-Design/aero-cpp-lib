// Units under test
#if defined(ARDUINO) || defined(CORE_TEENSY)
    // This if defined is added so Arduino does not compile this code
    // when this library is added as a submodule
#else

#include "test_Message.cpp"
#include "test_Utility.cpp"

// Main that runs all unit tests
int main( int argc, char **argv )
{
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

#endif
