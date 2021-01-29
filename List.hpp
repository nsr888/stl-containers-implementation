#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <memory>

namespace ft
{
    template<typename T, typename _Alloc = std::allocator<T> >
    class List_node {
    public:
        List_node<T>() {
            this->_M_data = _myalloc.allocate(1);
            _myalloc.construct(_M_data, T());
            this->_M_next = this->_M_prev = this;
        }
        List_node<T>(T data, List_node<T>* next, List_node<T>* prev) {
            this->_M_data = _myalloc.allocate(1);
            _myalloc.construct(_M_data, data);
            _M_next = next;
            _M_prev = prev;
        }
        ~List_node() {
            _myalloc.deallocate(_M_data, 1);
        }
        List_node<T>(const List_node<T> & other)
        {
            *this = other;
            return;
        }
        List_node<T>(const T & other)
        {
            this->_M_data = _myalloc.allocate(1);
            _myalloc.construct(_M_data, other);
            this->_M_next = this->_M_prev = this;
        }
        T& getData() const { return *_M_data; }
        List_node* getNext() const { return _M_next; }
        List_node* getPrev() const { return _M_prev; }
        List_node & operator=(const List_node & other) {
            if (this == &other)
                return *this;
            this->_M_data = new T(other.getData());
            this->_M_next = other.getNext();
            this->_M_prev = other.getPrev();
            return *this;
        }
        /* insert this node between */
        void _M_hook(List_node* const __position) {
            this->_M_next = __position;
            this->_M_prev = __position->getPrev();
            __position->_M_prev->_M_next = this;
            __position->_M_prev = this;
        }
        /* remove this node between next and prev */
        void _M_unhook() {
            List_node<T>* const next = this->_M_next;
            List_node<T>* const prev = this->_M_prev;
            prev->_M_next = next;
            next->_M_prev = prev;
        }
    private:
        T* _M_data;
        List_node<T>* _M_next;
        List_node<T>* _M_prev;
        _Alloc _myalloc;
    };

    template<class T>
    class List_iterator {
    private:
        typedef ft::List_iterator<T>       iterator;
        typedef ft::List_node<T>           _Node;
        typedef ft::List_iterator<T>       _Self;
        
    public:
        List_iterator() : _M_node() {}
        List_iterator<T>(const iterator & it) : _M_node(it.getNode()) {}
        List_iterator<T>(_Node* other) : _M_node(other) {}
        ~List_iterator() {}
        void _M_incr() { _M_node = _M_node->getNext(); }
        void _M_decr() { _M_node = _M_node->getPrev(); }
        
        _Self & operator=(const List_iterator & other) {
            this->_M_node = other.getNode();
            return *this;
        }
        bool operator==(const List_iterator & other) const {
          return _M_node == other._M_node;
        }
        bool operator!=(const List_iterator & other) const {
          return _M_node != other._M_node;
        }
        _Self _M_const_cast() const { return *this; }
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
        List_node<T>* getNode() const { return _M_node; }

    private:
        List_node<T>* _M_node;

    };

    template<class T>
    class List_const_iterator {
    private:
        typedef ft::List_iterator<T>       iterator;
        typedef const ft::List_node<T>           _Node;
        typedef ft::List_const_iterator<T>       _Self;
        
    public:
        List_const_iterator() : _M_node() {}
        List_const_iterator<T>(const iterator & it) : _M_node(it.getNode()) {}
        List_const_iterator<T>(_Node* other) : _M_node(other) {}
        ~List_const_iterator() {}
        void _M_incr() { _M_node = _M_node->getNext(); }
        void _M_decr() { _M_node = _M_node->getPrev(); }
        
        _Self & operator=(const List_const_iterator & other) {
            this->_M_node = other.getNode();
        }
        bool operator==(const List_const_iterator & other) const {
          return _M_node == other._M_node;
        }
        bool operator!=(const List_const_iterator & other) const {
          return _M_node != other._M_node;
        }
        _Self _M_const_cast() const { return *this; }
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
        List_node<T>* getNode() const { return _M_node; }

    private:
        const List_node<T>* _M_node;

    };

    template<typename T, typename _Alloc = std::allocator<T> >
    class List {
    public:
        typedef ft::List_iterator<T>               iterator;
        typedef ft::List_const_iterator<T>         const_iterator;
        typedef ft::List_node<T>                   _Node;
        typedef typename _Alloc::template rebind<List_node<T> >::other
            node_allocator;

