#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include "BagInterface.h"
#include "LinkedBag.h"

//delete the second node in the Linked Bag
template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340(){
  return remove(headPtr->getNext()->getItem());  //remove second node by passing in the data of the node next to it
}

//Insert the new node at the end of the Linked Bag
template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType &newItem){
  shared_ptr<Node<ItemType>> nextNodePtr {make_shared<Node<ItemType>> (newItem)};  //create new node
  shared_ptr<Node<ItemType>> aNode = headPtr;                             //pointer starts at the beginning of list
  if(getCurrentSize() > 1){                                               //if only a head in bag, don't bother cycling through
    while(aNode->getNext() != nullptr){
      aNode = aNode->getNext();                                           //cycle through all nodes to get to the end
    }//while
  }//if
  aNode->setNext(nextNodePtr);
  itemCount++;
  return true;
}

//count the number of nodes in the Linked Bag iteratively
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
  Node<ItemType>* curNode = headPtr.get();    // pointer curNode = current node
  int i{ 0 };                                 // node counter to count the nodes in the list
  while(curNode != nullptr){                  // cycle through for-loop counting each node until curNode->next = null
    i++;                                      // increment the node counter
    curNode = curNode->getNext().get();       // skip to the next node
  }//while
  return i;                                   // return node counter
}

//count the number of nodes in the Linked Bag recursively. Use 1 helper function: getCurrentSize340RecursiveHelper
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
  Node<ItemType>* nodePtr = headPtr.get();
  return getCurrentSize340RecursiveHelper(nodePtr);
}

//helper function for getCurrentSize340Recursive
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* nodePtr) const {
  static int i{ 0 };                                   //create a counter
  if(nodePtr == nullptr) return i;                     //base case
  nodePtr = nodePtr->getNext().get();                  //increment nodePtr
  i++;                                                 //increment i
  getCurrentSize340RecursiveHelper(nodePtr);           //call the helper
  return i;
}

//count the number of nodes in the Linked Bag recursively NO helper
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const{
  static int i{ 0 };                             //counter gets initialized once
  static Node<ItemType>* curNode = headPtr.get();//curNode gets initialized once
  if(curNode == nullptr) return i;               //return counter if curNode is null
  i++;                                           //increment counter
  curNode = curNode->getNext().get();            //increment curNode
  getCurrentSize340RecursiveNoHelper();          //repeat
  return i;                                      //return counter
}

//recursively count the number of times an entry appears in the linked bag. Use helper function getFrequencyOf340RecursiveHelper
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType &anItem) const{
  Node<ItemType>* nodePtr = headPtr.get();                     //pointer to start of list
  return getFrequencyOf340RecursiveHelper(nodePtr, anItem);
}

//helper for getFrequencyOf340Recursive
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* nodePtr, const ItemType &anItem) const {
  int i{ 0 };                                                             //counter for matching items
  if(nodePtr == nullptr) return i;                                        //if end of the list return the matching item count
  if(anItem == nodePtr->getItem()) i++;                                   //if our item matches one in list, increment i
  return i + getFrequencyOf340RecursiveHelper(nodePtr->getNext().get(), anItem);//add i to the result of all subsequent recursive results
}

//recursively count the # of times an entry appears in the Linked Bag, without helper functions
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType &anItem) const {
  int i{ 0 };                                              //counter for matching items
  static Node<ItemType>* curNode = headPtr.get();          //curNode gets initialized once
  if(curNode == nullptr){                                  //if end of the list
    curNode = headPtr.get();                               //reset curNode for the next fcn call in main
    return i;                                              //return the matching item count
  }//if
  if(anItem == curNode->getItem()) i++;                    //if our item matches one in list, increment i
  curNode = curNode->getNext().get();                      //skip to the next node
  return i + getFrequencyOf340RecursiveNoHelper(anItem);   //add i to the result of all subsequent recursive results
}

//remove a random entry from the Linked Bag
template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340(){
  ItemType itemToReturn;                            //a variable to hold the randomly removed item
  Node<ItemType>* curNode{ headPtr.get() };
  srand((unsigned int) time(0));                    //seed random number generator
  int length{ getCurrentSize() };                   //get the length of the list
  if(length > 0) {
    int randNum{ rand() % length };                 //random number to generate
    for(int i{ 0 }; i < length; i++){               //cycle through the bag unti i = random number
      if (i == randNum){
        itemToReturn = curNode->getItem();          //assign the current node to itemToReturn
        remove(itemToReturn);                       //remove the current node
        break;                                      //break from the loop
      }//if
      curNode = curNode->getNext().get();           //increment node pointer to point to the next node
    }//for
    return itemToReturn;
  }//if 
  return itemToReturn;
}



