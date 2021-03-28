#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <cmath>

namespace ft
{
    template<class T>
    struct Vector_iterator {
        typedef ft::Vector_iterator<T>      iterator;
        typedef T*                          pointer;
        typedef ft::Vector_iterator<T>      _Self;
        typedef int                         difference_type;
        
        Vector_iterator<T>() : _arr(0) {}
        Vector_iterator<T>(const iterator & it) {
            this->_arr = it._arr;
        }
        explicit Vector_iterator<T>(pointer p) {
            this->_arr = p;
        }
        ~Vector_iterator() {}
        Vector_iterator& operator= (const Vector_iterator& x) {
            this->_arr = x._arr;
            return *this;
        }
        bool operator== (const Vector_iterator & other) const {
          return this->_arr == other._arr;
        }
        bool operator!= (const Vector_iterator & other) const {
          return this->_arr != other._arr;
        }
        bool operator> (const Vector_iterator & other) const {
          return this->_arr > other._arr;
        }
        bool operator< (const Vector_iterator & other) const {
          return this->_arr < other._arr;
        }
        iterator operator+(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                ++ret;
            return (ret);
        }
        difference_type operator-(const Vector_iterator & other) {
            return (_arr - other._arr);
        }
        iterator operator-(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                --ret;
            return (ret);
        }
        T & operator*() const { 
            return *_arr;
        }
        T * operator->() const {
            return _arr;
        }
        _Self & operator++() { 
          _arr++;
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          _arr++;
          return __tmp;
        }
        _Self & operator--() { 
          _arr--;
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          _arr--;
          return __tmp;
        }

        pointer _arr;

    };

    template<class T>
    struct Vector_reverse_iterator {
        typedef ft::Vector_reverse_iterator<T>      iterator;
        typedef T*                                  pointer;
        typedef ft::Vector_reverse_iterator<T>      _Self;
        typedef int                                 difference_type;

        Vector_reverse_iterator<T>() : _arr(0) {}
        Vector_reverse_iterator<T>(const iterator & it) {
            this->_arr = it._arr;
        }
        explicit Vector_reverse_iterator<T>(pointer p) {
            this->_arr = p;
        }
        ~Vector_reverse_iterator() {}
        Vector_reverse_iterator& operator= (const Vector_reverse_iterator& x) {
            this->_arr = x._arr;
            return *this;
        }
        bool operator== (const Vector_reverse_iterator & other) const {
          return this->_arr == other._arr;
        }
        bool operator!= (const Vector_reverse_iterator & other) const {
          return this->_arr != other._arr;
        }
        bool operator> (const Vector_reverse_iterator & other) const {
          return this->_arr > other._arr;
        }
        bool operator< (const Vector_reverse_iterator & other) const {
          return this->_arr < other._arr;
        }
        iterator operator+(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                --ret;
            return (ret);
        }
        difference_type operator-(const Vector_reverse_iterator & other) {
            return (_arr - other._arr);
        }
        iterator operator-(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                ++ret;
            return (ret);
        }
        T & operator*() const { 
            return *_arr;
        }
        T * operator->() const {
            return _arr;
        }
        _Self & operator++() { 
          _arr--;
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          _arr--;
          return __tmp;
        }
        _Self & operator--() { 
          _arr++;
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          _arr++;
          return __tmp;
        }

        pointer _arr;

    };

    template<class T>
    struct Vector_const_iterator {
        typedef ft::Vector_const_iterator<T>    iterator;
        typedef T*                              pointer;
        typedef ft::Vector_const_iterator<T>    _Self;
        typedef int                             difference_type;
        
        Vector_const_iterator<T>() : _arr(0) {}
        Vector_const_iterator<T>(const iterator & it) {
            this->_arr = it._arr;
        }
        explicit Vector_const_iterator<T>(pointer p) {
            this->_arr = p;
        }
        ~Vector_const_iterator() {}
        Vector_const_iterator& operator= (const Vector_const_iterator& x) {
            this->_arr = x._arr;
            return *this;
        }
        bool operator==(const Vector_const_iterator & other) const {
          return this->_arr == other._arr;
        }
        bool operator!=(const Vector_const_iterator & other) const {
          return this->_arr != other._arr;
        }
        iterator operator+(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                ++ret;
            return (ret);
        }
        difference_type operator-(const Vector_const_iterator & other) {
            return (_arr - other._arr);
        }
        iterator operator-(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                --ret;
            return (ret);
        }
        T & operator*() const { 
            return *_arr;
        }
        T * operator->() const {
            return _arr;
        }
        _Self & operator++() { 
          _arr++;
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          _arr++;
          return __tmp;
        }
        _Self & operator--() { 
          _arr--;
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          _arr--;
          return __tmp;
        }

        pointer _arr;

    };


