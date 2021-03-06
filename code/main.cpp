#include "functions.h"

int main() {
    std::set<TramRoute> routesList;

    ifstream dataFile(FILE_NAME);
    if (dataFile.bad() || dataFile.peek() == std::ifstream::traits_type::eof()) {
        cout
                << "Файл с данными не был найден или записи отсутствуют. Будет создан новый со вставленными стандартными значениями."
                << '\n';
        SeedData(routesList);
    } else {
        cout << "Файл с данными найден. Загрузка производится из него." << '\n';
        FillDataFromFile(routesList, dataFile);
    }
    dataFile.close();

    Menu(routesList);


    return 0;
}
