#include "stdafx.h"
// Define liset
std::vector<DirectoryClass> FileList;
std::vector<FileClass> ObfuscateList;

// Define extensions
const char* extensions[] {
    ".h", ".hpp",
    ".cc", ".c", ".C", ".cpp", ".cxx", ".cp", ".c++",
    ".vcxproj", ".sln" };

/// <summary>
/// File settings
/// </summary>
bool ObfuscateFiles = true;

/// <summary>
/// Vcxproj settings
/// </summary>
bool ObfuscateVcxproj = false;
bool RandomizeVcxprojGuid = true; // Randomize GUID for vcxproj
string UserDefinedVcxprojGUID = "{SwZ-GUID}"; // If randomize guid false define this // not prefered

/// <summary>
/// .sln settings
/// </summary>
bool ObfuscateSln = false;
bool RandomizeSlnGuid = true; // Randomize GUID for vcxproj
string UserDefinedSlnGUID = "{SwZ-GUID}"; // If randomize guid false define this // not prefered
string UserDefinedSlnGUID2 = "{SwZ-GUID}"; // If randomize guid false define this // not prefered

bool GetDocuments(std::string Path);
void Setup(std::string path, std::string element, std::string newelement);
void ParseSolutionFile(std::string path, std::string vcxprojfile, std::string newslnguid, std::string newslnguid2);
void ObfusucateFiles(std::string path);

std::string Obfuscatestart = "O_O";
std::string Obfuscateend = "o_o";

