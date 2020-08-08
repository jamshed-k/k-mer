
#include "Algorithm.hpp"
#include "Application.hpp"
#include "Program_Params.hpp"

#include <cstdlib>
#include <iostream>


int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: k-mer <ref_file> <k>\n";
        return EXIT_FAILURE;
    }

    
    constexpr uint16_t MAX_K = 512;

    const std::string ref_file_name(argv[1]);
    const uint16_t k(atoi(argv[2]));

    const Program_Params params(ref_file_name, k);
    Application<MAX_K> app(params);

    app.execute();


    return EXIT_SUCCESS;
}
