#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>

namespace ft
{
    template<class Key, class T>
    struct Node {
        Node                    *left;
        Node                    *right;
        Node                    *root;
        bool                    is_end_node;
        std::pair<const Key, T> *pair;
        int height;
    };


    template<class Key, class T, class Compare = std::less<Key> >
    struct Map_iterator {
        typedef ft::Map_iterator<Key, T>                iterator;
        typedef ft::Map_iterator<Key, T>                _Self;
        typedef int                                     difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;
        typedef Compare                                 key_compare;

        Map_iterator() : _node() {}
        Map_iterator<T>(const iterator & it) : _node(it._node) {}
        Map_iterator<T>(node * other) : _node(other) {}
        ~Map_iterator() {}

        _Self & 
        operator=(const Map_iterator & other) 
        {
            this->_node = other._node;
            return *this;
        }

        bool operator==(const Map_iterator & other) const {
          return _node == other._node;
        }

        bool operator!=(const Map_iterator & other) const {
          return _node != other._node;
        }

        void 
        _increment() 
        {
            node * max = findMax(_node->root);
            if (_node == max)
                _node = _node->right;
            else 
            {
                _node = findSuccessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        void 
        _decrement() 
        { 
            if (_node->is_end_node)
                _node = findMax(_node->root);
            else
            {
                _node = findPredecessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        value_type &
        operator*()
        {
            return (*_node->pair);
        }

        value_type *
        operator->()
        {
            return (_node->pair);
        }

        _Self & 
        operator++() 
        { 
          this->_increment();
          return *this;
        }

        _Self 
        operator++(int) 
        { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }

        _Self & 
        operator--() 
        { 
          this->_decrement();
          return *this;
        }

        _Self 
        operator--(int) 
        { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        key_compare _compare;
        node *      _node;
    };


    template<class Key, class T, class Compare = std::less<Key> >
    struct Map_const_iterator: public Map_iterator<Key, T> {
        typedef ft::Map_const_iterator<Key, T>          iterator;
        typedef ft::Map_const_iterator<Key, T>          _Self;
        typedef int                                     difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;
        typedef Compare                                 key_compare;


        Map_const_iterator() : _node() {}
        Map_const_iterator<T>(const iterator & it) : _node(it._node) {}
        Map_const_iterator<T>(node * other) : _node(other) {}
        ~Map_const_iterator() {}

        _Self & 
        operator=(const Map_const_iterator & other)
        {
            this->_node = other._node;
            return *this;
        }

        bool operator==(const Map_const_iterator & other) const {
          return _node == other._node;
        }

        bool operator!=(const Map_const_iterator & other) const {
          return _node != other._node;
        }

        void 
        _increment() 
        {
            node * max = findMax(_node->root);
            if (_node == max)
                _node = _node->right;
            else 
            {
                _node = findSuccessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        void 
        _decrement() 
        { 
            if (_node->is_end_node)
                _node = findMax(_node->root);
            else
            {
                _node = findPredecessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        value_type &
        operator*()
        {
            return (*_node->pair);
        }

        value_type *
        operator->()
        {
            return (_node->pair);
        }

        _Self & 
        operator++() 
        { 
          this->_increment();
          return *this;
        }

        _Self 
        operator++(int) 
        { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }

        _Self & 
        operator--() 
        { 
          this->_decrement();
          return *this;
        }

        _Self 
        operator--(int) 
        { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        key_compare _compare;
        node * _node;
    };


    template<class Key, class T, class Compare = std::less<Key> >
    struct Map_reverse_iterator {
        typedef ft::Map_reverse_iterator<Key, T>        iterator;
        typedef ft::Map_reverse_iterator<Key, T>        _Self;
        typedef int                                     difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;
        typedef Compare                                 key_compare;

        Map_reverse_iterator() : _node() {}
        Map_reverse_iterator<T>(const iterator & it) : _node(it._node) {}
        Map_reverse_iterator<T>(node * other) : _node(other) {}
        ~Map_reverse_iterator() {}

        _Self & 
        operator=(const Map_reverse_iterator & other) 
        {
            this->_node = other._node;
            return *this;
        }

        bool operator==(const Map_reverse_iterator & other) const {
          return _node == other._node;
        }

        bool operator!=(const Map_reverse_iterator & other) const {
          return _node != other._node;
        }

        void 
        _increment() 
        {
            node * max = findMax(_node->root);
            if (_node == max)
                _node = _node->right;
            else 
            {
                _node = findSuccessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        void 
        _decrement() 
        { 
            if (_node->is_end_node)
                _node = findMax(_node->root);
            else
            {
                _node = findPredecessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        value_type &
        operator*()
        {
            return (*_node->pair);
        }

        value_type *
        operator->()
        {
            return (_node->pair);
        }

        _Self & 
        operator++() 
        { 
          this->_decrement();
          return *this;
        }

        _Self 
        operator++(int) 
        { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        _Self & 
        operator--() 
        { 
          this->_increment();
          return *this;
        }

        _Self 
        operator--(int) 
        { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }

        key_compare _compare;
        node *      _node;
    };


    template<class Key, class T, class Compare = std::less<Key> >
    struct Map_const_reverse_iterator {
        typedef ft::Map_const_reverse_iterator<Key, T>  iterator;
        typedef ft::Map_const_reverse_iterator<Key, T>  _Self;
        typedef int difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;
        typedef Compare                                 key_compare;

        Map_const_reverse_iterator () : _node() {}
        Map_const_reverse_iterator <T>(const iterator & it) : _node(it._node) {}
        Map_const_reverse_iterator<T>(node * other) : _node(other) {}
        ~Map_const_reverse_iterator() {}

        _Self & 
        operator=(const Map_const_reverse_iterator & other) 
        {
            this->_node = other._node;
            return *this;
        }

        bool operator==(const Map_const_reverse_iterator & other) const {
          return _node == other._node;
        }

        bool operator!=(const Map_const_reverse_iterator & other) const {
          return _node != other._node;
        }

        void 
        _increment() 
        {
            node * max = findMax(_node->root);
            if (_node == max)
                _node = _node->right;
            else 
            {
                _node = findSuccessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        void 
        _decrement() 
        { 
            if (_node->is_end_node)
                _node = findMax(_node->root);
            else
            {
                _node = findPredecessor(std::make_pair(_node->pair->first, 
                        _node->pair->second), this->_node, _compare); 
            }
        }

        value_type &
        operator*()
        {
            return (*_node->pair);
        }

        value_type *
        operator->()
        {
            return (_node->pair);
        }

        _Self & 
        operator++() 
        { 
          this->_decrement();
          return *this;
        }

        _Self 
        operator++(int) 
        { 
          _Self __tmp = *this;
          this->_decrement();
          return __tmp;
        }

        _Self & 
        operator--() 
        { 
          this->_increment();
          return *this;
        }

        _Self 
        operator--(int) 
        { 
          _Self __tmp = *this;
          this->_increment();
          return __tmp;
        }

        key_compare _compare;
        node *      _node;
    };


    template<class Key, class T, class Compare = std::less<Key>,
        class _Alloc = std::allocator<std::pair<const Key, T> > >
    class Map {
    protected:
        typedef Node<Key, T>                            node;
        typedef typename _Alloc::template rebind<Node<Key, T> >::other
            node_allocator;

    public:
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Compare                                 key_compare;
        typedef _Alloc                                  allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef ft::Map_iterator<Key, T>                iterator;
        typedef ft::Map_const_iterator<Key, T>          const_iterator;
        typedef ft::Map_reverse_iterator<Key, T>        reverse_iterator;
        typedef ft::Map_const_reverse_iterator<Key, T>  const_reverse_iterator;
        typedef std::ptrdiff_t                          difference_type;
        typedef size_t                                  size_type;

        Map(const key_compare & compare = key_compare()){
            this->_compare = compare;
            this->_root = 0;
            _init_end_nodes();
        };
        
        Map(iterator start, iterator finish, const key_compare & compare = key_compare()) {
            this->_compare = compare;
            this->_root = 0;
            _init_end_nodes();
            while (start != finish) {
                insert(std::make_pair(start->first, start->second));
                ++start;
            }
        }

        Map & operator=(const Map & other) {
            if (this == &other)
                return *this;
            this->_root = 0;
            _init_end_nodes();
            for(const_iterator it = other.begin(); it != other.end(); ++it)
                insert(std::make_pair(it->first, it->second));
            return *this;
        }

        Map(const Map & other) {
            *this = other;
        }

        ~Map(){
            _destroy_end_nodes();
        };

        std::pair<iterator,bool> 
        insert(const value_type& val)
        {
            node * found = findNode(val.first);
            if (found) { return std::make_pair(iterator(found),false); }
            _deattach_end_nodes();
            this->_root = _insert(this->_root, val);
            _attach_end_nodes();
            _update_all_nodes_root(this->_root, this->_root);
            return std::make_pair(find(val.first),true);
        };

        mapped_type& 
        operator[] (const key_type& k) 
        {
            node * found = findNode(k);
            if (found == 0) {
                insert(std::make_pair(k, mapped_type()));
                found = findNode(k);
                return findNode(k)->pair->second;
            }
            return found->pair->second;
        }

        iterator 
        insert (iterator position, const value_type& val)
        {
            node * found = findNode(val.first);
            if (found) { return iterator(found); }
            if (position == end())
                this->_root = _insert(this->_root, val);
            node * parent = findNodeParent(position->first);
            node * pos = findNode(position->first);
            _deattach_end_nodes();
            /* insert to left only if val < parent */
            if (parent->left == pos && _compare(val.first, parent->pair->first))
            {
                pos = _insert(pos, val);
                parent->left = pos;
            }
            /* insert to right only if val > parent */
            else if (parent->right == pos && _compare(parent->pair->first, val.first)) 
            {
                pos = _insert(pos, val);
                parent->right = pos;
            }
            else {
                this->_root = _insert(this->_root, val);
            }
            _attach_end_nodes();
            _update_all_nodes_root(this->_root, this->_root);
            return find(val.first);
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) 
        {
            while (first != last)
            {
                insert(*first);
                ++first;
            }
        }

        size_type 
        erase(const key_type& k) 
        {
            node * found = findNode(k);
            if (found == 0)
                return 0;
            _deattach_end_nodes();
            this->_root = _delete_node(this->_root, k);
            _attach_end_nodes();
            _update_all_nodes_root(this->_root, this->_root);
            return 1;
        };
        
        void
        erase(iterator position) 
        {
            erase(position->first);
        };

        void
        erase (iterator first, iterator last) {
            iterator next;
            while(next != last)
            {
                next = first;
                ++next;
                erase(first);
                first = next;
            }
        }

        void
        clear()
        {
            iterator tmp;
            iterator first = begin();
            iterator last = end();
            while(tmp != last)
            {
                tmp = first;
                ++tmp;
                erase(first);
                first = tmp;
            }
        }

        iterator 
        begin() 
        {
            if (this->_root == 0)
                return 0;
            node * tmp;
            tmp = _root;
            return iterator(findMin(tmp));
        }

        iterator 
        end() {
            if (this->_root == 0)
                return 0;
            return iterator(this->_end); 
        }

        const_iterator
        begin() const
        {
            if (this->_root == 0)
                return 0;
            node * tmp;
            tmp = _root;
            return const_iterator(findMin(tmp));
        }

        const_iterator 
        end() const 
        { 
            if (this->_root == 0)
                return 0;
            return const_iterator(this->_end); 
        }

        reverse_iterator 
        rbegin() 
        {
            if (this->_root == 0)
                return 0;
            node * tmp;
            tmp = _root;
            return reverse_iterator(findMax(tmp));
        }

        reverse_iterator 
        rend() 
        {
            if (this->_root == 0)
                return 0;
            return reverse_iterator(this->_rend); 
        }

        const_reverse_iterator 
        rbegin() const
        {
            if (this->_root == 0)
                return 0;
            node * tmp;
            tmp = _root;
            return const_reverse_iterator(findMax(tmp));
        }

        const_reverse_iterator
        rend() const
        {
            if (this->_root == 0)
                return 0;
            return const_reverse_iterator(this->_rend); 
        }

    private:
        size_type 
        _count_nodes_recursive(node * p) const 
        {
            size_type count = 1;
            if (p->left != 0 && !p->left->is_end_node)
                count += _count_nodes_recursive(p->left);
            if (p->right != 0 && !p->right->is_end_node)
                count += _count_nodes_recursive(p->right);
            return count;
        }

    public:
        size_type 
        size() const 
        {
            size_type count = 0;
            if (this->_root == 0)
                return 0;
            count = _count_nodes_recursive(this->_root);
            return count;
        };

        size_type
        count (const key_type& k) const
        {
            if (find(k) == end())
                return 0;
            return 1;
        }

        bool 
        empty() const
        {
            if (this->_root == 0)
                return true;
            return false;
        }

        const_iterator
        find (const key_type& k) const
        {
            node * curr = _root;
            node * parent = 0;
            while (curr != 0 && !is_keys_equal(curr->pair->first, k))
            {
                parent = curr;
                if (_compare(k, curr->pair->first)) 
                    curr = curr->left;
                else 
                    curr = curr->right;
            }
            if (curr == 0) 
                return const_iterator(this->end());
            else
                return const_iterator(curr);
        }

        iterator
        find (const key_type& k) 
        {
            node * curr = _root;
            node * parent = 0;
            while (curr != 0 && !is_keys_equal(curr->pair->first, k))
            {
                parent = curr;
                if (_compare(k, curr->pair->first)) 
                    curr = curr->left;
                else 
                    curr = curr->right;
            }
            if (curr == 0) 
                return iterator(this->end());
            else
                return iterator(curr);
        }

        key_compare 
        key_comp() const 
        {
            return (_compare);
        }

        iterator 
        lower_bound (const key_type& k) 
        {
            key_compare mycomp = key_comp();
            iterator first = begin();
            iterator last = end();
            while(first != last)
            {
                if (!mycomp(first->first, k))
                    return first;
                ++first;
            }
            return end();
        }

        const_iterator
        lower_bound (const key_type& k) const
        {
            key_compare mycomp = key_comp();
            const_iterator first = begin();
            const_iterator last = end();
            while(first != last)
            {
                if (!mycomp(first->first, k))
                    return first;
                ++first;
            }
            return last;
        }

        iterator 
        upper_bound (const key_type& k) 
        {
            key_compare mycomp = key_comp();
            iterator first = begin();
            iterator last = end();
            while(first != last)
            {
                if (!mycomp(first->first, k) && !is_keys_equal(first->first, k))
                    return first;
                ++first;
            }
            return end();
        }

        const_iterator 
        upper_bound (const key_type& k) const
        {
            key_compare mycomp = key_comp();
            const_iterator first = begin();
            const_iterator last = end();
            while(first != last)
            {
                if (!mycomp(first->first, k) && !is_keys_equal(first->first, k))
                    return first;
                ++first;
            }
            return last;
        }

        std::pair<const_iterator, const_iterator> 
        equal_range (const key_type& k) const 
        {
            return(std::make_pair(lower_bound(k),upper_bound(k)));
        }

        std::pair<iterator, iterator> 
        equal_range (const key_type& k)
        {
            return(std::make_pair(lower_bound(k),upper_bound(k)));
        }

        size_t max_size() const 
        { 
            return ((pow(2, 64) / sizeof(node)) - 1); 
        }

        class value_compare: public std::binary_function<value_type, value_type, bool>
        {
            friend class map;
        protected:
            Compare comp;
        public:
            value_compare (Compare c) : comp(c) {}
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

        value_compare value_comp() const
        {
            return (value_compare(key_comp()));
        }

        void 
        swap (Map& x)
        {
            Map tmp = *this;
            *this = x;
            x = tmp;
            tmp.clear();
        }

        void 
        display() 
        {
            _print_tree(this->_root, "", false);
        };


    private:
        node *          _root;
        node *          _rend;
        node *          _end;
        node_allocator  _node_alloc;
        _Alloc          _data_alloc;
        key_compare     _compare;


        /* AVL tree */
        node* 
        _alloc_node(const value_type& val, bool is_end_node)
        {
            node *n;
            n = _node_alloc.allocate(1);
            _node_alloc.construct(n, node());

            value_type * pr = _data_alloc.allocate(1);
            _data_alloc.construct(pr, val);

            n->pair = pr;
            n->left = n->right = 0;
            n->is_end_node = (is_end_node) ? true : false;
            n->root = this->_root;
            n->height = 1; 
            return n;             
        }

        void
        _dealloc_node(node * p)
        {
            _data_alloc.destroy(p->pair);
            _data_alloc.deallocate(p->pair, 1);
            _node_alloc.destroy(p);
            _node_alloc.deallocate(p, 1);
            p = 0;
        }

        node* 
        _insert(node *r, const value_type& val)
        {
            if(r == 0)
            {
                r = _alloc_node(val, false);
                return r;
            }
            else
            {
                if(_compare(val.first, r->pair->first))
                    r->left = _insert(r->left, val);
                else
                    r->right = _insert(r->right, val);
            }
            this->_root->height = _update_height(this->_root);
            if (_bf(r) == 2 && _bf(r->left) == 1)
            {
                r = _llrotation(r);
            }
            else if (_bf(r) == -2 && _bf(r->right) == -1)
            {
                r = _rrrotation(r);
            }
            else if (_bf(r) == -2 && _bf(r->right) == 1)
            {
                r = _rlrotation(r);
            }
            else if (_bf(r) == 2 && _bf(r->left) == -1)
            {
                r = _lrrotation(r);
            }        
            this->_root->height = _update_height(this->_root);
            return r;
        }

        node * 
        _delete_node(node *p, const key_type& k)
        {
            if(p->left == 0 && p->right == 0)
            {
                if (p == this->_root)
                    this->_root = 0;
                _node_alloc.destroy(p);
                _node_alloc.deallocate(p, 1);
                return 0;
            }
            node *q;
            if (_compare(p->pair->first, k))
            {
                p->right = _delete_node(p->right, k);
            }
            else if (_compare(k, p->pair->first))
            {
                p->left = _delete_node(p->left, k);
            }
            else
            {
                if(p->left != 0)
                {
                    q = findMax(p->left);
                    _data_alloc.destroy(p->pair);
                    _data_alloc.deallocate(p->pair, 1);
                    p->pair = q->pair;
                    p->left = _delete_node(p->left, q->pair->first);
                }
                else
                {
                    q = findMin(p->right);
                    _data_alloc.destroy(p->pair);
                    _data_alloc.deallocate(p->pair, 1);
                    p->pair = q->pair;
                    p->right = _delete_node(p->right, q->pair->first);
                }
            }
            this->_root->height = _update_height(this->_root);
            if (_bf(p) == 2 && _bf(p->left) == 1) 
            { 
                p = _llrotation(p); 
            } 
            else if (_bf(p) == 2 && _bf(p->left) == -1) 
            { 
                p = _lrrotation(p); 
            }
            else if (_bf(p) == 2 && _bf(p->left) == 0)
            {
                p = _llrotation(p);
            }
            else if (_bf(p) == -2 && _bf(p->right) == -1) 
            {
                p = _rrrotation(p); 
            }
            else if (_bf(p) == -2 && _bf(p->right) == 1) 
            { 
                p = _rlrotation(p); 
            }
            else if (_bf(p) == -2 && _bf(p->right) == 0) 
            { 
                p = _llrotation(p); 
            }
            return p;
        }

        int 
        _update_height(node * root)
        {
            if (root == 0)
                return 0;
            if (root->left)
                root->left->height = _update_height(root->left);
            if (root->right)
                root->right->height = _update_height(root->right);
            return 1 + std::max(_update_height(root->left), _update_height(root->right));
        }

        int 
        _calc_height(node * p)
        {
            if (p->left && p->right)
            {
                if (p->left->height < p->right->height)
                    return p->right->height + 1;
                else 
                    return  p->left->height + 1;
            }
            else if (p->left && p->right == 0)
            {
               return p->left->height + 1;
            }
            else if (p->left == 0 && p->right)
            {
               return p->right->height + 1;
            }
            return 1;
        }

        int 
        _bf(node *n)
        {
            if (n->left && n->right)
            {
                return n->left->height - n->right->height; 
            }
            else if (n->left && n->right == 0)
            {
                return n->left->height; 
            }
            else if (n->left == 0 && n->right )
            {
                return -n->right->height;
            }
            return 0;
        }

        node * 
        _llrotation(node *n)
        {
            node *p;
            node *new_root;
            p = n;
            new_root = p->left;
            p->left = new_root->right;
            new_root->right = p;
            return new_root; 
        }

        node* 
        _rrrotation(node*n)
        {
            node *p;
            node *new_root;
            p = n;
            new_root = p->right;
            p->right = new_root->left;
            new_root->left = p;
            return new_root; 
        }

        node *
        _rlrotation(node *n)
        {
            node *p;
            node *tp;
            node *new_root;
            p = n;
            tp = p->right;
            new_root = p->right->left;
            p->right = new_root->left;
            tp->left = new_root->right;
            new_root->left = p;
            new_root->right = tp; 
            return new_root; 
        }

        node * 
        _lrrotation(node *n)
        {
            node *p;
            node *tp;
            node *new_root;
            p = n;
            tp = p->left;
            new_root =p->left->right;
            p->left = new_root->right;
            tp->right = new_root->left;
            new_root->right = p;
            new_root->left = tp; 
            return new_root; 
        }

        void
        _init_end_nodes()
        {
            this->_end = _alloc_node(value_type(), true);
            this->_rend = _alloc_node(value_type(), true);
        }

        void
        _destroy_end_nodes()
        {
            _dealloc_node(this->_end);
            _dealloc_node(this->_rend);
        }

        void 
        _attach_end_nodes() 
        {
            if (this->_root == 0)
                return;
            findMin(_root)->left = this->_rend;
            findMax(_root)->right = this->_end;
        }

        void 
        _deattach_end_nodes() 
        {
            if (this->_root == 0)
                return;
            findMin(this->_root)->left = 0;
            findMax(this->_root)->right = 0;
        }

        void _update_all_nodes_root(node * p, node * rt) {
            if (p == 0)
                return;
            p->root = rt;
            _update_all_nodes_root(p->left, rt);
            _update_all_nodes_root(p->right, rt);
        };

        bool is_keys_equal(key_type k1, key_type k2) const
        {
            key_compare mycomp = key_comp();
            if (mycomp(k1, k2) == false && mycomp(k2, k1) == false)
                return true;
            return false;
        }

        node * 
        findNode(const key_type& k) 
        {
            key_compare mycomp = key_comp();
            node * curr = _root;
            node * parent = 0;
            while (curr != 0 && !is_keys_equal(curr->pair->first, k))
            {
                parent = curr;
                if (mycomp(k, curr->pair->first)) 
                    curr = curr->left;
                else 
                    curr = curr->right;
            }
            if (curr == 0) 
                return 0;
            if (parent == 0) 
                return _root;
            else
                return curr;
        }

        node * 
        findNodeParent(const key_type& k) 
        {
            key_compare mycomp = key_comp();
            node * curr = _root;
            node * parent = 0;
            while (curr != 0 && !is_keys_equal(curr->pair->first, k))
            {
                parent = curr;
                if (mycomp(k, curr->pair->first)) 
                    curr = curr->left;
                else 
                    curr = curr->right;
            }
            if (curr == 0) 
                return 0;
            if (parent == 0) 
                return _root;
            else
                return parent;
        }

        /* Debugging */
        /* void */ 
        /* _print_tree(node *node, std::string prefix, bool isLeft) */ 
        /* { */
        /*     if (node != 0) */ 
        /*     { */
        /*         std::cout << prefix; */
        /*         std::cout << (isLeft ? "├──" : "└──" ); */
        /*         std::cout << node->pair->first << "(" << node->height << ")" << std::endl; */
        /*         _print_tree(node->left, prefix + (isLeft ? "│   " : "    "), true); */
        /*         _print_tree(node->right, prefix + (isLeft ? "│   " : "    "), false); */
        /*     } */
        /* } */
    };


    template<class Key, class T>
    Node<Key, T> * 
    findMax(Node<Key, T> * p)
    {
        if (p == 0)
            return p;
        while(p->right != 0 && p->right->is_end_node != true)
            p = p->right;
        return p;    
    }


    template<class Key, class T>
    Node<Key, T> * 
    findMin(Node<Key, T> * p)
    {
        if (p == 0)
            return p;
        while(p->left != 0 && p->left->is_end_node != true)
            p = p->left;
        return p;    
    }

    template<class Key, class T>
    Node<Key, T> *
    findPredecessor(const std::pair<Key, T>& val, Node<Key, T> * p, 
            typename ft::Map<Key, T>::key_compare _compare)
    {
        Node<Key, T>* predecessor = 0;
        Node<Key, T>* root = p->root;
        while (1)
        {
            if (_compare(val.first, root->pair->first))
            {
                root = root->left;
            }
            else if (val.first > root->pair->first)
            {
                predecessor = root;
                root = root->right;
            }
            else 
            {
                if (root->left) 
                {
                    predecessor = findMax(root->left);
                }
                break;
            }
            if (!root) 
            {
                return 0;
            }
        }
        return predecessor;
    }

    template<class Key, class T>
    Node<Key, T> *
    findSuccessor(const std::pair<Key, T>& val, Node<Key, T> * p, 
            typename ft::Map<Key, T>::key_compare _compare)
    {
        Node<Key, T>* successor = 0;
        Node<Key, T>* root = p->root;
        while (1)
        {
            if (_compare(val.first, root->pair->first))
            {
                successor = root;
                root = root->left;
            }
            else if (val.first > root->pair->first) {
                root = root->right;
            }
            else {
                if (root->right) {
                    successor = findMin(root->right);
                }
                break;
            }
            if (!root) {
                return 0;
            }
        }
        return successor;
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y) {
        Map<Key, T> tmp = x;
        x = y;
        y = tmp;
        tmp.clear();
    }

    template <class InputIterator1, class InputIterator2>
      bool equal_maps ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
      while (first1!=last1) {
        if (!(*first1 == *first2))
          return false;
        ++first1; ++first2;
      }
      return true;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator== (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return equal_maps(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare_maps (InputIterator1 first1, InputIterator1 last1,
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

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs) {
        if (lhs == rhs)
            return false;
        return true;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator< (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs) {
        return lexicographical_compare_maps(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs) {
        if (lhs < rhs || lhs == rhs)
            return true;
        return false;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator> (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs) {
        if (lhs < rhs)
            return false;
        if (lhs == rhs)
            return false;
        return true;
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator>= (const Map<Key, T, Compare, Alloc>& lhs, const Map<Key, T, Compare, Alloc>& rhs) {
        if (!(lhs < rhs))
            return true;
        return false;
    }
};
#endif
