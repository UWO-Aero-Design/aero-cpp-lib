#pragma once

/***********************************************************
 
   Bit field representation of data signatures
  
   Defined such that MSB = 15, LSB = 0
  
   |  15  |  14  |  13  |  12  |  11  |  10  |  9   |  8   |
   | FREE | FREE | FREE | FREE | DATA | FREE | FREE | FREE |
  
  
   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |   
   | TEST | FREE | FREE | FREE | FREE | FREE | FREE | TEST |
 
***********************************************************/



enum class DataSignatures {   
                              Test0 = 0, Test1, Test2, Test3, Test4, 
                              Test5, Test6, Test7, Test8, Test9, Test10,
                              Test11, Test12, Test13, Test14, Test15 
                           };

struct __attribute__((__packed__)) Test0
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test1
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test2
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test3
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test4
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test5
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test6
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test7
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test8
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test9
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test10
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test11
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test12
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test13
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test14
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) Test15
{
    int num;
    char letter;
};

struct __attribute__((__packed__)) PacketTypes
{
    Test0* test0;
    Test1* test1;
    Test2* test2;
    Test3* test3;
    Test4* test4;
    Test5* test5;
    Test6* test6;
    Test7* test7;
    Test8* test8;
    Test9* test9;
    Test10* test10;
    Test11 test11;
    Test12* test12;
    Test13* test13;
    Test14* test14;
    Test15* test15;
};