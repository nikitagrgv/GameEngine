#include "FileManager.h"

#include <fstream>
#include <sstream>

std::string FileManager::getFileText(const char* file_path)
{
    std::ifstream ifstr(file_path);

    if (!ifstr)
        return "";

    std::ostringstream sstr;

    if (!sstr)
        return "";

    sstr << ifstr.rdbuf();

    return sstr.str();
}
