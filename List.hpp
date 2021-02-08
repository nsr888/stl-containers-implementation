#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <memory>
# include <cmath>

namespace ft
{
    template<typename T, typename _Alloc = std::allocator<T> >
    struct List_node {
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
        /* List_node* getNext() const { return _M_next; } */
        /* List_node* getPrev() const { return _M_prev; } */
        List_node & operator=(const List_node & other) {
            if (this == &other)
                return *this;
            this->_M_data = new T(other._M_data);
            this->_M_next = other._M_next;
            this->_M_prev = other._M_prev;
            return *this;
        }
        /* insert this node between */
        void _M_hook(List_node* const __position) {
            this->_M_next = __position;
            this->_M_prev = __position->_M_prev;
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
        /* 11 39(this) 42 55 */
        /* 0 1 2 3(first) 4 5 6(last) 7 8 */
        /* _M_transfer(first, last) */
        /* _M_transfer cuts nodes and puts it before "this" node */
        /* 0 1 2 6 7 8 */
        /* 11 39 4 5 3(this) 42 55  */
        void _M_transfer(List_node<T> * const first, List_node<T> * const last)
        {
          if (this != last)
          {
            // Remove [first, last) from its old position.
            last->_M_prev->_M_next  = this;
            first->_M_prev->_M_next = last;
            this->_M_prev->_M_next  = first;

            // Splice [first, last) into its new position.
            List_node<T> * const tmp = this->_M_prev;
            this->_M_prev            = last->_M_prev;
            last->_M_prev            = first->_M_prev;
            first->_M_prev           = tmp;
          }
        }
        static void swap(List_node<T> & __x, List_node<T> & __y)
        {
            if ( __x._M_next != &__x )
            {
              if ( __y._M_next != &__y )
                {
                  // Both __x and __y are not empty.
                  std::swap(__x._M_next,__y._M_next);
                  std::swap(__x._M_prev,__y._M_prev);
                  __x._M_next->_M_prev = __x._M_prev->_M_next = &__x;
                  __y._M_next->_M_prev = __y._M_prev->_M_next = &__y;
                }
            else
                {
                  // __x is not empty, __y is empty.
                  __y._M_next = __x._M_next;
                  __y._M_prev = __x._M_prev;
                  __y._M_next->_M_prev = __y._M_prev->_M_next = &__y;
                  __x._M_next = __x._M_prev = &__x;
                }
            }
            else if ( __y._M_next != &__y )
            {
              // __x is empty, __y is not empty.
              __x._M_next = __y._M_next;
              __x._M_prev = __y._M_prev;
              __x._M_next->_M_prev = __x._M_prev->_M_next = &__x;
              __y._M_next = __y._M_prev = &__y;
            }
        }
        T* _M_data;
        List_node<T>* _M_next;
        List_node<T>* _M_prev;
        _Alloc _myalloc;
    };

    template<class T>
    struct List_iterator {
        typedef ft::List_iterator<T>       iterator;
        typedef ft::List_node<T>           _Node;
        typedef ft::List_iterator<T>       _Self;
        typedef int difference_type;
        
        List_iterator() : _M_node() {}
        List_iterator<T>(const iterator & it) : _M_node(it._M_node) {}
        List_iterator<T>(_Node* other) : _M_node(other) {}
        ~List_iterator() {}
        void _M_incr() { _M_node = _M_node->_M_next; }
        void _M_decr() { _M_node = _M_node->_M_prev; }
        
        _Self & operator=(const List_iterator & other) {
            this->_M_node = other._M_node;
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
            return _M_node->_M_data;
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

        List_node<T>* _M_node;

    };

    template<class T>
    struct List_const_iterator {
        typedef ft::List_iterator<T>       iterator;
        typedef const ft::List_node<T>           _Node;
        typedef ft::List_const_iterator<T>       _Self;
        typedef int difference_type;
        
        List_const_iterator() : _M_node() {}
        List_const_iterator<T>(const iterator & it) : _M_node(it._M_node) {}
        List_const_iterator<T>(_Node* other) : _M_node(other) {}
        ~List_const_iterator() {}
        void _M_incr() { _M_node = _M_node->_M_next; }
        void _M_decr() { _M_node = _M_node->_M_prev; }
        
        _Self & operator=(const List_const_iterator & other) {
            this->_M_node = other._M_node;
        }
        bool operator==(const List_const_iterator & other) const {
          return _M_node == other._M_node;
        }
        bool operator!=(const List_const_iterator & other) const {
          return _M_node != other._M_node;
        }
        _Self _M_const_cast() const {
            return *this;
        }
        T & operator*() const { 
            return _M_node->getData();
        }
        T * operator->() const {
            return _M_node->_M_data;
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

        const List_node<T>* _M_node;

    };

