#ifndef MAP_HPP
# define MAP_HPP
# include <functional>
/* # include <iostream> */
/* # include <utility> */

namespace ft
{
    template<class Key, class T>
    struct Node {
        public:
            std::pair<const Key, T> pair;
            Node *left;
            Node *right;
            int height;
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
        /* typedef ft::Map_iterator<T>              iterator; */
        /* typedef ft::Map_const_iterator<T>        const_iterator; */
        /* typedef ft::Map_reverse_iterator<T>      reverse_iterator; */
        /* typedef ft::Map_const_reverse_iterator<T>    const_reverse_iterator; */
        typedef std::ptrdiff_t                          difference_type;
        typedef size_t                                  size_type;

        Map(void);
        ~Map(void);
        Map(const Map & other);
        Map & operator=(const Map & other);
    private:
        Node<Key, T> * _map;
    };
};

#endif
