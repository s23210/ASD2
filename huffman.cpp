#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "node.h"
#include "priority_queue.h"

using namespace std;

// tworzenie drzewa kodowania Huffmana
Node *createHuffmanTree(string line) {
      map<char, int> counter;
      for (char c : line) {
            if (counter.find(c) == counter.end()) {
                  counter[c] = 1;
            } else {
                  counter[c]++;
            }
      }

      // kolejka priorytetowa, która przechowuje wszystkie liście drzewa (najmniejsze liście będą najwyżej)
      PriorityQueue nodes(counter.size());

      for (auto entry : counter) {
            nodes.push(new Node(entry.first, entry.second, nullptr, nullptr));
      }
      // definicja korzenia drzewa
      Node *root;
      // iteracja do momentu aż zostanie sam korzeń
      while (nodes.size() > 1) {
            // pobranie pierwszego, najmniejszego elementu z kolejki
            Node *n1 = nodes.top().toNode();
            // usunięciego elementu z kolejki 
            nodes.pop();
            // to samo, tylko drugi najmniejszy element
            Node *n2 = nodes.top().toNode(); 
            nodes.pop();
            // jeżeli oba liście mają tą samą wartość, a jeden z nich jest kontenerem, to powinien on być traktowany jako większy
            if (n1->value == n2->value && !n1->isLeaf()) {
                  // zamiana wskaźników
                  Node *pom = n1;
                  n1 = n2;
                  n2 = pom;
            }
            // tworzenie kontenera, który będzie przechowywać dwa liście i sumę ich wartości
            root = new Node('\0', n1->value + n2->value, n1, n2); 
            // dodanie kontenera do kolejki priorytetowej
            nodes.push(root);
      }
      // gdy zostanie tylko root, to drzewo zostało zbudowane
      return root;
}

// funkcja kodująca znaki zależnie od ich pozycji w drzewie
void encodeNodes(Node *node, string val, map<char, string> *map) {
      // przerwanie, jeśli natrafi na koniec drzewa
      if (node == nullptr) {
            return; 
      }
      // jeśli jest liść, to zapisuje kod dla danego znaku do mapy
      if (node->isLeaf()) {
            cout << node->character << " : " + val << endl;
            map->insert({node->character, val});
      }
      // rekurencyjne wywołanie tej funkcji dla lewego i prawego dziecka 
      encodeNodes(node->left, val + '0', map);
      encodeNodes(node->right, val + '1', map);
}

// funkcja odkodowująca bazująca na drzewie
string decode(Node *root, string encoded) {
      string decoded = "";      // zmienna pomocnicza
      Node *currentNode = root;
      // iteracja po zakodonowanym tekscie
      for (char c : encoded) {
            // jeżeli iterowany znak jest zerem, to przechodzę do lewego dziecka
            if (c == '0') { 
                  // jeżeli lewe dziecko jest liściem, to zapisuje znak do zmiennej pomocniczej i wracam do korzenia
                  if (currentNode->left->isLeaf()) {                                              
                        decoded += currentNode->left->character;
                        currentNode = root;
                  } else {
                        // jeżeli lewe dziecko to kontener, to przechodzę do lewego dziecka
                        currentNode = currentNode->left;
                  }
            // jeżeli iterowany znak jest równy 1, to przechodzę do prawego dziecka      
            } else {
                  // jeżeli prawe dziecko jest liściem, to zapisuje znak do zmiennej pomocniczej i wracam do korzenia
                  if (currentNode->right->isLeaf()) {
                        decoded += currentNode->right->character;
                        currentNode = root;
                  } else {
                        // jeżeli prawe dziecko to kontener, to przechodzę do prawego dziecka
                        currentNode = currentNode->right;
                  }
            }
      }
      return decoded;
}

int main() {
      string line;

      ifstream input("input.txt");
      if (input.is_open()) {
            getline(input, line);
      } else {
            cout << "Nie udalo sie otworzyc pliku input.txt" << endl;
            return 1;
      }
      input.close();

      // tworzenie drzewa
      Node *root = createHuffmanTree(line);

      // kodujemy wartości w drzewie, drukujemy je i dodajemy do nowej mapy, która powiąże znaki z ich zakodowanymi wartościami
      cout << "Tablica kodowania Huffmana:" << endl;
      map<char, string> encodedValues;
      encodeNodes(root, "", &encodedValues);

      // zapisywanie tablicy kodowania do pliku
      ofstream output1("output.txt");
      if (output1.is_open()) {
            for (auto it = encodedValues.begin(); it != encodedValues.end(); ++it) {
                  output1 << it->first << " : " << it->second << endl;
            }
      } else {
            cout << "Nie udalo sie otworzyc pliku output.txt" << endl;
            return 1;
      }

      // kodowanie tekstu
      string encodedLine = "";
      for (char c : line) {
            encodedLine += encodedValues[c];
      }

      // zapis zakodowanego tekstu do pliku
      output1 << encodedLine << endl;

      output1.close();

      cout << "Tekst po zakodowaniu: " << encodedLine << endl;

      // odkodowanie tekstu
      cout << "Tekst po odkodowaniu: " << decode(root, encodedLine) << endl;

      delete root;
      return 0;
}