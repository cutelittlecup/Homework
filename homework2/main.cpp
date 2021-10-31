#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

//считывание с файла всех координат в формате string
std::vector<std::string> FileReader(const std::string& File_name){
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

//рекурсия для учёта сдвига парабол
double recurs(std::vector<double> X, double n){
    if (n == 0) {
        return 0;
    }
    else {
        return 2 * X[n-1] - recurs(X, n - 1);
    }
}

//значения координаты материальной точки при координате x стенок
std::vector<double> y_Coords_Finder(std::vector<double> xCoords, double vx, double vy, double h0, double g, int n, std::vector<double> xCollision){
    std::vector<double> yCoords;
    for(int i = 0; i < xCoords.size(); i++){
        double y = h0 + pow(-1, n) * (xCoords[i] - recurs(xCollision, n)) * vy / vx - pow((xCoords[i] - recurs(xCollision,n)),2) * g / (2*pow(vx,2));
        yCoords.push_back(y);
    }
    return yCoords;
}


int main(int argc, char** argv) {

    if (argc == 2){
        std::cout << "1st argument: "<< argv[1] << std::endl;
        int n = 0;
        int iCollision = 0;

        //начальное направление движения
        std::string LorR = "Right";

        std::string path = argv[1];

        std::vector<std::string> coords_in_string = FileReader(path);
        std::vector<double> coords = CoordsFinder(coords_in_string);

        double g = 9.81;
        double h0 = coords[0];
        double vx = coords[1];
        double vy = coords[2];

        //удаляем из массива с координатами константы
        coords.erase(coords.begin() + 0, coords.begin() + 3);

        //разделим на разные векторы координаты по х и у стенок
        std::vector<double> hCoords = x_and_h_coords(coords, 1);
        std::vector<double> xCoords = x_and_h_coords(coords, 0);

        std::vector<double> xCollision;

        std::vector<double> yCoords = y_Coords_Finder(xCoords, vx, vy, h0, g, n, xCollision);

        //первое столкновение
        for(int i = 0; i < xCoords.size(); i++){
            if(yCoords[i] < hCoords[i]){
                iCollision = i;
                xCollision.push_back(xCoords[i]);
                LorR = "Left";
                n++;
                break;
            }
        }
        if(LorR == "Right"){
            std::cout << "<" << xCoords.size() << ">";
            return 0;
        }

        // все последующие столкновения
        while(true){
            if(LorR == "Left"){
                yCoords = y_Coords_Finder(xCoords,vx,vy,h0,g,n,xCollision);
                for(int i = iCollision - 1; i >= 0; i--){

                    if (yCoords[i] <= hCoords[i]){
                        iCollision = i;
                        LorR = "Right";
                        n++;
                        xCollision.push_back(xCoords[i]);
                        break;
                    }
                }

                if(yCoords[iCollision] < 0){
                    std::cout << "<" << iCollision+1 << ">";
                    return 0;
                }

                if(LorR == "Left"){
                    std::cout << "<" << 0 << ">";
                    return 0;
                }
            }

            if(LorR == "Right"){
                yCoords = y_Coords_Finder(xCoords,vx,vy,h0,g,n,xCollision);
                for(int i = iCollision + 1 ; i < xCoords.size(); i++){

                    if (yCoords[i] <= hCoords[i]){
                        iCollision = i;
                        LorR = "Left";
                        n++;
                        xCollision.push_back(xCoords[i]);
                        break;
                    }
                }

                if(yCoords[iCollision] < 0){
                    std::cout << "<" << iCollision << ">";
                    return 0;
                }

                if(LorR  == "Right"){
                    std::cout << "<" << xCoords.size() << ">";
                    return 0;
                }
            }
        }
    } else{
        std::cout << "there are too few or too many arguments"<< std::endl;
    }
}
