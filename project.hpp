#ifndef PROJECT_H
#define PROJECT_H

/**
 * Functional requisites:
 * 1. random access operator +
 * 2. add to add new values to the set +
 * 3. remove to remove values from the set +
 * 4. const iterators +
 * 5. set constructor from iterators +
 * 6. toString operator +
 * 7. filtering function
 * 8. set concatenation +
 */

#include <ostream>
#include <algorithm> //std::swap
#include <iterator>  // std::forward_iterator_tag
#include <cstddef>   // std::ptrdiff_t

template <typename T, typename Eql>
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

    Eql _equal; ///< generic equal functor to compare T values

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
        // handling excpetion of new operator inside add
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

    /**
    * Getter size
    */
    unsigned int size(void) const
    {
        return _size;
    } // end of size getter

    // functional requisites

    /**
    * Random access operator
    * @param n position of element to access
    */
    const T &operator[](int n) const
    {

        node *tmp = _head;

        // out of bound
        if (n >= _size)
        {
            throw std::runtime_error("");
        }

        // iterating until access position
        for (int i = 0; i < n; i++)
        {
            tmp = tmp->next;
        }
        return tmp->value;
    } // end of random access operator

    /**
    * Add element of type T to set
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
        // in "worst" case stopping in last element
        while (tmp->next != NULL && !_equal(tmp->value, value))
        {
            tmp = tmp->next;
        }

        // avoiding duplicates inside set
        if (_equal(tmp->value, value))
        {
            delete n;
            throw std::runtime_error("");
        }

        // adding element at the end of the set
        tmp->next = n;
        // updating size
        _size++;
    } // end of add

    /**
    * Remove element of type T from set
    * @param value value to be removed from the set
    */
    void remove(const T &value)
    {
        node *tmp = _head;  ///< head pointer
        node *prev = _head; ///< previous pointer

        // searchign iteratevely for element
        while (tmp != NULL && !_equal(tmp->value, value))
        {
            prev = tmp;
            tmp = tmp->next;
        }

        // element not found or empty list
        if (tmp == NULL)
        {
            throw std::runtime_error("");
        }

        // element on head
        if (tmp == _head)
        {
            _head = _head->next;
            delete tmp;
            --_size;
            return;
        }

        // element in middle/tale
        if (_equal(tmp->value, value))
        {
            prev->next = tmp->next;
            delete tmp;
            --_size;
            return;
        }

    } // end of remove

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
    } // end of clear

    /**
    * secondary constructor that takes two iterators
    * from another set
    * @param it begin iterator of other set
    * @param ite end iterator of other set
    */
    template <typename IT>
    set(IT it, IT ite) : _head(0), _size(0)
    {
        while(it != ite)
        {
            add(static_cast<T>(*it));
            ++it;
        }
    }// end of iterator constructor

    // const_iterator
    class const_iterator
    {
        /**
         * iterator class definition
         * Set class only allows const iterators
         * Forward iterator implementation
        */

        const node *n; ///< iterator pivot
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;

        const_iterator() : n(NULL) {}

        const_iterator(const const_iterator &other) : n(other.n) {}

        const_iterator &operator=(const const_iterator &other)
        {
            n = other.n;
            return *this;
        }

        ~const_iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const
        {
            // retrieving T value pointed by n
            return n->value;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const
        {
            return &(n->value);
        }

        // Operatore di iterazione post-incremento
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            n = n->next;
            return tmp;
        }

        // Operatore di iterazione pre-incremento
        const_iterator &operator++()
        {
            n = n->next;
            return *this;
        }

        // Uguaglianza
        bool operator==(const const_iterator &other) const
        {
            return n == other.n;
        }

        // Diversita'
        bool operator!=(const const_iterator &other) const
        {
            return n != other.n;
        }

    private:
        //Dati membro

        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class set;

        // Costruttore privato di inizializzazione usato dalla classe container
        // tipicamente nei metodi begin e end
        const_iterator(node *nn) : n(nn) {}

    }; // end of const_iterator

    // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator begin() const
    {
        return const_iterator(_head);
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator end() const
    {
        return const_iterator(NULL);
    }

}; // end of set

/**
    * Set toString
    * @param os ostream to send values to be printed
    * @param s set to be printed
*/
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, const set<T, E> &s)
{
    typename set<T, E>::const_iterator it, ite;
    it = s.begin();
    ite = s.end();

    os << "[";
    while (it != ite)
    {
        os << " " << *it;
        ++it;
    }
    os << " ]";
    return os;
} // end of toString

/**
    * Set concatenation
    * @param left_s left set to be concatenated
    * @aparam right_s right set to be concatenated
*/
template <typename T, typename E>
set<T, E> operator+(const set<T, E> &left_s, const set<T, E> &right_s)
{
    // copy constructing left set
    set<T, E> s(left_s);

    // adding right set values to copied left set
    typename set<T, E>::const_iterator it, ite;
    it = right_s.begin();
    ite = right_s.end();

    // adding right set values to common set
    while (it != ite)
    {
        s.add(*it);
        ++it;
    }

    return s;
} // end of concatenation

/**
    * filtering set with predicate P
    * @param left_s left set to be concatenated
    * @aparam right_s right set to be concatenated
*/
template <typename T, typename E, typename P>
set<T, E> filter_out(const set<T, E> &s, P pred)
{
    set<T, E> tmp(s);
    typename set<T, E>::const_iterator it, ite;
    it = s.begin();
    ite = s.end();

    while(it != ite)
    {
        if(!pred(static_cast<T>(*it)))
        {
            tmp.add(static_cast<T>(*it));
        }
        ++it;
    }

    return tmp;
}// end of filter_out

#endif