#pragma once
// Common Includes
#include <windows.h>
#include <iomanip>
#include <cstdint>
#include <random>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

// Stream
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>

// STD
#include <stdio.h>
#include <string>
#include <filesystem>

// Namespace
using namespace std;
namespace fs = std::filesystem;

// User Define
#include "Helpers.h"
#include "ClassList.h"

// I am using CLI systems (I don't usually use it, but I used it for simplicity.)
#using <System.xml.dll>
#include <msclr\marshal_cppstd.h> // system::string -> std::string
using namespace msclr::interop;
using namespace System::Xml;