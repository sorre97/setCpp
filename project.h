#ifndef PROJECT_H
#define PROJECT_H

#include <ostream>
#include <algorithm>

template <typename T>
class set
{
    /**
    * Data structure that contains general data of type T
    * and do not accept repetitions
    */

  private:
    // struct declaration
    struct node
    {
        T value;    ///< generic data stored inside set
        node *next; ///< pointing to next node in the set

        // default constructor
        node(void) : next(0){};

        // secondary constructor
        node(const T &v, node *n = NULL) : value(v), next(n){};
    };

    node *_head;        ///< node pointing to head of the set
    unsigned int _size; ///< size of the set

  public:
    // basic methods

    /**
     * Default constructor
    */
    set(void) : _head(NULL), _size(0){};

    /**
     * Copy constructor
     * initialization list to avoid unconsistent state
     * @param other set to be copied
    */
    set(const set &other) : _head(0), _size(0)
    {
        // saving head to scan other set
        node *tmp = other._head;
        // handling new excpetion inside add
        try
        {
            // scanning over other set
            while (tmp != NULL)
            {
                // adding value to actual set
                add(tmp->value);
                // moving to next node in set
                tmp = tmp->next;
            }
        }
        catch (...)
        {
            clear();
        }
    } // end of copy constructor

    /**
    * Assignment operator
    * @param other set to be assigned
    */
    set &operator=(const set &other)
    {
        if (&other != this)
        {
            // swapping local set to actual set each member individually
            set tmp(other);
            std::swap(_head, tmp._head);
            std::swap(_size, tmp._size);
        }
        return *this;
    } // end of assignment operator

    /**
    * Distructor
    */
    ~set(void)
    {
        clear();
    } // end of distructor

    // functional requisites

    /**
    * Random access operator
    * @param n position of element to access
    */
    const T &operator[](int n) const
    {
        node *tmp = _head;

        // iterating until access position
        for (int i = 0; i < n && tmp->next!= NULL; i++)
        {
            // out of bound access
            if (tmp == NULL)
            {
                throw std::runtime_error("");
            }
            /* TODO CREATING PROBLEM
            * MOVING TO NULL */
            tmp = tmp->next;
        }
        return tmp->value;
    }

    /**
    * Adding element of type T to set
    * @param value value to be added to set
    */
    void add(const T &value)
    {
        // creating new node containing value of type T
        node *n = new node(value);
        // empty set case
        if (_head == NULL)
        {
            _head = n;
            _size = 1;
            return;
        }

        // general case
        node *tmp = _head;
        // iterating up to last element in set
        while (tmp->next != NULL && tmp->value != value)
        {
            tmp = tmp->next;
        }
        
        // avoiding duplicates inside set
        if (tmp->value == value)
        {
            delete n;
            throw std::runtime_error("");
        }

        // adding element at the end of the set
        tmp->next = n;
        // updating size
        _size++;
    }

    /**
    * Getter size
    */
    unsigned int size() const
    {
        return _size;
    }

    /**
    * Clear set from all values
    * @param other set to be assigned
    */
    void clear(void)
    {
        // using tmp to iterate over set
        node *tmp = _head;
        while (tmp != NULL)
        {
            // saving next of tmp to proceed forward after delete
            node *next = tmp->next;
            delete tmp;
            // moving forward to next node;
            tmp = next;
        }

        _head = NULL;
        _size = 0;
    }
}; // end of set

/**
    * Set toString
    * @param os ostream to send values to be printed
    * @param s set to be printed
*/
template <typename T>
std::ostream &operator<<(std::ostream &os, const set<T> &s)
{
    /* TODO */
}

#endif