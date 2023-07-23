#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <nlohmann/json.hpp>

class fileManager
{
public:
    fileManager();
    void load();
    nlohmann::json getLists();
    bool saveFile(nlohmann::json jsonData);

private:
    nlohmann::json jsonLists;


};


#endif // !FILEMANAGER_H

