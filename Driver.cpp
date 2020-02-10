/*****************************************
 ** File:    Driver.cpp
 ** Project: CMSC 341 Project 4 - Fake Min-Max Heaps, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    05/01/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file is the driver that tests various functions
 **    of the MinMaxHeap
 ***********************************************/
#include "MinMaxHeap.h"
#include "MinMaxHeap.cpp"

#include <stdlib.h>

int main(){
  MinMaxHeap<int> test(10);
  MinMaxHeap<int> trand(30);
  MinMaxHeap<char> tchar(10);

  std::cout << "Testing empty MinMax" <<std::endl;
  test.dump();

  std::cout << std::endl << "Testing Insert" << std::endl;
  test.insert(5);
  test.insert(10);
  test.insert(7);
  test.insert(9);
  test.insert(6);
  test.insert(2);
  test.insert(16);
  test.insert(12);
  test.insert(11);
  test.dump();

  std::cout << std::endl << "Testing Deleting Max" << std::endl;
  test.deleteMax();
  test.dump();  
  std::cout << std::endl << "Testing Deleting Max" << std::endl;
  test.deleteMax();
  test.dump(); 

  std::cout << std::endl << "Testing Deleting Min" << std::endl;
  test.deleteMin();
  test.dump();  
  std::cout << std::endl << "Testing Deleting Min" << std::endl;
  test.deleteMin();
  test.dump();

  std::cout << std::endl << "Testing Copy Constructor" << std::endl;
  MinMaxHeap<int> tcopy(test);
  tcopy.dump();

  std::cout << std::endl << "Testing Overloaded Assignment Operator" << std::endl;
  MinMaxHeap<int> tassign(3);
  tassign.insert(4);
  tassign.insert(3);
  tassign.dump();
  std::cout << "Assignment now occuring" << std::endl;
  tassign = test;
  tassign.dump();

  std::cout << std::endl << "Testing Insert using rand" << std::endl;
  int key;
  for (int i = 0; i < 30; i++){
    key = rand() % 20;
    //std::cout << std::endl <<"Inserting " << key << std::endl; 
    trand.insert(key);
  }
    trand.dump();

  std::cout << std::endl << "Testing Deleting Max" << std::endl;
  trand.deleteMax();
  trand.dump();  
  std::cout << std::endl << "Testing Deleting Max" << std::endl;
  trand.deleteMax();
  trand.dump();   

  std::cout << std::endl << "Testing Deleting Min" << std::endl;
  trand.deleteMin();
  trand.dump();  
  std::cout << std::endl << "Testing Deleting Min" << std::endl;
  trand.deleteMin();
  trand.dump();   

  std::cout << std::endl << "Testing Insert using chars" << std::endl;
  tchar.insert('q');
  tchar.insert('v');
  tchar.insert('h');
  tchar.insert('p');
  tchar.insert('a');
  tchar.insert('w');
  tchar.insert('m');
  tchar.insert('z');
  tchar.insert('c');
  tchar.dump();

  std::cout << std::endl << "Testing Deletion of Replacement Node (done with generic heap)" << std::endl;
  Heap<int> edge(40);
  edge.insert(4);
  edge.insert(8);
  edge.insert(3);
  edge.insert(5);
  edge.insert(2);
  edge.dump();
  edge.deleteAt(5);
  edge.dump();

  return 0;
}
