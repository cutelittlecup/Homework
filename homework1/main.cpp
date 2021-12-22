#include <iostream>
#include <fstream> // для чтения файлов
#include <cmath> //для корней

int main() {

    double Rightmost_x = 0, Rightmost_y = 0;
    double Leftmost_x = 0, Leftmost_y = 0;
    double roLastR = 0, roLastL = 0;

    std::string path = "in.txt";
    std::ifstream DotsFile;
    DotsFile.open(path);

    if (DotsFile.is_open()) {

        double A, B; // A - коэффициент при y, B - при x: Ax-By=0
        double x_i, y_i;
        double ro;

        DotsFile >> B >> A;
//
//        std::cout << "A: "<< A << std::endl;
//        std::cout << "B: "<< B << std::endl;


        while (!DotsFile.eof()) {

            DotsFile >> x_i >> y_i;

            ro = fabs( B * y_i - A * x_i) / sqrt(A * A + B * B);
            ro = round(ro*10000)/10000;
//            std::cout << "ro: "<< ro << std::endl;
//            std::cout << "rolastR: "<< roLastR << std::endl;
//            std::cout << "rolastL: "<< roLastL << std::endl;


            if (A*x_i - B * y_i >= 0) {

//                std::cout << "right dot: "<< x_i << " " << y_i << std::endl;

                if (ro >= roLastR) {

                    Rightmost_x = x_i;
                    Rightmost_y = y_i;
//                    std::cout << "Rightmost:" << " "<< Rightmost_x << " " << Rightmost_y << std::endl;
                    roLastR = ro;
                }


            } else {

                if (ro >= roLastL) {
//                    std::cout << "left dot: "<< x_i << " " << y_i << std::endl;
                    Leftmost_x = x_i;
                    Leftmost_y = y_i;
//                    std::cout << "Leftmost:" << " "<< Leftmost_x << " " << Leftmost_y << std::endl;
                    roLastL = ro;

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

