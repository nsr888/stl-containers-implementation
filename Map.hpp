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
        std::pair<const Key, T> * pair;
        int height;
    };

    template<class Key, class T>
    struct Map_iterator {
        typedef ft::Map_iterator<Key, T>       iterator;
        typedef ft::Map_iterator<Key, T>       _Self;
        typedef int difference_type;
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef Node<Key, T>                            node;

        Map_iterator() : _node() {}
        Map_iterator<T>(const iterator & it) : _node(it._node) {}
        Map_iterator<T>(node * other) : _node(other) {}
        ~Map_iterator() {}
        void _increment() {
            _node = findSuccessor(std::make_pair(_node->pair->first, _node->pair->second)); 
        }
        void _decrement() { 
            _node = findPredecessor(std::make_pair(_node->pair->first, _node->pair->second)); 
        }
        _Self & operator=(const Map_iterator & other) {
            this->_node = other._node;
            return *this;
        }
        Key first(){ 
            return _node->pair->first; 
        }
        T second(){ 
            return _node->pair->second; 
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


        node* findPredecessor(const value_type& val)
        {
            node* prec = 0;
            node* rt = _node->root;
            while (1)
            {
                if (val.first < rt->pair->first) {
                    rt = rt->left;
                }
                else if (val.first > rt->pair->first)
                {
                    prec = rt;
                    rt = rt->right;
                }
                else {
                    if (rt->left) {
                        prec = findMax(rt->left);
                    }
                    break;
                }
                if (!rt) {
                    return 0;
                }
            }
            return prec;
        }


        node* findSuccessor(const value_type& val)
        {
            node* succ = 0;
            node* rt = _node->root;
            while (1)
            {
                if (val.first < rt->pair->first)
                {
                    succ = rt;
                    rt = rt->left;
                }
                else if (val.first > rt->pair->first) {
                    rt = rt->right;
                }
                else {
                    if (rt->right) {
                        succ = findMin(rt->right);
                    }
                    break;
                }
                if (!rt) {
                    return nullptr;
                }
            }
            return succ;
        }


        node * _node;
    };

    template<class Key, class T, class Compare = std::less<Key>,
        class _Alloc = std::allocator<std::pair<const Key, T> > >
    class Map {
    public:
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef std::pair<const key_type, mapped_type>  value_type;
        typedef std::less<Key>                          key_compare;
        /* typedef value_compare()                         value_comp; */
        typedef _Alloc                                  allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef ft::Map_iterator<Key, T>              iterator;
        /* typedef ft::Map_const_iterator<T>        const_iterator; */
        /* typedef ft::Map_reverse_iterator<T>      reverse_iterator; */
        /* typedef ft::Map_const_reverse_iterator<T>    const_reverse_iterator; */
        typedef std::ptrdiff_t                          difference_type;
        typedef size_t                                  size_type;
        typedef typename _Alloc::template rebind<Node<Key, T> >::other
            node_allocator;
        typedef Node<Key, T>                            node;


        Map(){
            this->_root = NULL;
        };
        ~Map(){};
        void display() {
            _printTree(this->_root, "", false);
        };
        std::pair<iterator,bool> insert(const value_type& val) {
            node * found_before = findNode(val.first);
            if (found_before) {
                return std::make_pair(iterator(found_before),false);
            }
            this->_root = _insert(this->_root, val);
            /* node * found_after = findNode(val.first); */
            return std::make_pair(iterator(findNode(val.first)),true);
        };
        void remove(const value_type& val) {
            this->_root = _deleteNode(this->_root, val);
        };
        iterator begin() {
            node * tmp;
            tmp = _root;
            return iterator(findMin(tmp));
        }
        iterator end() {
            node * tmp;
            tmp = _root;
            return iterator(findMax(tmp));
        }
        mapped_type& operator[] (const key_type& k) {
            node * found = findNode(k);
            if (found == 0) {
                insert(std::make_pair(k, mapped_type()));
                found = findNode(k);
                return findNode(k)->pair->second;
            }
            return found->pair->second;
        }
        /* node * findNode(const key_type& k) { */
        /*     node * curr = _root; */
        /*     while (curr != 0) { */
        /*         std::cout << "key: " << curr->pair->first << std::endl; */
        /*         if (curr->pair->first == k) { */
        /*             return curr; */
        /*         } else if (curr->pair->first < k) { */
        /*             curr = curr->left; */
        /*         } else { */
        /*             curr = curr->right; */
        /*         } */
        /*     } */
        /*     return curr; */
        /* } */
        node * findNode(const key_type& k) {
            node * curr = _root;
            node * parent = 0;
            while (curr != 0 && curr->pair->first != k)
            {
                parent = curr;
                if (k < curr->pair->first) {
                    curr = curr->left;
                }
                else {
                    curr = curr->right;
                }
            }
            if (curr == 0) {
                return 0;
            }
            if (parent == 0) {
                return _root;
            } else {
                return curr;
            }
        }
        

    private:
        node * _root;
        node_allocator  _node_alloc;
        _Alloc          _data_alloc;


        /* AVL tree */
        node* _insert(node *r, const value_type& val){
            if(r == NULL){
                node *n;
                n = _node_alloc.allocate(1);
                _node_alloc.construct(n, node());

                value_type * pr = _data_alloc.allocate(1);
                _data_alloc.construct(pr, val);

                n->pair = pr;
                r = n;
                r->left = r->right = 0;
                r->height = 1; 
                r->root = this->_root;
                return r;             
            }
            else{
                if(val.first < r->pair->first)
                    r->left = _insert(r->left,val);
                else
                    r->right = _insert(r->right,val);
            }
            r->height = _calheight(r);
            if(_bf(r)==2 && _bf(r->left)==1){
                r = _llrotation(r);
            }
            else if(_bf(r)==-2 && _bf(r->right)==-1){
                r = _rrrotation(r);
            }
            else if(_bf(r)==-2 && _bf(r->right)==1){
                r = _rlrotation(r);
            }
            else if(_bf(r)==2 && _bf(r->left)==-1){
                r = _lrrotation(r);
            }        
            return r;
        }


        node * _deleteNode(node *p, const value_type& val){
            if(p->left == NULL && p->right == NULL){
                if(p==this->_root)
                    this->_root = NULL;
                _node_alloc.destroy(p);
                _node_alloc.deallocate(p, 1);
                return NULL;
            }
            node *q;
            if(p->pair->first < val.first){
                p->right = _deleteNode(p->right, val);
            }
            else if(p->pair->first > val.first){
                p->left = _deleteNode(p->left, val);
            }
            else{
                if(p->left != NULL){
                    q = findMax(p->left);
                    _data_alloc.destroy(p->pair);
                    _data_alloc.deallocate(p->pair, 1);
                    p->pair = q->pair;
                    p->left = _deleteNode(p->left, *q->pair);
                }
                else{
                    q = findMin(p->right);
                    _data_alloc.destroy(p->pair);
                    _data_alloc.deallocate(p->pair, 1);
                    p->pair = q->pair;
                    p->right = _deleteNode(p->right, *q->pair);
                }
            }
            if(_bf(p) == 2 && _bf(p->left) == 1){ p = _llrotation(p); } 
            else if(_bf(p)==2 && _bf(p->left)==-1){ p = _lrrotation(p); }
            else if(_bf(p)==2 && _bf(p->left)==0){ p = _llrotation(p); }
            else if(_bf(p)==-2 && _bf(p->right)==-1){ p = _rrrotation(p); }
            else if(_bf(p)==-2 && _bf(p->right)==1){ p = _rlrotation(p); }
            else if(_bf(p)==-2 && _bf(p->right)==0){ p = _llrotation(p); }
            return p;
        }


        int _calheight(node * p){
            if(p->left && p->right){
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
            }
            else if(p->left && p->right == NULL){
               return p->left->height + 1;
            }
            else if(p->left ==NULL && p->right){
               return p->right->height + 1;
            }
            return 0;
        }


        int _bf(node *n){
            if(n->left && n->right){
                return n->left->height - n->right->height; 
            }
            else if(n->left && n->right == NULL){
                return n->left->height; 
            }
            else if(n->left== NULL && n->right ){
                return -n->right->height;
            }
            return 0;
        }


        node * _llrotation(node *n){
            node *p;
            node *tp;
            p = n;
            tp = p->left;

            p->left = tp->right;
            tp->right = p;

            return tp; 
        }


        node* _rrrotation(node*n){
            node *p;
            node *tp;
            p = n;
            tp = p->right;

            p->right = tp->left;
            tp->left = p;

            return tp; 
        }


        node * _rlrotation(node *n){
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


        node * _lrrotation(node *n){
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


        

        

        /* print tree for testing only */
        void _printTree(node *node, std::string prefix, bool isLeft) {
            if (node != nullptr) {
                std::cout << prefix;
                std::cout << (isLeft ? "├──" : "└──" );
                std::cout << node->pair->first << node->pair->second << std::endl;
                _printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
                _printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
            }
        }
        
    };


    template<class Key, class T>
    Node<Key, T> * findMax(Node<Key, T> * p){
        while(p->right != NULL)
            p = p->right;
        return p;    
    }

    template<class Key, class T>
    Node<Key, T> * findMin(Node<Key, T> * p){
        while(p->left != NULL)
            p = p->left;
        return p;    
    }
};
#endif
