#pragma once
#include <bits/stdc++.h>
#include <functional> // std::less
#include <iostream>
#include <queue> // std::queue
#include <utility> // std::pair
#include <iostream> 
using std::cout, std::endl; 

template <typename K, typename V, typename Comparator = std::less<K>>
class BinarySearchTree
{
  public:
    using key_type        = K;
    using value_type      = V;
    using key_compare     = Comparator;
    using pair            = std::pair<key_type, value_type>; // first and second -- sort by key type (first)
    using pointer         = pair*;
    using const_pointer   = const pair*;
    using reference       = pair&;
    using const_reference = const pair&;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

  private:
    struct BinaryNode
    {
        pair element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const_reference theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( pair && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    using node           = BinaryNode;
    using node_ptr       = node*;
    using const_node_ptr = const node*;

    node_ptr _root;
    size_type _size;
    key_compare comp;

  public:
    BinarySearchTree() : _root{nullptr}, _size{0}, comp{} { }

    BinarySearchTree( const BinarySearchTree & rhs ) : _root{rhs._root}, _size{rhs._size}{  
        _root = clone(rhs._root); 
    }

    BinarySearchTree( BinarySearchTree && rhs ) {
        _root = std::move(rhs._root); // move the root 
        _size = rhs._size; // update the size 
        rhs._size = 0; // clear rhs 
        rhs._root = nullptr; 
    }
    ~BinarySearchTree() {
        clear(); 
    }

    const_reference min() const { return min( _root )->element; }
    const_reference max() const { return max( _root )->element; }
    const_reference root() const { return _root->element; }

    bool contains( const key_type & x ) const { return contains( x, _root ); }
    value_type & find( const key_type & key ) { return find( key, _root )->element.second; }
    const value_type & find( const key_type & key ) const { return find( key, _root )->element.second; }
    bool empty() const {
        return _size == 0;
    }
    size_type size() const {
        return _size;
    }

    void clear() {
        clear( _root );
        _size = 0;
    }
    void insert( const_reference x ) { insert( x, _root ); }
    void insert( pair && x ) { insert( std::move( x ), _root ); }
    void erase( const key_type & x ) { erase(x, _root); }

    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
        if (&rhs == this) return *this; 
        this->clear();
        this->_size = rhs._size; 
        this->_root = clone(rhs._root);
        return *this;  
    }
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
        if (&rhs == this) return *this; 
        this->clear();
        this->_size = rhs._size; 
        this->_root = std::move(rhs._root);
        rhs._size = 0; 
        rhs._root = nullptr;  
        return *this;  
    }

  private:
    void insert( const_reference x, node_ptr & t ) {

        // const_reference = const pair& therefore x contains the new element to add  
        
        // if t = nullptr --> insert right there  
        if (t == nullptr) {
            BinaryNode* newNode = new BinaryNode(x, nullptr, nullptr);// element{ theElement }, left{ lt }, right{ rt }
            t = newNode;
            _size++;
        }
        // if less than node --> go left; if not left --> insert 
        else if (comp(x.first, t->element.first)) {
            insert(x, t->left); 
        }
        // if greater than node --> go right; if not right --> insert 
        else if (comp(t->element.first, x.first)) {
            insert(x, t->right);
        }
        // if equal node --> update value 
        else if (x.first == t->element.first) {
            t->element.second = x.second; 
        }
        else {
            cout << "WHY HERE IN INSERT?" << endl; 
        }

    }
    void insert( pair && x, node_ptr & t ) {
        // if t = nullptr --> insert right there  
        if (t == nullptr) {
            BinaryNode* newNode = new BinaryNode(std::move(x), nullptr, nullptr);// element{ theElement }, left{ lt }, right{ rt }
            t = newNode;
            _size++;
        }
        // if less than node --> go left; if not left --> insert 
        else if (comp(x.first, t->element.first)) {
            insert(std::move(x), t->left); 
        }
        // if greater than node --> go right; if not right --> insert 
        else if (comp(t->element.first, x.first)) {
            insert(std::move(x), t->right);
        }
        // if equal node --> update value 
        else if (x.first == t->element.first) {
            t->element = std::move(x); 
        }
        else {
            cout << "WHY HERE IN INSERT MOVE?" << endl; 
        }

        
    }

