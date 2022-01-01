// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#include "imports.h"

bool operator<(const TramRoute &route1, const TramRoute &route2);

void SeedData(std::set<TramRoute> &);

void FillDataFromFile(std::set<TramRoute> &, ifstream &);

void PrintMenu();

void Menu(std::set<TramRoute> &);

void ShowRoutesList(const std::set<TramRoute> &);

void InsertRoute(std::set<TramRoute> &);

void EraseRoute(std::set<TramRoute> &);

void GetRoute(const std::set<TramRoute> &);

void SaveRoutes(const std::set<TramRoute>&);

#endif //CODE_FUNCTIONS_H
