#include "fileManager.h"


fileManager::fileManager()
{

}

void fileManager::load()
{
    std::ifstream inputFile("lists.json");

    if (inputFile) {
        inputFile.close();
    }
    else
    {
        std::ofstream outputfile("lists.json");
        nlohmann::json data;

        data["lists"] = nlohmann::json::array();

        outputfile << data.dump();

        outputfile.close();

    }
};


nlohmann::json fileManager::getLists()
{
    std::ifstream inputFile("lists.json");
    std::string data;
    std::getline(inputFile, data);
    jsonLists = nlohmann::json::parse(data);

    return jsonLists;
};

bool fileManager::saveFile(nlohmann::json jsonData) {

    try
    {

        std::ofstream outputFile("lists.json");

        outputFile << jsonData.dump();

        outputFile.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cout << "An error was encoured : " << e.what() << std::endl;

        return false;
    }

};
