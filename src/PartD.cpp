#include <iostream>
#include <memory>
#include <vector>
#include "LinkedBag.h"
using namespace std;

template<typename ItemType>
bool LinkedBag<ItemType>::findLocations(const ItemType &anItem){
  vector<shared_ptr<Node<ItemType>>> locations{ findLocationsHelper(getPointerTo(anItem)) };     //vector of locations where anItem appears
  cout << "\n !Display locations vector: ";
  for(auto index{ locations.begin() }; index != locations.end(); index++)  //cycle through the vector
    cout << (*index)->getItem() << " at " << *index << " ";                                                  //output the address
  cout << endl;
  return true;
}

template<typename ItemType>
vector<shared_ptr<Node<ItemType>>> LinkedBag<ItemType>::findLocationsHelper(shared_ptr<Node<ItemType>> searchItemPtr){
  vector<shared_ptr<Node<ItemType>>> locations;        //create an empty vector of locations
  shared_ptr<Node<ItemType>> index{ headPtr };         //create a node index to cycle through linked bag
  while(index != nullptr){                             //start a loop to cycle through linked bag
    ItemType anItem{index->getItem()};
    if(anItem == searchItemPtr->getItem()){            //if that value = value in searchItemPtr push_back that ptr to vector
      auto uPtr{ make_shared<Node<ItemType>> (anItem) };//create a new shared_ptr with anItem
      locations.push_back(uPtr);                        //add the uPtr to the vector
      remove(anItem);                                   //delete the node in the bag where the item is
    }
    index = index->getNext();                          //increment index
  }
  return locations;                                    //return vector
}

