#include "ScoreTracker.h"

ScoreTracker::ScoreTracker() {}

ScoreTracker::~ScoreTracker() {}

void ScoreTracker::updateScore(Player& player) 
{
    int newScore = player.getBoard().boardScore();
    player.setScore(newScore);
}

std::pair<int, int> ScoreTracker::evaluateScore(const Board& board) 
{
    int score = 0;
    int multiplier = 1;

    for (int col = 0; col < 3; ++col) 
    {
        std::unordered_map<int, int> count;
        for (int row = 0; row < 3; ++row) 
        {
            if (board.getBoard(row, col)[row][col] > 0)
            {
                int value = board.getBoard(row, col)[row][col];
                count[value]++;
            }
        }

        for (const auto& pair : count)
        {
            int value = pair.first;
            int freq = pair.second;
            score += value * freq * freq;
            multiplier = std::max(multiplier, freq);
        }
    }
    return { score, multiplier };
}

int ScoreTracker::getWinnerIndex(const std::vector<Player>& players) const 
{
    int maxScore = -1;
    int winnerIndex = -1;

    for (int i = 0; i < players.size(); ++i) 
    {
        if (players[i].getScore() > maxScore) 
        {
            maxScore = players[i].getScore();
            winnerIndex = i;
        }
    }

    return winnerIndex;
}

void ScoreTracker::displayScores(const std::vector<Player>& players) const 
{
    std::cout << "Scores:\n";
    for (const auto& player : players) 
    {
        std::cout << player.getPlayer() << ": " << player.getScore() << "\n";
    }
}