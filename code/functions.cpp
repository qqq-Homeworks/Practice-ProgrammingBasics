// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>

#include "functions.h"

//template<typename charT, typename traits = std::char_traits<charT> >
//class center_helper {
//    std::basic_string<charT, traits> str_;
//public:
//    center_helper(std::basic_string<charT, traits> str) : str_(str) {}
//
//    template<typename a, typename b>
//    friend std::basic_ostream<a, b> &operator<<(std::basic_ostream<a, b> &s, const center_helper<a, b> &c);
//};
//
//template<typename charT, typename traits = std::char_traits<charT> >
//center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
//    return center_helper<charT, traits>(str);
//}
//
//// redeclare for std::string directly so we can support anything that implicitly converts to std::string
//center_helper<std::string::value_type, std::string::traits_type> centered(const std::string &str) {
//    return center_helper<std::string::value_type, std::string::traits_type>(str);
//}
//
//template<typename charT, typename traits>
//std::basic_ostream<charT, traits> &
//operator<<(std::basic_ostream<charT, traits> &s, const center_helper<charT, traits> &c) {
//    std::streamsize w = s.width();
//    if (w > c.str_.length()) {
//        std::streamsize left = (w + c.str_.length()) / 2;
//        s.width(left);
//        s << c.str_;
//        s.width(w - left);
//        s << "";
//    } else {
//        s << c.str_;
//    }
//    return s;
//}

bool operator<(const TramRoute &route1, const TramRoute &route2) {
    return route1.Number < route2.Number;
}

void SeedData(multiset<TramRoute> &arrayToFill) {
    const TramRoute defaultRoutes[] = {{"12А",  13.2, 184},
                                       {"47",   8,    140},
                                       {"11",   11.8, 165},
                                       {"167",  3.8,  38},
                                       {"15",   27.1, 273},
                                       {"174к", 19.2, 204},
                                       {"812",  10.6, 120},
                                       {"83А",  10.1, 117},
                                       {"12А",  17,   189},
                                       {"74к",  9,    98},
                                       {"87А",  1.2,  12},
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

void FillDataFromFile(multiset<TramRoute> &routes, ifstream &file) {
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
    for (size_t i = 0; i < 6; ++i) {
        cout << i + 1 << ". " << menu[i] << '\n';
    }
    cout << "Введите необходимый вам пункт меню:\n";
}

void Menu(multiset<TramRoute> &routes) {
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

                break;
            case Exit:
                return;
            default:
                break;
        }
    }
}

void ShowRoutesList(const multiset<TramRoute> &routes) {
    // TODO: оформление таблички
    cout << '|' << std::right << std::setw(strlen("Номер маршрута") + 2) << "Номер маршрута" << std::setw(3) << '|'
         << std::right << std::setw(strlen("Протяжённость") + 2) << "Протяжённость" << std::setw(3) << '|'
         << std::right << std::setw(strlen("Время в пути") + 2) << "Время в пути" << std::setw(3) << '|'
         << '\n';
    // cout << "|" << std::setw(23) << centered("Номер маршрута") << '|'
    //         << std::right << std::setw(static_cast<int>(round(strlen("Протяжённость") * 1.5)))
    //         << "Протяжённость" << std::right
    //         << std::setw(static_cast<int>(round(strlen("Время в пути") * 1.5))) <<
    //         "Время в пути" << "\n\n";
    for (const auto &route: routes) {
        cout << std::setw(10) << route.Number
             << std::setw(16) << route.Length << " км.";
        if (route.RoadTime / 60 < 10) {
            cout << std::right
                 << std::setw(strlen("Время в пути") / 2) << '0' << route.RoadTime / 60;
        } else {
            cout << std::right
                 << std::setw(strlen("Время в пути") / 2) << route.RoadTime / 60;
        }
        cout << ':';
        if (route.RoadTime % 60 < 10) {
            cout << '0' << route.RoadTime % 60;
        } else {
            cout << route.RoadTime % 60;
        }
        cout << '\n';
    }
}

void InsertRoute(multiset<TramRoute> &routes) {
    TramRoute tempRoute;
    cout << "Введите номер маршрута для добавления:" << std::endl;
    cin >> tempRoute.Number;
    //tempRoute.Number.erase(std::remove_if(tempRoute.Number.begin(), tempRoute.Number.end(), ::isspace),
    //   tempRoute.Number.end());
//    while (tempRoute.Number.empty()) {
//        cout << "Строка номера не может быть пустой, повторите ввод согласно правилам:" << '\n';
//        cin >> tempRoute.Number;
//        tempRoute.Number.erase(std::remove_if(tempRoute.Number.begin(), tempRoute.Number.end(), ::isspace),
//                               tempRoute.Number.end());
//    }
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
//    cin >> tempRoute.Length;
//    while (!cin) {
//        cout << "Введённое вами значение не является числом, повторите ввод согласно правилам:" << '\n';
////        cin >> tempRoute.Length;
//    }
}

//TODO: подумать над выходом
void EraseRoute(multiset<TramRoute> &routes) {
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

void GetRoute(const multiset<TramRoute> &routes){
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