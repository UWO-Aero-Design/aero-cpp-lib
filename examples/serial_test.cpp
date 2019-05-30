#if defined(ARDUINO) || defined(CORE_TEENSY)
    // This if defined is added so Arduino does not compile this code
    // when this library is added as a submodule
#else

#include <iostream>
#include <fstream>
#include <Message.hpp>

int main(void)
{
    using namespace aero;
    using namespace aero::def;
    aero::Message messageHandler;
    
    std::ofstream arduino;
    arduino.open( "/dev/ttyACM0");
    IMU_t imu;
    imu.ax = 100;
    imu.gy = 55;
    messageHandler.add_imu(imu);
    RawMessage_t message = messageHandler.build( ID::G1, ID::G2 );
    char* buf = (char*) &message;
    //write to it
    for(int i = 0; i < sizeof(message); ++i)
    {
        arduino << *(buf+i);
    } 

    arduino.close();

    return 0;
}

#endif