    template<class T>
    struct Vector_const_reverse_iterator {
        typedef ft::Vector_const_reverse_iterator<T>    iterator;
        typedef T*                                      pointer;
        typedef ft::Vector_const_reverse_iterator<T>    _Self;
        typedef int                                     difference_type;
        
        Vector_const_reverse_iterator<T>() : _arr(0) {}
        Vector_const_reverse_iterator<T>(const iterator & it) {
            this->_arr = it._arr;
        }
        explicit Vector_const_reverse_iterator<T>(pointer p) {
            this->_arr = p;
        }
        ~Vector_const_reverse_iterator() {}
        Vector_const_reverse_iterator& operator= (const Vector_const_reverse_iterator& x) {
            this->_arr = x._arr;
            return *this;
        }
        bool operator==(const Vector_const_reverse_iterator & other) const {
          return this->_arr == other._arr;
        }
        bool operator!=(const Vector_const_reverse_iterator & other) const {
          return this->_arr != other._arr;
        }
        iterator operator+(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                ++ret;
            return (ret);
        }
        difference_type operator-(const Vector_const_reverse_iterator & other) {
            return (_arr - other._arr);
        }
        iterator operator-(int n) {
            iterator ret(_arr);
            for (int i = 0; i < n; ++i)
                --ret;
            return (ret);
        }
        T & operator*() const { 
            return *_arr;
        }
        T * operator->() const {
            return _arr;
        }
        _Self & operator++() { 
          _arr++;
          return *this;
        }
        _Self operator++(int) { 
          _Self __tmp = *this;
          _arr++;
          return __tmp;
        }
        _Self & operator--() { 
          _arr--;
          return *this;
        }
        _Self operator--(int) { 
          _Self __tmp = *this;
          _arr--;
          return __tmp;
        }

        pointer _arr;

    };

    template<typename T, typename _Alloc = std::allocator<T> >
    class Vector {
    public:
        typedef T                                   value_type;
        typedef _Alloc                              allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         pointer;
        typedef const value_type*                   const_pointer;
        typedef ft::Vector_iterator<T>              iterator;
        typedef ft::Vector_const_iterator<T>        const_iterator;
        typedef ft::Vector_reverse_iterator<T>      reverse_iterator;
        typedef ft::Vector_const_reverse_iterator<T> const_reverse_iterator;
        typedef std::ptrdiff_t                      difference_type;
        typedef size_t                              size_type;

