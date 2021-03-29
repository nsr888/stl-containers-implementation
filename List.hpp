#ifndef LIST_HPP
# define LIST_HPP
# include <algorithm>
# include <memory>
# include <cmath>

namespace ft
{
    template<typename T, typename _Alloc = std::allocator<T> >
    struct List_node {
        List_node<T>() {
            this->_data = _myalloc.allocate(1);
            _myalloc.construct(_data, T());
            this->_next = this->_prev = this;
        }
        List_node<T>(T data, List_node<T>* next, List_node<T>* prev) {
            this->_data = _myalloc.allocate(1);
            _myalloc.construct(_data, data);
            _next = next;
            _prev = prev;
        }
        ~List_node() {
            _myalloc.deallocate(_data, 1);
        }
        List_node<T>(const List_node<T> & other)
        {
            *this = other;
            return;
        }
        List_node<T>(const T & other)
        {
            this->_data = _myalloc.allocate(1);
            _myalloc.construct(_data, other);
            this->_next = this->_prev = this;
        }
        T& getData() const { return *_data; }
        List_node & operator=(const List_node & other) {
            if (this == &other)
                return *this;
            this->_data = new T(other._data);
            this->_next = other._next;
            this->_prev = other._prev;
            return *this;
        }
        /* insert this node between */
        void _hook(List_node* const __position) {
            this->_next = __position;
            this->_prev = __position->_prev;
            __position->_prev->_next = this;
            __position->_prev = this;
        }
        /* remove this node between next and prev */
        void _unhook() {
            List_node<T>* const next = this->_next;
            List_node<T>* const prev = this->_prev;
            prev->_next = next;
            next->_prev = prev;
        }
        /* _transfer cuts nodes (first included, last not included) and puts it before "this" node */
        void _transfer(List_node<T> * const first, List_node<T> * const last)
        {
          if (this != last)
          {
            // Remove [first, last) from its old position.
            last->_prev->_next  = this;
            first->_prev->_next = last;
            this->_prev->_next  = first;

            // Splice [first, last) into its new position.
            List_node<T> * const tmp = this->_prev;
            this->_prev            = last->_prev;
            last->_prev            = first->_prev;
            first->_prev           = tmp;
          }
        }
        static void swap(List_node<T> & x, List_node<T> & y)
        {
            if ( x._next != &x )
            {
                if ( y._next != &y )
                {
                  // Both __x and __y are not empty.
                  std::swap(x._next,y._next);
                  std::swap(x._prev,y._prev);
                  x._next->_prev = x._prev->_next = &x;
                  y._next->_prev = y._prev->_next = &y;
                }
                else
                {
                  // __x is not empty, __y is empty.
                  y._next = x._next;
                  y._prev = x._prev;
                  y._next->_prev = y._prev->_next = &y;
                  x._next = x._prev = &x;
                }
            }
            else if ( y._next != &y )
            {
              // __x is empty, __y is not empty.
              x._next = y._next;
              x._prev = y._prev;
              x._next->_prev = x._prev->_next = &x;
              y._next = y._prev = &y;
            }
        }

        T*              _data;
        List_node<T>*   _next;
        List_node<T>*   _prev;
        _Alloc          _myalloc;
    };

    template<class T>
    struct List_iterator {
        typedef ft::List_iterator<T>       iterator;
        typedef ft::List_node<T>           node_t;
        typedef ft::List_iterator<T>       _Self;
        typedef int                        difference_type;
        
        List_iterator() : _node() {}
        List_iterator<T>(const iterator & it) : _node(it._node) {}
        List_iterator<T>(node_t* other) : _node(other) {}
        ~List_iterator() {}
        void _increment() { _node = _node->_next; }
        void _decrement() { _node = _node->_prev; }
        