    void erase( const key_type & x, node_ptr & t ) {

        if (t == nullptr) {
            cout << "Couldn't find the key"; 
        }
        // if less than node --> go left; if left is equal to key  
        else if (comp(x, t->element.first)) {
            erase(x, t->left); 
        }
        // if greater than node --> go right; if right is equal to key
        else if (comp(t->element.first, x)) {
            erase(x, t->right); 
        }
        // if equal node --> figure out the deleting process  
        else {//(x.first == t->element.first) 
            
            // case 1 -- no children; parent node left /right = nullptr  -- ????? 
            if (t->left == nullptr && t->right == nullptr) {
                node_ptr OG_node = t; 
                t=nullptr;
                delete OG_node; 
                _size--; 
            }

            // case 2 -- one child; replace parent node left/right with the single child 
            else if (t->left == nullptr) {
                node_ptr OG_node = t;  
                node_ptr rightNode = t->right; 
                t = rightNode; 
                delete OG_node; 
                _size--;
            }
            else if (t->right == nullptr) {
                node_ptr OG_node = t; 
                node_ptr leftNode = t->left; 
                t = leftNode; 
                delete OG_node; 
                _size--; 
            }

            // case 3 -- two children; right subtree and find leftmost node(min) and that is now the root 
            else {
                const_node_ptr swapNode = min(t->right); 
                t->element = swapNode->element; 
                erase(swapNode->element.first, t->right); 
            }
        }

    }

    /*
    node_ptr & parent_of_del; // reference to parent 
        node_ptr & to_delete; // reference to thing to delete 

        // traverse to parent of thing you wanna erase  
        if (t == nullptr) {
            cout << "Couldn't find the key"; 
        }
        // if less than node --> go left; if left is equal to key --> update to_delete parent  
        else if (comp(x, t->element.first)) {
            if (t->left.element.first == x) 
                parent_of_del = &t; 
            erase(x, t->left); 
        }
        // if greater than node --> go right; if right is equal to key --> update to_delete parent  
        else if (comp(t->element.first, x)) {
            if (t->right.element.first == x) 
                parent_of_del = &t; 
            erase(x, t->right); 
        }
        // if equal node --> update to_delete var 
        else {
        //(x.first == t->element.first) 
            to_delete = &t; 
        }
        */

    const_node_ptr min( const_node_ptr t ) const {
        // go left 
        if (t->left == nullptr) {
            return t; 
        }
        min(t->left); 
    }
    const_node_ptr max( const_node_ptr t ) const {
        // go right 
        if (t->right == nullptr) {
            return t; 
        }
        max(t->right);
    }

    bool contains( const key_type & x, const_node_ptr t ) const {
        
        // go left / right until equal or nullptr; x is a key!

        // if t = nullptr return false  
        if (t == nullptr) {
            return false;
        }
        // if less than node --> go left
        else if (x < t->element.first) {
            contains(x, t->left); 
        }
        // if greater than node --> go right
        else if (x > t->element.first) {
            contains(x, t->right); 
        }
        // if equal node --> update value 
        else if (x == t->element.first) {
            return true; 
        }
        else {
            cout << "WHY HERE IN contains?" << endl; 
        }

    }
    node_ptr find( const key_type & key, node_ptr t ) {
        bool comparison = comp(key, t->element.first);
    
        // if nullptr stop recurring 
        if (t == nullptr) {
            return nullptr;
        }
        else if (key == t->element.first) {
            return t; 
        }
        // if less than node --> go left; if not left --> insert 
        else if (comparison) {
            find(key, t->left);
        }
        // if greater than node --> go right; if not right --> insert 
        else {
            find(key, t->right);
        }
    }
    const_node_ptr find( const key_type & key, const_node_ptr t ) const {
        bool comparison = comp(key, t->element.first);
    
        // if nullptr stop recurring 
        if (t == nullptr) {
            return nullptr;
        }
        else if (key == t->element.first) {
            return t; 
        }
        // if less than node --> go left; if not left --> insert 
        else if (comparison) {
            find(key, t->left);
        }
        // if greater than node --> go right; if not right --> insert 
        else {
            find(key, t->right);
        }
    }   

