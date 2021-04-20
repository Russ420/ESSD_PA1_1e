#include "src/system.h"

/*****************************************************
Compiling: make part#.out 

e.g.       make part1.out 
           make part2.out 
           make part3_fifo.out 
           make part3_rr.out 

Execute	: ./part#.out <Input file>

e.g.      ./part1.out ./input/part1_Input.txt 
          ./part2.out ./input/part2_Input_10.txt
          ./part2.out ./input/part2_Input_20.txt
          sudo ./part3_fifo.out ./input/part3_Input.txt 
          sudo ./part3_rr.out ./input/part3_Input.txt 
******************************************************/

int main(int argc, char** argv)
{
    System sys( argv[1] );
    sys.singleCoreMatrixMulti(); // Single thread matrix multiplication


#if (PART == 1)
    /* Part1 */
    sys.globalMultiCoreMatrixMulti(); // Global multi-thread matrix multiplicaiton
    sys.partitionMultiCoreMatrixMulti(); // Partition multi-thread matrix multiplication
#else
    /* Part2 and Part3 */
    sys.partitionFirstFit(); // Partition first-fit matrix multiplication
    sys.partitionBestFit(); // Partititon best-fit matrix multiplication
    sys.partitionWorstFit(); // Partition worst-fit matrix multiplication
#endif

    return 0;
}
