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

class FileClass {
public:
	std::string FilePath = "NULL";
	std::string OrginalName = "NULL";
	std::string ObfuscateName = "NULL";
	bool operator==(FileClass d) {
		if (d.FilePath == this->FilePath) return true;
		else return false;
	}
};