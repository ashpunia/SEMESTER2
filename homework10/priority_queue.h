#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data**********************************
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
      for (unsigned int i = 0; i < values.size(); i++) {
          push(values[i]);
      }
  }
  //*************************************************************************
  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  //a bool function to check if current point has parent point***************
  bool has_parent(int i) {return (i > 0 && i < size());}
  //*************************************************************************
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  int has_left_child(int i) { return (2*i)+1 < size(); }
  int has_right_child(int i) { return (2*i)+2 < size(); }
  int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

  // read the top element
  DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }
  // get the index of the top distancepixel
  int get_index(DistancePixel* element) {
      std::map<DistancePixel*,int>:: iterator itr = backpointers.find(element);
      return itr->second;
  }
    
  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1; // save the index to the map
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  }
  
    
 private:
  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;

  // private helper functions
  //***********************************************************************
  void percolate_up(int i)
   {
      int current_index = i;
      while (get_parent(i) != -1)  
      {
          int parent_index = get_parent(i);
          // if current pixel's distance is smaller than its parent's, then swap
          if (*(m_heap[current_index]) < *(m_heap[parent_index])) 
          {
              swap(m_heap[i], m_heap[parent_index]);
              //current_index = parent_index;
          } else break;
      }
  }
  // -----------------------------------------------------------------------
  void percolate_down(int i) 
  {
      int current_index = i;
      while(current_index <= last_non_leaf()) 
      {
          if (has_left_child(current_index) == 0) 
            {
              break;
            }
          // firstly set the left child as its minimum child
          int lowest_child_index = get_left_child(current_index);
          // if it has right child and right child is smaller than left child,
          // then minimum child should be right child
          if (has_right_child(current_index) == 1) 
          {
              int left_c_index = get_left_child(current_index);
              int right_c_index = get_right_child(current_index);
              if (*(m_heap[right_c_index]) < *(m_heap[left_c_index]))
                  lowest_child_index = get_right_child(current_index);
          }
          // if current pixel's distance is larger than its minimum child's, then swap
          if (*(m_heap[current_index]) > *(m_heap[lowest_child_index])) 
          {
              swap(m_heap[current_index], m_heap[lowest_child_index]);
              swap(backpointers[m_heap[current_index]], backpointers[m_heap[lowest_child_index]]);
          } else break;
      }
  }
//***********************************************************************
};
#endif





