        explicit Vector (const allocator_type& alloc = allocator_type())
            : _array(0)
            , _size(0)
            , _capacity(0)
            , _alloc(alloc)
        {};
        explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _array(0)
            , _size(n)
            , _capacity(n)
            , _alloc(alloc) {
            _array = _alloc.allocate(n);
            for (size_type i = 0; i < n; ++i)
                _alloc.construct(&_array[i], val);
        }
        Vector (iterator first, iterator last) {
            size_type n;
            n = static_cast<size_type>(last - first);
            _size = n;
            _capacity = n;
            _array = _alloc.allocate(n);
            for (size_type i = 0; i < n; ++i, ++first)
                _alloc.construct(&_array[i], *first);
        }
        template <class InputIterator>
        Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) {
            size_type n;
            n = static_cast<size_type>(last - first);
            _size = n;
            _capacity = n;
            _alloc = alloc;
            _array = _alloc.allocate(n);
            for (size_type i = 0; i < n; ++i, ++first)
                _alloc.construct(&_array[i], *first);
        }
        Vector (const Vector& x) 
            : _array(0)
            , _size(0)
            , _capacity(0) {
            *this = x;
        }
        ~Vector() {
            this->clear();
        }
        Vector& operator= (const Vector& x) {
            if (this == &x)
                return *this;
            if (this->_capacity)
                this->clear();
            _size = x.size();
            _capacity = x.capacity();
            _array = _alloc.allocate(_capacity);
            Vector_const_iterator<T> it = x.begin();
            for (size_type i = 0; i < _capacity; ++i, ++it)
                _alloc.construct(&_array[i], *it);
            return *this;
        }
        reference operator[](int i) {
            return _array[i];
        }
        reference at(size_type n) {
            if (n > this->size())
                throw std::out_of_range("size is greater than array size");
            return _array[n];
        }
        iterator begin() {
            return iterator(_array);
        }
        iterator end() {
            return iterator(&_array[_size]);
        }
        reverse_iterator rbegin() {
            return reverse_iterator(&_array[_size - 1]);
        }
        reverse_iterator rend() {
            return reverse_iterator(_array - 1);
        }
        const_iterator begin() const {
            return const_iterator(_array);
        }
        const_iterator end() const {
            return const_iterator(&_array[_size]);
        }
        reference front() {
            return _array[0];
        }
        reference back() {
            return _array[_size - 1];
        }
        size_type size() const {
            return (_size);
        }
        size_t max_size() const 
        { 
            return ((pow(2, 64) / sizeof(T)) - 1); 
        }
        size_type capacity() const {
            return (_capacity);
        }
        bool empty() const {
            if (this->size() == 0)
                return true;
            return false;
        }
        void clear() {
            for (size_type i = 0; i < _capacity; ++i)
                _alloc.destroy(&_array[i]);
            _alloc.deallocate(_array, _capacity);
            _array = 0;
            _size = 0;
            _capacity = 0;
        }
        iterator erase(iterator position) {
            iterator return_pos(position);
            for(; position != end(); ++position)
                *position = *(position + 1);
            --_size;
            return return_pos;
        }
        iterator erase(iterator first, iterator last) {
            iterator return_pos(last);
            size_type new_size = _size - static_cast<size_type>(last - first);
            while (last != end())
            {
                *first = *last;
                ++last;
                ++first;
            }
            _size = new_size;
            return (return_pos);
        }
        void assign (size_type n, const value_type& val) {
            Vector tmp(n, val);
            this->clear();
            *this = tmp;
        }
        template <class InputIterator>
        void assign(InputIterator first,
                InputIterator last, char (*)[sizeof(*first)] = NULL) {
            size_type len = static_cast<size_type>(last - first);
            if (len > _capacity )
                this->reserve(len);
            _size = 0;
            iterator pos(begin());
            while (first != last)
            {
                *pos = *first;
                ++first; 
                ++pos;
                ++_size;
            }
        }
        void pop_back() {
            iterator start = iterator(this->begin());
            iterator finish = iterator(this->end());
            --finish;
            Vector tmp(start, finish);
            this->clear();
            *this = tmp;
        }
        void reserve(size_type n) {
            if (n < _capacity)
                return;
            if (_capacity * 2 > n)
                n = _capacity * 2;
            Vector tmp(n);
            tmp.assign(begin(), end());
            this->clear();
            *this = tmp;
        }
        void push_back(const value_type& val) {
            if (_size == _capacity)
                reserve(_capacity + 1);
            _array[_size] = val; 
            ++_size;
        }
        iterator insert (iterator position, const value_type& val) {
            size_type len = static_cast<size_type>(position - begin());
            insert(position, 1, val);
            return iterator(&_array[len]);
        }
        void insert (iterator position, size_type n, const value_type& val) {
            Vector tmp(begin(), position);
            for (size_type i = 0; i < n; ++i)
                tmp.push_back(val);
            iterator ret(tmp.end() - 1);
            while (position != end()) {
                tmp.push_back(*position);
                ++position;
            }
            this->clear();
            *this = tmp;
        }
        template <class InputIterator>
        void insert (iterator position, InputIterator first,
                InputIterator last, char (*)[sizeof(*first)] = NULL) {
            Vector tmp(begin(), position);
            for (; first != last; ++first)
                tmp.push_back(*first);
            iterator ret(tmp.end() - 1);
            while (position != end()) {
                tmp.push_back(*position);
                ++position;
            }
            this->clear();
            *this = tmp;
        }
        void resize (size_type n, value_type val = value_type()) {
            if (n > this->_size) {
                this->insert(this->end(), n - this->_size, val);
            }
            if (n < this->_size) {
                Vector tmp(begin(), iterator(&this->_array[n]));
                this->clear();
                *this = tmp;
            }
        }
        void swap (Vector& x) {
                Vector tmp = *this;
                *this = x;
                x = tmp;
                tmp.clear();
        }

    private:
        pointer     _array;
        size_type   _size;
        size_type   _capacity; 
        _Alloc      _alloc;

        template <class InputIterator>
        difference_type distance (InputIterator first, InputIterator last) {
            difference_type d = 0;
            while (first != last)
            {
                ++first;
                ++d;
            }
            return d;
        }
    };

    template <class InputIterator1, class InputIterator2>
      bool equal_vector ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
      while (first1!=last1) {
        if (!(*first1 == *first2))
          return false;
        ++first1; ++first2;
      }
      return true;
    }

    template <class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return equal_vector(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare_vector (InputIterator1 first1, InputIterator1 last1,
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
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        if (lhs == rhs)
            return false;
        return true;
    }

    template <class T, class Alloc>
    bool operator< (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return lexicographical_compare_vector(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        if (lhs < rhs || lhs == rhs)
            return true;
        return false;
    }

    template <class T, class Alloc>
    bool operator> (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        if (lhs < rhs)
            return false;
        if (lhs == rhs)
            return false;
        return true;
    }
    
    template <class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        if (!(lhs < rhs))
            return true;
        return false;
    }

    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
        Vector<T> tmp = x;
        x = y;
        y = tmp;
        tmp.clear();
    }
}

#endif
