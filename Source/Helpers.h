#include "stdafx.h"
#pragma once
namespace Helpers {
	std::string CreateGuid();
	void replaceAll(std::string& str, const std::string& from, const std::string& to);
	std::string random_string_only_char(std::string::size_type length);
	std::string random_int(std::string::size_type length);
	std::string random_hex(std::string::size_type length);
	std::string random_string(std::string::size_type length);
}

