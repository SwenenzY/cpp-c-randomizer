#include "stdafx.h"

int main(int argc, char* argv[])
{
    SetConsoleTitleA(_xor_("Randomizer []").c_str());

    //std::string GUID = Helpers::CreateGuid();

    string NiggerPath = _xor_("C:\\Users\\ykaan\\Documents\\GitHub\\cpp-c-randomizer\\Example-Project\\").c_str();
    for (const auto& entry : fs::directory_iterator(NiggerPath))
    {
        std::string CurrentPath = entry.path().string();
        CurrentPath.replace(CurrentPath.find(NiggerPath), NiggerPath.length(), "");
        std::cout << CurrentPath << std::endl;
    }


}