    void clear( node_ptr & t ) {
        if (t == nullptr) // base case 
            return; 
        clear(t->left); // go thru the left side until leaf 
        clear(t->right); // go thru right until leaf 
        delete t; // delete the current leaf 
        t = nullptr; // for the root node 
    }
    
    node_ptr clone ( const_node_ptr t ) const {
        if(t == nullptr)
            return nullptr;  

        BinaryNode* newBinNode = new BinaryNode(t->element, clone(t->left), clone(t->right)); // continue to make new nodes until the entire tree is made
        return newBinNode; 
    }

  public:
    template <typename KK, typename VV, typename CC>
    friend void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend std::ostream& printNode(std::ostream& o, const typename BinarySearchTree<KK, VV, CC>::node& bn);

    template <typename KK, typename VV, typename CC>
    friend void printTree( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
        std::ostream & out,
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev
    );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        const BinarySearchTree<KK, VV, CC> & bst, 
        std::ostream & out
    );
};

template <typename KK, typename VV, typename CC>
std::ostream& printNode(std::ostream & o, const typename BinarySearchTree<KK, VV, CC>::node & bn) {
    return o << '(' << bn.element.first << ", " << bn.element.second << ')';
}

template <typename KK, typename VV, typename CC>
void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out = std::cout ) {
    
    using node = typename BinarySearchTree<KK, VV, CC>::node;
    using node_ptr = typename BinarySearchTree<KK, VV, CC>::node_ptr;
    using const_node_ptr = typename BinarySearchTree<KK, VV, CC>::const_node_ptr;
    
    // TODO -- Guide in Instructions
    if (bst.empty()) return; 

    std::queue <node_ptr> node_queue; 
    node_queue.push(bst._root);

    int node_count = 1;
    bool has_children = false; 

    while (node_count > 0) {
        node_ptr curr_node = node_queue.front();
        node_queue.pop(); // front most element 
        node_count--;
        if (curr_node) {
            printNode<KK, VV, CC>(out, *curr_node);
            out << " ";
            node_queue.push(curr_node->left); 
            node_queue.push(curr_node->right); 

            if (curr_node->left != nullptr || curr_node->right != nullptr) {
                has_children = true;
            }
        } 
        else {
            out << "null "; 
            node_queue.push(nullptr); 
            node_queue.push(nullptr); 
        }
        if (node_count == 0) {
            out << std::endl; 
            if (!has_children) return;
            has_children = false;
            node_count = node_queue.size();
        }
        // double check = log2(node_count); 
        // if ((double)(int)check == check) {
        //     out << std::endl;
        //     if (!has_children) return;
        //     has_children = false;
        // }
    }
    
}

template <typename KK, typename VV, typename CC>
void printTree( const BinarySearchTree<KK, VV, CC> & bst, std::ostream & out = std::cout ) { printTree<KK, VV, CC>(bst._root, out ); }

template <typename KK, typename VV, typename CC>
void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth = 0 ) {
    if (t != nullptr) {
        printTree<KK, VV, CC>(t->right, out, depth + 1);
        for (unsigned i = 0; i < depth; ++i)
            out << '\t';
        printNode<KK, VV, CC>(out, *t) << '\n';
        printTree<KK, VV, CC>(t->left, out, depth + 1);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
    std::ostream & out,
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev = nullptr
) {
    if(node) {
        std::hash<KK> khash{};

        out << "\t" "node_" << (uint32_t) khash(node->element.first)
            << "[label=\"" << node->element.first 
            << " [" << node->element.second << "]\"];" << std::endl;
        
        if(prev)
            out << "\tnode_" << (uint32_t) khash(prev->element.first) <<  " -> ";
        else
            out << "\t";
        
        out << "node_" << (uint32_t) khash(node->element.first) << ";" << std::endl;
    
        vizTree<KK, VV, CC>(node->left, out, node);
        vizTree<KK, VV, CC>(node->right, out, node);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    const BinarySearchTree<KK, VV, CC> & bst, 
    std::ostream & out = std::cout
) {
    out << "digraph Tree {" << std::endl;
    vizTree<KK, VV, CC>(bst._root, out);
    out << "}" << std::endl;
}
