// Hellow World.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <string> //String vs string view is string view is cheaper but read only
#include <algorithm>
#include "A.h"
void local_variables(); //Forward declaration so main can see it despite written after
void variable_shadowing();
void lambda();
int repeat(int i, const auto& fn);
void lambdas_20_6();

/*
learncpp 20.6
*/
struct Student {
    std::string name;
    int points;
};
struct Season
{
    std::string_view name{};
    double averageTemperature{};
};



int main()
{
    bool x{};
    std::cout << sizeof(x);
}

void sort_20_6() {
    std::array<Season, 4> seasons{
    { { "Spring", 285.0 },
      { "Summer", 296.0 },
      { "Fall", 288.0 },
      { "Winter", 263.0 } }
    };

    /*
    * https://en.cppreference.com/cpp/algorithm/sort
     * std::sort(s.begin(), s.end(), [](int a, int b)
        {
            return a > b;
        });
     */
    std::sort(seasons.begin(), seasons.end(), [](Season a, Season b) {return a.averageTemperature < b.averageTemperature;});
    for (const auto& season : seasons)
    {
        std::cout << season.name << '\n';
    }
}
void lambdas_20_6() {
    std::array<Student, 8> arr{
      { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };
    auto maxStudent = std::max_element(arr.begin(), arr.end(), [](Student i, Student j) { return i.points < j.points;});
    /*
    * https://en.cppreference.com/cpp/algorithm/max_element
    * result = std::max_element(v.begin(), v.end(), [](int a, int b)
    {
        return std::abs(a) < std::abs(b);
    });
    */
    std::cout << maxStudent->name << " is the best student";
}
/*
Exercise from learncpp.com 7.3
Variable shadowing is interesting as well 7.5
*/
void local_variables() {
    std::cout << "Please enter two numbers" << std::endl;
    int smaller{};
    int larger{};
    std::cin >> smaller >> larger;
    if (smaller > larger) {
        int temp{ smaller };
        smaller = larger;
        larger = temp;
    } //temp dies here, interesting
    //std::cout << temp; is undefined because temp dies outside of the scope
    std::cout << "Smaller: " << smaller << "Larger: " << larger << std::endl;
}

void variable_shadowing() {
    int value{ 7 };
    {
        int value{ 3 };
        std::cout << value << std::endl;
    }
    std::cout << value << std::endl;
}

/*
If a function name is shared in different files, even if header files are separate, we receive linker error
*/
/*
2.9: std is just the name of the namespace that contains cout, this avoids
name collisions if we want to implement our own cout() function
rarely do we want to use using namespace X because that essentially
merges our namespaces and provides the collisions back without clarity of namespaces
*/
void test() {
    Foo::doSomething();
    namespace Active = Foo; //points a namespace to another so if we migrate content away from Foo, we can redeclare
    Active::doSomething();
    
}
/*
Lambdas act as subfunctions similar to python. We can't do nested functions in c++ so 
lambdas are more important. Also, this avoids potential namespace collisions
use lambdas for oneoff functions
*/

void lambda() {
    //Define isEven lambda that checks if given i is even
    //lambdas are functors
    auto isEven{
        [](int i)
        {
            return (i % 2) == 0;
        }
    };
    std::cout << repeat(3, isEven);
    
}

int repeat(int i, const auto& fn) {
    return fn(i);
}