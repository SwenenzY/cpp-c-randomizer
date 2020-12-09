#include "Helpers.h"

std::string Helpers::CreateGuid() {
    GUID guid;
    CoCreateGuid(&guid);

    std::ostringstream os;
    os << std::hex << std::setw(8) << std::setfill('0') << guid.Data1;
    os << '-';
    os << std::hex << std::setw(4) << std::setfill('0') << guid.Data2;
    os << '-';
    os << std::hex << std::setw(4) << std::setfill('0') << guid.Data3;
    os << '-';
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[0]);
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[1]);
    os << '-';
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[2]);
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[3]);
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[4]);
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[5]);
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[6]);
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(guid.Data4[7]);

    std::string s(os.str());

    return s;
}
