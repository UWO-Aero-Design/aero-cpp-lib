#ifndef PINS_HPP
#define PINS_HPP

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

// Typedef for Pin type
using Pin = const unsigned int;

/**
 * @brief Struct defining I2C pins
 */
struct I2C  { Pin SDA; Pin SCL; };

/**
 * @brief Struct defining SPI pins
 */
struct SPI  { Pin MOSI; Pin MISO; Pin SCK; Pin CS; };

/**
 * @brief Struct defining UART pins
 */
struct UART { Pin TX; Pin RX; };

/*!
 *  \addtogroup teensy35
 *  @{
 */

//! Teensy3.5 pin definitions interfaces
namespace teensy35
{

/*
             -----------
        GND -|   USB   |- VIN  ( 3.6 to 6 Volts )
         D0 -|         |- AGND
         D1 -|         |- 3.3V ( 250mA Max )
         D2 -|         |- D23
         D3 -|         |- D22
         D4 -|         |- D21
         D5 -|         |- D20
         D6 -|         |- D19
         D7 -|         |- D18
         D8 -|         |- D17
         D9 -|         |- D16
        D10 -|         |- D15
        D11 -|         |- D14
        D12 -|  FRONT  |- D13
       3.3V -|         |- GND
        D24 -|         |- DAC1
        D25 -|         |- DAC0
        D26 -|         |- D39
        D27 -|         |- D38
        D28 -|         |- D37
        D29 -|         |- D36
        D30 -|         |- D35
        D31 -|         |- D34
        D32 -|  SDCRD  |- D33
             -----------
*/

    // Currently only have the front pins defined because bottom pins aren't breakout friendly

    // Digital Pins
    Pin P0 = 0;
    Pin P1 = 1;
    Pin P2_PWM  = 2;
    Pin P3_PWM  = 3;
    Pin P4_PWM  = 4;
    Pin P5_PWM  = 5;
    Pin P6_PWM  = 6;
    Pin P7_PWM  = 7;
    Pin P8_PWM  = 8;
    Pin P9_PWM  = 9;
    Pin P10_PWM = 10;
    Pin P11 = 11;
    Pin P12 = 12;
    Pin P13 = 13;
    Pin P14_PWM = 14;
    Pin P15 = 15;
    Pin P16 = 16;
    Pin P17 = 17;
    Pin P18 = 18;
    Pin P19 = 19;
    Pin P20_PWM = 20;
    Pin P21_PWM = 21;
    Pin P22_PWM = 22;
    Pin P23_PWM = 23;
    Pin P24 = 24;
    Pin P25 = 25;
    Pin P26 = 26;
    Pin P27 = 27;
    Pin P28 = 28;
    Pin P29_PWM = 29;
    Pin P30_PWM = 30;
    Pin P31 = 31;
    Pin P32 = 32;
    Pin P33 = 33;
    Pin P34 = 34;
    Pin P35_PWM = 35;
    Pin P36_PWM = 36;
    Pin P37_PWM = 37;
    Pin P38_PWM = 38;
    Pin P39 = 39;

    // Analog Pins
    Pin A0_PWM = P14_PWM;
    Pin A1 = P15;
    Pin A2 = P16;
    Pin A3 = P17;
    Pin A4 = P18;
    Pin A5 = P19;
    Pin A6_PWM = P20_PWM;
    Pin A7_PWM = P21_PWM;
    Pin A8_PWM = P22_PWM;
    Pin A9_PWM = P23_PWM;
    Pin A12 = P31;
    Pin A13 = P32;
    Pin A14 = P33;
    Pin A15 = P34;
    Pin A16_PWM = P35_PWM;
    Pin A17_PWM = P36_PWM;
    Pin A18_PWM = P37_PWM;
    Pin A19_PWM = P38_PWM;
    Pin A20 = P39;

    // I2C Definitions
    const I2C I2C0 { P18, P19 };
    const I2C I2C1 { P38_PWM, P17 };
    const I2C I2C2 { P4_PWM,  P3_PWM };

    //SPI Definitions
    const SPI SPI0 { P11, P12, P13, P10_PWM };
    const SPI SPI1 { P0,  P1,  P32, P31 };

    // UART Definitions
    const UART UART1 { P1, P0 };
    const UART UART2 { P10_PWM, P9_PWM };
    const UART UART3 { P8_PWM, P7_PWM };
    const UART UART4 { P32, P31 };
    const UART UART5 { P33, P34 };

    // Onboard LED
    Pin LED = P13;

} // End of namespace teensy3.5

/*! @} End of Doxygen Groups*/

} // End of namespace aero

/*! @} End of Doxygen Groups*/

#endif // PINS_HPP