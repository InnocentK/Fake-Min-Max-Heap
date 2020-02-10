/*****************************************
 ** File:    MinMaxHeap.h
 ** Project: CMSC 341 Project 4 - Fake Min-Max Heaps, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    05/01/18
 ** Section: 03      
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains the class and function declarations of 
 **     the MinMaxHeap and generic Heap classes as well as the node struct
 **
 **   The node struct manages information about the data stored in the heap
 **   The generic Heap class manages how a heap is populated and all
 **    functions used by all heaps
 **   The MinMaxHeap class utilizes the generic heap class and funciton pointers
 **     to create two heaps, a Min and a Max heap, to 'discretly' mimic a real
 **     MinMaxHeap
 ** 
 ***********************************************/
#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

// Functions used by Function Pointer to determine type of heap
// Used to create Max Heap
template <typename T>
bool max(const T& lhs, const T& rhs){
  return lhs >= rhs;
}
// Used to create Min Heap
template <typename T>
bool min(const T& lhs, const T& rhs){
  return lhs <= rhs;
}


template <typename T>
struct Node
{
  //Overloaded Constructor
  Node(T data, int index, const int& capacity);

  //Destructor
  ~Node();

  //Copy Constructor
  Node(const Node<T>& other);

  //Assignment Operator
  const Node<T>& operator=(const Node<T>& rhs);

  //Helper Functions
  void destroyNode();
  void swap(Node<T>* other);

  //Member variables
  T m_data;
  int* m_index;
  int* m_other_index;
};

template <typename T>
class Heap
{
 public:  
  //Overloaded Constructor
  Heap(int capacity, bool (&compare)(const T& lhs, const T& rhs) = min);

  //Copy Constructor
  Heap(const Heap<T>& other);

  //Overloaded Copy Constructor
  Heap(const Heap<T>& other, const Heap<T>& partner);

  //Destructor
  ~Heap();

  //Overloaded Assignment Operator
  const Heap<T>& operator=(const Heap<T>& rhs);
  // const Heap<T>& operator=(const Heap<T>& rhs);

  //Member Functions
  void destroyHeap();
  int size();
  int* insert(const T& data);
  int* insert(const T& data, Node<T>* &twin);
  void deleteAt(const int index = 1);
  void dump();

  // Access to heap's elements are unrestricted (makes access easier)
  // Same for Heap's capacity
  Node<T>** m_heap;
  int m_capacity;

 private:
  // Member Variables
  int m_size;
  bool (*m_compare)(const T& lhs, const T& rhs);

  //Helper Functions
  int bubbleUp(int hole);
  void trickleDown(int hole);
};

template <typename T>
class MinMaxHeap
{
 public:
  //Overloaded Constructor
  MinMaxHeap(int capacity);

  //Copy Constructor
  MinMaxHeap(const MinMaxHeap<T>& other);

  //Destructor
  ~MinMaxHeap();

  //Overloaded Assignment Operator
  const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);

  //Member Functions
  int size();
  void insert(const T& data);
  T deleteMin();
  T deleteMax();
  void dump();
  void locateMin(int pos, T& data, int& index);
  void locateMax(int pos, T& data, int& index); 

 private:
  //Member Variables
  Heap<T>* m_max;
  Heap<T>* m_min;

  //Helper Function
  void destroyMinMax();
};

#include "MinMaxHeap.cpp"

#endif
