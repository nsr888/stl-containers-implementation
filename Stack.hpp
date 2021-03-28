#ifndef STACK_HPP
# define STACK_HPP
# include "List.hpp"

namespace ft
{
    template <class T, class Container = List<T> >
    class Stack {
        typedef T               value_type;
        typedef Container       container_type;
        typedef size_t          size_type;

    protected:
        container_type      _c;

    public:
        explicit Stack (const container_type& ctnr = container_type())
            :_c(ctnr) { };

        ~Stack() {};

        Stack(const Stack & other) 
        {
            *this = other;
        }
        
        Stack & operator=(const Stack & other) 
        {
            this->_c = other->_c;
            return *this;
        }
        
        bool empty() const { return _c.empty(); }

        void pop() { return _c.pop_back(); }

        void push (const value_type& val) { return _c.push_back(val);}

        size_type size() const { return _c.size(); }

        value_type& top() { return _c.back(); }

        const value_type& top() const { return _c.back(); }

        /* https://stackoverflow.com/questions/17021447/relational-operators-on-a-class-template */
        friend bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
        {
            return lhs._c == rhs._c;
        }

        friend bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
        {
            return lhs._c != rhs._c;
        }

        friend bool operator< (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
        {
            return lhs._c < rhs._c;
        }

        friend bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
        {
            return lhs._c <= rhs._c;
        }

        friend bool operator> (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
        {
            return lhs._c > rhs._c;
        }

        friend bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
        {
            return lhs._c >= rhs._c;
        }
    };
}
#endif
