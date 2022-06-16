#ifndef NODE_H
#define NODE_H

struct Node {
 Node *left;
 Node *right;
 char character;
 int value;
 Node(char c, int v, Node* l=nullptr, Node* r=nullptr){ //tworzymy konstruktor struktury
  left = l;
  right = r;
  character = c;
  value = v;
 }
 //domyślny konstruktor
    Node(){
    left = nullptr;
    right = nullptr;
    character = '\0';
    value = 0;
    }
//convert node* to node
    Node(Node* n){
    left = n->left;
    right = n->right;
    character = n->character;
    value = n->value;
    }
//convert node to node*
    Node* toNode(){
    Node* n = new Node();
    n->left = left;
    n->right = right;
    n->character = character;
    n->value = value;
    return n;
    }

 ~Node(){ //pamiętajmy, że zawsze powinno się wyczyścić wszelkie zmienne
  delete right; //dlatego zwalniamy pamięc zajętą przez dwójkę dzieci
  delete left; //z racji, iż jest to destruktor, funkcja ta wywoła się również u usuniętych dzieci
 }
 bool isLeaf(){
  return character != '\0'; //tworzymy funkcję pomocniczą, która wskażę, czy jest to liść zawierający jakiś znak
 }
};

#endif