        _Self & operator=(const List_iterator & other) {
            this->_node = other._node;
            return *this;
        }
        bool operator==(const List_iterator & other) const {
          return _node == other._node;
        }
        bool operator!=(const List_iterator & other) const {
          return _node != other._node;
        }
        T & operator*() const { 
            return _node->getData(); 
        }
        T * operator->() const {
            return _node->_data;
        }
        _Self & operator++() { 
          this->_increment();
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }
        _Self & operator--() { 
          this->_decrement();
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        List_node<T>* _node;

    };

    template<class T>
    struct List_const_iterator {
        typedef ft::List_iterator<T>            iterator;
        typedef const ft::List_node<T>          node_t;
        typedef ft::List_const_iterator<T>      _Self;
        typedef int                             difference_type;
        
        List_const_iterator() : _node() {}
        List_const_iterator<T>(const iterator & it) : _node(it._node) {}
        List_const_iterator<T>(node_t* other) : _node(other) {}
        ~List_const_iterator() {}
        void _increment() { _node = _node->_next; }
        void _decrement() { _node = _node->_prev; }
        
        _Self & operator=(const List_const_iterator & other) {
            this->_node = other._node;
        }
        bool operator==(const List_const_iterator & other) const {
          return _node == other._node;
        }
        bool operator!=(const List_const_iterator & other) const {
          return _node != other._node;
        }
        T & operator*() const { 
            return _node->getData();
        }
        T * operator->() const {
            return _node->_data;
        }
        _Self & operator++() { 
          this->_increment();
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }
        _Self & operator--() { 
          this->_decrement();
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        const List_node<T>* _node;

    };

    template<class T>
    class List_reverse_iterator: public List_iterator<T> {
    public:
        typedef ft::List_reverse_iterator<T>        iterator;
        typedef const ft::List_node<T>              node_t;
        typedef ft::List_reverse_iterator<T>        _Self;
        typedef int                                 difference_type;
        
        List_reverse_iterator<T>(const ft::List_iterator<T> & it)
            : _node(it._node)
        {
           this->_increment(); 
        }
        _Self & operator=(const List_iterator<T> & other) {
            this->_node = other._node;
            return *this;
        }

        void _increment() { _node = _node->_prev; }
        void _decrement() { _node = _node->_next; }
        
        T & operator*() const { 
            return _node->getData();
        }
        _Self & operator++() { 
          this->_increment();
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }
        _Self & operator--() { 
          this->_decrement();
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        const List_node<T>* _node;

    };

    template<class T>
    class List_reverse_const_iterator: public List_const_iterator<T> {
    public:
        typedef ft::List_reverse_const_iterator<T>      iterator;
        typedef const ft::List_node<T>                  node_t;
        typedef ft::List_reverse_const_iterator<T>      _Self;
        typedef int                                     difference_type;
        
        List_reverse_const_iterator<T>(const ft::List_const_iterator<T> & it)
            : _node(it._node) 
        {
           this->_increment(); 
        }
        _Self & operator=(const List_const_iterator<T> & other) {
            this->_node = other._node;
            return *this;
        }

        void _increment() { _node = _node->_prev; }
        void _decrement() { _node = _node->_next; }
        
        T & operator*() const { 
            return _node->getData();
        }
        _Self & operator++() { 
          this->_increment();
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }
        _Self & operator--() { 
          this->_decrement();
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        const List_node<T>* _node;

    };

    template<typename T, typename _Alloc = std::allocator<T> >
    class List {
    public:
        typedef T                                   value_type;
        typedef _Alloc                              allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         pointer;
        typedef const value_type*                   const_pointer;
        typedef ft::List_iterator<T>                iterator;
        typedef ft::List_const_iterator<T>          const_iterator;
        typedef ft::List_reverse_iterator<T>        reverse_iterator;
        typedef ft::List_reverse_const_iterator<T>  const_reverse_iterator;
        typedef std::ptrdiff_t                      difference_type;
        typedef size_t                              size_type;
        typedef ft::List_node<T>                    node_t;
        typedef typename _Alloc::template rebind<List_node<T> >::other
            node_allocator;


