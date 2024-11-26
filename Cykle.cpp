#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct Path
{
    std::string input;
    std::string output;
};

struct Apex
{
    int beginning;
    int end;
};

Path GetPaths(int argc, char* argv[])
{
    Path path{"", ""};
    std::string currentArgument;
    for (int i = 0; i < argc; i++)
    {
        currentArgument = argv[i];
        if (currentArgument == "-g")
            path.input = argv[i + 1];
        else if (currentArgument == "-c")
            path.output = argv[i + 1];
    }
    return path;
}

std::vector<Apex> ReadDataFromFile(std::string path)
{
    std::vector<Apex> vec;
    std::ifstream file(path);

    if (!file)
    {
        std::cerr << "Failed to open the input file" << std::endl;
        return vec;
    }

    std::string line;
    std::string result = "";
    while (getline(file, line))
        result += line;

    result.erase(std::remove_if(result.begin(), result.end(), isspace), result.end());

    std::istringstream resultStream(result);
    int beginning, end;
    char tempChar;
    while (resultStream >> beginning >> tempChar >> tempChar >> end)
    {
        vec.push_back({ beginning, end });
        if (resultStream.peek() == ',')
            resultStream.ignore();
    }

    return vec;
}

int main(int argc, char* argv[])
{
    Path path = GetPaths(argc, argv);

    if (path.input == "" || path.output == "")
    {
        std::cerr << "Failed to find input/output path argument!" << std::endl;
        return 1;
    }

    std::vector<Apex> dataFromFile = ReadDataFromFile(path.input);

    for (const auto& value : dataFromFile)
        std::cout << value.beginning << " " << value.end << std::endl;

    return 0;
}
