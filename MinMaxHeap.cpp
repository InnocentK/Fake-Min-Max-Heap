/*****************************************
 ** File:    MinMaxHeap.cpp
 ** Project: CMSC 341 Project 4 - Fake Min-Max Heaps, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    05/01/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains the implementation of the MinMaxHeap class,
 **     the generic Heap class and the Node struct
 **
 **   These classes (and struct) work together in order to mimic  
 **    a true MinMax Heap by managing two generic heaps that are made
 **    to be either into a Min or Max heap based on their function pointer
 **
 ***********************************************/
#ifndef MINMAXHEAP_CPP
#define MINMAXHEAP_CPP

#include "MinMaxHeap.h"
#include <stdexcept>
#include <iostream>

#define TOP 1
#define NIL 0

/***********************************
 ** Member Functions for Node Struct
 ************************************/

// Overloaded Node Constructor
template <typename T>
Node<T>::Node(T data, int index, const int& capacity){

  m_data = data;
  m_index = new int(index);
  m_other_index = NULL;
}

// Node Destructor
template <typename T>
Node<T>::~Node(){
  destroyNode();
}

// Node Destructor's helper function
// Deletes all of a node's data
template <typename T>
void Node<T>::destroyNode(){

  // Checks if index exists
  if (m_index != NULL)
    delete m_index;
  m_index = NULL;
}

// Node Copy Constructor
template <typename T>
Node<T>::Node(const Node<T>& other){

  // Setting member variables
  m_data = other.m_data;
  m_index = new int(*other.m_index);
  m_other_index = NULL;
}

// Node Assignment Operator
template <typename T>
const Node<T>& Node<T>::operator=(const Node<T>& rhs){

 // Checks for self-assignment
  if (this == &rhs)
    return *this;

  // Cleaning up memory
  destroyNode();

  // Setting other member variables
  m_data = rhs.m_data;
  m_index = new int(*rhs.m_index);
  m_other_index = NULL;
  return *this;
}

// Sets one node equal to another
// Only swaps their data and references to their position in another heap
// Used when trickling down, bubbling up or replacing nodes
template <typename T>
void Node<T>::swap(Node<T>* other){

  // Checking for valid node to swap
  if( (m_index == NIL) || (other->m_index == NIL) ){
    std::cout << "Invalid Node trying to be swapped"<< std::endl;
    return;
  }

  // Temporarily holds current node's information
  int index = *m_index;
  int other_index = *other->m_index;
  T temp_data = m_data;
  int* temp_index = m_index;
  int* temp_twin_index = m_other_index;

  // Swapping data
  m_data = other->m_data;
  other->m_data = temp_data;

  // Swapping indexes
  *m_index = other_index;
  *other->m_index = index;

  // Restores the indexes to match actual index being held in
  m_index = other->m_index;
  other->m_index = temp_index;

  // Swapping locations for other node
  m_other_index = other->m_other_index;
  other->m_other_index = temp_twin_index;
  return;
}

/******************************************
 ** Member Functions for Generic Heap Class
 ******************************************/

// Overloaded Heap Constructor
// Compare Function Pointer set to min by default
//  (i.e. min heap by default)
template <typename T>
Heap<T>::Heap(int capacity, bool (&compare)(const T& lhs, const T& rhs)){

  m_size = NIL;
  m_capacity = capacity + TOP;
  m_heap = new Node<T>*[m_capacity];
  m_compare = &compare;
}

// Heap Copy Constructor
template <typename T>
Heap<T>::Heap(const Heap<T>& other){

  // Copying member variables
  m_size = other.m_size;
  m_capacity = other.m_capacity;
  m_compare = other.m_compare;
  m_heap = new Node<T>*[m_capacity];

  // Copying nodes
  for (int i = TOP; i <= m_size; i++)
    m_heap[i] = new Node<T>(*other.m_heap[i]);
}

// Heap Destructor
template <typename T>
Heap<T>::~Heap(){
  destroyHeap();
}

// Destructor Helper Function
template <typename T>
void Heap<T>::destroyHeap(){

  // Loops through heap deleting each individual node
  for (int i = TOP; i <= m_size; i++){

    // Checks if node exists
    if (m_heap[i] != NULL)
      delete m_heap[i];

    m_heap[i] = NULL;
  }
  delete [] m_heap;
  return;
}

// Overloaded Heap Assingment operator
template <typename T>
const Heap<T>& Heap<T>::operator=(const Heap<T>& rhs){
  // Checks for self-assignment
  if (this == &rhs)
    return *this;

  // Heap is deleted
  destroyHeap();

  // Copying member variables
  m_size = rhs.m_size;
  m_capacity = rhs.m_capacity;
  m_compare = rhs.m_compare;
  m_heap = new Node<T>*[m_capacity];

  // Copying nodes
  for (int i = TOP; i <= m_size; i++)
    m_heap[i] = new Node<T>(*rhs.m_heap[i]);

  return *this;
}

