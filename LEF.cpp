#include "LEF.hpp"

std::mt19937 mt(12345678);
std::uniform_real_distribution<> rand01(0,1);

LEFs::LEF::LEF(){
    average_velocity = 1.0;
    tau = 1e5;
    moving_probability = 1.0;
}

LEFs::LEFs(size_t arg_monomer_num,size_t arg_LEF_num,double arg_dt){
    monomer_num = arg_monomer_num;
    LEF_num = arg_LEF_num;
    if (monomer_num < 2*LEF_num) {
        std::cout << "too many LEFs on polymer\n";
        std::exit(1);
    }
    dt = arg_dt;
    is_occupied.resize(monomer_num);
    for (size_t idx = 0; idx < monomer_num; idx++) {
        is_occupied[idx] = false;
    }
    //TO DO  ary random initiation
    //here, place LEFs at equal intervals in ary
    LEF_ary.resize(LEF_num);
    for (size_t idx = 0; idx < LEF_num; idx++) {
        LEF_ary[idx].head1_progress = 0;
        LEF_ary[idx].head2_progress = 0;
    }
    size_t LEF_interval = monomer_num/LEF_num;
    LEF_ary[0].head1 = 0;
    is_occupied[LEF_ary[0].head1] = true;
    LEF_ary[0].head2 = 1;
    is_occupied[LEF_ary[0].head2] = true;
    for (size_t idx = 1; idx < LEF_num; idx++) {
        LEF_ary[idx].head1 = LEF_ary[idx-1].head1 + LEF_interval;
        is_occupied[LEF_ary[idx].head1] = true;
        LEF_ary[idx].head2 = LEF_ary[idx].head1 + 1;
        is_occupied[LEF_ary[idx].head2] = true;
    }
    /*
    //debug
    for (size_t idx = 0; idx < LEF_num; idx++) {
        std::cout << LEF_ary[idx].head1 << " : " << LEF_ary[idx].head2 << "\n";
    }
    */
}

void LEFs::update(){
    for (size_t idx = 0; idx < LEF_num; idx++) {
        if (LEF_ary[idx].head1 != 0 && !is_occupied[LEF_ary[idx].head1-1]) {
            LEF_ary[idx].head1_progress += LEF_ary[idx].average_velocity
                                            * LEF_ary[idx].moving_probability
                                            * dt;
            if (LEF_ary[idx].head1_progress >= 1) {
                is_occupied[LEF_ary[idx].head1] = false;
                LEF_ary[idx].head1--;
                is_occupied[LEF_ary[idx].head1] = true;
                LEF_ary[idx].head1_progress = 0;
            }
        }

        if (LEF_ary[idx].head2 != monomer_num-1 &&
             !is_occupied[LEF_ary[idx].head2+1]) {
            LEF_ary[idx].head2_progress += LEF_ary[idx].average_velocity 
                                            * LEF_ary[idx].moving_probability
                                            * dt;
            if (LEF_ary[idx].head2_progress >= 1) {
                is_occupied[LEF_ary[idx].head2] = false;
                LEF_ary[idx].head2++;
                is_occupied[LEF_ary[idx].head2] = true;
                LEF_ary[idx].head2_progress = 0;
            }
        }

        if ((1.0/LEF_ary[idx].tau)*dt > rand01(mt)) {
            is_occupied[LEF_ary[idx].head1] = false;
            is_occupied[LEF_ary[idx].head2] = false;

            std::vector<size_t> can_rebind;
            for (size_t cr_idx = 0; cr_idx < monomer_num-1; cr_idx++) {
                if (!is_occupied[cr_idx] && !is_occupied[cr_idx+1]) {
                    can_rebind.push_back(cr_idx);
                }
            }

            if (can_rebind.size() == 0) {
                is_occupied[LEF_ary[idx].head1] = true;
                is_occupied[LEF_ary[idx].head2] = true;
            } else {
                LEF_ary[idx].head1_progress = 0;
                LEF_ary[idx].head2_progress = 0;
                std::uniform_int_distribution<> rand_rebind_sight
                                                (0,can_rebind.size()-1);
                size_t rebind_sight = rand_rebind_sight(mt);
                LEF_ary[idx].head1 = can_rebind[rebind_sight];
                LEF_ary[idx].head2 = can_rebind[rebind_sight]+1;
                is_occupied[LEF_ary[idx].head1] = true;
                is_occupied[LEF_ary[idx].head2] = true;
            }
        }
    }
}

void LEFs::make_circle(std::ofstream &of,size_t index) {
    for (int itr = 0; itr < 1000; itr++) {
        double center = static_cast<double>(LEF_ary[index].head1 +
        LEF_ary[index].head2)/2.0;
        double half = static_cast<double>(LEF_ary[index].head2) - center;
        of << center + half * std::cos(M_PI*(static_cast<double>(itr)/1000)) << ' '
            << half * std::sin(M_PI*(static_cast<double>(itr)/1000)) << "\n";
    }
}

void LEFs::save_state(std::ofstream &of) {
    for (size_t idx = 0; idx < LEF_num; idx++) {
        make_circle(of,idx);
    }
}
