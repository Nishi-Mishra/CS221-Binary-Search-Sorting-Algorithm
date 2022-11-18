#include "executable.h"

TEST(constructor_default) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {

        using IITree = BinarySearchTree<int, int>;

        {
            char BST_MEM[sizeof(IITree)];
            memset(BST_MEM, 0xEE, sizeof(BST_MEM));
            IITree * tree = new (BST_MEM) IITree;

            IITree::const_pointer ptr = &tree->root();
            ASSERT_EQ_(ptr, nullptr, 
                "The binary search tree should be initalized to nullptr"
            );
            ASSERT_EQ(tree->size(), 0ULL);

            tree->~IITree();
        }

        Memhook mh;
        IITree * tree = new IITree;

        ASSERT_EQ(tree->size(), 0ULL);
        ASSERT_EQ(1ULL, mh.n_allocs());

        delete tree;
    }
}
