#ifndef NODE_H
#define NODE_H

// klasa Node (liść)
// wskaźniki na lewe dziecko i prawe dziecko,
// wartość(ilość wystąpień), znak do kodowania, a także zakodowany znak.
class Node {
public:
    Node *left;
    Node *right;
    char character;
    int value;
    Node(char, int, Node *, Node *);
    Node();
    Node(int);
    Node(Node *);
    Node *toNode();
    // ~Node() {};
    bool isLeaf();
};

#endif