#pragma once
#include <cmath>
struct Location
{
    explicit Location(int row = -1, int col = -1) : row(row), col(col) {}
    int row;
    int col;
};

// calculate distance between two locations
double getDistance(const Location& loc1, const Location& loc2);
// compare two locations
bool operator==(const Location& left, const Location& right);