
#include "Algorithm.hpp"

#include <cstdlib>
#include <iostream>


int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: k-mer <ref_file>\n";
        return EXIT_FAILURE;
    }


    constexpr uint16_t K = 101;
    const std::string ref_file_name(argv[1]);

    Algorithm<K> algorithm(ref_file_name);

    algorithm.process();


    return EXIT_SUCCESS;
}