    template<class T>
    class List_reverse_iterator: public List_iterator<T> {
    public:
        typedef ft::List_reverse_iterator<T>        iterator;
        typedef const ft::List_node<T>              _Node;
        typedef ft::List_reverse_iterator<T>        _Self;
        typedef int                                 difference_type;
        
        List_reverse_iterator<T>(const ft::List_iterator<T> & it)
            : _M_node(it._M_node)
        {
           this->_M_incr(); 
        }
        _Self & operator=(const List_iterator<T> & other) {
            this->_M_node = other._M_node;
            return *this;
        }

        void _M_incr() { _M_node = _M_node->_M_prev; }
        void _M_decr() { _M_node = _M_node->_M_next; }
        
        T & operator*() const { 
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

        const List_node<T>* _M_node;

    };

    template<class T>
    class List_reverse_const_iterator: public List_const_iterator<T> {
    public:
        typedef ft::List_reverse_const_iterator<T>      iterator;
        typedef const ft::List_node<T>                  _Node;
        typedef ft::List_reverse_const_iterator<T>      _Self;
        typedef int                                     difference_type;
        
        List_reverse_const_iterator<T>(const ft::List_const_iterator<T> & it)
            : _M_node(it._M_node) 
        {
           this->_M_incr(); 
        }
        _Self & operator=(const List_const_iterator<T> & other) {
            this->_M_node = other._M_node;
            return *this;
        }

        void _M_incr() { _M_node = _M_node->_M_prev; }
        void _M_decr() { _M_node = _M_node->_M_next; }
        
        T & operator*() const { 
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

        const List_node<T>* _M_node;

    };

    template<typename T, typename _Alloc = std::allocator<T> >
    class List {
    public:
        typedef ft::List_iterator<T>                iterator;
        typedef ft::List_const_iterator<T>          const_iterator;
        typedef ft::List_reverse_iterator<T>        reverse_iterator;
        typedef ft::List_reverse_const_iterator<T>  const_reverse_iterator;
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
        /* constructor for my iterators range */
        List(const_iterator first, const_iterator last) {
            this->_M_size = 0;
            _M_node = _node_alloc.allocate(1);
            _node_alloc.construct(_M_node, 0);
            for (; first != last; ++first)
                push_back(*first);
        };
        /* Solution for int overload */
        /* https://stackoverflow.com/questions/37803630/c-function-overloading-alternatives-to-enable-if */
        template <class InputIterator>
        List(InputIterator first, InputIterator last,
                char (*)[sizeof(*first)] = NULL) {
            /* calculate distance */
            /* https://en.cppreference.com/w/cpp/iterator/iterator_traits */
            typename std::iterator_traits<InputIterator>::difference_type n = std::distance(first, last);
            this->_M_size = 0;
            _M_node = _node_alloc.allocate(1);
            /* put distance inside end node */
            _node_alloc.construct(_M_node, n);
            for (; first != last; ++first)
                push_back(*first);
        };
        void _M_clear()
        {
            _Node* current = _M_node->_M_next;
            while (current != _M_node)
            {
                _Node* tmp = current;
                current = current->_M_next;
                _node_alloc.destroy(tmp);
                _node_alloc.deallocate(tmp, 1);
            }
            this->_M_size = 0;
            _M_node->_M_next = _M_node->_M_prev = this->_M_node;
        }
        ~List() {
            _M_clear();
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
            return const_iterator(this->_M_node->_M_next);
        }
        const_iterator end() const {
            return const_iterator(this->_M_node);
        }
        iterator begin() { 
            return iterator(this->_M_node->_M_next);
        }
        iterator end() {
            return iterator(this->_M_node);
        }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        /* On 64 bit theoretically maximum allocate 2^64 = 18.45 exabytes.
         * Deviding it by size of node will get us maximum size of list.
         * https://stackoverflow.com/questions/3813124/c-vector-max-size */
        size_t max_size() const { return ((pow(2, 64) / sizeof(List_node<T>)) - 1); }

        bool empty() const { return _M_node->_M_next == _M_node; }
        size_t size() const { 
            const_iterator ptr = begin();
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
          tmp->_M_hook(__position._M_node);
          this->_M_inc_size(1);
        }

        void push_front(const T & val) { this->_M_insert(begin(), val); }
        void push_back(const T & val) { this->_M_insert(end(), val); }
        void pop_front() { this->_M_erase(begin()); }
        void pop_back() { this->_M_erase(iterator(this->_M_node->_M_prev)); }

