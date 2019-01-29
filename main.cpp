// generic c++ includes
#include <iostream>
#include <cassert> // std::swap
#include <stdexcept> //std::runtime_error

//custom includes
#include "project.hpp"  //set
#include <complex> // std::complex



// functors
struct is_odd_int
{
    // int functor
    bool operator()(int a) const
    {
        return a % 2 == 0;
    }
} is_odd_int;


struct is_major_complex_double
{
    // int functor
    bool operator()(const std::complex<double> &c) const
    {
        return c.real() > c.imag();
    }
} is_major_complex_double;

// complex equal
template <typename T>
struct complex_equal
{
    bool operator()(const std::complex<T> &c1, const std::complex<T> &c2) const
    {
        return c1.real() == c2.real() && c1.imag() == c2.imag();
    }
};


// tests
void primitive_type_tests(void)
{
    /**
     * TESTING with integers:
     *  1. default constructor + getter for size
     *  2. add
     *  3. random access operator
     *  4. copy conctructor
     *  5. assignment operator
     *  6. clear
     *  7. remove
     *  8. const_iterator
     *  9. toString
     * 10. concatenation
     * 11. iterator constructor
     * 12. filter_out
     */

    std::cout << "/**** Primitive type tests ****/" << std::endl;
    // test variables
    typedef set<int, std::equal_to<int> > set_int; ///< typedef to avoid template rewriting
    bool exception = false;                        ///< try catch checker
    set_int::const_iterator it;                    ///< begin iterator
    set_int::const_iterator ite;                   ///< end iterator

    /** 1. default constructor + size **/
    std::cout << "default constructor + size ";
    set_int s;
    assert(s.size() == 0);
    std::cout << " --- OK" << std::endl;

    /** 2. add **/
    std::cout << "add";
    s.add(5);
    s.add(7);
    s.add(20);
    assert(s.size() == 3);
    //duplicate add
    try
    {
        s.add(7);
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    assert(s.size() == 3);
    std::cout << " --- OK" << std::endl;

    /** 3. random access test **/
    std::cout << "random access";
    assert(s[0] == 5);
    assert(s[1] == 7);
    assert(s[2] == 20);
    // out of bound access
    exception = false;
    try
    {
        s[3];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    std::cout << " --- OK" << std::endl;

    /** 4. copy constructor **/
    std::cout << "copy constructor";
    set_int s2(s);
    assert(s2.size() == s.size());
    assert(s2[0] == s[0]);
    assert(s2[1] == s[1]);
    assert(s2[2] == s[2]);
    std::cout << " --- OK" << std::endl;

    /** 5. assignment operator **/
    std::cout << "assignment operator";
    set_int s3 = s2;
    assert(s3.size() == s2.size());
    assert(s3[0] == s2[0]);
    assert(s3[1] == s2[1]);
    assert(s3[2] == s2[2]);
    std::cout << " --- OK" << std::endl;

    /** 6. clear **/
    std::cout << "clear";
    s2.clear();
    assert(s2.size() == 0);
    // no more values inside
    exception = false;
    try
    {
        s2[0];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    std::cout << " --- OK" << std::endl;

    /** 7. remove **/
    std::cout << "remove";
    set_int s4;
    s4.add(1);
    s4.add(3);
    s4.add(6);
    s4.add(2);
    assert(s4.size() == 4);

    // tail removal
    s4.remove(2);
    assert(s4.size() == 3);
    exception = false;
    try
    {
        s4[3];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);

    // no number found
    exception = false;
    try
    {
        s4.remove(50);
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);

    // middle removal
    s4.add(2);
    assert(s4.size() == 4);
    s4.remove(3);
    // shifting linked list
    assert(s4[1] == 6);
    exception = false;
    try
    {
        s4[3];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    s4.add(3);

    // head removal
    //[1 -> 6 -> 2 -> 3]
    s4.remove(1);
    assert(s4[0] == 6);

    s4.remove(6);
    assert(s4[0] == 2);

    // empty set
    s4.remove(2);
    s4.remove(3);
    exception = false;
    try
    {
        s4[0];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    std::cout << " --- OK" << std::endl;

    /** 8. const_iterator **/
    std::cout << "const_iterator";

    set_int s5;
    s5.add(1);
    s5.add(3);
    s5.add(6);
    s5.add(2);

    //begin iterator
    it = s5.begin();
    //end iterator
    ite = s5.end();
    // priting values inside s5 iteratively
    std::cout << " [ ";

    int i = 0;
    while (it != ite)
    {
        assert(*it == s5[i]);
        std::cout << *it << " ";
        ++it;
        ++i;
    }
    std::cout << "]";

    std::cout << " --- OK" << std::endl;

    /** 9. toString **/
    std::cout << "toString ";
    std::cout << s5;
    std::cout << " --- OK" << std::endl;

    /** 10. concatenation **/
    std::cout << "concatenation ";
    set_int s6;
    s6.add(20);
    s6.add(4);
    s6.add(10);
    s6.add(9);

    // s5 = [1 -> 3 -> 6 -> 2]
    // s6 = [20 -> 4 -> 10 -> 9]
    set_int s7 = s5 + s6;
    // asserting s5 copied inside s7
    for (int i = 0; i < s5.size(); i++)
    {
        assert(s7[i] == s5[i]);
    }
    // asserting 26 copied inside s7
    for (int i = s5.size(); i < s6.size(); i++)
    {
        assert(s7[i] == s6[i]);
    }

    // adding two set with equal values
    s6.add(2);
    s7.clear();
    exception = false;
    try
    {
        s7 = s5 + s6;
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    s6.remove(2);

    std::cout << " --- OK" << std::endl;

    /** 11. iterator constructor **/
    std::cout << "iterator constructor ";

    // iterators from s5 + s6
    set_int s9 = s5 + s6;
    it = s9.begin();
    ite = s9.end();

    // iterator constructor
    set_int s8(it, ite);

    // asserting equal values
    for (int i = 0; i < s9.size(); i++)
    {
        assert(s8[i] == s9[i]);
    }

    std::cout << " --- OK" << std::endl;

    /** 12. filter_out **/
    std::cout << "filter_out ";
    set_int s10;

    s10 = filter_out(s8, is_odd_int);

    // asserting equal values
    for (int i = 0; i < s10.size(); i++)
    {
        assert(!is_odd_int(s10[i]));
    }

    std::cout << " --- OK" << std::endl;

    std::cout << "/**** End of primitive type tests ****/" << std::endl << std::endl;
}

void custom_type_tests(void)
{
     /**
     * TESTING with complex:
     *  1. default constructor + getter for size
     *  2. add
     *  3. random access operator
     *  4. copy conctructor
     *  5. assignment operator
     *  6. clear
     *  7. remove
     *  8. const_iterator
     *  9. toString
     * 10. concatenation
     * 11. iterator constructor
     * 12. filter_out
     */

    std::cout << "/****  Custom type tests ****/" << std::endl;

    // test variables
    typedef std::complex<double> complex_double;
    typedef set<complex_double, complex_equal<double> > set_complex_double; ///< typedef to avoid template rewriting
    
    bool exception = false;                           ///< try catch checker
    set_complex_double::const_iterator it;            ///< begin iterator
    set_complex_double::const_iterator ite;           ///< end iterator

    /** 1. default constructor + size **/
    std::cout << "default constructor + size ";
    set_complex_double s;
    assert(s.size() == 0);
    std::cout << " --- OK" << std::endl;

    /** 2. add **/
    std::cout << "add";
    s.add(complex_double(1, 2));
    s.add(complex_double(7, 3));
    s.add(complex_double(20, 10));
    assert(s.size() == 3);

    //duplicate add
    exception = false;
    try
    {
        s.add(complex_double(1, 2));
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    assert(s.size() == 3);
    std::cout << " --- OK" << std::endl;

    /** 3. random access test **/
    std::cout << "random access";
    assert(s[0] == complex_double(1, 2));
    assert(s[1] == complex_double(7, 3));
    assert(s[2] == complex_double(20, 10));
    // out of bound access
    exception = false;
    try
    {
        s[3];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    std::cout << " --- OK" << std::endl;

    /** 4. copy constructor **/
    std::cout << "copy constructor";
    set_complex_double s2(s);
    assert(s2.size() == s.size());
    assert(s2[0] == s[0]);
    assert(s2[1] == s[1]);
    assert(s2[2] == s[2]);
    std::cout << " --- OK" << std::endl;

    /** 5. assignment operator **/
    std::cout << "assignment operator";
    set_complex_double s3 = s2;
    assert(s3.size() == s2.size());
    assert(s3[0] == s2[0]);
    assert(s3[1] == s2[1]);
    assert(s3[2] == s2[2]);
    std::cout << " --- OK" << std::endl;

    /** 6. clear **/
    std::cout << "clear";
    s2.clear();
    assert(s2.size() == 0);
    // no more values inside
    exception = false;
    try
    {
        s2[0];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    std::cout << " --- OK" << std::endl;

    /** 7. remove **/
    std::cout << "remove";
    set_complex_double s4;
    s4.add(complex_double(1, 2));
    s4.add(complex_double(3, 5));
    s4.add(complex_double(6, 7));
    s4.add(complex_double(2, 10));
    assert(s4.size() == 4);

    // tail removal
    s4.remove(complex_double(2, 10));
    assert(s4.size() == 3);
    exception = false;
    try
    {
        s4[3];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);

    // no number found
    exception = false;
    try
    {
        s4.remove(complex_double(100, 100));
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);

    // middle removal
    s4.add(complex_double(2, 10));
    assert(s4.size() == 4);
    s4.remove(complex_double(3, 5));
    // shifting linked list
    assert(s4[1] == complex_double(6, 7));
    exception = false;
    try
    {
        s4[3];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    s4.add(complex_double(3, 5));

    // head removal
    //[(1, 2) -> (6, 7) -> (2, 10) -> (3, 5)]
    s4.remove(complex_double(1, 2));
    assert(s4[0] == complex_double(6, 7));

    s4.remove(complex_double(6, 7));
    assert(s4[0] == complex_double(2, 10));

    // empty set
    s4.remove(complex_double(2, 10));
    s4.remove(complex_double(3, 5));
    exception = false;
    try
    {
        s4[0];
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    std::cout << " --- OK" << std::endl;

    /** 8. const_iterator **/
    std::cout << "const_iterator";

    set_complex_double s5;
    s5.add(complex_double(1, 2));
    s5.add(complex_double(3, 5));
    s5.add(complex_double(6, 7));
    s5.add(complex_double(2, 10));

    //begin iterator
    it = s5.begin();
    //end iterator
    ite = s5.end();
    // priting values inside s5 iteratively
    std::cout << " [ ";

    int i = 0;
    while (it != ite)
    {
        assert(*it == s5[i]);
        std::cout << *it << " ";
        ++it;
        ++i;
    }
    std::cout << "]";

    std::cout << " --- OK" << std::endl;

    /** 9. toString **/
    std::cout << "toString ";
    std::cout << s5;
    std::cout << " --- OK" << std::endl;

    /** 10. concatenation **/
    std::cout << "concatenation ";
    set_complex_double s6;
    s6.add(complex_double(20, 30));
    s6.add(complex_double(4, 7));
    s6.add(complex_double(10, 30));
    s6.add(complex_double(9, 2));

    // s5 = [(1,2) -> (3,5) -> (6,7) -> (2,10)]
    // s6 = [(20,30) -> (4,7) -> (10,30) -> (9,2)]
    set_complex_double s7 = s5 + s6;
    // asserting s5 copied inside s7
    for (int i = 0; i < s5.size(); i++)
    {
        assert(s7[i] == s5[i]);
    }
    // asserting 26 copied inside s7
    for (int i = s5.size(); i < s6.size(); i++)
    {
        assert(s7[i] == s6[i]);
    }

    // adding two set with equal values
    s6.add(complex_double(2, 10));
    s7.clear();
    exception = false;
    try
    {
        s7 = s5 + s6;
    }
    catch (std::runtime_error e)
    {
        exception = true;
    }
    assert(exception == true);
    s6.remove(complex_double(2, 10));

    std::cout << " --- OK" << std::endl;

    /** 11. iterator constructor **/
    std::cout << "iterator constructor ";

    // iterators from s5 + s6
    set_complex_double s9 = s5 + s6;
    it = s9.begin();
    ite = s9.end();

    // iterator constructor
    set_complex_double s8(it, ite);

    // asserting equal values
    for (int i = 0; i < s9.size(); i++)
    {
        assert(s8[i] == s9[i]);
    }

    std::cout << " --- OK" << std::endl;

    /** 12. filter_out **/
    std::cout << "filter_out ";
    set_complex_double s10;

    s10 = filter_out(s8, is_major_complex_double);

    // asserting equal values
    for (int i = 0; i < s10.size(); i++)
    {
        assert(!is_major_complex_double(s10[i]));
    }

    std::cout << " --- OK" << std::endl;

    std::cout << "/****   End of custom type tests ****/" << std::endl << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit); // enables exeptions
    primitive_type_tests();
    custom_type_tests();
    return 0;
}
