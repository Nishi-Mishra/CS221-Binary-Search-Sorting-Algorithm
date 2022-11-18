#include "executable.h"
#include "generate_tree_data.h"

TEST(clear_and_empty) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = i == 0 ? 0ULL : t.range<size_t>(1, 256);
        
        auto pairs = generate_kv_pairs<double, double>(t, sz, true);

        Memhook mh;
        BinarySearchTree<double, double> bst;

        for(auto const & pair : pairs)
            bst.insert(pair);
        
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, bst);
        ASSERT_EQ(sz, bst.size());
        ASSERT_EQ(sz, mh.n_allocs());

        if(sz) ASSERT_FALSE(bst.empty());

        bst.clear();

        ASSERT_EQ(sz, mh.n_frees());
        ASSERT_EQ(0ULL, bst.size());
        ASSERT_TRUE(bst.empty());
    }
}