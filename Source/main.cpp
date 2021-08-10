#include "stdafx.h"

// Define extensions
const char* extensions[]{
    ".h", ".hpp",
    ".cc", ".c", ".C", ".cpp", ".cxx", ".cp", ".c++",
    ".vcxproj", ".sln" };

const char* blacklist_folders[] { ".vs", "x64", "Release", "Debug", "lib", "wdk" };

/// <summary>
/// File settings
/// </summary>
bool ObfuscateFiles = true;
/// <summary>
/// Vcxproj settings
/// </summary>
bool ObfuscateVcxproj = true;
bool RandomizeVcxprojGuid = true; // Randomize GUID for vcxproj
string UserDefinedVcxprojGUID = "{SwZ-GUID}"; // If randomize guid false define this // not prefered

/// <summary>
/// .sln settings
/// </summary>
bool ObfuscateSln = true;
bool RandomizeSlnGuid = true; // Randomize GUID for vcxproj
string UserDefinedSlnGUID = "{SwZ-GUID}"; // If randomize guid false define this // not prefered
string UserDefinedSlnGUID2 = "{SwZ-GUID}"; // If randomize guid false define this // not prefered

/// <summary>
/// Obfuscate Markers
/// </summary>
/// type 1 = in all files
/// type 2 = in only own file
std::string Obfuscatestart = "O_O"; // type 1
std::string Obfuscateend = "o_o"; // type 1
std::string Obfuscatestart1 = "O__O"; // type 2
std::string Obfuscateend2 = "o__o"; // type 2

// Define list
std::vector<DirectoryClass> FileList;
std::vector<FileClass> ObfuscateList;
std::vector<FolderClass> FolderList;


bool GetDocuments(std::string Path);
void Setup(std::string path, std::string element, std::string newelement);
void ParseSolutionFile(std::string path, std::string vcxprojfile, std::string newslnguid, std::string newslnguid2);
void ObfusucateFiles(std::string path);
FolderClass FindFile(std::string filepath);

int TotalObfCount = 0;
int main(int argc, char* argv[])
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

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

    if (GetDocuments("D:\\Kernel\\")) {
    //if (GetDocuments("C:\\Users\\ykaan\\Documents\\GitHub\\cpp-c-randomizer\\Example-Project\\")) {

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
            if (File.FileExt == ".vcxproj" && ObfuscateVcxproj) {
                
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
                } catch (exception& e) {
                    std::cerr << "[-] Unable to read XML " << e.what() << std::endl;
                    system("pause");
                }
            }

            #pragma endregion

            // SLN
            else if (File.FileExt == ".sln" && ObfuscateSln && CanObsufucateSln)  ParseSolutionFile(File.FullPath, restorevcxprojname, slnGUID, slnGUID2);
            // C/CPP
            else if (ObfuscateFiles)  ObfusucateFiles(File.FullPath);

        } // exit for.

        if (!CanObsufucateSln) {
            std::cout << "[-] Could'nt get .sln trying again." << std::endl;
            goto returnfor;
        }

        #pragma region C/C++

        if(ObfuscateList.size() > 0) {
            // define index
            static int Index = 0;
            // define index2
            static int Index2 = 0;
            // enter obfuscated list
            for (const auto& File : ObfuscateList)
            {
                // prevent null string
                if (File.FilePath != "" || File.FilePath != "NULL") {
                    // Find File
                    FolderClass ItemFirst = FindFile(File.FilePath);
                    // enter folder list
                    for (FolderClass Item : FolderList)
                    {
                        // if is only in own file
                        if (File.OnlyInOwnFile) {
                            // match ++
                            if (Item.FilePath == File.FilePath) {
                                // match ++
                                if (Item.FilePath == ItemFirst.FilePath) {
                                    // copy string for memory
                                    std::string CopyString = FolderList[Index2].TempString;
                                    // replace strings 
                                    Helpers::replaceAll(CopyString, File.OrginalName, File.ObfuscateName);
                                    // save string
                                    FolderList[Index2].TempString = CopyString;
                                    // break
                                    break;
                                }
                            }
                        }
                        else {
                            // copy string for memory
                            std::string CopyString = FolderList[Index2].TempString;
                            // replace strings 
                            Helpers::replaceAll(CopyString, File.OrginalName, File.ObfuscateName);
                            // save string
                            FolderList[Index2].TempString = CopyString;
                        }
                        // count index 2
                        Index2++;
                    }
                    // find this item in list and set true
                    ObfuscateList[Index].IsObsufucated = true;
                    // Count index
                    Index++;
                    if (File.OnlyInOwnFile) Index2 = 0;
                }
                // reset index 2
                Index2 = 0;
            }// exit for
            // enter last for
            for (FolderClass Item : FolderList)
            {
                // print result
                // std::cout << "\n-------------------------------\n" << Item.FilePath << "\n-------------------------------\n" << Item.TempString << std::endl;
                // create ofstream
                ofstream myfile;
                // open stream
                myfile.open(Item.FilePath);
                myfile << Item.TempString; // re output file
                // close stream
                myfile.close();
            }//exit for
        }
        std::cout << "\n[-] Total obf define : " << TotalObfCount <<"\n\n";
        #pragma endregion
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "\n[-] Finished operation in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
    }
    else {
        // Print error and wait for user action.
        std::cerr << "[-] Unable to find members." << std::endl;
        system("pause");
    }
    return 0;
}

