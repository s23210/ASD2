#ifndef NODE_H
#define NODE_H

class Node {
    public:
    Node *left;
    Node *right;
    char character;
    int value;
    Node(char, int, Node*, Node*);
    Node();
    Node(int);
    Node(Node*);
    Node* toNode();
    // ~Node() {};
    bool isLeaf();
};


#endif