#include "node.h"

using namespace std;

//konstruktor
 Node::Node(char c, int v, Node* l=nullptr, Node* r=nullptr){
  left = l;
  right = r;
  character = c;
  value = v;
 }
 //domyślny konstruktor
    Node::Node(){
    left = nullptr;
    right = nullptr;
    character = '\0';
    value = 0;
    }
// konstruktor tylko z value
    Node::Node(int v){
    left = nullptr;
    right = nullptr;
    character = '\0';
    value = v;
    }
//konwersja node* na node
    Node::Node(Node* n){
    left = n->left;
    right = n->right;
    character = n->character;
    value = n->value;
    }
//konwersja node na node*
    Node* Node::toNode(){
    Node* n = new Node();
    n->left = left;
    n->right = right;
    n->character = character;
    n->value = value;
    return n;
    }
//funkcja sprawdzająca czy dany node jest liściem (zawiera jakiś znak)
 bool Node::isLeaf(){
  return character != '\0';
 }
