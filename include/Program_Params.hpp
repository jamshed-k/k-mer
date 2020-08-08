
#ifndef PROGRAM_PARAMS_HPP
#define PROGRAM_PARAMS_HPP



#include <string>


class Program_Params
{
private:

    const std::string ref_file_name_;
    const uint16_t k_;


public:

    Program_Params(const std::string& ref_file_name, const uint16_t k);

    const std::string& ref_file_name() const;

    uint16_t k() const;
};


inline Program_Params::Program_Params(const std::string& ref_file_name, const uint16_t k):
    ref_file_name_(ref_file_name), k_(k)
{}


inline const std::string& Program_Params::ref_file_name() const
{
    return ref_file_name_;
}


inline uint16_t Program_Params::k() const
{
    return k_;
}



#endif