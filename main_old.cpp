#include "List.hpp"

int main() {
    /* ft::List<int> lst; */
    {
        ft::List<int>* lst = new ft::List<int>;
        lst->push_back(77);
        std::cout << "mylist->front() is now " << lst->front() << '\n';
        lst->push_back(22);
        lst->front() -= lst->back();
        std::cout << "mylist->front() is now " << lst->front() << '\n';
        delete lst;
        while (1) {};
    }
    /* ft::List<int> empty_list; */
	/* { */
		/* std::cout << "[begin] == [end] on empty list" << '\n'; */
			/* assert(empty_list.begin() == empty_list.end()); */
		/* std::cout << "max_size (list) = " << empty_list.max_size() << '\n'; */
		/* std::cout << "empty? " << empty_list.empty() << '\n'; */
			/* assert(empty_list.empty()); */
    /*     std::cout << "empty list size = " << empty_list.size() << '\n'; */
			/* assert(empty_list.size() == 0); */
	/* } */

    /* ft::List<int> lst; */
	/* lst.push_back(5); */
	/* lst.push_back(42); */
	/* { */
		/* std::cout << "list [5, 42].size() = " << lst.size() << '\n'; */
			/* assert(lst.size() == 2); */
		/* std::cout << "[5, 42].front() = " << lst.front() << " (it:" << *lst.begin() << ")" << '\n'; */
			/* assert(lst.front() == 5); */
			/* assert(*lst.begin() == 5); */
		/* std::cout << "[5, 42].back()  = " << lst.back() << " (it:" << *--lst.end() << ")" << '\n'; */
			/* assert(lst.back() == 42); */
			/* assert(*--lst.end() == 42); */
	/* } */
    return 0;
}