int main(int argc, char* argv[])
{
    SetConsoleTitleA("C/C++ Randomizer By SwenenzY :)");

    printf("[>] Initialiting...\n");

    string VcxprojGUID = RandomizeVcxprojGuid ? Helpers::CreateGuid() : UserDefinedVcxprojGUID;
    string slnGUID = ObfuscateSln ? Helpers::CreateGuid() : UserDefinedSlnGUID;
    string slnGUID2 = ObfuscateSln ? Helpers::CreateGuid() : UserDefinedSlnGUID2;
    printf("[+] Initialized\n");
    
    printf("\n[>] Settings;\n");
    std::cout << "[-] Obfuscate Vcxproj = " << ObfuscateVcxproj << std::endl;
    std::cout << "[-] Randomize Vcxproj Guid = " << RandomizeVcxprojGuid << std::endl;
    std::cout << "[-] User Defined Vcxproj GUID = " << UserDefinedVcxprojGUID << std::endl;
    printf("\n");
    std::cout << "[-] Obfuscate Sln = " << ObfuscateSln << std::endl;
    std::cout << "[-] Randomize Sln Guid = " << RandomizeSlnGuid << std::endl;
    std::cout << "[-] User Defined Sln GUID = " << UserDefinedSlnGUID << std::endl;
    std::cout << "[-] User Defined Sln GUID 2 = " << UserDefinedSlnGUID2 << std::endl;
    printf("\n");
    std::cout << "[-] Obfuscate Files = " << ObfuscateFiles << std::endl;
    printf("\n\n");
    Sleep(2500);
    //if (GetDocuments("C:\\Users\\Administrator\\Desktop\\swz-rust-simple\\SwZ-Internal\\Internal\\")) {
    //if (GetDocuments("C:\\Users\\Administrator\\Desktop\\swz-rust-premium\\Cheat\\Internal\\")) {
    if (GetDocuments("C:\\Users\\ykaan\\Documents\\GitHub\\cpp-c-randomizer\\Example-Project\\")) {
        //File List For.
        bool CanObsufucateSln = false;
        std::string restorevcxprojname;
        returnfor:
        for (const auto& File : FileList)
        {
            #pragma region Vcxproj
            if (File.FileExt == ".vcxproj") {
                restorevcxprojname = File.FullName;
                CanObsufucateSln = true;
            }
            else if (File.FileExt == ".vcxproj" && ObfuscateVcxproj) {
                
                try {
                    System::String^ PathString = gcnew System::String(File.FullPath.c_str()); // std::string to system::string

                    XmlTextReader^ reader = gcnew XmlTextReader(PathString);
                    bool b00l = false;
                    std::string element = "";
                    while (reader->Read())
                    {
                        if (reader->NodeType == XmlNodeType::Element)
                        {
                            std::string ElementString = marshal_as<std::string>(reader->Name); // system::string to std::string
                            b00l = ElementString == "ProjectGuid";
                        }
                        if (reader->NodeType == XmlNodeType::Text && b00l)
                        {
                            element = marshal_as<std::string>(reader->Value); // system::string to std::string
                        }  
                        if (reader->NodeType == XmlNodeType::EndElement && b00l)
                        {
                            b00l = false;
                            reader->Close();
                            break;
                        }
                    }
                    if (element != "") {
                        std::cout << "[*] Old Vcxproj Guid : " << element << std::endl;
                        std::cout << "[*] New Vcxproj Guid : " << VcxprojGUID << std::endl;
                        Setup(File.FullPath.c_str(),element, VcxprojGUID);
                    }
                    else {
                        std::cerr << "[-] Unable to find Project GUID" << std::endl;
                        system("pause");
                    }
                }
                catch (exception& e) {
                    std::cerr << "[-] Unable to read XML " << e.what() << std::endl;
                    system("pause");
                }
            }

            #pragma endregion

            #pragma region .sln
            else if (File.FileExt == ".sln" && ObfuscateSln && CanObsufucateSln) {
                ParseSolutionFile(File.FullPath, restorevcxprojname, slnGUID, slnGUID2);
            }
            #pragma endregion

            #pragma region C/C++
            else {
                if (ObfuscateFiles) {
                    ObfusucateFiles(File.FullPath);
                }
            }
            #pragma endregion

        } // exit for.
        if (!CanObsufucateSln) {
            std::cout << "[-] Could'nt get .sln trying again." << std::endl;
            goto returnfor;
        }
        for (const auto& File : ObfuscateList)
        {
            std::cout << File.FilePath << std::endl;
            std::cout << File.ObfuscateName << std::endl;
            std::cout << File.OrginalName << std::endl;
        }
    }
    else {
        // Print error and wait for user action.
        std::cerr << "[-] Unable to find members." << std::endl;
        system("pause");
    }

    return 0;
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
                // Saving Full Path
                NiggaFile.FullPath = entry.path().string();
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

void Setup(std::string path, std::string element, std::string newelement) {
    std::ifstream file(path);
    std::string str;
    std::string tempfile;
    while (std::getline(file, str))
    {
        tempfile += str + "\n"; // save file string in temp string
    
    }  
    Helpers::replaceAll(tempfile, element, newelement); // replace all strings in text
    ofstream myfile; 
    myfile.open(path);
    myfile << tempfile; // re output file
    myfile.close();
}

void ParseSolutionFile(std::string path, std::string vcxprojfile, std::string newslnguid, std::string newslnguid2) {
    std::ifstream file(path);
    std::string str;
    std::string tempfile;
    std::string restoreheader;
    std::string guidold;
    std::string guidold2;
    while (std::getline(file, str))
    {
        if (str.find(vcxprojfile) != std::string::npos) {
            restoreheader = str;
            printf("\n");
            //  Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "Example-Project", "Example-Project.vcxproj", "{22CCC249-B8E8-45B8-8459-8C467FC5A52E}"
            std::string restorestring = str.substr(str.find(vcxprojfile));
            Helpers::replaceAll(restorestring, vcxprojfile, ""); // 'Example-Project.vcxproj'
            Helpers::replaceAll(restorestring, "\", ", ""); // '", '
            Helpers::replaceAll(restorestring, "\"", ""); // '"'
            std::cout << "[*] Old Sln Guid   : " << restorestring << std::endl;
            guidold = restorestring;
        }   
        if (str.find("SolutionGuid = ") != std::string::npos) {
            std::string restorestring = str.substr(str.find("SolutionGuid = "));
            Helpers::replaceAll(restorestring, "SolutionGuid = ", "");
            std::cout << "[*] Old Sln Guid 2 : " << restorestring << std::endl;
            guidold2 = restorestring;
        }
        tempfile += str + "\n";
    }
    Helpers::replaceAll(tempfile, guidold, newslnguid);
    std::cout << "[*] New Sln Guid   : " << newslnguid << std::endl;
    Helpers::replaceAll(tempfile, guidold2, newslnguid2);
    std::cout << "[*] New Sln Guid 2 : " << newslnguid2 << std::endl;


    ofstream myfile;
    myfile.open(path);
    myfile << tempfile; // re output file
    myfile.close();
}

void ObfusucateFiles(std::string path) {
    std::ifstream file(path);
    std::string str;
    while (std::getline(file, str))
    {
        if (str.find(Obfuscatestart) != std::string::npos && str.find(Obfuscateend) != std::string::npos) {

            // Remove first blank //O_O Test o_o = "MyValue";
            std::string restorestring = str.substr(str.find(Obfuscatestart)); 
            //o_o = "MyValue";
            std::string EndToEnd = restorestring.substr(restorestring.find(Obfuscateend));
            // remove o_o = "MyValue"; // after O_O Test
            Helpers::replaceAll(restorestring, EndToEnd, "");
            // remove O_O // after ' varriable '
            Helpers::replaceAll(restorestring, Obfuscatestart, ""); 
            // Search Blank Char
            if (restorestring.find(" ") != std::string::npos) {
                // If found replace with ""
                Helpers::replaceAll(restorestring, " ", "");
            }

            // Creating Class.
            FileClass MyFile;
            // save orginal path
            MyFile.FilePath = path;
            // save orginal name
            MyFile.OrginalName = restorestring;
            // get random name
            std::string SecondChar = Helpers::random_string_only_char(3) + Helpers::random_string(12);
            // save random name 
            MyFile.ObfuscateName = SecondChar;
            
            // Search Vector.
            if (std::find(ObfuscateList.begin(), ObfuscateList.end(), MyFile) != ObfuscateList.end()) { /*Found do nothing*/ }
            else {
                // Insert in vector.
                ObfuscateList.insert(ObfuscateList.begin(), MyFile);
            }
        }
    }
}