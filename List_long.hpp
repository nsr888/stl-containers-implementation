#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <memory>

namespace ft
{
    struct _List_node_base {
        _List_node_base(): _M_next(0), _M_prev(0) {}
        _List_node_base* _M_next;
        _List_node_base* _M_prev;
    };

    template<typename T>
    struct _List_node: public _List_node_base {
        _List_node(): _List_node_base(), _M_data() {}
        T _M_data;
    };

    struct _List_iterator_base {
        _List_node_base *_M_node;

        _List_iterator_base(_List_node_base* __x) : _M_node(__x) {}
        _List_iterator_base() {}
        
        void _M_incr() { _M_node = _M_node->_M_next; }
        void _M_decr() { _M_node = _M_node->_M_prev; }
        
        bool operator==(const _List_iterator_base& __x) const {
          return _M_node == __x._M_node;
        }
        bool operator!=(const _List_iterator_base& __x) const {
          return _M_node != __x._M_node;
        }
    };

    template<class T>
    struct _List_iterator: public _List_iterator_base {
        typedef _List_iterator<T>       iterator;
        typedef _List_node<T>           _Node;
        typedef _List_iterator<T>       _Self;
        
        _List_iterator(_Node* __x) : _List_iterator_base(__x) {}
        _List_iterator() {}
        _List_iterator(const iterator& __x) : _List_iterator_base(__x._M_node) {}
        T& operator*() const {return *static_cast<_Node*>(_M_node)->_M_data; }
        T* operator->() const { return static_cast<_Node*>(_M_node)->_M_data; }
        _Self& operator++() { 
          this->_M_incr();
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          this->_M_incr();
          return __tmp;
        }
        _Self& operator--() { 
          this->_M_decr();
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          this->_M_decr();
          return __tmp;
        }
    };

    template<class T>
    class List {
    public:
        typedef _List_iterator<T>               iterator;
        typedef _List_node<T>                   _Node;

        List<T>() {};
        /* List<T>(size_t n, const T & val) { */
        /*     insert(begin(), n, val); */
        /* }; */
        ~List() {};
        List(const List & other);
        List & operator=(const List & other);
        iterator begin() const { return static_cast<_Node*>(_M_node->_M_next); }
        iterator end() const { return _M_node; }
        size_t max_size() const { return size_t(-1); }
        bool empty() const { return _M_node->_M_next == _M_node; }
        size_t size() const { 
            iterator ptr;
            int n = 0;
            while(ptr != end())
            {
                ++ptr;
                ++n;
            }
            return n; 
        }

    private:
        _List_node<T>* _M_node;
    };
}

#endif
