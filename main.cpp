#include <iostream>
#include <iomanip>
#include <sstream>
#include "LEF.hpp"

int main(){
    LEFs test(6e4,4e2,1e-2);
    long loop_num = 1e9;
    long loop_per_progress = loop_num/100;
    long loop_per_save = loop_num/10000;
    long file_number = 0;
    for (long loop = 0; loop < loop_num; loop++) {
        test.update();
        if (loop%(loop_per_progress/10) == 0) {
            std::cout << static_cast<double>(loop)/loop_per_progress << "\n";
        }
        if (loop%loop_per_save == 0) {
            std::stringstream file_name;
            file_name << "files/file"
            << std::setw(5) << std::setfill('0') << file_number
            << ".txt";
            std::ofstream of(file_name.str());
            test.save_state(of);
            file_number++;
        }
    }
    return 0;
}
