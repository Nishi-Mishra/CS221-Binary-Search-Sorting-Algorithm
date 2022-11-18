#include <iostream>
#include <string>

#include "BinarySearchTree.h"

int main() {

    BinarySearchTree <int, int> hi;
    hi.insert(std::pair(5,6));
    hi.insert(std::pair(9,6));
    hi.insert(std::pair(2,6));
    hi.insert(std::pair(3,6));

    
    std::cout << "Size: " << hi.size() << std::endl;
    printLevelByLevel(hi); 
    return 0; 

    hi.clear();

    std::cout << "Size: " << hi.size() << std::endl;
    vizTree(hi);

    return 0;

    // Give us a random tree each time
    srand(time(NULL));
    // 15 elements in the tree
    constexpr int TREE_SIZE = 15;

    BinarySearchTree<std::string, int> simpleTree;
    std::string names[TREE_SIZE] {"Teresa", "Carlos", "Nkemdi", "Dante", "Alexander", "Evelyn", "Dillon", "Thomas", "Armando", "Mariel", "Furkan", "Anjali", "Jeremy", "Clayton", "Jessica"};
    for (int i = 0; i < TREE_SIZE; ++i) {
        simpleTree.insert( { names[i], rand() % TREE_SIZE } );
    }

    printTree(simpleTree);
}