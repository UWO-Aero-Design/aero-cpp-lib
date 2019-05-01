#pragma once

#include <vector>
#include <cstdint>
#include <cmath>
#include <iostream>

#include "Data.hpp"

struct Message
{
    uint8_t start;       // Start byte for serial transfer
    uint16_t link;       // Link describes the connection the message is trying to bridge. Sender --> Recipient
    uint16_t signature; // Bits for determining what data is being sent

    uint8_t buffer[256];    // Actual data. Max size

    uint16_t crc;        // Try fast crc
    uint8_t end;         // End byte for serial transfer
};

// If we can get vector in teensy, we could scan through the signatures and then push_back every selected signature (deque)
// Then pop from front and memcpy 

// Parse and builds. Cant do both with the same object?
// Have struct of structs that MessageHandle copies into too


class MessageBuilder
{
public:
    MessageBuilder()
    {
        // Default struct
        msg = {};
        // test = {};
        test = {};
    }

    MessageBuilder& AddToBuffer(DataSignatures signature, const char* data)
    {
        // Sets the signature flag
        uint16_t temp_signature = 1 << static_cast<unsigned int>( signature );
    
        // Do the whole switch statement thing here
        //SetData( temp_signature, data );

        buffers.at(signature) = (uint8_t *) data);
        msg.signature |= temp_signature;
        return *this;
    }

    Message build()
    {
        // Check our set signatures
        // If signature set, copy in approriate data buffer
        // Calculate checksum
        // Reset length for next build

        std::cout << "Signature: " << msg.signature << std::endl;

        packets.test0 = ( Test0 * ) test[0];

        // if(test[1] == NULL)
        // {
        //     std::cout << "seg";
        // }
        //std::cout << (( Test0 * ) test[1])->num;
        std::cout << packets.test0->num << " " << packets.test0->letter << std::endl;
        
        int signatures = msg.signature;
        for( int i = 0; i < 16; ++i )
        {
            if ( signatures & 1 )
            {
                //len += parse( msg.buffer, i );
                //std::cout << "Len: " << len << std::endl;
            }
            
            signatures >>= 1;
        }

        test[0] = nullptr;
        return msg;
    }
private:
    void SetData( int signature, const char* data )
    {   
        int bit = log2(signature);
        DataSignatures ss = static_cast< DataSignatures > ( bit );

        switch (  ss )
        {
            case DataSignatures::Test0:
            {
                std::cout << "Test" << " ";
                packets.test0 = ( Test0 * ) data;

                test.insert(test.begin() + 0, (uint8_t *) data) ;
            } break;
            case DataSignatures::Test11:
            {
                std::cout << "TestData" << " ";
                // return (int) sizeof(struct Test11);
            } break;
            default:
            {
                std::cout << "Undefined" << " ";
                // return 0;
            } break;
                
        } 
    } 

    Message msg;
    uint16_t len;
    PacketTypes packets;

    std::vector<uint8_t*> test;
};






// Steps on how to add a new data parsing case
// 1. Add the new data structure you want to parse into
// 2. Add the member variable that the results will be stored into message handler
// 3. Add unique data signanture into the enum that represents the bit location
// 4. Add the switch case to memcpy the buffer in


class MessageHandle
{
public:
    MessageHandle( Message msg )
    {
        
        int structs = msg.signature;
        int len = 0;

        for(int i = 0; i < 16; ++i)
        {
            int bit = ( structs & 1 );
            structs >>= 1;

            // Check if bit i is set
            if (bit)
            {
                len += parse( msg.buffer, i );
                std::cout << "Len: " << len << std::endl;
            }
        }
    }

private:
    int parse( uint8_t* buffer, int s )
    {
        DataSignatures ss = static_cast< DataSignatures > ( s );
        switch (  ss )
        {
            case DataSignatures::Test0:
            {
                std::cout << "Test" << " ";
                return (int) sizeof(struct Test0);
            } break;
            case DataSignatures::Test11:
            {
                std::cout << "TestData" << " ";
                return (int) sizeof(struct Test11);
            } break;
            default:
            {
                std::cout << "Undefined" << " ";
                return 0;
            } break;
                
        }
    }
};





// Receive message BUF

// Message_t data = (Message_t) BUF
// MessageHandle( data )
// MessageHandle.imu().roll