        /* insert: single element (1) */	
        iterator insert(iterator __position, const T & __x)
        {
          _Node* __tmp = _M_create_node(__x);
          __tmp->_M_hook(__position._M_const_cast()._M_node);
          this->_M_inc_size(1);
          return iterator(__tmp);
        }
        /* insert: fill (2) */	
        void insert(iterator position, size_t n, const T & val) {
            List tmp(n, val);
            splice(position, tmp);
        }
        /* insert: range (3) */	
        template <class InputIterator>
        void insert(iterator position, InputIterator first, 
                InputIterator last, char (*)[sizeof(*first)] = NULL) {
            List tmp(first, last);
            splice(position, tmp);
        }
        // Erases element at position given.
        void _M_erase(iterator __position) {
            this->_M_dec_size(1);
            __position._M_node->_M_unhook();
            _node_alloc.destroy(__position._M_node);
            _node_alloc.deallocate(__position._M_node, 1);
        }
        iterator erase(iterator __position)
        {
          iterator __ret = iterator(__position._M_node->_M_next);
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
        /* splice: entire list (1) */	
        void splice(iterator __position, List & x) {
          if (!x.empty())
          {
            this->_M_transfer(__position._M_const_cast(), x.begin(), x.end());
            this->_M_inc_size(x._M_get_size());
            x._M_set_size(0);
          }
        }
        /* splice: single element (2) */
        /* The second version (2) transfers only the element pointed by i from x into the container. */
        void splice(iterator __position, List & __x, iterator __i)
        {
            iterator __j = __i._M_const_cast();
            ++__j;
            if (__position == __i || __position == __j)
              return;

            this->_M_transfer(__position._M_const_cast(),
                      __i._M_const_cast(), __j);

            this->_M_inc_size(1);
            __x._M_dec_size(1);
        }
        static size_t _S_distance(const List_node<T>* __first,
                const List_node<T>* __last)
        {
            size_t __n = 0;
            while (__first != __last)
            {
                __first = __first->_M_next;
                ++__n;
            }
            return __n;
        }
        /* splice: element range (3) */
        /* The third version (3) transfers the range [first,last) from x into the container. */
        void splice(iterator position, List & x, iterator first, iterator last) {
          if (first != last)
          {
            size_t n = _S_distance(first._M_node, last._M_node);
            this->_M_inc_size(n);
            x._M_dec_size(n);

            this->_M_transfer(position._M_const_cast(),
                      first._M_const_cast(),
                      last._M_const_cast());
          }
        }
        void _M_transfer(iterator __position, iterator __first, iterator __last)
        { 
            __position._M_node->_M_transfer(__first._M_node, __last._M_node); 
        }
        void swap(List & x)
        {
            List_node<T>::swap(*this->_M_node, *x._M_node);
            size_t xsize = x._M_get_size();
            x._M_set_size(this->_M_get_size());
            this->_M_set_size(xsize);
        }
        void _M_default_append(size_t n)
        {
              size_t i = 0;
              for (; i < n; ++i)
                push_back(0);
        }
        iterator _M_resize_pos(size_t & new_size) {
            iterator i;
            size_t len = 0;
            for (i = begin(); i != end() && len < new_size; ++i, ++len)
                ;
            new_size -= len;
            return i;
        }
        void resize(size_t new_size)
        {
            iterator i = _M_resize_pos(new_size);
            if (new_size)
                _M_default_append(new_size);
            else
                erase(i, end());
        }
        void resize(size_t new_size, T x)
        {
          iterator i = _M_resize_pos(new_size);
          if (new_size)
            insert(end(), new_size, x);
          else
            erase(i._M_const_cast(), end());
        }
        void clear()
        {
            _M_clear();
        }
        void remove(const T & value)
        {
            List<T> to_destroy;
            iterator first = begin();
            iterator last = end();
            while (first != last)
            {
                iterator next = first;
                ++next;
                if (*first == value)
                {
                    to_destroy.splice(to_destroy.begin(), *this, first);
                }
                first = next;
            }
        }
        template<typename Predicate>
        void remove_if(Predicate pred)
        {
            List<T> to_destroy;
            iterator first = begin();
            iterator last = end();
            while (first != last)
            {
                iterator next = first;
                ++next;
                if (pred(*first))
                {
                    to_destroy.splice(to_destroy.begin(), *this, first);
                }
                first = next;
            }
        }
        void unique()
        {
            iterator first = begin();
            iterator last = end();
            if (first == last)
                return;
            List<T> to_destroy;
            iterator next = first;
            while (++next != last)
            {
                if (*first == *next)
                {
                    to_destroy.splice(to_destroy.begin(), *this, next);
                }
                else
                {
                    first = next;
                }
                next = first;
            }
        }
        template<typename BinaryPredicate>
        void unique(BinaryPredicate binary_pred)
        {
            iterator first = begin();
            iterator last = end();
            if (first == last)
                return;
            List<T> to_destroy;
            iterator next = first;
            while (++next != last)
            {
                if (binary_pred(*first, *next))
                {
                    to_destroy.splice(to_destroy.begin(), *this, next);
                }
                else
                {
                    first = next;
                }
                next = first;
            }
        }

    private:
        List_node<T>*  _M_node;
        std::size_t     _M_size;
        node_allocator  _node_alloc;
        _Alloc          _data_alloc;
    };
}

#endif
