#pragma once

class DirectoryClass
{
public:
	bool IsObsufucated = false;
	string FullName = "NULL";
	string FileName = "NULL";
	string FileExt = "NULL";
	string FullPath = "NULL";
	bool operator==(DirectoryClass d) {
		if (d.FullName == this->FullName) return true;
		else return false;
	}
};
