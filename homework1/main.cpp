#include <iostream>
#include <fstream> // для чтения файлов
#include <cmath> //для корней

int main() {

    double Rightmost_x = 0, Rightmost_y = 0;
    double Leftmost_x = 0, Leftmost_y = 0;
    double roLastR, roLastL = 0;

    std::string path = "in.txt";
    std::ifstream DotsFile;
    DotsFile.open(path);

    if (DotsFile.is_open()) {

        double A, B;
        double x_i, y_i;
        double ro;

        DotsFile >> A >> B;

//        std::cout << A << std::endl;
//        std::cout << B << std::endl;

        while (!DotsFile.eof()) {

            DotsFile >> x_i >> y_i;

            ro = (A * x_i + B * y_i) / sqrt(A*A + B*B);
            ro = round(ro*10000)/10000;
//            std::cout << ro << std::endl;

            if (A*y_i <= B*x_i) {

                if (ro >= roLastR) {

                    Rightmost_x = x_i;
                    Rightmost_y = y_i;
                    roLastR = ro;
                }


            } else {

                if (ro >= roLastL) {

                    Leftmost_x = x_i;
                    Leftmost_y = y_i;
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

