#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include <queue>
# include <unordered_map>

namespace ft
{
    template<class Key, class T>
    struct Node {
        Node *left;
        Node *right;
        Node *root;
        bool is_end_node;
        std::pair<const Key, T> * pair;
        int height;
    };

    template<class Key, class T, class Compare = std::less<Key> >
    struct Map_iterator {
        typedef ft::Map_iterator<Key, T>       iterator;
        typedef ft::Map_iterator<Key, T>       _Self;
        typedef int difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;
        typedef Compare                          key_compare;

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

        Key 
        first()
        { 
            return _node->pair->first; 
        }

        T 
        second()
        { 
            return _node->pair->second; 
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
        typedef ft::Map_const_iterator<Key, T>       iterator;
        typedef ft::Map_const_iterator<Key, T>       _Self;
        typedef int difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;
        typedef Compare                          key_compare;


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

        Key 
        first()
        { 
            return _node->pair->first; 
        }

        T 
        second()
        { 
            return _node->pair->second; 
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
        typedef Compare                          key_compare;
        /* typedef value_compare()                         value_comp; */
        typedef _Alloc                                  allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef ft::Map_iterator<Key, T>              iterator;
        typedef ft::Map_const_iterator<Key, T>        const_iterator;
        /* typedef ft::Map_reverse_iterator<T>      reverse_iterator; */
        /* typedef ft::Map_const_reverse_iterator<T>    const_reverse_iterator; */
        typedef std::ptrdiff_t                          difference_type;
        typedef size_t                                  size_type;

        Map(const key_compare & compare = key_compare()){
            this->_compare = compare;
            this->_root = 0;
            this->_rend = 0;
            this->_end = 0;
        };
        
        Map(iterator start, iterator finish, const key_compare & compare = key_compare()) {
            this->_compare = compare;
            this->_root = 0;
            this->_rend = 0;
            this->_end = 0;
            while (start != finish) {
                insert(std::make_pair(start.first(), start.second()));
                ++start;
            }
        }
        Map(const Map & other) {
            this->_root = 0;
            this->_rend = 0;
            this->_end = 0;
            for(const_iterator first = other.begin(); first != other.end(); ++first)
                insert(std::make_pair(first.first(), first.second()));
        }

        ~Map(){ };

        std::pair<iterator,bool> 
        insert(const value_type& val)
        {
            node * found = findNode(val.first);
            if (found) { return std::make_pair(iterator(found),false); }
            _delete_end_nodes();
            this->_root = _insert(this->_root, val);
            _insert_end_nodes();
            _update_all_nodes_root(this->_root, this->_root);
            return std::make_pair(iterator(findNode(val.first)),true);
        };

        void 
        remove(const value_type& val) 
        {
            this->_root = _delete_node(this->_root, val);
            _update_all_nodes_root(this->_root, this->_root);
        };

        iterator 
        begin() 
        {
            node * tmp;
            tmp = _root;
            return iterator(findMin(tmp));
        }

        iterator 
        end() { return iterator(this->_end); }

        const_iterator
        begin() const
        {
            node * tmp;
            tmp = _root;
            return const_iterator(findMin(tmp));
        }

        const_iterator 
        end() const { return const_iterator(this->_end); }

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

        void 
        display() 
        {
            _print_tree(this->_root, "", false);
        };

        node * 
        findNode(const key_type& k) 
        {
            node * curr = _root;
            node * parent = 0;
            while (curr != 0 && !is_keys_equal(curr->pair->first, k))
            {
                parent = curr;
                if (_compare(k, curr->pair->first)) 
                {
                    curr = curr->left;
                }
                else 
                {
                    curr = curr->right;
                }
            }
            if (curr == 0) 
            {
                return 0;
            }
            if (parent == 0) 
            {
                return _root;
            }
            else
            {
                return curr;
            }
        }

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
                /* std::cout << "_insert()" << val.first << std::endl; */
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
            r->height = _calc_height(r);
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
            return r;
        }

        node * 
        _delete_node(node *p, const value_type& val)
        {
            if(p->left == 0 && p->right == 0)
            {
                if(p==this->_root)
                    this->_root = NULL;
                _node_alloc.destroy(p);
                _node_alloc.deallocate(p, 1);
                return 0;
            }
            node *q;
            if(_compare(p->pair->first, val.first))
            {
                p->right = _delete_node(p->right, val);
            }
            else if (_compare(p->pair->first, val.first))
            {
                p->left = _delete_node(p->left, val);
            }
            else
            {
                if(p->left != 0)
                {
                    q = findMax(p->left);
                    _data_alloc.destroy(p->pair);
                    _data_alloc.deallocate(p->pair, 1);
                    p->pair = q->pair;
                    p->left = _delete_node(p->left, *q->pair);
                }
                else
                {
                    q = findMin(p->right);
                    _data_alloc.destroy(p->pair);
                    _data_alloc.deallocate(p->pair, 1);
                    p->pair = q->pair;
                    p->right = _delete_node(p->right, *q->pair);
                }
            }
            if (_bf(p) == 2 && _bf(p->left) == 1) { p = _llrotation(p); } 
            else if (_bf(p)==2 && _bf(p->left)==-1) { p = _lrrotation(p); }
            else if (_bf(p)==2 && _bf(p->left)==0) { p = _llrotation(p); }
            else if (_bf(p)==-2 && _bf(p->right)==-1) { p = _rrrotation(p); }
            else if (_bf(p)==-2 && _bf(p->right)==1) { p = _rlrotation(p); }
            else if (_bf(p)==-2 && _bf(p->right)==0) { p = _llrotation(p); }
            return p;
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
            else if (p->left && p->right == NULL)
            {
               return p->left->height + 1;
            }
            else if (p->left ==NULL && p->right)
            {
               return p->right->height + 1;
            }
            return 0;
        }

        int 
        _bf(node *n)
        {
            if (n->left && n->right)
            {
                return n->left->height - n->right->height; 
            }
            else if (n->left && n->right == NULL)
            {
                return n->left->height; 
            }
            else if (n->left== NULL && n->right )
            {
                return -n->right->height;
            }
            return 0;
        }

        node * 
        _llrotation(node *n)
        {
            node *p;
            node *tp;
            p = n;
            tp = p->left;

            p->left = tp->right;
            tp->right = p;

            return tp; 
        }

        node* 
        _rrrotation(node*n)
        {
            node *p;
            node *tp;
            p = n;
            tp = p->right;

            p->right = tp->left;
            tp->left = p;

            return tp; 
        }

        node *
        _rlrotation(node *n)
        {
            node *p;
            node *tp;
            node *tp2;
            p = n;
            tp = p->right;
            tp2 =p->right->left;

            p->right = tp2->left;
            tp->left = tp2->right;
            tp2->left = p;
            tp2->right = tp; 
            
            return tp2; 
        }

        node * 
        _lrrotation(node *n)
        {
            node *p;
            node *tp;
            node *tp2;
            p = n;
            tp = p->left;
            tp2 =p->left->right;

            p->left = tp2->right;
            tp->right = tp2->left;
            tp2->right = p;
            tp2->left = tp; 
            
            return tp2; 
        }

        void 
        _insert_end_nodes() 
        {
            if (this->_root == 0)
                return;
            node * tmp;
            tmp = _root;
            node * min = findMin(tmp);
            min->left = _alloc_node(value_type(), true);
            /* std::cout << "max" << std::endl; */
            this->_rend = min->left;
            tmp = _root;
            node * max = findMax(tmp);
            /* std::cout << "after_max" << std::endl; */
            max->right = _alloc_node(value_type(), true);
            /* _print_tree(_root, "", false); */
            this->_end = max->right;
        }

        void 
        _delete_end_nodes() 
        {
            if (this->_root == 0)
                return;
            node * tmp;
            tmp = _root;
            while(tmp->left != 0)
                tmp = tmp->left;
            findMin(this->_root)->left = 0;
            _dealloc_node(tmp);
            tmp = _root;
            while(tmp->right != 0)
                tmp = tmp->right;
            findMax(this->_root)->right = 0;
            _dealloc_node(tmp);
        }

        void _update_all_nodes_root(node * p, node * rt) {
            if (p == 0)
                return;
            p->root = rt;
            _update_all_nodes_root(p->left, rt);
            _update_all_nodes_root(p->right, rt);
        };

        bool is_keys_equal(key_type k1, key_type k2)
        {
            if (_compare(k1, k2) == false && _compare(k2, k1) == false)
                return true;
            return false;
        }

        /* Debugging */
        void 
        _print_tree(node *node, std::string prefix, bool isLeft) 
        {
            if (node != 0) 
            {
                std::cout << prefix;
                std::cout << (isLeft ? "├──" : "└──" );
                std::cout << node->pair->first << "(" << node->pair->second << ")" << std::endl;
                /* std::cout << node->pair->first << node->pair->second << std::endl; */
                _print_tree(node->left, prefix + (isLeft ? "│   " : "    "), true);
                _print_tree(node->right, prefix + (isLeft ? "│   " : "    "), false);
            }
        }
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
};
#endif
