#ifndef QUEUE_HPP
# define QUEUE_HPP
# include "List.hpp"

namespace ft
{
    template <class T, class Container = List<T> >
    class Queue {
        typedef T               value_type;
        typedef Container       container_type;
        typedef size_t          size_type;

    protected:
        container_type      _c;

    public:
        explicit Queue (const container_type& ctnr = container_type())
            :_c(ctnr) { };

        ~Queue() {};

        Queue(const Queue & other) 
        {
            *this = other;
        }
        
        Queue & operator=(const Queue & other) 
        {
            this->_c = other->_c;
            return *this;
        }
        
        bool empty() const { return _c.empty(); }

        void pop() { return _c.pop_back(); }

        void push (const value_type& val) { return _c.push_back(val);}

        size_type size() const { return _c.size(); }

        value_type& back() { return _c.back(); }

        const value_type& back() const { return _c.back(); }

        value_type& front() { return _c.front(); }

        const value_type& front() const { return _c.front(); }

        /* https://stackoverflow.com/questions/17021447/relational-operators-on-a-class-template */
        friend bool operator== (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
        {
            return lhs._c == rhs._c;
        }

        friend bool operator!= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
        {
            return lhs._c != rhs._c;
        }

        friend bool operator< (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
        {
            return lhs._c < rhs._c;
        }

        friend bool operator<= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
        {
            return lhs._c <= rhs._c;
        }

        friend bool operator> (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
        {
            return lhs._c > rhs._c;
        }

        friend bool operator>= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
        {
            return lhs._c >= rhs._c;
        }
    };
}
#endif