bool is_whitelist_file(std::string file, std::string path) {
    bool status = false;
    for (const auto& Item : extensions) {
        std::string StringItem = file;
        StringItem.replace(StringItem.find(path), path.length(), "");
        if ((StringItem.find(Item) != std::string::npos)
            && !(StringItem.find(".user") != std::string::npos)
            && !(StringItem.find(".filters") != std::string::npos)) {
            status = true;
            break;
        }
    } return status;
}

bool is_whitelist_folder(std::string file, std::string path) {
    bool status = true;
    for (const auto& Item : blacklist_folders) {
        std::string StringItem = file;
        StringItem.replace(StringItem.find(path), path.length(), "");
        if ((StringItem.find(Item) != std::string::npos)) { status = false; break; }
    } return status;
}

// gen 2.0
bool GetDocuments(std::string path) {
    std::string temp_path = path;

    std::vector<FileClass> file_list;
    std::vector<FolderClass> folder_list;
    int folder_index = 0;

find:
    for (const auto& entry : fs::directory_iterator(temp_path)) {
        if (std::filesystem::is_directory(entry.path().string()) && is_whitelist_folder(entry.path().string(), temp_path)) {

            FolderClass folder;
            folder.FilePath = entry.path().string();
            if (std::find(folder_list.begin(), folder_list.end(), folder) != folder_list.end());
            else folder_list.insert(folder_list.begin(), folder);

        } else if (is_whitelist_file(entry.path().string(), temp_path)){

            FileClass file;
            file.OrginalName = entry.path().string();
            file.ext = entry.path().extension().string();
            file.FilePath = temp_path;
            if (std::find(file_list.begin(), file_list.end(), file) != file_list.end());
            else file_list.insert(file_list.begin(), file);

        }
    }
    folder_index == 0;
    for (const auto& _folder : folder_list)
    {
        if (!_folder.is_searched) {
            folder_list[folder_index].is_searched = true;
            temp_path = _folder.FilePath;
            goto find;
        }
        folder_index++;
    }

    for (const auto& _file : file_list)
    {
        DirectoryClass NiggaFile;
        NiggaFile.IsObsufucated = false;
        std::string CurrentPath = _file.OrginalName;
        CurrentPath.replace(CurrentPath.find(_file.FilePath), _file.FilePath.length(), "");
        NiggaFile.FullName = CurrentPath;
        NiggaFile.FileExt = _file.ext;
        NiggaFile.FullPath = _file.OrginalName;
        NiggaFile.FileName = fs::path(CurrentPath).replace_extension().string();
        if (std::find(FileList.begin(), FileList.end(), NiggaFile) != FileList.end());
        else FileList.insert(FileList.begin(), NiggaFile);
    }

    return FileList.size() > 0 ? true : false;
}

