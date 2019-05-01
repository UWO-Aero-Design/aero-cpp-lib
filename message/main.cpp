// #include "Message.hpp"
#include "MessageFormatter.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>



int main(int argc, char const *argv[])
{
    MessageHandler messageHandler;

    IMU imu;
    imu.ax = 10;
    imu.ay = 100;
    imu.az = 1000;
    
//     struct __attribute__((__packed__)) Status
// {
//     int16_t rssi;        // Signal strength
//     uint32_t state;      // State bit fields
// };


    messageHandler.set_imu( imu );
    RawMessage message;


    // for(int i = 0; i < 256; ++i)
    // {
    //     std::cout << std::hex << (int) message.buffer[i] << " ";
    // }
    // std::cout << std::endl;


    message = messageHandler.build( ID::G1, ID::G2 );
    // std::cout << (message.signature);

    // for(int i = 0; i < 256; ++i)
    // {
    //     std::cout << std::hex << (int) message.buffer[i] << " ";
    // }

    // DEBUG THIS. BUILD SEGFAULTS
    ParsedMessage parsed = messageHandler.parse ( (uint8_t *) &message );


    std::cout << "Parsed: " << (( IMU * ) parsed.segments[ static_cast<int>(Signature::IMU) ])->ay;
    return 0;
}













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