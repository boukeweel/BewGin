#include "GameData.h"

#include <algorithm>
#include <iostream>
#include "fstream"
#include <sstream>
#include "ResourceManager.h"


void GameData::LoadLeaderBoard()
{
    m_HighScoreList.clear();

    std::ifstream file = bew::ResourceManager::GetInstance().LoadTxtFileIf(m_HighScoreFile);
    if (!file)
    {
        std::cerr << "Failed to open file: " << "LeaderBoard.txt" << std::endl;
    }

    std::string line;
    int rank = 1;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        auto data = std::make_unique<HighScoreData>();

        ss >> data->Score;
        size_t comma_pos = line.find(',');
        if (comma_pos != std::string::npos)
        {
            data->Initials = line.substr(comma_pos + 1);
        }

        // Generating number based on rank
        data->number = rank;

        m_HighScoreList.push_back(std::move(data));

        // Increment rank
        ++rank;
    }
}

void GameData::WriteToLeadBoard(int score, const std::string& initials)
{
    m_HighScoreList.push_back(std::make_unique<HighScoreData>(HighScoreData{ 0, score, initials }));
    
    std::sort(m_HighScoreList.begin(), m_HighScoreList.end(), [](const std::unique_ptr<HighScoreData>& a, const std::unique_ptr<HighScoreData>& b) {
        return a->Score > b->Score;
        });

    if (m_HighScoreList.size() > 8)
    {
        m_HighScoreList.resize(8);
    }

    WriteHighScoresToFile();
    LoadLeaderBoard();
}

void GameData::WriteHighScoresToFile()
{
    std::ofstream file = bew::ResourceManager::GetInstance().LoadTxtFileOf(m_HighScoreFile);
    if (!file)
    {
        std::cerr << "Failed to open file for writing: " << m_HighScoreFile << std::endl;
        return;
    }

    for (const auto& score : m_HighScoreList)
    {
        file << score->Score << ',' << score->Initials << '\n';
    }
}
