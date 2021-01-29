#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <memory>

namespace ft
{
    template<typename T, typename _Alloc = std::allocator<T> >
    class _List_node {
    public:
        _List_node<T>() {
            /* this->_M_data = new T; */
            this->_M_data = _myalloc.allocate(1);
            _myalloc.construct(_M_data, T());
            this->_M_next = this->_M_prev = this;
        }
        _List_node<T>(T data, _List_node<T>* next, _List_node<T>* prev) {
            this->_M_data = _myalloc.allocate(1);
            _myalloc.construct(_M_data, data);
            _M_next = next;
            _M_prev = prev;
        }
        ~_List_node() {
            _myalloc.deallocate(_M_data, 1);
            /* delete _M_data; */
        }
        _List_node<T>(const _List_node<T> & other)
        {
            *this = other;
            return;
        }
        _List_node<T>(const T & other)
        {
            /* this->_M_data = new T(other); */
            this->_M_data = _myalloc.allocate(1);
            _myalloc.construct(_M_data, other);
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
        /* insert this node between */
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
        _Alloc _myalloc;
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

    template<class T>
    class _List_const_iterator {
    private:
        typedef ft::_List_iterator<T>       iterator;
        typedef const ft::_List_node<T>           _Node;
        typedef ft::_List_const_iterator<T>       _Self;
        
    public:
        _List_const_iterator() : _M_node() {}
        _List_const_iterator<T>(const iterator & it) : _M_node(it.getNode()) {}
        _List_const_iterator<T>(_Node* other) : _M_node(other) {}
        ~_List_const_iterator() {}
        void _M_incr() { _M_node = _M_node->getNext(); }
        void _M_decr() { _M_node = _M_node->getPrev(); }
        
        bool operator==(const _List_const_iterator & other) const {
          return _M_node == other._M_node;
        }
        bool operator!=(const _List_const_iterator & other) const {
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
        const _List_node<T>* _M_node;

    };

    template<typename T, typename _Alloc = std::allocator<T> >
    class List {
    public:
        typedef ft::_List_iterator<T>               iterator;
        typedef ft::_List_const_iterator<T>         const_iterator;
        typedef ft::_List_node<T>                   _Node;
        typedef typename _Alloc::template rebind<ft::_List_node<T> >::other allocator;

        List<T>() {
            this->_M_size = 0;
            this->_M_node = _myalloc.allocate(1);
            _myalloc.construct(_M_node, _List_node<T>());
            /* _myalloc.construct(_M_node, _List_node<T>()); */
            /* this->_M_node = new _List_node<T>(); */
        };
        List(const List & other) {
            this->_M_size = 0;
            this->_M_node = _myalloc.allocate(1);
            _myalloc.construct(_M_node, _List_node<T>());
            /* this->_M_node = new _List_node<T>(); */
            for(const_iterator first = other.begin(); first != other.end(); ++first)
                push_back(*first);
        };
        explicit List(std::size_t n, const T & val = T() ) {
            this->_M_size = 0;
            this->_M_node = _myalloc.allocate(1);
            _myalloc.construct(_M_node, _List_node<T>());
            /* this->_M_node = new _List_node<T>(); */
            for(std::size_t i = 0; i < n; i++)
                push_back(val);
        };
        List(iterator first, iterator last) {
            this->_M_size = 0;
            this->_M_node = _myalloc.allocate(1);
            _myalloc.construct(_M_node, _List_node<T>());
            /* this->_M_node = new _List_node<T>(); */
            for (; first != last; ++first)
                push_back(*first);
        };
        /* template <class InputIterator> */
        /* List(InputIterator first, InputIterator last) { */
        /*     this->_M_size = 0; */
        /*     this->_M_node = new _List_node<T>(); */
        /*     for (; first != last; ++first) */
        /*         push_back(*first); */
        /* }; */
        ~List() {
            _Node* current = _M_node->getNext();
            while (current != _M_node)
            {
                _Node* tmp = current;
                current = current->getNext();
                _myalloc.deallocate(tmp, 1);
                /* delete tmp; */
            }
            _myalloc.deallocate(_M_node, 1);
            /* delete _M_node; */
        };
        List & operator=(const List & other);
        void _M_inc_size(size_t __n) { _M_size += __n; }
        const_iterator begin() const { 
            return const_iterator(this->_M_node->getNext());
        }
        const_iterator end() const {
            return const_iterator(this->_M_node);
        }
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
        _Node* _M_create_node(const T & val)
        {
            _List_node<T>* node;
            node = _myalloc.allocate(1);
            _myalloc.construct(node, val);
            return node;
            /* return new _List_node<T>(__x); */
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
        _List_node<T>*  _M_node;
        std::size_t     _M_size;
        allocator       _myalloc;
    };
}

#endif
