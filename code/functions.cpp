// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>

#include "functions.h"

bool operator<(const TramRoute &route1, const TramRoute &route2) {
    return route1.Number < route2.Number;
}

void SeedData(std::set <TramRoute> &arrayToFill) {
    const TramRoute defaultRoutes[] = {{"17A",  13.2, 184},
                                       {"47",   8,    140},
                                       {"11",   11.8, 165},
                                       {"167",  3.8,  38},
                                       {"15",   27.1, 273},
                                       {"174K", 19.2, 204},
                                       {"812",  10.6, 120},
                                       {"83A",  10.1, 117},
                                       {"12A",  17,   189},
                                       {"74K",  9,    98},
                                       {"87A",  1.2,  12},
                                       {"87",   13,   132},
                                       {"1",    14.5, 154},
    };
    ofstream ofFile(FILE_NAME);
    for (const auto &route: defaultRoutes) {
        arrayToFill.insert(route);
        ofFile.write((char *) &route, sizeof(TramRoute));
    }
    ofFile.close();
}

void FillDataFromFile(std::set <TramRoute> &routes, ifstream &file) {
    TramRoute tempRoute;
    while (!file.eof()) {
        file.read((char *) &tempRoute, sizeof(TramRoute));
        routes.insert(tempRoute);
        //почему-то два 1
    }
}

void PrintMenu() {
    const char *menu[6] = {"Показать список трамвайных маршрутов",
                           "Добавить маршрут в список",
                           "Удалить маршрут из списка",
                           "Узнать информацию по номеру маршрута",
                           "Сохранить список в файл",
                           "Закрыть программу"};
    cout << '\n';
    for (size_t i = 0; i < 6; ++i) {
        cout << i + 1 << ". " << menu[i] << '\n';
    }
    cout << "Введите необходимый вам пункт меню:\n";
}

void Menu(std::set <TramRoute> &routes) {
    unsigned menuPoint;
    while (true) {
        PrintMenu();
        cin >> menuPoint;
        switch (menuPoint) {
            case ShowRoutes:
                ShowRoutesList(routes);
                break;
            case AddRoute:
                InsertRoute(routes);
                break;
            case DeleteRoute:
                EraseRoute(routes);
                break;
            case GetInfo:
                GetRoute(routes);
                break;
            case SaveToFile:
                SaveRoutes(routes);
                break;
            case Exit:
                return;
            default:
                break;
        }
    }
}

void ShowRoutesList(const std::set <TramRoute> &routes) {
    // TODO: оформление таблички(если не впадлу сделать уголки и попытаться убрать отступы)
    cout << ' ';
    for (size_t i = 0; i < 54; ++i) {
        cout << "_";
    }
    cout << '\n';
// РУССКИЕ символы не учитываются в string.length  !!??
    cout << std::left << std::setw(3) << '|' << "Номер маршрута" << std::setw(3) << std::right << '|'
         << std::setw(strlen("Протяжённость") + 3) << "Протяжённость" << std::setw(3) << '|' << std::setw(
            strlen("Время в пути") + 2) << "Время в пути" << std::setw(3) << '|' << '\n';
    cout << ' ';
    for (size_t i = 0; i < 54; ++i) {
        cout << "‾";
    }
    cout << '\n';
    for (const auto &route: routes) {
        cout << '|' << std::setw(7) << ' ' << std::left << route.Number
             << std::right << std::setw(12 - route.Number.length()) << '|' << std::left << std::setw(5) << ' ' <<
             std::setw(5) << route.Length << " км." << std::right << std::setw(5) << '|';
        if (route.RoadTime / 60 < 10) {
            cout << std::right
                 << std::setw(7) << '0' << route.RoadTime / 60;
        } else {
            cout << std::right
                 << std::setw(7) << route.RoadTime / 60;
        }
        cout << ':';
        if (route.RoadTime % 60 < 10) {
            cout << '0' << route.RoadTime % 60;
        } else {
            cout << route.RoadTime % 60;
        }
        cout <<std::setw(6) << '|';
             cout << '\n';
    }
    cout << ' ';
    for (size_t i = 0; i < 54; ++i) {
        cout << "‾";
    }
}