// Returns size of the heap
template <typename T>
int Heap<T>::size(){
  return m_size;
}

// Inserts a new item into the heap
// Returns position of newly added node
template <typename T>
int* Heap<T>::insert(const T& data){

  // Heap is full and exception is thrown
  if (m_size == m_capacity - TOP)
    throw std::out_of_range("Heap is Full. Cannot add");

  m_size++;
  m_heap[m_size] = new Node<T>(data, m_size, m_capacity);

  // Properly repositions nodes
  int index = bubbleUp(m_size);
  return m_heap[index]->m_index;
}

// Overloaded Insertion
// Inserts a new item into the heap
// Returns position of newly added node
template <typename T>
int* Heap<T>::insert(const T& data, Node<T>* &twin){
  
  // Heap is full and exception is thrown
  if (m_size == m_capacity - TOP)
    throw std::out_of_range("Heap is Full. Cannot add");

  m_size++;
  m_heap[m_size] = new Node<T>(data, m_size, m_capacity);
  m_heap[m_size]->m_other_index = twin->m_index;

  // Properly repositions nodes
  int index = bubbleUp(m_size);
  return m_heap[index]->m_index;
}

// Deletes the item at the top of the heap
// Default value for index = 1 (position 1 is the root)
// Returns posiion of node's twin (in another heap)
template <typename T>
void Heap<T>::deleteAt(int index){

  // Heap is empty; no deleting occurs and exception thrown
  if (m_size <= NIL)
    throw std::out_of_range("Heap is Empty. Cannot delete");

  // Checks if heap has more than 1 element
  if (m_size > TOP)
    m_heap[index]->swap(m_heap[m_size]);

  // Last element in the heap is deleted
  if (m_heap[m_size] != NULL)
    delete m_heap[m_size];

  m_heap[m_size] = NULL;
  m_size--;

  // Properly repositions nodes
  trickleDown(index);
  return;
}

// Prints the contents of the heap 
template <typename T>
void Heap<T>::dump(){
  std::cout << "size = " << m_size << ", capacity = " 
	    << m_capacity - TOP << std::endl;

  // Checks for empty Heap
  if (m_size < TOP){
    std::cout << "Heap is Empty" << std::endl;
    return;
  }
  
  // Otherwise prints all nodes
  for (int i = TOP; i <= m_size; i++){

    // Checks if node exists
    if (m_heap[i] == NULL){
      std::cout << "Heap[" << i << "] = (NULL,";
      std::cout << "NULL)" << std::endl;
    }

    // Node exists
    else{
      std::cout << "Heap[" << i << "] = (" << m_heap[i]->m_data 
	      << ",";      

      // Checks if heap has a twin
      if (m_heap[i]->m_other_index != NULL)
	std::cout << *m_heap[i]->m_other_index << ")" << std::endl;
      
      // Node has no twin
      else
	std::cout << "NULL)" << std::endl;
    }
  }
  return;
}

// Helper Function to fix node order
// Helps when adding a node
// Returns position of newly added node
template <typename T>
int Heap<T>::bubbleUp(int hole){
  const int CALC_PARENT = 2;

  // Used to track the node being moved
  Node<T>* tmp = m_heap[hole];

  // Loops up the subtree until the newly added node is properly positioned
  for (; TOP < hole && (hole / CALC_PARENT) && m_compare(tmp->m_data,m_heap[hole / CALC_PARENT]->m_data); hole /= CALC_PARENT){

    m_heap[hole]->swap(m_heap[hole / CALC_PARENT]);
    tmp = m_heap[hole / CALC_PARENT];
  }
  return hole;
}

// Helper Function to fix node order
// Helps when deleting a node
template <typename T>
void Heap<T>::trickleDown(int hole){

  const int CALC_CHILD = 2;
  int child = hole * CALC_CHILD;
  Node<T>* tmp = m_heap[hole];

  // Loops down the subtree swapping nodes until the
  //  replacement node is in it's proper position
  for (;hole * CALC_CHILD <= m_size; hole = child){
    child = hole * CALC_CHILD;

    // Replacement should go to the right subtree of current node
    if (child != m_size && m_compare(m_heap[child + TOP]->m_data, m_heap[child]->m_data) )
      child++;

    // Replacement should go to the left subtree of current node
    if ( m_compare(m_heap[child]->m_data, tmp->m_data) ){
      m_heap[hole]->swap(m_heap[child]);

      // temp must be updated whenever nodes are swapped to continue to track the right node
      tmp = m_heap[child];
    }

    // Proper position is reached
    else
      return;
  }

  // This portion of the code only runs if trickleDown does not run
  // Validates hole (as to not cause errors)
  if (hole > m_size)
    hole /= CALC_CHILD;

  // If after moving the replacement node the heap condition is broken then bubble up
  if( (hole > 1) && (hole * CALC_CHILD) > m_size && 
      m_compare(m_heap[hole]->m_data, m_heap[hole / CALC_CHILD]->m_data) )
    bubbleUp(hole);
  return;
}