        List<T>() {
            _node = _node_alloc.allocate(1);
            _node_alloc.construct(_node, T());
        };
        List(const List & other) {
            _node = _node_alloc.allocate(1);
            _node_alloc.construct(_node, other.size());
            for(const_iterator first = other.begin(); first != other.end(); ++first)
                push_back(*first);
        };
        explicit List(std::size_t n, const T & val = T() ) {
            _node = _node_alloc.allocate(1);
            _node_alloc.construct(_node, n);
            for(std::size_t i = 0; i < n; i++)
                push_back(val);
        };
        List(iterator first, iterator last) {
            _node = _node_alloc.allocate(1);
            size_t n = _calc_distance(first._node, last._node);
            _node_alloc.construct(_node, n);
            for (; first != last; ++first)
                push_back(*first);
        };
        /* constructor for my iterators range */
        List(const_iterator first, const_iterator last) {
            _node = _node_alloc.allocate(1);
            size_t n = _calc_distance(first._node, last._node);
            _node_alloc.construct(_node, n);
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
            _node = _node_alloc.allocate(1);
            /* put distance inside end node */
            _node_alloc.construct(_node, n);
            for (; first != last; ++first)
                push_back(*first);
        };
        ~List() {
            clear();
            _node_alloc.destroy(_node);
            _node_alloc.deallocate(_node, 1);
        };
        List & operator=(const List & other) {
            if (this == &other)
                return *this;
            this->assign(other.begin(), other.end());
            iterator last = end();
            *last._node->_data = T(other.size());
            return *this;
        }
        const_iterator begin() const { 
            return const_iterator(this->_node->_next);
        }
        const_iterator end() const {
            return const_iterator(this->_node);
        }
        iterator begin() { 
            return iterator(this->_node->_next);
        }
        iterator end() {
            return iterator(this->_node);
        }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const
        { 
            return const_reverse_iterator(end());
        }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const 
        {
            return const_reverse_iterator(begin()); 
        }

        /* On 64 bit theoretically maximum allocate 2^64 = 18.45 exabytes.
         * Deviding it by size of node will get us maximum size of list.
         * https://stackoverflow.com/questions/3813124/c-vector-max-size */
        size_t max_size() const 
        { 
            return ((pow(2, 64) / sizeof(List_node<T>)) - 1); 
        }
        bool empty() const { return _node->_next == _node; }
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

        void push_front(const T & val) { this->_insert(begin(), val); }
        void push_back(const T & val) { this->_insert(end(), val); }
        void pop_front() { this->_erase(begin()); }
        void pop_back() { this->_erase(iterator(this->_node->_prev)); }

