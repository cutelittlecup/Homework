#include <iostream>
#include <fstream> // для чтения файлов
#include <cmath> //для корней

int main() {

    double A, B;
    double x_i, y_i;
    double ro;
    double Rightmost_x, Rightmost_y;
    double Leftmost_x, Leftmost_y;

    std::string path = "in.txt";
    std::ifstream DotsFile;
    DotsFile.open(path);

    if (DotsFile.is_open()) {

        DotsFile >> A >> B;

//        std::cout << A << std::endl;
//        std::cout << B << std::endl;

        while (!DotsFile.eof()) {

            DotsFile >> x_i >> y_i;
            ro = round(fabs((A * x_i + B * y_i)) / sqrt(A*A + B*B)*10000)/10000;
//            std::cout << ro << std::endl;

            if (A*y_i <= B*x_i) {
                double Rolast_r = ro;
                if (ro >= Rolast_r) {
                    Rightmost_x = x_i;
                    Rightmost_y = y_i;
                }

            } else {
                double Rolast_l = ro;
                if (ro >= Rolast_l) {
                    Leftmost_x = x_i;
                    Leftmost_y = y_i;
                }

            }


        }

    } else {

        std::cout << "there is no file..."<< std::endl;

    }

    std::cout << "Leftmost:" << " "<< Leftmost_x << " " << Leftmost_y << std::endl;

    std::cout << "Rightmost:" << " "<< Rightmost_x << " " << Rightmost_y << std::endl;

    DotsFile.close();

    return 0;
}

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cmath>
//
////считывает данные с файла и отдаёт вектор с точками в формате string
//std::vector<std::string> FileReader(const std::string& name){
//    std::string str;
//    std::vector<std::string> DotsInString;
//    std::ifstream DotsFile;
//
//    DotsFile.open(name);
//
//    if (DotsFile.is_open()) {
//        while (!DotsFile.eof()){
//            str = "";
//            DotsFile >> str;
//            DotsInString.push_back(str);
//        }
//    } else{
//        std::cout << "there is no file..."<< std::endl;
//    }
//
//    DotsFile.close();
//
//    return DotsInString;
//}
//
////переводит вектор с точками в формат double
//std::vector<double> DotsFinder(std::vector<std::string> array) {
//    std::vector<double> dots;
//    for (int i = 0; i < array.size(); i++) {
//        std::string b = array[i];
//        double c = std::strtod(b.c_str(), nullptr);
//        dots.push_back(c);
//    }
//    return dots;
//}
//
////функция для разделения вектора с координатами на вектор с x и y
//std::vector<double> coords(std::vector<double> array, int n){
//    std::vector<double> coords;
//    for (int i = 0; i < array.size()/2; i++) {
//        coords.push_back(array[2*i + n]);
//    }
//    coords.erase(coords.begin() + 0);
//    return coords;
//}
//
////разделяет координаты с точками на левые и правые
//std::vector<double> DotsSight (std::vector<double> yDots, std::vector<double> xDots, double A, double B, const std::string& XorY, const std::string& LorR) {
//    std::vector<double> xDotsLeft;
//    std::vector<double> yDotsLeft;
//    std::vector<double> xDotsRight;
//    std::vector<double> yDotsRight;
//    if (B > 0) {
//        double k = A / B;
//        for (int i = 0; i < yDots.size(); i++) {
//            if (yDots[i] > k * xDots[i]) {
//                yDotsLeft.push_back(yDots[i]);
//                xDotsLeft.push_back(xDots[i]);
//            } else if (yDots[i] <= k * xDots[i]) {
//                yDotsRight.push_back(yDots[i]);
//                xDotsRight.push_back(xDots[i]);
//            }
//        }
//    } else if (B < 0) {
//        double k = A / B;
//        for (int i = 0; i < yDots.size(); i++) {
//            if (yDots[i] >= k * xDots[i]) {
//                yDotsRight.push_back(yDots[i]);
//                xDotsRight.push_back(xDots[i]);
//
//            } else if (yDots[i] < k * xDots[i]) {
//                yDotsLeft.push_back(yDots[i]);
//                xDotsLeft.push_back(xDots[i]);
//            }
//        }
//    } else {
//        for (int i = 0; i < yDots.size(); i++) {
//            if (xDots[i] >= 0) {
//                yDotsRight.push_back(yDots[i]);
//                xDotsRight.push_back(xDots[i]);
//
//            } else if (xDots[i] < 0) {
//                yDotsLeft.push_back(yDots[i]);
//                xDotsLeft.push_back(xDots[i]);
//            }
//        }
//    }
//
//    if (XorY == "X") {
//        if (LorR == "L") {
//            return xDotsLeft;
//        } else {
//            return xDotsRight;
//        }
//    }
//    if (XorY == "Y") {
//        if (LorR == "L") {
//            return yDotsLeft;
//        } else {
//            return yDotsRight;
//        }
//    }
//    return {};
//}
//
////считает расстояние от точки до прямой
//std::vector<double> Ro(double A, double B, std::vector<double> array1, std::vector<double> array2){
//    std::vector<double> Ro;
//    for (int i = 0; i < array1.size(); i++) {
//        double ro = fabs((A * array1[i] + B * array2[i]) /
//                         (sqrt(A*A + B*B)));
//        Ro.push_back(ro);
//    }
//    return Ro;
//}
//
////выдаёт значение индекса координат с максимальным расстоянием
//int findI(std::vector<double> array) {
//    int k = 0;
//    for (int i = 0; i < array.size(); i++) {
//        if (array[i] > array[k]) k = i;
//    }
//    return k;
//}
//
//int main() {
//
//    std::string path = "in.txt";
//
//    std::vector<std::string> dots_in_string = FileReader(path);
//
//    std::vector<double> dots = DotsFinder(dots_in_string);
//    std::vector<double> xDots = coords(dots, 0);
//    std::vector<double> yDots = coords(dots, 1);
//
//    double A = dots[1];
//    double B = dots[0];
//
//    std::vector<double> xDotsLeft = DotsSight (yDots, xDots, A, B, "X", "L");
//    std::vector<double> xDotsRight = DotsSight (yDots, xDots, A, B, "X", "R");
//    std::vector<double> yDotsLeft = DotsSight (yDots, xDots, A, B, "Y", "L");
//    std::vector<double> yDotsRight = DotsSight (yDots, xDots, A, B, "Y", "R");
//
//    if (!xDotsLeft.empty()){
//        std::vector<double> Leftmost = Ro(A, B, xDotsLeft, yDotsLeft);
//        int b = findI(Leftmost);
//        std::cout << "Leftmost:" << " " << xDotsLeft[b] << " " << yDotsLeft[b] << std::endl;
//    }
//    if (!xDotsRight.empty()){
//        std::vector<double> Rightmost = Ro(A, B, xDotsRight, yDotsRight);
//        int c = findI(Rightmost);
//        std::cout << "Rightmost:" << " " << xDotsRight[c] << " " << yDotsRight[c] << std::endl;
//    }
//
//    int a = 0;
//    if (xDotsLeft.empty()){
//        std::cout << "Leftmost:" << " "<< a << a << std::endl;
//    }
//    if (xDotsRight.empty()){
//        std::cout << "Rightmost:" << " " << a << a << std::endl;
//    }
//
//    return 0;
//}