#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <cmath>
#include <fstream>

class LEFs{
private:
	class LEF{
	public:
        LEF();
		size_t head1,head2;
		double average_velocity,tau;
        double moving_probability;
        double head1_progress,head2_progress;
	};

	size_t monomer_num,LEF_num;
	double dt;
    std::vector<bool> is_occupied;

    void make_circle(std::ofstream &of,size_t index);
	std::vector<LEF> LEF_ary;
public:
    LEFs(size_t arg_monomer_num,size_t arg_LEF_num,double arg_dt);
	void update();
    void save_state(std::ofstream &of);
};