        /* insert: single element (1) */	
        iterator insert(iterator position, const T & x)
        {
          node_t* tmp = _create_node(x);
          tmp->_hook(position._node);
          return iterator(tmp);
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
        iterator erase(iterator position)
        {
          iterator ret = iterator(position._node->_next);
          _erase(position);
          return ret;
        }
        iterator erase(iterator first, iterator last)
        {
            while (first != last)
                first = erase(first);
            *last._node->_data = T(size());
            return last;
        }
        /* assign: range (1) */	
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                char (*)[sizeof(*first)] = NULL)
        {
            iterator first_tmp = begin();
            iterator last_tmp = end();
            while (first_tmp != last_tmp && first != last)
            {
                *first_tmp = *first;
                ++first_tmp;
                ++first;
            }
            if (first == last)
                erase(first_tmp, last_tmp);
            else
                insert(last_tmp, first, last);
        }
        /* assign: fill (2) */
        void assign(size_t n, const T & val)
        {
            iterator i = begin();
            while(i != end() && n > 0)
            {
                *i = val;
                ++i;
                --n;
            }
            if (n > 0)
                insert(end(), n, val);
            else
                erase(i, end());
        }
        /* splice: entire list (1) */	
        void splice(iterator position, List & x) {
            if (!x.empty())
            {
                this->_transfer(position, x.begin(), x.end());
            }
        }
        /* splice: single element (2) */
        /* The second version (2) transfers only the element pointed by i from x into the container. */
        void splice(iterator position, List & x, iterator i)
        {
            (void)(x);
            if (position == i)
              return;
            iterator j = i;
            ++j;
            this->_transfer(position, i, j);
        }
        /* splice: element range (3) */
        /* The third version (3) transfers the range [first,last) from x into the container. */
        void splice(iterator position, List & x, iterator first, iterator last) {
            if (first != last)
            {
                (void)(x);
                this->_transfer(position, first, last);
            }
        }
        void _transfer(iterator position, iterator first, iterator last)
        { 
            position._node->_transfer(first._node, last._node); 
        }
        void swap(List & x)
        {
            List_node<T>::swap(*this->_node, *x._node);
        }
        void resize(size_t new_size)
        {
            iterator i = _resize_pos(new_size);
            if (new_size)
            {
                size_t n = 0;
                while (n < new_size)
                {
                    push_back(0);
                    ++n;
                }
            }
            else
                erase(i, end());
        }
        void resize(size_t new_size, T x)
        {
            iterator i = _resize_pos(new_size);
            if (new_size)
                insert(end(), new_size, x);
            else
                erase(i, end());
        }
        void clear()
        {
            node_t* current = this->_node->_next;
            while (current != this->_node)
            {
                node_t* tmp = current;
                current = current->_next;
                _node_alloc.destroy(tmp);
                _node_alloc.deallocate(tmp, 1);
            }
            this->_node->_next = this->_node->_prev = this->_node;
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
        /* rewhrite */
        void merge(List & x)
        {
            if (this != &x)
            {
                iterator first1 = begin();
                iterator last1 = end();
                iterator first2 = x.begin();
                iterator last2 = x.end();
                while (first1 != last1 && first2 != last2)
                {
                    if (*first2 < *first1)
                    {
                        iterator next = first2;
                        ++next;
                        _transfer(first1, first2, next);
                        first2 = next;
                    }
                    else
                        ++first1;
                }
                if (first2 != last2)
                    _transfer(last1, first2, last2);
            }
        }
        template <class Compare>
        void merge(List & x, Compare comp)
        {
            if (this != &x)
            {
                iterator first1 = begin();
                iterator last1 = end();
                iterator first2 = x.begin();
                iterator last2 = x.end();
                while (first1 != last1 && first2 != last2)
                {
                    if (comp(*first2, *first1))
                    {
                        iterator next = first2;
                        ++next;
                        _transfer(first1, first2, next);
                        first2 = next;
                    }
                    else
                        ++first1;
                }
                if (first2 != last2)
                    _transfer(last1, first2, last2);
            }
        }
        void sort()
        {
            // Do nothing if the list has length 0 or 1.
            if (this->_node->_next != this->_node &&
                    this->_node->_next->_next != this->_node)
            {
                /* bubble sort :) */
                bool swapped = true;
                int count = this->size();
                while (swapped)
                {
                    swapped = false;
                    int i = 0;
                    iterator h = begin();
                    while (i < count - 1)
                    {
                        iterator p1 = h;
                        iterator p2(h._node->_next);
                        if (*p1 > *p2)
                        {
                            std::swap(p1._node->_data, p2._node->_data);
                            swapped = true;
                        }
                        h = iterator(h._node->_next);
                        i++;
                    }
                }
            }
        }
        template <class Compare>
        void sort (Compare comp)
        {
            // Do nothing if the list has length 0 or 1.
            if (this->_node->_next != this->_node &&
                    this->_node->_next->_next != this->_node)
            {
                /* bubble sort :) */
                bool swapped = true;
                int count = this->size();
                while (swapped)
                {
                    swapped = false;
                    int i = 0;
                    iterator h = begin();
                    while (i < count - 1)
                    {
                        iterator p1 = h;
                        iterator p2(h._node->_next);
                        if (comp(*p2, *p1))
                        {
                            std::swap(p1._node->_data, p2._node->_data);
                            swapped = true;
                        }
                        h = iterator(h._node->_next);
                        i++;
                    }
                }
            }
        }
        void unique()
        {
            int i = 0;
            int count = this->size();
            iterator h = begin();
            List<T> to_destroy;
            while (i < count - 1)
            {
                iterator p1 = h;
                iterator p2(h._node->_next);
                if (*p2 == *p1)
                    to_destroy.splice(to_destroy.begin(), *this, p2);
                h = iterator(h._node->_next);
                i++;
            }
            to_destroy.clear();
        }
        template<typename BinaryPredicate>
        void unique(BinaryPredicate binary_pred)
        {
            int i = 0;
            int count = this->size();
            iterator h = begin();
            List<T> to_destroy;
            while (i < count - 1)
            {
                iterator p1 = h;
                iterator p2(h._node->_next);
                if (binary_pred(*p2, *p1))
                    to_destroy.splice(to_destroy.begin(), *this, p2);
                h = iterator(h._node->_next);
                i++;
            }
            to_destroy.clear();
        }
        void reverse()
        {
            List<T> reversed;
            for (ft::List_iterator<T> it = rbegin(); it != rend(); ++it)
                reversed.push_back(*it);
            clear();
            *this = reversed;
        }

    private:
        List_node<T>*  _node;
        node_allocator  _node_alloc;
        _Alloc          _data_alloc;

        node_t* _create_node(const T & val)
        {
            List_node<T>* node;
            node = _node_alloc.allocate(1);
            _node_alloc.construct(node, val);
            return node;
        }
        void _insert(iterator __position, const T & __x) {
            node_t* tmp = _create_node(__x);
            tmp->_hook(__position._node);
            iterator last = end();
            *last._node->_data = this->size();
        }
        // Erases element at position given.
        void _erase(iterator __position) {
            __position._node->_unhook();
            _node_alloc.destroy(__position._node);
            _node_alloc.deallocate(__position._node, 1);
        }
        static size_t _calc_distance(const List_node<T>* first,
                const List_node<T>* last)
        {
            size_t __n = 0;
            while (first != last)
            {
                first = first->_next;
                ++__n;
            }
            return __n;
        }
        iterator _resize_pos(size_t & new_size) {
            iterator i = begin();
            size_t len = 0;
            while (i != end() && len < new_size)
            {
                ++i;
                ++len;
            }
            new_size -= len;
            return i;
        }
    };

    template <class InputIterator1, class InputIterator2>
      bool equal_list ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
      while (first1!=last1) {
        if (!(*first1 == *first2))
          return false;
        ++first1; ++first2;
      }
      return true;
    }

    template <class T, class Alloc>
    bool operator== (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return equal_list(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare_list (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2)
    {
      while (first1!=last1)
      {
        if (first2==last2 || *first2<*first1) return false;
        else if (*first1<*first2) return true;
        ++first1; ++first2;
      }
      return (first2!=last2);
    }

    template <class T, class Alloc>
    bool operator!= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
        if (lhs == rhs)
            return false;
        return true;
    }

    template <class T, class Alloc>
    bool operator< (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
        return lexicographical_compare_list(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
        if (lhs < rhs || lhs == rhs)
            return true;
        return false;
    }

    template <class T, class Alloc>
    bool operator> (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
        if (lhs < rhs)
            return false;
        if (lhs == rhs)
            return false;
        return true;
    }
    
    template <class T, class Alloc>
    bool operator>= (const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
        if (!(lhs < rhs))
            return true;
        return false;
    }

}

#endif
