#include "bst.h"

template<typename T>
bool isomorphic_binarynode(binary_node<T>* M1, binary_node<T>* M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  if(M1->value != M2->value) return false;

  return isomorphic_binarynode(M1->left,M2->left)
    && isomorphic_binarynode(M1->right,M2->right);
}

template<typename T>
void traversal_node(binary_node<T>* root) {
  if(root==NULL) return;
  traversal_node(root->left);
  std::cout << root->value<<"->";
  traversal_node(root->right);
}

template<typename T>
void print_tree(bst<T> *Tree) {
  if(Tree==NULL) return;
  std::cout << "/* message */" << '\n';
  traversal_node(Tree->root);
  std::cout << std::endl << "/* message */" << '\n';
}
