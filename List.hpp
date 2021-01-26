#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <memory>

namespace ft
{
    template<typename T>
    class _List_node {
    public:
        _List_node<T>() {
            this->_M_data = new T;
            this->_M_next = this->_M_prev = this;
        }
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
        _List_node<T>(const T & other)
        {
            this->_M_data = new T(other);
            this->_M_next = this->_M_prev = this;
        }
        T& getData() const { return *_M_data; }
        _List_node* getNext() const { return _M_next; }
        _List_node* getPrev() const { return _M_prev; }
        _List_node & operator=(const _List_node & other) {
            if (this == &other)
                return *this;
            this->_M_data = new T(other.getData());
            this->_M_next = other.getNext();
            this->_M_prev = other.getPrev();
            return *this;
        }
        /* insert this node before __position node */
        void _M_hook(_List_node* const __position) {
            this->_M_next = __position;
            this->_M_prev = __position->getPrev();
            __position->_M_prev->_M_next = this;
            __position->_M_prev = this;
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
        _List_iterator<T>(const iterator & it) : _M_node(it.getNode()) {}
        _List_iterator<T>(_Node* other) : _M_node(other) {}
        ~_List_iterator() {}
        void _M_incr() { _M_node = _M_node->getNext(); }
        void _M_decr() { _M_node = _M_node->getPrev(); }
        
        bool operator==(const _List_iterator & other) const {
          return _M_node == other._M_node;
        }
        bool operator!=(const _List_iterator & other) const {
          return _M_node != other._M_node;
        }
        T & operator*() const { 
            return _M_node->getData(); 
        }
        T * operator->() const {
            return _M_node->getData();
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

    /* template<typename T, typename _Alloc = std::allocator<T> > */
    template<typename T>
    class List {
    public:
        typedef ft::_List_iterator<T>               iterator;
        typedef ft::_List_node<T>                   _Node;
        /* typedef _Alloc                              allocator_type; */

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
        void _M_inc_size(size_t __n) { _M_size += __n; }
        iterator begin() { 
            return iterator(this->_M_node->getNext());
        }
        iterator end() {
            return iterator(this->_M_node);
        }
        size_t max_size() const { return size_t(-1); }
        bool empty() const { return _M_node->_M_next == _M_node; }
        size_t size() const { 
            iterator ptr(begin());
            int n = 0;
            while(ptr != end())
            {
                ++ptr;
                ++n;
            }
            return n; 
        }
        T& front() {
            return *begin();
        }
        T& back() {
            iterator tmp = end();
            --tmp;
            return *tmp;
        }
        _Node* _M_create_node(const T & __x)
        {
          return new _List_node<T>(__x);
        }
        void _M_insert(iterator __position, const T & __x) {
          _Node* tmp = _M_create_node(__x);
          tmp->_M_hook(__position.getNode());
          this->_M_inc_size(1);
        }
        void push_back(const T & val) {
            this->_M_insert(end(), val);
        }

    private:
        _List_node<T>* _M_node;
        std::size_t _M_size;
    };
}

#endif