void Setup(std::string path, std::string element, std::string newelement) {
    std::ifstream file(path);
    std::string str;
    std::string tempfile;
    while (std::getline(file, str)) tempfile += str + "\n"; // save file string in temp string
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
    } // exit while
    // replace first guid to new
    Helpers::replaceAll(tempfile, guidold, newslnguid);
     
    std::cout << "[*] New Sln Guid   : " << newslnguid << std::endl;

    // replace seconds guid to new
    Helpers::replaceAll(tempfile, guidold2, newslnguid2);

    std::cout << "[*] New Sln Guid 2 : " << newslnguid2 << std::endl;

    // create ofstream
    ofstream myfile;
    // open stream
    myfile.open(path);

    myfile << tempfile; // re output file
    // close stream
    myfile.close();
}


int WordOccurrenceCount(std::string const& str, std::string const& word)
{
    int count(0);
    std::string::size_type word_pos(0);
    while (word_pos != std::string::npos)
    {
        word_pos = str.find(word, word_pos);
        if (word_pos != std::string::npos)
        {
            ++count;

            // start next search after this word 
            word_pos += word.length();
        }
    }
    // return
    return count;
}


void ObfusucateFiles(std::string path) {

    // set strings to !OnlyInOwnFile
    std::string string1 = Obfuscatestart;
    std::string string2 = Obfuscateend;
    // prevent inf loop
    bool IsSearched = false;
SearchBack:
    // define ifstream
    std::ifstream file(path);
    // set str 
    std::string str2;
    // set tempfile
    std::string tempfile;
    while (std::getline(file, str2))
    {
        // set temp string and count
        std::string str = str2;
        int searchCount = 0;
    Back2:
        if (str.find(string1) != std::string::npos && str.find(string2) != std::string::npos) {

            // Remove first blank //O_O Test o_o = "MyValue";
            std::string restorestring = str.substr(str.find(string1));
            //o_o = "MyValue";
            std::string EndToEnd = restorestring.substr(restorestring.find(string2));
            // remove o_o = "MyValue"; // after O_O Test
            Helpers::replaceAll(restorestring, EndToEnd, "");
            // remove O_O // after ' varriable '
            Helpers::replaceAll(restorestring, string1, "");
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
            // save false
            MyFile.IsObsufucated = false;
            // save bool
            MyFile.OnlyInOwnFile = IsSearched;
            // Search Vector.
            if (std::find(ObfuscateList.begin(), ObfuscateList.end(), MyFile) != ObfuscateList.end()) { /*Found do nothing*/ }
            else {
                // Insert in vector.
                ObfuscateList.insert(ObfuscateList.begin(), MyFile);
            }
            int type = IsSearched ? 2 : 1;
            //std::cout << "[*] Type "<< type <<" : " << restorestring << std::endl;
            //std::cout << "[*] Type "<< type <<" (New) : " << SecondChar << "\n"<< std::endl;
            TotalObfCount++;
            // check multiple define
            int IntVarriable = WordOccurrenceCount(str2, string1);
            // if have
            if (IntVarriable > 1)
            {
                // if count dont match
                if (searchCount != IntVarriable) {
                    // apply count
                    searchCount++;
                    // define a define = define ssss define -> define = define ssss define
                    str = EndToEnd;
                    // back to serach
                    goto Back2;
                }
            }
        }
        // save to temp file edit in memory
        tempfile += str2 + "\n";
    } // exit while
    // set strings to OnlyInOwnFile
    string1 = Obfuscatestart1;
    string2 = Obfuscateend2;
    // go back
    if (!IsSearched) { IsSearched = true;  goto SearchBack; }
    // creating class
    FolderClass MyFolder;
    // save memory file
    MyFolder.TempString = tempfile;
    // set file path
    MyFolder.FilePath = path;
    if (std::find(FolderList.begin(), FolderList.end(), MyFolder) != FolderList.end()) { /*Found do nothing*/ }
    else {
        // Insert in vector.
        FolderList.insert(FolderList.begin(), MyFolder);
    }
}

FolderClass FindFile(std::string filepath) {

    // Enter for in folders
    for (FolderClass Item : FolderList)
    {
        // if match file
        if (Item.FilePath == filepath) {
            // return item
            return Item;
            // break for
            break;
        }
    } //exit for
    // if dont match file
    // return null file
    FolderClass myclass;
    std::cout << "Return null" << std::endl;
    return myclass;
}