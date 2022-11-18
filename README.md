# Binary Search Tree

This Programming Assignment is the first where we are not implementing an STL class. There is no `std::binary_search_tree`. The function names attempt to mimic those of the STL.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Implement Binary Search Tree](#implement-binary-search-tree)

- [Print Level By Level](#print-level-by-level)

- [Disclaimer About Comparator](#disclaimer-about-comparator)

[Run Tests](#run-tests)

[Incremental Testing and Debugging](#incremental-testing-and-debugging)

- [Visualizing Trees](#visualizing-trees)

- [Custom Assertions](#custom-assertions)

[Turn In](#turn-in)

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-binary-search-tree.git && cd leyk-csce221-assignment-binary-search-tree
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment

### Implement Binary Search Tree

From your textbook:
> The property that makes a binary tree into a binary search tree is that for every node, *X*, in the tree, the values of all the items in its left subtree are smaller than the item in *X*, and the values of all the items in its right subtree are larger than the item in *X*.

All keys should be compared using the strict partial order defined by the comparator `comp`. In the event that you are attempting to insert a value and see a duplicate key, update the value stored at the key with the new value you are attempting to insert. Then `return`.

#### Implement the following functions:

----

`BinarySearchTree();` &ndash; *Default Constructor*

**Description:** Constructs an empty Binary Search Tree

**Time Complexity:** Constant.

**Test Names:** `constructor_default`, *commonly utilized*

----

`BinarySearchTree( const BinarySearchTree & rhs );` &ndash; *Copy Constructor*

**Description:** Clones all the elements from `rhs`. Preserves the same tree structure.

**Time Complexity:** Linear in the number of elements in `rhs`.

**Test Names:** `constructor_copy`

----

`BinarySearchTree( BinarySearchTree && rhs );` &ndash; *Move Constructor*

**Description:** Moves the elements from `rhs`.

**Time Complexity:** Constant.

**Test Names:** `constructor_move`

----

`~BinarySearchTree();` &ndash; *Destructor*

**Description:** Destroys all of the objects in `*this`.

**Time Complexity:** Linear in the number of elements in `*this`.

**Test Names:** *commonly utilized*

----

`const_reference root() const;`

**Description:** Returns a `const` reference to the `pair` contained in the `_root` node.

**Time Complexity:** Constant.

**Test Names:** - `root`

----

`bool empty() const;`

**Description:** Returns whether the Binary Search Tree is empty.

**Time Complexity:** Constant.

**Test Names:** `clear_and_empty`

----

`size_type size() const;`

**Description:** Returns the number of elements in the Binary Search Tree.

**Time Complexity:** Constant.

**Test Names:** *commonly utilized*

----

`BinarySearchTree & operator=( const BinarySearchTree & rhs );` &ndash; *Copy Assignment Operator*

**Description:** Empties `*this` before cloning elements over from `rhs`.

**Time Complexity:** Linear in the number of elements in `*this` plus the number of elements in `rhs`.

**Test Names:** `operator_copy`

----

`BinarySearchTree & operator=( BinarySearchTree && rhs );` &ndash; *Move Assignment Operator*

**Description:** Empties `*this` before moving elements over from `rhs`.

**Time Complexity:** Linear in the number of elements in `*this`.

**Test Names:** `operator_move`

----

`void insert( const_reference x, node_ptr & t );`

**Description:** Private `insert` helper. Recursively seeks the correct position to insert and then constructs a new node containing `x`. If the key of `x` is already in `*this`, replaces the value with the value of `x`.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `insert_and_count`, `insert_and_find`,  *commonly utilized* - tested through `void insert( pair && x );`

----

`void insert( pair && x, node_ptr & t );`

**Description:** Private `insert` helper. Recursively seeks the correct position to insert and then constructs a new node containing `x`. If the key of `x` is already in `*this`, replaces the value with the value of `x`.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `insert_and_count`, `insert_and_find`,  *commonly utilized* - tested through `void insert( const_reference x );`

----

`void erase( const key_type & x, node_ptr & t );` 

**Description:** Private `erase` helper. Recursively seeks the correct position to erase and then destroys the node with the key `x`.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `erase` - tested through `void erase( const key_type & x );`

----

`const_node_ptr min( const_node_ptr t ) const;`

**Description:** Private `min` helper. Seeks the correct position of the minimum node and returns a pointer to that node. You could do this recursively or non-recursively.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `min` - tested through `const_reference min() const;`

----

`const_node_ptr max( const_node_ptr t ) const;`

**Description:** Private `max` helper. Seeks the correct position of the maximum node and returns a pointer to that node. You could do this recursively or non-recursively.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `max` - tested through `const_reference max() const;`

----

`bool contains( const key_type & x, const_node_ptr t ) const;`

**Description:** Private `contains` helper. Seeks the correct position of the node with key `x`. Returns `true` if such a node exists and `false` otherwise.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `insert_and_contains`, *frequently utilized* - tested through `bool contains( const key_type & x ) const;`

----

`node_ptr find( const key_type & key, node_ptr t );`

**Description:** Private `find` helper. Seeks the correct position of the node with key `x`. Returns a pointer to the node if such it exists and `nullptr` otherwise.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `insert_and_find`, *frequently utilized* - tested through `value_type & find( const key_type & key );`

----

`const_node_ptr find( const key_type & key, const_node_ptr t ) const;`

**Description:** Private `find` helper. Seeks the correct position of the node with key `x`. Returns a pointer to the node if such it exists and `nullptr` otherwise. This version is used to get a `const_reference` to the value back, whereas the above version returns a mutable `reference` in its public caller.

**Time Complexity:** Linear in the number of elements in `*this` for an unbalanced tree. Typically logarithmic in the number of elements of `*this`.

**Test Names:** `insert_and_find`, *frequently utilized* - tested through `const value_type & find( const key_type & key ) const;`

----

`void clear( node_ptr & t );`

**Description:** Private `clear` helper. Recursively destroys every node in `*this` and resets the `_size`.

**Time Complexity:** Linear in the number of elements in `*this`.

**Test Names:** `clear_and_empty` - tested through `void clear( node_ptr & t )`

----

`node_ptr clone ( const_node_ptr t ) const;`

**Description:** Private `clone` helper. Recursively clones every node at or under `t` and returns the node at the root of the cloned subtree. This function is used in Copy Construction and Copy Assignment.

**Time Complexity:** Linear in the number of elements in the subtree rooted at `t`. Typically, this will be Linear in the number of elements of `rhs` (the tree you're cloning).

**Test Names:** *private, untested*

----

`void printLevelByLevel( std::ostream & out ) const;`

**Description:** Prints the tree in a pretty manner. See [this section of the document](#print-level-by-level) for more details.

**Time Complexity:** Linear in the number of elements in `*this`.

**Test Names:** `print_level_by_level`

----

#### Print Level By Level

You will write a method to perform a level-by-level traversal of a tree:

```
         7
        / \
       4   9
      / \ / \
     1  x 8  x
    /
   0
```

This traversal visits all nodes with the same depth value ("same level") before visiting any nodes on a lower level (with a greater depth.) Our verson will iterate though the nodes from left to right. With regards to the tree pictured above, this would translate into the following visitation order: 7, 4, 9, 1, 8, 0

```
level 0 - 7
level 1 - 4, 9
level 2 - 1, 8
level 4 - 0
```

The printLevelByLevel function will require that you both perform the tranversal, print key value pairs, and print the null nodes:
```
(7, 0)
(4, 1) (9, 2)
(1, 3) null (8, 4) null
(0, 5) null null null null null null null
```

The elements are printed in (key, value) form. Nulls are represented by the string "null". Notice that each null child on level `(n - 1)` results in two null children on level `n` to proprly align the tree. 

To accomplish this, you will want to follow the [Breadth First Search Algorithm](https://en.wikipedia.org/wiki/Breadth-first_search). A program traversing the tree from left to right along each level requires a data structure to recall which nodes must be visited across a single level. This can be accomplished by traversing along all nodes in a level, adding the children of all nodes to a queue, and only advancing to the next level when all nodes on the current level have been visited. Notice that when all the nodes on a single level have been visited, all of their children have been enqueued. This means there is no need for separate queues between levels - the nodes can be continuously added to a single queue and the front of the queue will always contain the next element in the traversal. When traversing along the current level, the front of the queue contains the next node on the current level. When it reaches the end of the current level, it will contain the first node on the next level assuming that we added the left node to the queue before the right node.

To provide the proper alignment, a null node dequeued must result in two more null nodes enqueued. This will ensure that the nodes are aligned properly in the triangular pattern above. Without this, it would be difficult to tell which children belonged to the left and right subtrees. The algorithm is terminated when all the nodes on the next level are NULL. This can be accounted for by tracking whether we have seen any non-null nodes on the next level. If there are non-null nodes on the next level, we must traverse through that level. Otherwise, no further information needs to be printed. 

All nodes on a single level must be printed on a single line. To insert the end-of-line delimiter, an external counter must maintain the number of nodes encountered during the current level. If it is a multiple of two 2^1, 2^2, 2^3, … we have reached the end of the level. On reaching the end of the current level, we can insert the line ending and break out of the loop if the entire next level consists of null nodes.

[You may wish to use an STL queue in your solution](https://en.cppreference.com/w/cpp/container/queue)

----

#### Disclaimer About Comparator

This assignment uses a comparator to navigate the tree, as nodes are ordered based on comparisons to allow for easy searching in the data structure. (This is similar to how the binary search algorithm works.) The comparator will need to be used in navigation-based functions like `find`, `insert`, and `erase`. The test cases ensure that the comparator is being properly used to navigate and organize the tree by counting the amount of times it is called. In order to pass the test cases, you will need to make sure that you use the comparator a max of two times for every node traversed in the tree. Not doing so can cause the test cases to fail.

----

#### Further Reading
- [Binary Search Tree - GeeksforGeeks](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
- [Binary search tree - Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
- [Data Structure - Binary Search Tree](https://www.tutorialspoint.com/data_structures_algorithms/binary_search_tree.htm)
- Your textbook Chapter 4 Section 3 (page 132)
- [Class template bstree - 1.78.0](https://www.boost.org/doc/libs/1_78_0/doc/html/boost/intrusive/bstree.html) &ndash; Boost header with detailed reference at the bottom.

## Run Tests

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-binary-search-tree` folder to accomplish what you need:

**Build all of the tests**
```sh
make -C tests -j12 build-all
```

**Run the test called `<test-name>`.** Replace `<test-name>` with the name of any `.cpp` file in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run/<test-name>
```

**Run every test** in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 -k
```

**Debugging tests** 
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.


## Incremental Testing and Debugging:

The ADT interface you build in this assignment effectively encapsulates the binary search tree. Users of the binary search tree cannot access the memory directly or traverse the underlying  tree. Normally, an iterator would be provided to access the elements sequentially. While many implementations of binary search trees provide an iterator, we have elected to exclude it from the assignment to simplify it. This means we are required to test it though the public interface provided by the ADT - largely through membership tests. This means that the `insert`, `find`, and `contains` tests, while complicated, are used extensively to test the other functions. We recommend you follow the following testing procedure to mitigate the high level of interdependence between test cases.

#### 1. Establishing Roots

First, complete `root()`, `size()`, and the default constructor `BinarySearchTree()`. If you have completed this trio correctly, `constructor_default.cpp` will pass. 

#### 2. The First Few Leafs

After passing `constructor_default.cpp` you should write your `insert` methods. `insert` can only be tested extensively in concert with membership tests (contains, find). Once `insert` is written, the `insert_and_count` test should pass without additional dependencies. This test will count the number of comparisons made on the path to an insertion ensuring it is bounded reasonably (verifying the insert method is placing items at the correct depth.) `insert_and_count` also expects that you will free the memory allocated during an insert. Thus, a destructor is required for test completion.

#### 3. Uptake (Traversing the Tree)

After completing the `find` method, the `insert_and_find` method passes. After this test case passes, the `insert_and_move` and the `insert_find_and_count` methods should be tested. The former will require the move variant of the `insert` method to be implemented. The latter should pass the `find` and `insert` methods are properly written. The `insert_and_contains` method should also be completed at this stage.

#### 4. Pruning, Flowering & Reseeding

All further methods are able to be completed assuming the dependencies above are fully working.

### Debugging:

#### Visualizing Trees:

There are two methods we provide to visualize trees. The first, `printTree`, is a simple helper function which will print the tree to a debug stream. The tree is printed on its side - indentation indicates increasing depth. There is a more complicated function, `vizTree` which prints out the tree in a standard format called Graphviz. It can be copied and pasted into an [online viewer](http://dreampuf.github.io/GraphvizOnline) to render a full image of the tree.

```
BinarySearchTree<int, int> bst;
bst.insert({ 0, 2 });
printTree(bst); // Print tree
vizTree(bst); // Print Graphviz
```

#### Debug Trees in Test Cases:

Some test cases will optionally print the offending tree when a failure occurs. This is disabled by default but can be enabled by adding special preprocessor directives to the BinarySearchTree.h header file (by convention, they are grouped at the top of the file with the includes): 

To enable this, you must specify the output format. You can either use Graphviz or ASCII but not both concurrently. Pick whichever line suits you better:

```
// Print out debug trees in Graphviz format
#define TREE_ASSERT_VIZ
// Print out debug trees in ascii using tabular depth
#define TREE_ASSERT_PRINT
```

By default, trees will not be printed if they have more than 15 nodes. This limit is adjustable and can also be overridden with a define:

```
// Increase the limit to 50 nodes
#define TREE_ASSERT_PRINT_SZ_LIMIT 50
``` 

#### Custom Assertions:

If you read through the testing code, you may see custom test assertions. They are defined in `tree_assert.h` in `include`. Here a brief summary of their behavior:

- `ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, tree)` - Ensures all (key, value) pairs are in the tree. This is done by first checking if `contains` succeeds. If it reports the value is contained in the tree, a `find` is attempted.

- `INSERT_AND_ASSERT_COMPARISONS_BETWEEN(lower_bound, upper_bound, tree, pair)` - injects a custom comparator to ensure the number of comparisons made with the comparator is between [lower_bound, upper_bound] inclusive. This allows us to ensure you are inserting the pair at the correct depth.

- `ASSERT_VALUE_IN_TREE(expected_value, tree, key)` - attempts a `find` to ensure the value is in the tree.

## Main.cpp:
In `main.cpp`, the code attempts to build and print a tree. Note that the names are used as the keys rather than the integers. This means that the binary tree is lexicographically ordered by the string key (not strictly numerically.)

## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`BinarySearchTree.h`](src/BinarySearchTree.h)
