#if defined(ARDUINO) || defined(CORE_TEENSY)
    // This if defined is added so Arduino does not compile this code
    // when this library is added as a submodule
#else

// #include "Message.hpp"
#include "../include/Message.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>

// For getopt
#include "unistd.h"

int main(int argc, char **argv)
{
    using namespace aero;

    Message messageHandler;

    IMU imu = {10, -12212, 131};
    Status status = { 1234, 992 };

    messageHandler.add_imu( imu );
    messageHandler.add_status( status );
    
    RawMessage message = messageHandler.build( ID::G1, ID::G2 );
    ParsedMessage parsed = messageHandler.parse ( (uint8_t *) &message );

    IMU *imuu = ( reinterpret_cast<IMU*>( parsed.segments[ static_cast<int>(Signature::IMU) ] ) );
    Status *statuss = ( reinterpret_cast<Status*>( parsed.segments[ static_cast<int>(Signature::Status) ] ) );
    std::cout << "Parsed: " << imuu->ay << " " << statuss->rssi;

    return 0;
}

#endif












    // // // Message msg;

    // // // msg.signature = 15;

    // // // int val = 1;
    // // // val <<= 11;

    // // // msg.signature |= val;
    

    // // // MessageHandle msgHandle ( msg );




    // // MessageBuilder builder;
    // Test0 test;
    // test.num = 6;
    // test.letter = 'c';

    // // builder.addSignature(DataSignatures::Test0, (char *) &test );
    // // builder.addSignature(DataSignatures::Test2, NULL);
    // // builder.addSignature(DataSignatures::Test5, NULL);

    // // Message msg = builder.build();

    // // test.num = 7;
    // // builder.addSignature(DataSignatures::Test0, (char *) &test );
    // // msg = builder.build();

    // // msg = builder.build();

    // // return 0;

    // uint8_t data[1024];

    // int sizes[16];
    // uint8_t* buffers[16];


    // for(int i = 0; i < 15; ++i)
    //     buffers[i] = NULL;

    // if(buffers[0] == NULL)
    // {
    //     std::cout << "Hello";
    // }
    // else
    // {

    // }


    // // AddToBuffer(Signature, data, Sizeof( struct))
    // /*
    //     int signature = static_cast<ENUM>(Signature);

    //     buffer[signature] = data;
    //     size[signature] = sizeof( struct )

    // */
    
    
    // sizes[1] = sizeof(Test1);

    // std::cout << sizes[1];

    // buffers[1] = (uint8_t *) &test;

    // if(buffers[1] == NULL)
    // {
    //     std::cout << "Hello";
    // }
    // else
    // {
    //     std::cout << (( Test0 * ) buffers[1])->num;
    // }

    // std::cout << "\nSize" << (sizes[1]) ;

    // int len = 0;
    // for(int i = 0; i < 15; ++i)
    // {   
    //     if ( buffers[i] != NULL )
    //     {
    //         memcpy(data, buffers[i], sizes[i]);
    //     }
    // }

    // uint8_t rrr[5];
    // memcpy(rrr, data, 5);

    // std::cout << "Parse result" << (( Test0 * ) rrr)->num;
        

    // // int x = *buffers[0];

    // // std::cout << x;