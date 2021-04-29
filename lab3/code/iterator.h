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
    Iterator(): ptr{nullptr}{}

    // operator*
   /* Iterator& operator*(const Iterator& it) {

    }
    */
    // operator->
    Node* operator->() {
        return ptr;
    }
/*
    // operator==
    Iterator& operator==(const Iterator& it) {

    }

    // operator!=
    Iterator& operator!=(const Iterator& it) {

    }

    // operator++ preincrement
    Iterator& operator++() {

    }

    // operator++ postincrement
    Iterator operator++(Iterator it) {

    }

    // operator-- predecrement
    Iterator& operator--() {

    }

    // operator-- postdecrement
    Iterator operator--(Iterator it) {

    }*/

 
private:   
    Node* ptr;

    // contructor given a pointer to a tree's node 
    Iterator(Node* t): ptr{t}{}
  
   template <typename Comparable>
    friend class BinarySearchTree;
};