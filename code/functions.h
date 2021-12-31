// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

#include "imports.h"

bool operator<(const TramRoute &route1, const TramRoute &route2);

void SeedData(multiset<TramRoute> &);

void FillDataFromFile(multiset<TramRoute> &, ifstream &);

void PrintMenu();

void Menu(multiset<TramRoute> &);

void ShowRoutesList(const multiset<TramRoute> &);

void InsertRoute(multiset<TramRoute> &);

void EraseRoute(multiset<TramRoute> &);

void GetRoute(const multiset<TramRoute> &);

#endif //CODE_FUNCTIONS_H
