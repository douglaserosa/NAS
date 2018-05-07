#include <iostream>
#include <string>
#include <fstream>
#include "mobile.h"

int
main(int argc, char * argv[])
{
    Mobile phone;

    std::cout << "Battery: " << phone.getCapacity() << std::endl;

    return 0;
}