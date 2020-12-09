#include "stdafx.h"


int main(int argc, char* argv[])
{
    SetConsoleTitleA("Randomizer []");

    std::string GUID = Helpers::CreateGuid();

    std::cout << GUID << std::endl;
    getchar();


}