/******************************************
 ** Member Functions for MinMaxHeap Class
 ******************************************/

// Overloaded MinMaxHeap Constructor                                                                           
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){

  m_max = new Heap<T>(capacity, max);
  m_min = new Heap<T>(capacity, min);
}

// MinMaxHeap Copy Constructor
// Makes use of insert function to position nodes in
//  new heap. Insert runs in O(log(n)) so this runs in O(nlog(n))
//  Necessary in order to better keep track of twin node's position 
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){
  m_max = new Heap<T>(other.m_min->m_capacity, max);
  m_min = new Heap<T>(other.m_min->m_capacity, min);

  // Goes through the min heap of other copying data
  //  and organizing it in own heaps
  for (int i = TOP; i < other.m_min->size(); i++)
    insert(other.m_min->m_heap[i]->m_data);
}

// MinMaxHeap Destructor
template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){
  destroyMinMax();
}

// MinMaxHeap Destructor's helper function
template <typename T>
void MinMaxHeap<T>::destroyMinMax(){
  // Deletes Max Heap
  if (m_max != NULL)
    delete m_max;
  m_max = NULL;

  // Deletes Min Heap
  if (m_min != NULL)
    delete m_min;
  m_min = NULL;
}

// Overloaded Assignment Operator
// Makes use of insert function to position nodes in
//  new heap. Insert runs in O(log(n)) so this runs in O(nlog(n))
//  Necessary in order to better keep track of twin node's position                                                                   
template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){
 // Checks for self-assignment
  if (this == &rhs)
    return *this;

  // Resetting member variables
  destroyMinMax();
  m_max = new Heap<T>(rhs.m_min->m_capacity, max);
  m_min = new Heap<T>(rhs.m_min->m_capacity, min);

  // Goes through the min heap of other copying data
  //  and organizing it in own heaps
  for (int i = TOP; i < rhs.m_min->size(); i++)
    insert(rhs.m_min->m_heap[i]->m_data);

  return *this;
}

// Returns size of the Min-Max Heap
// Because this is a fake Min-Max Heap size = size of one of the heaps
template <typename T>
int MinMaxHeap<T>::size(){
  return m_min->size();
}

// Inserts a new node into the heap
// Data must be inserted to both heaps and sorted according to the
//  properties of the heap being inserted into
template <typename T>
void MinMaxHeap<T>::insert(const T& data){

  // Inserts into both Heaps 
  int* min_twin = m_min->insert(data);
  int* max_twin = m_max->insert(data, m_min->m_heap[*min_twin]);

  // Fixes the index pointers
  m_min->m_heap[*min_twin]->m_other_index = max_twin;
}

// Deletes the min node
// Node must be deleted in both heaps
//   (Root of Min Heap and Leaf of Max Heap)
template <typename T>
T MinMaxHeap<T>::deleteMin(){
  T data = m_min->m_heap[TOP]->m_data;

  // Deletes Node's Twin first
  m_max->deleteAt(*m_min->m_heap[TOP]->m_other_index);

  // By default deletes root node which is min
  m_min->deleteAt();
  return data;
}

// Deletes the max node
// Node must be deleted in both heaps
//   (Root of Max Heap and Leaf of Min Heap)
template <typename T>
T MinMaxHeap<T>::deleteMax(){
  T data = m_max->m_heap[TOP]->m_data;

  // Deletes Node's twin first
  m_min->deleteAt(*m_max->m_heap[TOP]->m_other_index);

  // By default deletes root node which is max
  m_max->deleteAt();
  return data;
}

// Prints out the contents of both lists
// Utilizes Heap's dump() function
template <typename T>
void MinMaxHeap<T>::dump(){
  std::cout << std::endl << " ..... MinMaxHeap::dump() ....." << std::endl << std::endl;

  // Prints Min Heap first
  std::cout << "------------Min Heap------------" << std::endl;
  if (m_min != NULL)
    m_min->dump();
  else
    std::cout << "No Min Heap" << std::endl;

  // Prints Max Heap
  std::cout << std::endl << "------------Max Heap------------" << std::endl;
  if (m_max != NULL)
    m_max->dump();
  else
    std::cout << "No Max Heap" << std::endl;
  std::cout << std::endl << " .............................." << std::endl << std::endl;
}

// Grading Functions used to return information about the Max and Min nodes

// Returns information about min heap
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){

  // Copying data of node and index of node's twin
  data = m_min->m_heap[pos]->m_data;
  index = *m_min->m_heap[pos]->m_other_index;
}

// Returns information about max heap
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){

  // Copying data of node and index of node's twin
  data = m_max->m_heap[pos]->m_data;
  index = *m_max->m_heap[pos]->m_other_index;
}
#endif
