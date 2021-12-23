#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

//считывание с файла всех координат в формате string
std::vector<std::string> FileReader(std::string File_name){
    std::string str;
    std::vector<std::string> DotsInString;
    std::ifstream CoordsFile;

    CoordsFile.open(File_name);

    if (CoordsFile.is_open()) {
        while (!CoordsFile.eof()){
            str = "";
            CoordsFile >> str;
            DotsInString.push_back(str);
        }
    } else{
        std::cout << "there is no file"<< std::endl;
    }

    CoordsFile.close();

    return DotsInString;
}

//переводит координаты в double
std::vector<double> CoordsFinder(std::vector<std::string> array) {
    std::vector<double> coords;
    for (int i = 0; i < array.size(); i++) {
        std::string b = array[i];
        double c = std::strtod(b.c_str(), nullptr);
        coords.push_back(c);
    }
    return coords;
}

//разделяет x и h стенок
std::vector<double> x_and_h_coords(std::vector<double> array, int n) {
    std::vector<double> coords;
    for (int i = 0; i < array.size() / 2; i++) {
        coords.push_back(array[2 * i + n]);
    }
    return coords;
}

double summ_for_parab(std::vector<double> xCollision, std::vector<double> xCoords,double summ, int xCollise){
    if (xCollision.size() == 0){
        summ = 0;
    } else {
        summ = 2*xCoords[xCollise] - summ;
    }
    return summ;
}

//значения координаты материальной точки при координате x стенок
std::vector<double> y_Coords_Finder(std::vector<double> xCoords, double vx, double vy, double h0, double g, int n, int xCollise, double summ, std::vector<double> xCollision){
    std::vector<double> yCoords;
    for(int i = 0; i < xCoords.size(); i++){
        double y = h0 + pow(-1, n) * (xCoords[i] - summ_for_parab(xCollision, xCoords, summ, xCollise)) * vy / vx - pow((xCoords[i] - summ_for_parab(xCollision, xCoords, summ, xCollise)),2) * g / (2 * vx * vx);
        yCoords.push_back(y);
    }
    return yCoords;
}


int main(int argc, char** argv) { //

    if (argc == 2) {

        std::vector<double> xCollision;

        int n = 0;
        int xCollise = 0;
        double summ = 0;

//    std::string path = "homework2.txt";
        std::string path = argv[1];

        std::vector<std::string> coords_in_string = FileReader(path);
        std::vector<double> coords = CoordsFinder(coords_in_string);

        double g = 9.81;
        double h0 = coords[0];
        double vx = coords[1];
        double vy = coords[2];

//        std::cout << "h0: " << h0 << std::endl;
//        std::cout << "vx: " << vx << std::endl;
//        std::cout << "vy: " << vy << std::endl;

        //удаляем из массива с координатами константы
        coords.erase(coords.begin() + 0, coords.begin() + 3);


        if (coords.size() <= 1) {

            std::cout << 0; // Нет стенок

        } else {

            //разделим на разные векторы координаты по х и у стенок
            std::vector<double> hCoords = x_and_h_coords(coords, 1);
            std::vector<double> xCoords = x_and_h_coords(coords, 0);

//            for (int i = 0; i < hCoords.size(); i++){
//                std::cout << "xCoords: " << xCoords[i] << std::endl;
//                std::cout << "hCoords: " << hCoords[i] << std::endl;
//            }

            std::vector<double> yCoords = y_Coords_Finder(xCoords, vx, vy, h0, g, n, xCollise, summ, xCollision);

//            for (int i = 0; i < yCoords.size(); i++){
//                std::cout << "yCoords: " << yCoords[i] << std::endl;
//            }

            //  П Р О В Е Р К А  Н А  П Е Р В О Е  С Т О Л К Н О В Е Н И Е
            for (int i = 0; i < xCoords.size(); i++) {

                if (yCoords[i] < hCoords[i] && yCoords[i] >= 0) {   // Сталкивается
                    xCollision.push_back(xCoords[i]);
                    xCollise = i;
                    n++;
//                for (int i = 0; i < xCollision.size(); i++) {
//                        std::cout << "xCollision: " << xCollision[i] << std::endl;
//                    }
//                    std::cout << "xCollise: " << xCollise << std::endl;
                    break;
                }

                if (yCoords[i] < hCoords[i] && yCoords[i] < 0) {    // Не сталкивается
                    std::cout << i;
                    return 0;
                }

                if (yCoords[xCoords.size() - 1] > hCoords[xCoords.size() - 1]) {    // Перелетает все стенки
                    std::cout << xCoords.size();
                    return 0;
                }
            }

            vx = -vx;

//            std::cout << "xCollise: " << xCollise << std::endl;

            // П О С Л Е Д У Ю Щ И Е  С Т О Л К Н О В Е Н И Я
            while (true) {

                if (vx < 0) {   // Летит влево

                    yCoords = y_Coords_Finder(xCoords, vx, vy, h0, g, n, xCollise, summ, xCollision);

//                    for (int i = 0; i < yCoords.size(); i++){
//                        std::cout << "yCoords: " << yCoords[i] << std::endl;
//                    }

                    if (xCoords.size() == 1) {   // Стенка одна
                        std::cout << 0;
                        return 0;
                    }


                    for (int i = xCollise - 1; i >= 0; i--) {

                        if (yCoords[i] < hCoords[i] && yCoords[i] >= 0) {      // Сталкивается со стенкой
                            xCollision.push_back(xCoords[i]);
                            xCollise = i;
                            n++;
                            break;
                        }

//                        for (int i = 0; i < xCollision.size(); i++){
//                            std::cout << "yCoords: " << xCollision[i] << std::endl;
//                        }
//                        std::cout << "xCollise: " << xCollise << std::endl;
//                        std::cout << "n: " << n << std::endl;

                        if (yCoords[i] > hCoords[0]) {  // Перелетает первую стенку -> попадает в 0 зону
                            std::cout << 0;
                            return 0;
                        }

                        if (yCoords[i] < hCoords[i] && yCoords[i] < 0) {    // Не сталкивается
                            std::cout << i;
                            return 0;

                        }

                    }

                    vx = -vx;
                }

                if (vx > 0) {   // Летит вправо

                    yCoords = y_Coords_Finder(xCoords, vx, vy, h0, g, n, xCollise, summ, xCollision);

                    for (int i = xCollise + 1; i > xCoords.size(); i++) {

                        if (yCoords[i] < hCoords[i] && yCoords[i] >= 0) {   // Сталкивается
                            xCollision.push_back(xCoords[i]);
                            xCollise = i;
                            n++;
                            break;
                        }

                        if (yCoords[i] < hCoords[i] && yCoords[i] < 0) {    // Не сталкивается
                            std::cout << i;
                            return 0;
                        }

                        if (yCoords[xCoords.size() - 1] > hCoords[xCoords.size() - 1]) {    // Перелетает все стенки
                            std::cout << xCoords.size();
                            return 0;
                        }

                    }

                    vx = -vx;
                }
            }


        }

    } else {
        std::cout << "there are too few or too many arguments" << std::endl;
    }
}
