#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const char HIDDEN_SYMBOL = '#';
const int MAX_PAIRS = 50;
extern int flipCount;

void playMatchSound();
void playNoMatchSound();

vector<vector<char>> createBoard(int pairs);
void printBoard(const vector<vector<char>>& board, const vector<vector<bool>>& revealed);

void getCardCoords(int& row, int& col,
    const vector<vector<bool>>& revealed,
    const vector<vector<char>>& board,
    const string& prompt,
    int prevRow = -1, int prevCol = -1);

void playGame(int pairs, int playerCount);
