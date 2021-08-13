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

    std::string s;
    s += "{";
    s += os.str();
    s += "}";

    return s;
}

void Helpers::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::string Helpers::random_string(std::string::size_type length)
{
    string possible_characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    string ret = "";
    for (int i = 0; i < length; i++) {
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    return ret;
}

std::string Helpers::random_string_only_char(std::string::size_type length)
{
    string possible_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    string ret = "";
    for (int i = 0; i < length; i++) {
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    return ret;
}

std::string Helpers::random_int(std::string::size_type length)
{
    string possible_characters = "0123456789";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    string ret = "";
    for (int i = 0; i < length; i++) {
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    return ret;
}


std::string Helpers::random_hex(std::string::size_type length)
{
    string possible_characters = "0123456789abcdefABCDEF";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    string ret = "";
    for (int i = 0; i < length; i++) {
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    return ret;
}