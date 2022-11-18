#include "executable.h"
#include "generate_tree_data.h"

TEST(insert_and_contains) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        int lower = t.range(0, 250);
        int upper = lower + t.range(1, 250);
        
        int d = t.range(1, 10);
        
        depth_list<int> dlist = generate_tree_data(t, lower, upper);

        Memhook mh;
        {
            BinarySearchTree<int, int, comparison_tracking_comparitor> tree;
            size_t expected_sz = 0;
            for(auto ins_pos = dlist.cbegin(); ins_pos != dlist.cend(); ins_pos++) {
                
                {
                    Memhook mh;
                    
                    INSERT_AND_ASSERT_COMPARISONS_BETWEEN(
                        ins_pos->depth, 2 * ins_pos->depth,
                        tree, std::move(std::pair { ins_pos->key, d * ins_pos->key })
                    );

                    ASSERT_EQ(1ULL, mh.n_allocs());
                }

                ASSERT_EQ(++expected_sz, tree.size());
                
                
                auto it = --dlist.cbegin();
                while(it++ != ins_pos)
                    ASSERT_TRUE(tree.contains(it->key));
                
                while(it != dlist.cend())
                    ASSERT_FALSE(tree.contains((it++)->key));
                
            }
        }
        
        ASSERT_EQ(mh.n_allocs(), mh.n_frees());
    }
}
