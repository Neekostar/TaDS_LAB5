#include <iostream>
#include <limits>
#include "BMP/bmp.h"
#include "Menu/MyMenu.h"
#include "Menu/MyMenuItem.h"
#include "Errors/Errors.h"

#define POINTS_OF_MENU 5

using namespace MyGraph;

std::string load_data_file = "/home/neekostar/CLionProjects/TaDS_LAB5/input.bmp";
std::string write_data_file = "/home/neekostar/CLionProjects/TaDS_LAB5/result.bmp";
std::string log_data_file = "Errors.txt";

void rectangle(vector<any> params){
    BMP *bmp = new BMP(1920, 1080, 0);
//    bmp->save(load_data_file);
//    bmp->load(load_data_file);
    uint32_t width = bmp->getWidth();
    uint32_t x0 = width/2;
    uint32_t height = bmp->getHeight();
    uint32_t y0 = height/2;
    bmp->fillRegion(x0, y0, 50, 100, 255, 0, 0, 0);
    bmp->save(write_data_file);
    cout<<"Успешно!"<<endl;
}

void fills(vector<any> params) {
    int32_t x, y, w,h;
    uint8_t r,g,b;
    auto *bmp = any_cast<BMP*>(params[0]);
    std::cout << "Введите стартовую точку x: ";
    cin >> x;
    std::cout << "Введите стартовую точку y: ";
    cin >> y;
    std::cout << "Введите ширину заливки: ";
    cin >> w;
    std::cout << "Введите высоту заливки: ";
    cin >> h;
    std::cout << "Введите код красного цвета (R 0<=255): ";
    cin >> r;
    std::cout << "Введите код зеленого цвета (G 0<=255): ";
    cin >> g;
    std::cout << "Введите код синего цвета (B 0<=255): ";
    cin >> b;
    bmp->fillRegion(x,y,w,h,r,g,b,0);
    std::cout << "Область успешно залита!\n";
}
void scale(vector<any>params) {
    auto *bmp = any_cast<BMP*>(params[0]);
    int32_t w,h;
    std::cout << "Введите ширину: ";
    cin >> w;
    std::cout << "Введите высоту: ";
    cin >> h;
    bmp->scale(w,h);
    cout << "Изображение успешно сжато!\n";
}
void saveFile(vector<any>params) {
    auto *bmp = any_cast<BMP*>(params[0]);
    std::string write_file = any_cast<string>(params[2]);
    cout << "Запущена функция сохранения файла...\n";
    bmp->save(write_file);
    cout << "Сохранение успешно выполнено в файл " << write_file << "\n";
}
void exitt(vector<any>params) {
    saveFile(params);
    cout << "Выход из программы...";
    exit(0);
}
void clearCIN() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}
string Errors::file_name = "Errors.txt";

int main(int argc, char *argv[]) {
    std::string load_data_file = "/home/neekostar/CLionProjects/TaDS_LAB5/input.bmp";
    std::string write_data_file = "/home/neekostar/CLionProjects/TaDS_LAB5/result.bmp";
    std::string log_data_file = "Errors.txt";
    if (argc>=3) {
        load_data_file = argv[1];
        write_data_file = argv[2];
        log_data_file = argv[3];
    }
    MyGraph::Errors::setFileName(log_data_file);

    BMP *file = new BMP(load_data_file);
    MyMenuItem items[POINTS_OF_MENU] = {
            MyMenuItem("Нарисовать красный прямоугольник в открытом файле", rectangle),
            MyMenuItem("Заливка", fills),
            MyMenuItem("Сжать изображение", scale),
            MyMenuItem("Сохранить", saveFile),
            MyMenuItem("Выход", exitt)
    };
    MyMenu menu("BMP", items, POINTS_OF_MENU);
    vector<any> params {file, load_data_file, write_data_file};
    while (true) {
        try {
            menu.runCommand(params);
        }
        catch(const Errors &ex) {
            std::cout << "\nError: " << ex.getError() << "\n";
            clearCIN;
        }
    }
    return 0;
}