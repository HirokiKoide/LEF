# LEF
Implementation of "Chromosome Compaction by Active Loop Extusion"

These codes are an implementation of "Chromosome Compaction by Active Loop Extusion" (https://doi.org/10.1016/j.bpj.2016.02.041).

## LEF.hpp

definition of the interface of the set of LEF.

### public
<strong>save_state(std::ofstream&)</strong> is writing all LEFs as a semicircle into ofs.

### private

#### internal class LEF

This class charactrize LEF. <strong>tau</strong> is dssociation constant. <strong>head*_progress</strong> is used to determine whether or not to move LEF head (if this veriable is more than 1, the head moves and the veriable go to 0).
