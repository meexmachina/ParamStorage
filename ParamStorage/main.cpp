// test_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "param.h"
#include "paramstorage.h"

using namespace std;

typedef ParamStorageFlash<5, 0x400> Storage1;
typedef ParamStorageEeprom<3, 0x100> Storage2;

Param<float, Storage1> parameter1(100.5);
Param<int8_t, Storage1> parameter2('f');
Param<uint16_t, Storage1> parameter3(456);
Param<int8_t, Storage2> parameter4('g');
Param<uint16_t, Storage2> parameter5(56);


int main()
{
	parameter1 = 40.234;
	Storage1::print();
	Storage2::print();
	getchar();
    return 0;
}

