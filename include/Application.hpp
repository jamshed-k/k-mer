
#ifndef APPLICATION_HPP
#define APPLICATION_HPP



#include "Algorithm.hpp"
#include "Program_Params.hpp"


template <uint16_t k>
class Application
{
private:

    // Pointer to an application instance of the next `Application` class in the top-down hierarchy (on `k`).
    Application<k - 1>* app_next_level;

    // Pointer to an algorithm instance operating on `k` value of this class.
    Algorithm<k>* algorithm;


public:

    Application(const Program_Params& params);

    ~Application();

    void execute() const;
};



// Specialization of the template class for the lowest k-value (`k = 1`).
template <>
class Application<1>
{
private:

    // Pointer to an algorithm instance operating with `k = 1`.
    Algorithm<1>* algorithm;


public:

    Application(const Program_Params& params):
        algorithm(params.k() == 1 ? new Algorithm<1>(params) : nullptr)
    {}

    ~Application()
    {
        if(algorithm != nullptr)
            delete algorithm;
    }

    void execute() const
    {
        if(algorithm != nullptr)
            algorithm->execute();
    }
};



template <uint16_t k>
inline Application<k>::Application(const Program_Params& params):
    app_next_level(new Application<k - 1>(params)),
    algorithm(params.k() == k ? new Algorithm<k>(params) : nullptr)
{}


template <uint16_t k>
inline Application<k>::~Application()
{
    delete app_next_level;

    if(algorithm != nullptr)
        delete algorithm;
}


template <uint16_t k>
inline void Application<k>::execute() const
{
    if(algorithm != nullptr)
        algorithm->execute();
    else
        app_next_level->execute();
}



#endif
