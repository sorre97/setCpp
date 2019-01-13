#include <iostream>
#include <cassert>
#include "project.h"

void base_test(void)
{
    typedef set<int> set_int;
    bool exception = false;

    // default constructor + size
    set_int s;
    assert(s.size() == 0);
    
    // add
    s.add(5);
    s.add(7);
    s.add(20);
    // duplicate add
    try
    {
        s.add(7);
    }
    catch(std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    
    // random access
    assert(s[0] == 5);
    assert(s[1] == 7);
    assert(s[2] == 20);
    // out of bound access
    exception = false;
    try
    {
        int n = s[3];
    }
    catch(std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
}

int main(int argc, char const *argv[])
{
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit); // enables exeptions
    base_test();
    return 0;
}