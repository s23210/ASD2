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

//Tworzymy strukturę liścia, który będzie podstawowym budulcem drzewa kodowania.
//Definiujemy w niej wskaźniki na lewe dziecko i prawe dziecko,
//jej wartość(ilość wystąpień/ich sumę), znak do kodowania, a także zakodowany znak.
// struct Node{
//  Node *left;
//  Node *right;
//  char character;
//  int value;
//  Node(char c, int v, Node* l=nullptr, Node* r=nullptr){ //tworzymy konstruktor struktury
//   left = l;
//   right = r;
//   character = c;
//   value = v;
//  }
//  ~Node(){ //pamiętajmy, że zawsze powinno się wyczyścić wszelkie zmienne
//   delete right; //dlatego zwalniamy pamięc zajętą przez dwójkę dzieci
//   delete left; //z racji, iż jest to destruktor, funkcja ta wywoła się również u usuniętych dzieci
//  }
//  bool isLeaf(){
//   return character != '\0'; //tworzymy funkcję pomocniczą, która wskażę, czy jest to liść zawierający jakiś znak
//  }
// };





//Tworzymy strukturę, która pomoże nam przy tworzeniu drzewa kodowania.
//Będzie ona porównywać dwa liście z drzewa/
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










void heapify(Node arr[], int n, int i)
{
    int smallest = i; // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is smaller than root
    if (l < n && arr[l].value < arr[smallest].value)
        smallest = l;
 
    // If right child is smaller than smallest so far
    if (r < n && arr[r].value < arr[smallest].value)
        smallest = r;
 
    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, smallest);
    }
}
 
// main function to do heap sort
void heapSort(Node arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call min heapify on the reduced heap
        heapify(arr, i, 0);
    }
}








//Definiujemy metodę, która stworzy drzewo kodowania Huffmana, a następnie zwróci jego korzeń
//Argumentem jest tekst, który chcemy zakodować
Node * createHuffmanTree(string line){
 map<char, int> counter; //korzystamy z obiektu map, aby zliczyć wystąpienia dla każdego znaku
 for(char c : line){
  if(counter.find(c) == counter.end()){ //jeżeli znaku nie ma w mapie
   counter[c] = 1; //dodajemy go
  }
  else{
   counter[c]++; //jeżeli jest, zwiększamy jego ilość wystąpień
  }
 }

//  struct Heap {
//       void clear();
//       int size();
//       void push(Node *node);
//       bool empty();
//       Node *top();
//       Node *pop();
//  };



 
 
 //Tworzymy obiekt priority_queue, który będzie przechowywać nieprzypisane elementy drzewa.
 //Obiekt priority_queue pozwoli nam stworzyć uporządkowaną listę liści drzewa - najmniejsze będą najwyżej.
 //Do porównywania elementów wykorzystujemy wcześniej zdefiniowaną strukturę comparator.
//  priority_queue<Node*, vector<Node*>, comparator> nodes; 

// PriorityQueue nodes(11);

//make queue of nodes
PriorityQueue nodes(counter.size());


//add new node to the queue
// for(auto it = counter.begin(); it != counter.end(); it++){
//       Node * node = new Node(it->first, it->second, nullptr, nullptr);
//       nodes[it->second] = node;
// }

// int N = sizeof(nodes)/sizeof(nodes[0]);

 for(auto entry : counter){
  nodes.push(new Node(entry.first, entry.second, nullptr, nullptr)); //tworzymy liście drzewa, bazując na znakach i ich ilości wystąpień
 }
 Node *root; //definiujemy zmienną, która docelowo będzie korzeniem naszego drzewa
 while(nodes.size() > 1){ //następnie iterujemy, dopóki w nodes nie zostanie ostatni element - korzeń drzewa
  Node *n1 = nodes.top().toNode(); //pobieramy pierwszy, najmniejszy element z priority queue
  nodes.pop(); //a następnie go usuwamy
  Node *n2 = nodes.top().toNode(); //ponawiamy powyższe kroki, aby uzyskać drugi, najmniejszy element
  nodes.pop();
  if(n1->value == n2->value && !n1->isLeaf()){ //jeżeli oba liście mają tą samą wartość, a jeden z nich jest kontenerem, to powinien on być traktowany jako większy element
   Node *pom = n1; //dlatego w takiej sytuacji podmieniamy wskaźniki
   n1 = n2;
   n2 = pom;
  }
  root = new Node('\0', n1->value + n2->value, n1, n2); //tworzymy liść-kontener, który będzie przechowywać dwa powyższe elementy i sumę ich wartości
  nodes.push(root); //a następnie dodajemy go do priority queue
 }
 return root; //gdy w priority queue zostanie tylko jeden wyraz, to oznacza, że drzewo zostało zbudowane, a wyraz ten jest jego korzeniem; zwracamy go
}



