#include <Arduino.h>
#include <Message.hpp>

using namespace aero;

Message messageHandler;

void read_serial();

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );
  pinMode( LED_BUILTIN, OUTPUT );
}

void loop() {
  // put your main code here, to run repeatedly:

  bool started = false;
  bool ended = false;
  int index = 0;
  int buffersize = 1000;
  char _buffer[buffersize];
  bool bufferFilled = false;

  while(Serial.available())
  {
    // Read in a single input byte
    char in = Serial.read();
    Serial.println((uint8_t)in);

    // If the input byte is the start byte, and we havent already received the start byte, reset the buffer and store the first byte
    if(in == START_BYTE && started == false)
    {
      index = 0;
      _buffer[index] = (uint8_t) in;

      Serial.print("Index: ");
      Serial.print(index);
      Serial.print(" Start: ");
      Serial.println((uint8_t)_buffer[index]);

      started = true;
      ended = false;
    }
    // If the input byte is the end byte, end the bufer
    else if(in == END_BYTE)
    {
      _buffer[++index] = in;

      Serial.print("Index: ");
      Serial.print(index);
      Serial.print(" End: ");
      Serial.println((uint8_t)_buffer[index]);

      ended = true;
    }
    // If the byte is between start and end, increment the index and add it to the buffer
    else if(started == true)
    {
      if(index < (buffersize - 1))
      {
        _buffer[++index] = in;

        Serial.print("Index: ");
        Serial.print(index);
        Serial.print(" Else: ");
        Serial.println((uint8_t)_buffer[index]);
      }
    }

    // If we have hit both the start and end bytes, message is fully recevied
    if(started && ended){
      // Buffer is full
      bufferFilled = true;

      // Reset flags and index and fail counter
      started = false;
      ended = false;
      index = 0;

      Serial.println("Bluetooth message read");
    }
    else{
      // Number of fails should not exceed size of message. If it does, then we have a problem
    }
  }

  if( bufferFilled )
  {
    Serial.println("FILLED");
    ParsedMessage parsed = messageHandler.parse((uint8_t *)_buffer);
    IMU *imuu = ( reinterpret_cast<IMU*>( parsed.segments[ static_cast<int>(Signature::IMU) ] ) );
    Serial.print("Hello: ");
    Serial.print( imuu->ax );
    Serial.println( imuu->gy );
    delay(2000);
  }
  else
  {
     Serial.println("NOT FILLED");
     delay(500);
  }
  
}

void read_serial()
{
  
}