#include "Location.h"

/**
 * get distance between two locations
 */
double getDistance(const Location& loc1, const Location& loc2){
    return sqrt(pow(loc1.col - loc2.col, 2) + pow(loc1.row - loc2.row, 2));
}

/**
 * compare two location
 */
bool operator==(const Location& left, const Location& right) {
    return left.col == right.col && left.row == right.row;
}