//  Node.cpp
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <iostream>
#include <memory>
#include "Node.h"
using namespace std;

//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

template<typename ItemType>
Node<ItemType>::Node() : next(nullptr) {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr) {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, std::shared_ptr<Node<ItemType>> nextNodePtr) :
  item(anItem), next(nextNodePtr) {}

template<typename ItemType>
Node<ItemType>::~Node(){
  cout << "\nDestructing Node " << this->getItem() << " at: " << this << endl;
}

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
  item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setNext(std::shared_ptr<Node<ItemType>> nextNodePtr) {
  next = nextNodePtr;                  //move nextNodePtr to next
}

template<typename ItemType>
ItemType Node<ItemType>::getItem() const {
  return item;
}

template<typename ItemType>
std::shared_ptr<Node<ItemType>> Node<ItemType>::getNext() const {
  return next;
}
