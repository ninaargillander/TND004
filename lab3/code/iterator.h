#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&

    /* ****************************************************************** */

    // Exercise 2: ADD CODE   

    // Default constructor
    Iterator(): current{nullptr}{}

    Comparable& operator*() const {
        return current->element; // ??
    }
    
    Comparable* operator->() const {
        return ptr; // ??
    }

    bool operator==(const Iterator& it) const {
        return this->current == it->current;

    }

    bool operator!=(const Iterator& it) const {
        return this->current != it->current;
    }

    // operator++ preincrement
    Iterator& operator++() {
        current = find_successor(current);
        return *this;
    }

    // operator++ postincrement
    Iterator operator++(Iterator it) {
        
    }

    // operator-- predecrement
    Iterator& operator--() {
        current = find_predecessor(current);
        return *this;
    }

    // operator-- postdecrement
    Iterator operator--(Iterator it) {

    }

 
private:   
    Node* current;

    // contructor given a pointer to a tree's node 
    Iterator(Node* t = nullptr): current{t}{}
  
   template <typename Comparable>
    friend class BinarySearchTree;
};