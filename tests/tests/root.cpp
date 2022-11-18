#include "executable.h"
#include "generate_tree_data.h"

TEST(clear_and_empty) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = t.range<size_t>(1, 256);
        
        auto pairs = generate_kv_pairs<double, double>(t, sz, true);

        Memhook mh;
        BinarySearchTree<double, double> bst;

        for(auto const & pair : pairs)
            bst.insert(pair);
        
        auto const & root_pair = bst.root();
        auto const & root_result = pairs[0];
        
        ASSERT_EQ(root_result.first, root_pair.first);
        ASSERT_EQ(root_result.second, root_pair.second);
    }
}