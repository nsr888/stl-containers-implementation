#include "Map.hpp"

int main() {
    ft::Map<int, int> b;

    b.insert(std::make_pair(33,1));
    b.insert(std::make_pair(13,2));
    b.insert(std::make_pair(53,3));
    b.insert(std::make_pair(9,4));
    b.insert(std::make_pair(21,5));
    b.insert(std::make_pair(61,6));
    b.insert(std::make_pair(8,7));
    b.insert(std::make_pair(11,8));
    b.display();
    b.remove(std::make_pair(13,0));
    b.display();
    ft::Map_iterator<int, int> it = b.begin();
    std::cout << it.first() << std::endl;
    ft::Map_iterator<int, int> finish = b.end();
    std::cout << "end: " << finish.first() << std::endl;
    --finish;
    std::cout << "--end(): " << finish.first() << std::endl;
    finish++;
    std::cout << "++end(): " << finish.first() << std::endl;
    std::cout << "find 8,7 second is: " << b.findNode(8)->pair->second << std::endl;
    /* while(1) */
    /*     ; */
}
