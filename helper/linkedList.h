#include <iostream>

class node
{
public:
  int value;
  node* next;
public:
  node(int);
  ~node();

  void  setValue(int);
  void  setNext(node*);
  int   getValue();
  node* getNext();
};

/*declaration*/
node::node(int _value = 0): value(_value), next(NULL) {}

node::~node() {
}

void node::setValue(int value) {
  this->value = value;
}

void node::setNext(node* next) {
  this->next = next;
}

int node::getValue() {
  return this->value;
}

node* node::getNext() {
  return this->next;
}

// class linkedList {
// private:
//   node* header;
// public:
//   linkedList();
//   ~linkedList();
//
//   bool insert(int);
//   bool update(int, int);
//   bool search(int);
//   bool delete(int);
// }
