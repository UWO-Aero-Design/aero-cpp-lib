#include <iostream>
#include <fstream>
#include <Message.hpp>

int main(void)
{
    aero::Message messageHandler;
    
    std::ofstream arduino;
	arduino.open( "/dev/ttyACM0");
    IMU imu;
    imu.ax = 100;
    imu.gy = 55;
    messageHandler.add_imu(imu);
    RawMessage message = messageHandler.build( ID::G1, ID::G2 );
    char* buf = (char*) &message;
	//write to it
    for(int i = 0; i < sizeof(message); ++i)
    {
        arduino << *(buf+i);
    } 

	arduino.close();

	return 0;
}