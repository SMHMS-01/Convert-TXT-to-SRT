#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale>

std::string TXT_FILE_PATH = ".";
std::string TXT_FILE_NAME = "Yanis Varoufakis & Slavoj Zizek _ Festival INDIGO 2021";
std::string txt_file_path = TXT_FILE_NAME + ".txt";
std::string srt_file_path = TXT_FILE_NAME + ".srt";

std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos)
    {
        return "";
    }
    return str.substr(start, end - start + 1);
}

void convertTxtToSrt(const std::string &txtFilePath, const std::string &srtFilePath)
{
    std::ifstream txtFile(txtFilePath, std::ios::binary);
    if (!txtFile)
    {
        std::cerr << "Failed to open the input text file." << std::endl;
        return;
    }

    std::vector<std::string> srtLines;
    int line_number = 1;
    std::string line;
    while (std::getline(txtFile, line))
    {
        line = trim(line);
        if (!line.empty())
        {
            if (line[0] == '[')
            {
                line = line.substr(1); // Remove leading '['
            }
            size_t timestamp_end_index = line.find(']');
            std::string timestamp = line.substr(0, timestamp_end_index);
            std::string subtitle = line.substr(timestamp_end_index + 3);

            // Convert format [00:00:00.000 --> 00:00:15.0000] to 00:00:00,000 --> 00:00:15,000
            size_t arrow_position = timestamp.find("-->");
            if (arrow_position != std::string::npos)
            {
                timestamp.replace(arrow_position, 3, " --> ");
            }
            size_t dot_position = timestamp.find('.');
            if (dot_position != std::string::npos)
            {
                timestamp.replace(dot_position, 1, ",");
            }

            srtLines.push_back(std::to_string(line_number));
            srtLines.push_back(timestamp);
            srtLines.push_back(subtitle);
            srtLines.push_back("");
            line_number++;
        }
    }

    std::ofstream srtFile(srtFilePath, std::ios::binary);
    if (!srtFile)
    {
        std::cerr << "Failed to create the output SRT file." << std::endl;
        return;
    }

    for (const auto &line : srtLines)
    {
        srtFile << line << std::endl;
    }

    std::cout << "Conversion successful. SRT file created: " << srtFilePath << std::endl;
}

int main()
{
    // std::locale::global(std::locale("en_USutf8")); // Set global locale to support UTF-8 encoding/decoding
    convertTxtToSrt(txt_file_path, srt_file_path);

    return 0;
}