//Tworzymy rekurencyjną funkcję, która zakoduje elementy zależnie od ich pozycji w drzewie.
//Jako argumenty podajemy korzeń drzewa, tekst pomocniczy przy rekurencji, a także mapę kodowania
void encodeNodes(Node *node, string val, map<char, string> *map) {
 if(node == nullptr){ //warunek STOP funkcji rekurencyjnej:
  return; //jeżeli trafimy na koniec drzewa, przerywamy działanie
 }
 if(node->isLeaf()){ //jeżeli jest to liść przechowujący znak
  cout << node->character << " : " + val << endl; //to drukujemy go i jego zakodowaną wartość
  map->insert({node->character, val}); //a następnie dodajemy obie wartości do mapy
 }
 encodeNodes(node->left, val + '0', map); //wywołujemy jeszcze raz funkcję dla lewej strony drzewa - rekurencja
 encodeNodes(node->right, val + '1', map); //wywołujemy jeszcze raz funkcję dla prawej strony drzewa - rekurencja
}





//Tworzymy funkcję, która odkoduje zakodowany tekst bazując na zbudowanym drzewie.
string decode(Node *root, string encoded){
 string decoded = ""; //zmienna pomocnicza
 Node *currentNode = root; //wskaźnik na aktualnie sprawdzany liść
 for(char c : encoded){ //iterujemy poprzez zakodowany tekst
  if(c == '0'){ //jeżeli iterowany znak jest zerem, to oznacza, że musimy iść w lewo
   if(currentNode->left->isLeaf()){ //jeżeli dziecko po lewo jest liściem przechowującym znak
    decoded += currentNode->left->character; //dodajemy ten znak do zmiennej pomocniczej
    currentNode = root; //a następnie wracamy na początek drzewa
   }
   else{
    currentNode = currentNode->left; //jeżeli trafiliśmy na kontener, ustawiamy na niego wskaźnik
   }
  
  }
  else{ //jeżeli jest to inny znak (1), to przechodzimy na prawą stronę
   if(currentNode->right->isLeaf()){ //jeżeli dziecko po prawo jest liściem przechowującym znak
    decoded += currentNode->right->character;//dodajemy ten znak do zmiennej pomocniczej
    currentNode = root;//a następnie wracamy na początek drzewa
   }
   else{
    currentNode = currentNode->right;//jeżeli trafiliśmy na kontener, ustawiamy na niego wskaźnik
   }
  
  }
  
 }
 return decoded; //na koniec zwracamy odkodowany tekst
 
}





int main(){
 string line;

ifstream input("input.txt");
if(input.is_open()) {
      getline(input, line);
} else {
      cout << "Nie udalo sie otworzyc pliku input.txt" << endl;
      return 1;
      }
input.close();
 
 //tworzymy drzewo bazując na tekście
 Node *root = createHuffmanTree(line);
 
 //kodujemy wartości w drzewie, drukujemy je i dodajemy do nowej mapy, która powiąże znaki z ich zakodowanymi wartościami
 cout<< "Tablica kodowania Huffmana:" << endl;
 map<char, string> encodedValues;
 encodeNodes(root, "", &encodedValues);
 
//zapisujemy tablicę kodowania do pliku
ofstream output1("output.txt");
if(output1.is_open()) {
      for(auto it = encodedValues.begin(); it != encodedValues.end(); ++it) {
            output1 << it->first << " : " << it->second << endl;
      }
} else {
      cout << "Nie udalo sie otworzyc pliku output.txt" << endl;
      return 1;
      }





 //kodujemy tekst, bazując na utworzonej mapie kodowania
 string encodedLine = "";
 for(char c : line){
  encodedLine  += encodedValues[c];
 }

      //zapisujemy zakodowany tekst do pliku

output1 << encodedLine << endl;

output1.close();
//zapisz zakodowany tekst do pliku output.txt
// ofstream output("output.txt");
// if(output.is_open()) {
//       output << encodedLine;
// } else {
//       cout << "Nie udalo sie otworzyc pliku output.txt" << endl;
//       return 1;
//       }
// output.close();


 cout << "Tekst po zakodowaniu: " << encodedLine << endl;
 
 
 //odkodowujemy tekst, aby sprawdzić działanie
 cout << "Tekst po odkodowaniu: " << decode(root, encodedLine) << endl;
 
 //sprzątamy po sobie :)
 delete root;
 return 0;
}