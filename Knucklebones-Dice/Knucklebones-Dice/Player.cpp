#include "Player.h"

Player::Player() : m_player(""), m_board(), m_score(0) {}

Player::Player(const std::string& name, const Board& board) : m_player(name), m_board(board), m_score(0) {}

Player::~Player() {}

void Player::setPlayer(const std::string& name) {
    this->m_player = name;
}

std::string Player::getPlayer() const {
    return this->m_player;
}

void Player::setBoard(const Board& board) {
    this->m_board = board;
}

Board Player::getBoard() const {
    return this->m_board;
}

void Player::setScore(int score) {
    this->m_score = score;
}

int Player::getScore() const {
    return this->m_score;
}

void Player::updateScore(int points) {
    this->m_score += points;
}

void Player::resetScore() {
    this->m_score = 0;
}
