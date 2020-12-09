#include "stdafx.h"
// Define liset
std::vector<DirectoryClass> FileList;

// Define extensions
const char* extensions[] {
    ".h", ".hpp",
    ".cc", ".c", ".C", ".cpp", ".cxx", ".cp", ".c++",
    ".vcxproj", ".sln" };

// Define voids();

bool GetDocuments(std::string Path);

//Main
int main(int argc, char* argv[])
{
    SetConsoleTitleA(_xor_("Randomizer").c_str());

    if (GetDocuments(_xor_("C:\\Users\\ykaan\\Documents\\GitHub\\cpp-c-randomizer\\Example-Project\\").c_str())) {
        //File List For.
        for (const auto& File : FileList)
        {
            std::cout << File.FullName << std::endl;
        } // exit for.
    }
    else {
        // Print error and wait for user action.
        std::cerr << "File has no members..." << std::endl;
        system("pause");
    }
}


bool GetDocuments(std::string path) {
    // Get files in path.
    for (const auto& entry : fs::directory_iterator(path))
    {
        // Get String From Entry.
        std::string CurrentPath = entry.path().string();
        // Removing Directory.
        CurrentPath.replace(CurrentPath.find(path), path.length(), "");
        // Creating Class.
        DirectoryClass NiggaFile;
        NiggaFile.IsObsufucated = false;
        // For in extensions.
        for (const auto& Item : extensions)
        {
            std::string StringItem = Item;

            // If have extensions.
            if ((CurrentPath.find(Item) != std::string::npos)
                && !(CurrentPath.find(".user") != std::string::npos)
                && !(CurrentPath.find(".filters") != std::string::npos)) {
                // Save Full Name.
                NiggaFile.FullName = CurrentPath;
                // Save extensions.
                NiggaFile.FileExt = Item;
                // get temp string.
                std::string TempString = CurrentPath.c_str();
                // Remove extensions and save file name.
                NiggaFile.FileName = fs::path(CurrentPath).replace_extension().string();

                // Search Vector.
                if (std::find(FileList.begin(), FileList.end(), NiggaFile) != FileList.end()) { /*Found do nothing*/ }
                else {
                    // Insert in vector.
                    FileList.insert(FileList.begin(), NiggaFile);
                }
            }
        }
    } // exit for.
    // If size 0 return false
    // If size bigger 0 return true;
    return FileList.size() > 0 ? true : false;
}