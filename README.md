# LEF
Implementation of "Chromosome Compaction by Active Loop Extusion"

These codes are an implementation of "Chromosome Compaction by Active Loop Extusion" (https://doi.org/10.1016/j.bpj.2016.02.041).

## LEF.hpp

### public
#### save_state(std::ofstream&)
write all LEFs as a semicircle into ofs.

### private

#### internal class LEF

This class charactrize LEF. <strong>tau</strong> is dssociation constant. <strong>head*_progress</strong> are used to determine whether or not to move LEF heads (if this veriables are more than 1, the heads move and the veriables go to 0).

#### monomer_num
determine the length of strand.

#### is_occupied
if LEF is at the strand index n, is_occupied[n] is true.

#### make_circle
sub function for <strong>save_state</strong>.

## LEF.cpp

#### constructor
Although in the article LEFs bind at random sight at the begining of simulation, this constractor place LEFs at equal intervals on strand.

#### update
While time gose by dt, <strong>head*_progress</strong> get minute values. if <strong>head*_progress</strong> are more than 1, the LEF heads move and the variables go to 0. 
LEF dissociate at a rate of 1/tau and immediately rebind at random singht.

## main.cpp
The simulation runs for 10 tau and makes 10,000 datafiles.
