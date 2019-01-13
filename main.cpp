// generic c++ includes
#include <iostream>
#include <cassert>  // std::swap

//custom includes
#include "project.h"

void primitive_types_test(void)
{
    /**
     * TESTING with integers:
     * 1. default constructor + getter for size
     * 2. add
     * 3. random access operator
     * 4. copy conctructor
     * 5. assignment operator
     * 6. clear
     */

    typedef set<int, std::equal_to<int> > set_int;   ///< typedef to avoid template rewriting
    bool exception = false;     ///< try catch checker

    /** 1. default constructor + size **/
    set_int s;
    assert(s.size() == 0);
    
    /** 2. add **/
    s.add(5);
    s.add(7);
    s.add(20);
    assert(s.size() == 3);
    //duplicate add
    try
    {
        s.add(7);
    }
    catch(std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    assert(s.size() == 3);
    
    /** 3. random access test **/
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

    /** 4. copy constructor **/
    set_int s2(s);
    assert(s2.size() == s.size());
    assert(s2[0] == s[0]);
    assert(s2[1] == s[1]);
    assert(s2[2] == s[2]);

    /** 5. assignment operator **/
    set_int s3 = s2;
    assert(s3.size() == s2.size());
    assert(s3[0] == s2[0]);
    assert(s3[1] == s2[1]);
    assert(s3[2] == s2[2]);

    /** 6. clear **/
    s3.clear();
    assert(s3.size() == 0);
    // no more values inside
    exception = false;
    try
    {
        int n = s3[0];
    }
    catch(std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
};

int main(int argc, char const *argv[])
{
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit); // enables exeptions
    primitive_types_test();
    return 0;
};