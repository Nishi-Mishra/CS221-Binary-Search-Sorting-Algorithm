
#include "executable.h"
#include "generate_tree_data.h"
#include <algorithm>
#include <limits>

TEST(min) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = t.range<size_t>(0, 1024);
        
        auto pairs = generate_kv_pairs<double, double>(t, sz);

        Memhook mh;
        BinarySearchTree<double, double> bst;
        
        double min_value, min_key;
        min_value = min_key = std::numeric_limits<double>::max();

        for(auto const & [key, value] : pairs) {
            if(key < min_key) {
                min_key = key;
                min_value = value;
            }

            bst.insert({key, value});

            auto const & min = bst.min();
            {
                tdbg << "Expected min key " << min_key << " got " << min.first << std::endl;
                maybe_print_tree(tdbg, bst);
                ASSERT_EQ(min_key, min.first);
            }

            {
                tdbg << "Got min value = " << min_value << " got " << min.second << std::endl;
                maybe_print_tree(tdbg, bst);
                ASSERT_EQ(min_value, min.second);
            }
        }
    }
}