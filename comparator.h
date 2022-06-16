#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "node.h"

struct comparator{
 bool operator() (Node *a, Node *b){
  if(a->value != b->value) //jeżeli liście są różnej wartości
  return a->value > b->value; //wykonaj zwykłe porównanie
 if(!a->isLeaf() && b->isLeaf()) //jeżeli są równe i drugi jest kontenerem, to zawsze będzie on uznawany jako większy
  return false;
 if(!b->isLeaf() && a->isLeaf()) //jeżeli są równe i drugi jest kontenerem, to zawsze będzie on uznawany jako większy
  return true;
 if(a->isLeaf() && b->isLeaf()) //jeżeli oba są liściami
  return a->character > b->character; //to decyduje kolejność alfabetyczna
        return true; // jeżeli żaden z powyższych warunków nie zostanie spełniony, zwracamy true
 }
};

#endif