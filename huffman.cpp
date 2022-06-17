#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "heap.h"
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
      Node *root; // definicja korzenia drzewa
      while (nodes.size() > 1) {                                      // iteracja do momentu aż zostanie sam korzeń
            Node *n1 = nodes.top().toNode(); // pobranie pierwszego, najmniejszego elementu z kolejki
            nodes.pop();                     // usunięciego elementu z kolejki
            Node *n2 = nodes.top().toNode(); // to samo, tylko drugi najmniejszy element
            nodes.pop();
            if (n1->value == n2->value && !n1->isLeaf()) {                     // jeżeli oba liście mają tą samą wartość, a jeden z nich jest kontenerem, to powinien on być traktowany jako większy element
                  Node *pom = n1; // dlatego w takiej sytuacji podmieniamy wskaźniki
                  n1 = n2;
                  n2 = pom;
            }
            root = new Node('\0', n1->value + n2->value, n1, n2); // tworzymy liść-kontener, który będzie przechowywać dwa powyższe elementy i sumę ich wartości
            nodes.push(root);                                     // a następnie dodajemy go do priority queue
      }
      return root; // gdy zostanie tylko root, to drzewo zostało zbudowane
}

// Tworzymy rekurencyjną funkcję, która zakoduje elementy zależnie od ich pozycji w drzewie.
// Jako argumenty podajemy korzeń drzewa, tekst pomocniczy przy rekurencji, a także mapę kodowania
void encodeNodes(Node *node, string val, map<char, string> *map) {
      if (node == nullptr) {             // warunek STOP funkcji rekurencyjnej:
            return; // jeżeli trafimy na koniec drzewa, przerywamy działanie
      }
      if (node->isLeaf()) {                                                     // jeżeli jest to liść przechowujący znak
            cout << node->character << " : " + val << endl; // to drukujemy go i jego zakodowaną wartość
            map->insert({node->character, val});            // a następnie dodajemy obie wartości do mapy
      }
      encodeNodes(node->left, val + '0', map);  // wywołujemy jeszcze raz funkcję dla lewej strony drzewa - rekurencja
      encodeNodes(node->right, val + '1', map); // wywołujemy jeszcze raz funkcję dla prawej strony drzewa - rekurencja
}

// funkcja odkodowująca bazująca na drzewie
string decode(Node *root, string encoded) {
      string decoded = "";      // zmienna pomocnicza
      Node *currentNode = root; // wskaźnik na aktualnie sprawdzany liść
      for (char c : encoded) { // iterujemy poprzez zakodowany tekst
            if (c == '0') { // jeżeli iterowany znak jest zerem, to oznacza, że musimy iść w lewo
                  if (currentNode->left->isLeaf()) {                                              // jeżeli dziecko po lewo jest liściem przechowującym znak
                        decoded += currentNode->left->character; // dodajemy ten znak do zmiennej pomocniczej
                        currentNode = root;                      // a następnie wracamy na początek drzewa
                  } else {
                        currentNode = currentNode->left; // jeżeli trafiliśmy na kontener, ustawiamy na niego wskaźnik
                  }
            } else { // jeżeli jest to inny znak (1), to przechodzimy na prawą stronę
                  if (currentNode->right->isLeaf()) {                                               // jeżeli dziecko po prawo jest liściem przechowującym znak
                        decoded += currentNode->right->character; // dodajemy ten znak do zmiennej pomocniczej
                        currentNode = root;                       // a następnie wracamy na początek drzewa
                  } else {
                        currentNode = currentNode->right; // jeżeli trafiliśmy na kontener, ustawiamy na niego wskaźnik
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