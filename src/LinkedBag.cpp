//  LinkedBag.cpp
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <memory>
#include <cstddef>
#include "Node.h"
#include "LinkedBag.h"

//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {}

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {
  itemCount = aBag.itemCount; //copy the item count from the old bag to the new
  std::shared_ptr<Node<ItemType>> origChainPtr{move(aBag.headPtr)}; //origChainPtr is a uniquePtr

  if (origChainPtr == nullptr) {
    headPtr = nullptr;
  }
  else {
    headPtr = std::make_shared<Node<ItemType>> (origChainPtr->getItem());
    std::shared_ptr<Node<ItemType>> newChainPtr{move(origChainPtr->getNext())};

    while (origChainPtr != nullptr)
    {
      ItemType nextItem = origChainPtr->getItem();
      auto newNodePtr{std::make_shared<Node<ItemType>> (nextItem)}; //create a newNode Unique Pointer
      newChainPtr->setNext(move(newNodePtr)); //pass by move
      newChainPtr = newChainPtr->getNext(); //increment newChainPtr
      origChainPtr = origChainPtr->getNext(); //increment origChainPtr
    }

    newChainPtr->setNext(nullptr); //the last node's next should point to null
  }
}

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag() {
  cout << "LinkedBag destructor has slayed starting at - \n";
  cout << "\t\t  head pointer at: " << this << ", with data: ";
  cout << this->headPtr->getItem() << endl;
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
  return itemCount == 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
  return itemCount;
}

template<typename ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
  shared_ptr<Node<ItemType>> nextNodePtr {make_shared<Node<ItemType>> (newEntry)};
  nextNodePtr->setNext(headPtr);
  headPtr = move(nextNodePtr);
  itemCount++;
  return true;
}

//create and return a vector from the LinkedBag contents
template<typename ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
  std::vector<ItemType> bagContents;
  Node<ItemType>* curPtr{ headPtr.get() };
  int counter = 0;

  while ((curPtr != nullptr) && (counter < itemCount)) {
    bagContents.push_back(curPtr->getItem());
    curPtr = curPtr->getNext().get();
    counter++;
  }

  return bagContents;
}

template<typename ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
  auto entryNodePtr{ getPointerTo(anEntry) };           //this will die once it goes out of scope
  bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
  
  if (canRemoveItem) {
    shared_ptr<Node<ItemType>> prev{ headPtr };         //create a prev pointer that points to head
    shared_ptr<Node<ItemType>> cur { prev };            //create a cur pointer that points to head
    while(entryNodePtr != cur){                         //as long as entryNodePtr != cur....
      if(cur == headPtr) cur = cur->getNext();          //if cur points to head, only increment cur
      else{                                             //otherwise increment both prev and cur
        cur = cur->getNext();
        prev = prev->getNext();
      }//else
   
      if(cur == entryNodePtr){                          //test to see if cur points at entryNodePtr
        cur = cur->getNext();                           //cur needs to point to the node right after entryNodePtr
        break;                                          //get out of the loop
      }//if
    }//while
    
    prev->setNext(cur);                                  //move cur into prev's next using setNext() function
    entryNodePtr.reset();                                //reset entryNodePtr's address

    itemCount--;
  }//if

  return canRemoveItem;
  //return 0;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear() {
  headPtr.reset();
  itemCount = 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
  int frequency = 0;
  int counter = 0;
  Node<ItemType>* curPtr = headPtr.get();

  while ((curPtr != nullptr) && (counter < itemCount)) {
    if (anEntry == curPtr->getItem()) {
      frequency++;
    }
    counter++;
    curPtr = curPtr->getNext().get();
  }

  return frequency;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
  return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
std::shared_ptr<Node<ItemType>> LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const {
  bool found = false;
  shared_ptr<Node<ItemType>> curPtr { headPtr };

  while (!found && (curPtr != nullptr)) {
    if (anEntry == curPtr->getItem()) {
      found = true;
    }
    else {
      curPtr = curPtr->getNext();
    }
  }
 
  return curPtr; //returns a shared_pointer to a particular object in the list
}