        List<T>() {
            _M_size = 0;
            _M_node = _node_alloc.allocate(1);
            _node_alloc.construct(_M_node, 0);
        };
        List(const List & other) {
            _M_size = 0;
            _M_node = _node_alloc.allocate(1);
            _node_alloc.construct(_M_node, 0);
            for(const_iterator first = other.begin(); first != other.end(); ++first)
                push_back(*first);
        };
        explicit List(std::size_t n, const T & val = T() ) {
            _M_size = 0;
            _M_node = _node_alloc.allocate(1);
            _node_alloc.construct(_M_node, 0);
            for(std::size_t i = 0; i < n; i++)
                push_back(val);
        };
        List(iterator first, iterator last) {
            _M_size = 0;
            _M_node = _node_alloc.allocate(1);
            _node_alloc.construct(_M_node, 0);
            for (; first != last; ++first)
                push_back(*first);
        };
        /* Solution for int overload */
        /* https://stackoverflow.com/questions/37803630/c-function-overloading-alternatives-to-enable-if */
        template <class InputIterator>
        List(InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
            this->_M_size = 0;
            _M_node = _node_alloc.allocate(1);
            _node_alloc.construct(_M_node, 0);
            for (; first != last; ++first)
                push_back(*first);
        };
        ~List() {
            _Node* current = _M_node->getNext();
            while (current != _M_node)
            {
                _Node* tmp = current;
                current = current->getNext();
                _node_alloc.destroy(tmp);
                _node_alloc.deallocate(tmp, 1);
            }
            _node_alloc.destroy(_M_node);
            _node_alloc.deallocate(_M_node, 1);
        };
        List & operator=(const List & other) {
            if (this == &other)
                return *this;
            this->assign(other.begin(), other.end());
            return *this;
        }
        size_t _M_get_size() const { return _M_size; }
        void _M_set_size(size_t __n) { _M_size = __n; }
        void _M_dec_size(size_t __n) { _M_size -= __n; }
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
            List_node<T>* node;
            node = _node_alloc.allocate(1);
            _node_alloc.construct(node, val);
            return node;
        }
        void _M_insert(iterator __position, const T & __x) {
          _Node* tmp = _M_create_node(__x);
          tmp->_M_hook(__position.getNode());
          this->_M_inc_size(1);
        }
        void push_back(const T & val) {
            this->_M_insert(end(), val);
        }
        /* insert: single element (1) */	
        void insert(iterator __position, const T & __x)
        {
          _Node* __tmp = _M_create_node(__x);
          __tmp->_M_hook(__position._M_const_cast()._M_node);
          this->_M_inc_size(1);
          return iterator(__tmp);
        }
        /* insert: fill (2) */	
        void insert (iterator position, size_t n, const T & val);
        /* insert: range (3) */	
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last);
        // Erases element at position given.
        void _M_erase(iterator __position) {
            this->_M_dec_size(1);
            __position.getNode()->_M_unhook();
            _node_alloc.destroy(__position.getNode());
            _node_alloc.deallocate(__position.getNode(), 1);
        }
        iterator erase(iterator __position)
        {
          iterator __ret = iterator(__position.getNode()->getNext());
          _M_erase(__position._M_const_cast());
          return __ret;
        }
        iterator erase(iterator __first, iterator __last)
        {
          while (__first != __last)
            __first = erase(__first);
          return __last._M_const_cast();
        }
        void _M_fill_assign(size_t __n, const T & __val)
        {
          iterator __i = begin();
          for (; __i != end() && __n > 0; ++__i, --__n)
            *__i = __val;
          if (__n > 0)
            insert(end(), __n, __val);
          else
            erase(__i, end());
        }
        template <class InputIterator>
        /* void assign (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) */
        void _M_assign_dispatch(InputIterator __first2, InputIterator __last2, char (*)[sizeof(*__first2)] = NULL)
      {
        iterator __first1 = begin();
        iterator __last1 = end();
        for (; __first1 != __last1 && __first2 != __last2;
	     ++__first1, (void)++__first2)
          *__first1 = *__first2;
        if (__first2 == __last2)
          erase(__first1, __last1);
        else
          insert(__last1, __first2, __last2);
      }
        /* assign: range (1) */	
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL)
        {
            _M_assign_dispatch(first, last);
        }
        /* assign: fill (2) */
        void assign(size_t __n, const T & __val)
        {
            _M_fill_assign(__n, __val);
        }


    private:
        List_node<T>*  _M_node;
        std::size_t     _M_size;
        node_allocator  _node_alloc;
        _Alloc          _data_alloc;
    };
}

#endif
