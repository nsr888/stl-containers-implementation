#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <memory>

namespace ft
{
    template<typename T>
    class _List_node {
    public:
        _List_node<T>(): _M_data(0), _M_next(0), _M_prev(0) {}
        _List_node<T>(T data, _List_node<T>* next, _List_node<T>* prev)
            : _M_data(new T(data))
            , _M_next(next)
            , _M_prev(prev) {}
        ~_List_node() {
            delete _M_data;
        }
        _List_node<T>(const _List_node<T> & other)
        {
            *this = other;
            return;
        }
        T& getData() const { return *_M_data; }
        _List_node* getNext() const { return _M_next; }
        _List_node* getPrev() const { return _M_prev; }
        void setNext(_List_node<T> other) {
            _M_next = &other;
            return;
        }
        _List_node & operator=(const _List_node & other) {
            if (this == &other)
                return *this;
            this->_M_data = new T(other.getData());
            this->_M_next = other.getNext();
            this->_M_prev = other.getPrev();
            return *this;
        }

    private:
        T* _M_data;
        _List_node<T>* _M_next;
        _List_node<T>* _M_prev;
    };

    template<class T>
    class _List_iterator {
    private:
        typedef ft::_List_iterator<T>       iterator;
        typedef ft::_List_node<T>           _Node;
        typedef ft::_List_iterator<T>       _Self;
        
    public:
        _List_iterator() : _M_node() {}
        /* explicit _List_iterator<T>(const iterator & it) : _M_node(it.getNode()) {} */
        /* explicit _List_iterator<T>(_Node __x) : _M_node(__x) {} */
        ~_List_iterator() {}
        void _M_incr() { _M_node = _M_node->_M_next; }
        void _M_decr() { _M_node = _M_node->_M_prev; }
        
        bool operator==(const _List_iterator & other) const {
          return _M_node == other._M_node;
        }
        bool operator!=(const _List_iterator & other) const {
          return _M_node != other._M_node;
        }
        T & operator*() const { 
            return *static_cast<_Node*>(_M_node)->_M_data; 
        }
        T * operator->() const {
            return static_cast<_Node*>(_M_node)->_M_data;
        }
        _Self & operator++() { 
          this->_M_incr();
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          this->_M_incr();
          return __tmp;
        }
        _Self & operator--() { 
          this->_M_decr();
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          this->_M_decr();
          return __tmp;
        }
        _List_node<T>* getNode() const { return _M_node; }

    private:
        _List_node<T>* _M_node;

    };

    template<class T>
    class List {
    public:
        /* typedef ft::_List_iterator<T>               iterator; */
        /* typedef ft::_List_node<T>                   _Node; */

        List<T>() {
            this->_M_node = new _List_node<T>();
            this->_M_size = 0;
        };
        /* List<T>(size_t n, const T & val) { */
        /*     insert(begin(), n, val); */
        /* }; */
        ~List() {
            delete _M_node;
        };
        List(const List & other);
        List & operator=(const List & other);
        /* iterator begin() { */ 
        /*     return iterator(this->_M_next); */
        /* } */
        /* iterator end() { */
        /*     _Node tmp(_M_node); */
        /*     while(tmp) */
        /*         tmp = tmp.getNext(); */
        /*     return iterator(tmp); */
        /* } */
        /* size_t max_size() const { return size_t(-1); } */
        /* bool empty() const { return _M_node->_M_next == _M_node; } */
        /* size_t size() const { */ 
        /*     iterator ptr(begin()); */
        /*     int n = 0; */
        /*     while(ptr != end()) */
        /*     { */
        /*         ++ptr; */
        /*         ++n; */
        /*     } */
        /*     return n; */ 
        /* } */
        T& front() {
            _List_node<T>* tmp = _M_node;
            while (_M_node->getNext())
            {
                std::cout << 1 << std::endl;
                _M_node = _M_node->getNext();
            }
            T& data = _M_node->getData();
            _M_node = tmp;
            return data;
        }
        T& back() {
            return _M_node->getData();
        }
        void push_back(const T & val) {
            _List_node<T>* tmp = _M_node;
            while (_M_node->getNext())
                _M_node = _M_node->getNext();
            _M_node->setNext(_List_node<T>(val, 0, tmp)); 
            _M_node = tmp;
        }

    private:
        _List_node<T>* _M_node;
        std::size_t _M_size;
    };
}

#endif