void InsertRoute(std::set <TramRoute> &routes) {
    TramRoute tempRoute;
    cout << "Введите номер маршрута для добавления:" << std::endl;
    cin >> tempRoute.Number;
    cout << "Введите длину маршрута в километрах, если число не целое, введте дробную часть через точку:" << '\n';
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cin >> tempRoute.Length;
            aux = true;
        }
        catch (std::ios_base::failure &fail) {
            aux = false;
            cout << "Введённое вами значение не является числом, пожалуйста, повторите ввод:" << '\n';
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (!aux);

    cout << "Введите время в пути на маршруте в минутах:" << '\n';
    aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cin >> tempRoute.RoadTime;
            if (tempRoute.RoadTime <= 0) {
                aux = false;
                cout << "Введённое вами значение не превосходит ноль, пожалуйста, повторите ввод:" << '\n';
            } else aux = true;

        }
        catch (std::ios_base::failure &fail) {
            aux = false;
            cout
                    << "Введённое вами значение не является числом, пожалуйста, повторите ввод:"
                    << '\n';
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (!aux);

    routes.insert(tempRoute);
    cout << "Добавлен новый маршрут со следующими параметрами:" << '\n';
    cout << "Номер маршрута: " << tempRoute.Number << '\n';
    cout << "Длина маршрута: " << tempRoute.Length << " км." << '\n';
    cout << "Время в пути: ";
    if (tempRoute.RoadTime / 60 < 10) {
        cout << '0' << tempRoute.RoadTime / 60;
    } else {
        cout << tempRoute.RoadTime / 60;
    }
    cout << ':';
    if (tempRoute.RoadTime % 60 < 10) {
        cout << '0' << tempRoute.RoadTime % 60;
    } else {
        cout << tempRoute.RoadTime % 60;
    }
    cout << '\n';
    cout << '\n';
}

//TODO: подумать над выходом
void EraseRoute(std::set <TramRoute> &routes) {
    string numberToDelete;
    cout << "Введите номер маршрута для удаления:" << '\n';
    cin >> numberToDelete;
    auto c = std::find_if(routes.begin(), routes.end(),
                          [numberToDelete](const TramRoute &route) {
                              return route.Number == numberToDelete;
                          });
    while (c == routes.end()) {
        cout << "Маршрута с таким номером не найдено, повторите ввод:" << '\n';
        cin >> numberToDelete;
        c = std::find_if(routes.begin(), routes.end(),
                         [numberToDelete](const TramRoute &route) {
                             return route.Number == numberToDelete;
                         });
    }
    cout << "Следующий маршрут успешно удалён:" << '\n';
    cout << "Номер маршрута: " << (*c).Number << '\n';
    cout << "Длина маршрута: " << (*c).Length << " км." << '\n';
    cout << "Время в пути: ";
    if ((*c).RoadTime / 60 < 10) {
        cout << '0' << (*c).RoadTime / 60;
    } else {
        cout << (*c).RoadTime / 60;
    }
    cout << ':';
    if ((*c).RoadTime % 60 < 10) {
        cout << '0' << (*c).RoadTime % 60;
    } else {
        cout << (*c).RoadTime % 60;
    }
    cout << '\n';
    routes.erase(c);
}

void GetRoute(const std::set <TramRoute> &routes) {
    string numberToFind;
    cout << "Введите номер маршрута по которому хотите получить информацию:" << '\n';
    cin >> numberToFind;
    auto c = std::find_if(routes.begin(), routes.end(),
                          [numberToFind](const TramRoute &route) {
                              return route.Number == numberToFind;
                          });
    while (c == routes.end()) {
        cout << "Маршрута с таким номером не найдено, повторите ввод:" << '\n';
        cin >> numberToFind;
        c = std::find_if(routes.begin(), routes.end(),
                         [numberToFind](const TramRoute &route) {
                             return route.Number == numberToFind;
                         });
    }
    cout << "Информация по маршруту:" << '\n';
    cout << "Номер маршрута: " << (*c).Number << '\n';
    cout << "Длина маршрута: " << (*c).Length << " км." << '\n';
    cout << "Время в пути: ";
    if ((*c).RoadTime / 60 < 10) {
        cout << '0' << (*c).RoadTime / 60;
    } else {
        cout << (*c).RoadTime / 60;
    }
    cout << ':';
    if ((*c).RoadTime % 60 < 10) {
        cout << '0' << (*c).RoadTime % 60;
    } else {
        cout << (*c).RoadTime % 60;
    }
    cout << '\n';
}

void SaveRoutes(const std::set <TramRoute> &routes) {
    ofstream ofFile(FILE_NAME);
    ofFile.clear();
    for (const auto &route: routes) {
        ofFile.write((char *) &route, sizeof(TramRoute));
    }
    ofFile.close();
}