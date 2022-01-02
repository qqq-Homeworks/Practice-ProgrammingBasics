// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#ifndef CODE_IMPORTS_H
#define CODE_IMPORTS_H

#define FILE_NAME "database.qqq"

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

using std::cin, std::cout, std::ifstream, std::ofstream, std::string;

struct TramRoute{
    string Number;
    double Length;
    int RoadTime; //in minutes
};

enum MenuItem {
    ShowRoutes = 1,
    AddRoute,
    EditRoute,
    DeleteRoute,
    GetInfo,
    SaveToFile,
    Exit
};

#endif //CODE_IMPORTS_H
