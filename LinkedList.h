#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:

   struct Node {
      T data;
      Node* next;
      Node* prev;
      Node() {
         next = nullptr;
         prev = nullptr;
      }
   };
   
   bool RemoveHead() {

      // 0, 1, 1+ elements
      
      if (head == nullptr) {
         return false;   
      } else if (head->next == nullptr) {
         Node* currentNode = head;
         delete currentNode;
         // reset
         head = nullptr;
         tail = nullptr;
         numNodes--;
         return true;
      } else {
         Node* currentNode = head;
         currentNode->next->prev = nullptr;
         head = head->next;
         delete currentNode;
         numNodes--;
         return true;
      }
      
   }
   
   bool RemoveTail() {

      // 0, 1, 1+ elements
      
      if (tail == nullptr) {
         return false;   
      } else if (tail->prev == nullptr) {
         Node* currentNode = head;
         delete currentNode;
         // reset
         head = nullptr;
         tail = nullptr;
         numNodes--;
         return true;
      } else {
         Node* currentNode = tail;
         currentNode->prev->next = nullptr;
         tail = tail->prev;
         delete currentNode;
         numNodes--;
         return true;
      }
      
   }
   
   bool RemoveAt(unsigned int index) {
      if (int(index) > numNodes) {
         return false;
      } else {
      
            Node* currentNode = head;
            Node* cNext;
            unsigned int i = 0;
         
            while (currentNode->next != nullptr) {
               cNext = currentNode->next;
               if (i == index) {
                  currentNode->prev->next = currentNode->next;
                  currentNode->next->prev = currentNode->prev;
                    
                  numNodes--;
                  delete currentNode;
                  return true;
                  
                  if (i == 0) {
                     head = currentNode->next;
                  }
                  if (int(i) == numNodes-1) {
                     tail = currentNode->next;   
                  }
               }
               i++;
               currentNode = cNext;
            }
            cNext = currentNode->next;  
            
            return false;
            delete cNext;
      }
      return false;
   }
   
   unsigned int Remove(const T& data) {
      // if any node->data == data, remove it from list
      // set node->prev->next to node->next, delete memory
      // return # of removed nodes
      
      unsigned int numRemoved = 0;
      
      Node* currentNode = head;
      Node* cNext;
      
      while (currentNode != nullptr) {
         // if at head
         // if at tail
         // if in middle
         cNext = currentNode->next;
         if (currentNode->data == data) {
            if (currentNode->next == nullptr) {
               // tail
               currentNode->prev->next = nullptr;
            } else if (currentNode->prev == nullptr) {
               // head
               currentNode->next->prev = nullptr;
            } else {
               currentNode->prev->next = currentNode->next;
               currentNode->next->prev = currentNode->prev;
            }   
            delete currentNode;
            numRemoved++;
         }
         
         currentNode = cNext;
      }
      numNodes -= numRemoved;
      
      
      return numRemoved;
   }
   
   void Clear() {
      Node* currentNode;
      Node* n = head;
      
      while (n != nullptr) {
         currentNode = n->next;
         delete n;
         n = currentNode;
      }

		head = nullptr;
		tail = nullptr;
		numNodes = 0;
   }
   
   void PrintForwardRecursive(const Node* node) const {
      // takes in a pointer to a Node - a starting node. From that node,
      // recursively visit each node that follows, in forward order, and print their values
      // must use recursion
      
      if (node->next != nullptr) {
         cout << node->data << endl;
         node = node->next;
         PrintForwardRecursive(node);
      } else {
         cout << node->data << endl;
      }
      
      //cout << node->data << endl;   
   }
   
   void PrintReverseRecursive(const Node* node) const {
      if (node->prev != nullptr) {
         cout << node->data << endl;
         node = node->prev;
         PrintReverseRecursive(node);
      } else {
         cout << node->data << endl;   
      }
   }
   
   void InsertAfter(Node* node, const T& data) {
      Node* newNode = new Node;
      
      newNode->prev = node;
      newNode->next = node->next;
      newNode->data = data;
      
      node->next->prev = newNode;
      node->next = newNode;
      
      numNodes++;
   }
   
   void InsertBefore(Node* node, const T& data) {
      Node* newNode = new Node;
      
      newNode->prev = node->prev;
      newNode->next = node;
      newNode->data = data;
      
      node->prev->next = newNode;
      node->prev = newNode;
      
      numNodes++;
   }
   void InsertAt(const T& data, unsigned int index) {
      // iterate through nodes, then isnert node AFTER the index
      
      if (int(index) > numNodes) {
         
         throw out_of_range("Bad index");  
         
      } else if (int(index) == numNodes) {
         
         Node* newNode = new Node;
         tail->next = newNode;
         newNode->data = data;
         newNode->prev = tail;
         newNode->next = nullptr;
         tail = newNode;
         
         numNodes++;
      } else {
         
         Node* newNode = new Node;
         Node* currentNode = head;
         Node* temp;
         
         newNode->data = data;
         int i = 0;
         
         while (currentNode->next != nullptr) {
            if (i == int(index)) {
               temp = currentNode;
            }
            currentNode = currentNode->next;
            i++;
         }
         
         newNode->prev = temp->prev;
         newNode->next = temp;
         
         if (temp->prev != nullptr) {
            temp->prev->next = newNode;   
         } else {
            head = newNode;   
         }
         
         temp->prev = newNode;
         
         numNodes++;
         
      }
      
   }
   
   int NodeCount() {
      return numNodes;
   }
   
   Node* Head() { return head; }
   const Node* Head() const { return head; }

   Node* Tail() { return tail; }
   const Node* Tail() const { return tail; }

   Node* GetNode(unsigned int index) {
      if (index >= numNodes) {
         throw out_of_range("Bad index");
      }   
   }
   const Node* GetNode(unsigned int index) const {
      if (index >= numNodes) {
         throw out_of_range("Bad index");
      }     
   }

   Node* Find(const T& data) {
      Node* currentNode = head;
      while(currentNode->next != nullptr) {
         if (currentNode->data == data) {
            return currentNode;   
         }  
         currentNode = currentNode->next;
      }
      return nullptr;
   }
   const Node* Find(const T& data) const {
      Node* currentNode = head;
      while(currentNode->next != nullptr) {
         if (currentNode->data == data) {
            return currentNode;   
         }  
         currentNode = currentNode->next;
      }
      return nullptr;   
   }

   void FindAll(vector<Node*>& outData, const T& value) const {
      Node* currentNode = head;
      while(currentNode->next != nullptr) {
         if (currentNode->data == value) {
            outData.push_back(currentNode);  
         }  
         currentNode = currentNode->next;
      }
      if (currentNode->data == value) {
         outData.push_back(currentNode);  
      }  
   }
   
   void AddHead(const T& data) {
      Node *newHead = new Node();
      newHead->data = data;
      newHead->prev = nullptr;
      
      if (head != nullptr) {
         head->prev = newHead;   
      }
      newHead->next = head;
      
      head = newHead;
      
      // loop through all and make tail
      Node* currentNode = head;
      while (currentNode->next != nullptr) {
         currentNode = currentNode->next;   
      }
      tail = currentNode;
      
      numNodes++;
   }
   
   void AddTail(const T& data) {
      Node *newTail = new Node();
      newTail->data = data;
      newTail->next = nullptr;
      
      if (tail != nullptr) {
         tail->next = newTail;   
      }
      newTail->prev = tail;
      
      tail = newTail;
      
      // loop through all and make head
      Node* currentNode = tail;
      while (currentNode->prev != nullptr) {
         currentNode = currentNode->prev;   
      }
      head = currentNode;
      
      numNodes++;
   }
   
   void AddNodesHead(const T* data, unsigned int count) {
      for (int i = int(count)-1; i >= 0; i--) {
         AddHead(data[i]);   
      } 
   }
   
   void AddNodesTail(const T* data, unsigned int count) {
      for (int i = 0; i < int(count); i++) {
         AddTail(data[i]);   
      } 
   }
   
   void PrintForward() {
      // start at head and go until nextNode = nullptr 
      Node* currentNode = head;
      while (currentNode->next != nullptr) {
         cout << currentNode->data << endl;
         currentNode = currentNode->next;
      }
      cout << currentNode->data << endl;
   }
   
   void PrintReverse() {
      
      // start at tail and go to previousNode = nullptr   
      Node* currentNode = tail;
      while (currentNode->prev != nullptr) {
         cout << currentNode->data << endl;
         currentNode = currentNode->prev;
      }
      cout << currentNode->data << endl;
   }
   
   LinkedList() {
      numNodes = 0;
      head = nullptr;
      tail = nullptr;
   }
   
   LinkedList(const LinkedList<T>& list) { // copy constructor
      // make a deep copy of the linked list
      
      if (list.head == nullptr) {
         head = nullptr;
         tail = nullptr;
         numNodes = 0;
      } else {
         head = nullptr;
         tail = nullptr;
         numNodes = 0;
         Node* currentNode = list.head;   
         
         while (currentNode != nullptr) {
            Node* newNode = new Node;
            newNode->data = currentNode->data;
            newNode->prev = nullptr;
            newNode->next = nullptr;
            
            if (numNodes == 0) { // no nodes
               head = newNode;
               tail = newNode;
            } else { // add to back, scoot elements over
               tail->next = newNode;
               newNode->prev = tail;
               tail = tail->next;
            }
            
            currentNode = currentNode->next;
            numNodes++;
            
         }
      }
      
   }
   
   T& operator[](unsigned int index) const {
      if (index >= numNodes) {
         throw out_of_range("Bad index");   
      }
      int i = 0;
      Node* currentNode = head; // head is index 0
      while (currentNode->next != nullptr) {
         if (i == index) {
            return currentNode->data;
         } else {
            i++;  
         }
      }
      
   };
   
   LinkedList<T>& operator=(const LinkedList<T>& rhs) { // assignment operator
      delete head->next;
      delete tail;
      delete head;
   
      if (rhs.head == nullptr) {
         head = nullptr;
         tail = nullptr;
         numNodes = 0;
      } else {
         head = nullptr;
         tail = nullptr;
         numNodes = 0;
         Node* currentNode = rhs.head;   
         
         while (currentNode != nullptr) {
            Node* newNode = new Node;
            newNode->data = currentNode->data;
            newNode->prev = nullptr;
            newNode->next = nullptr;
            
            if (numNodes == 0) { // no nodes
               head = newNode;
               tail = newNode;
            } else { // add to back, scoot elements over
               tail->next = newNode;
               newNode->prev = tail;
               tail = tail->next;
            }
            
            currentNode = currentNode->next;
            numNodes++;
         }
      }
      
      return *this;
   };
   
   bool operator==(const LinkedList<T> rhs) const {
      Node* currentNode = head;
      Node* rhsNode = rhs.head;
      bool isEqual = true;
      while (currentNode->next != nullptr && rhsNode->next != nullptr) {
         if (currentNode->data != rhsNode->data) {
            isEqual = false;   
         }
         currentNode = currentNode->next;
         rhsNode = rhsNode->next;
      }
      return isEqual;
   }
   
   ~LinkedList() {
      Clear();
   }
   
private:
   int numNodes;
   Node* head;
   Node* tail;
};