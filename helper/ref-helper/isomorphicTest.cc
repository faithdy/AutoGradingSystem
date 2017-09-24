#include "gtest/gtest.h"
#include "../isomorphic_array.h"
#include "../isomorphic_node.h"
#include "../isomorphic_linkedList.h"
#include "../isomorphic_circularlinkedlist.h"
#include "../isomorphic_binarynode.h"

/***********************************
          CASE 1 : Array
***********************************/
TEST(Array,Root_has_null) {
  int validArray[6] = {0,};

  EXPECT_TRUE(isomorphic_array<int>(NULL, NULL));
  EXPECT_FALSE(isomorphic_array<int>(NULL, validArray));
  EXPECT_FALSE(isomorphic_array<int>(validArray, NULL));
}

TEST(Array,has_different_size) {
  double Array_size_of_6[6] = {1,2,3,4,5,6};
  double Array_size_of_7[7] = {1,2,3,4,5,6,7};

  EXPECT_FALSE(isomorphic_array<double>(Array_size_of_6, Array_size_of_7));
}

TEST(Array,has_different_value) {
  int Array_1to6[6] = {1,2,3,4,5,6};
  int Array_multiples_of_2_from_1[6] = {1,2,4,8,16,32};
  int Array_divisors_of_12[6] = {1,2,3,4,6,12};

  EXPECT_FALSE(isomorphic_array<int>(Array_1to6, Array_multiples_of_2_from_1));
  EXPECT_FALSE(isomorphic_array<int>(Array_multiples_of_2_from_1,Array_divisors_of_12));
  EXPECT_FALSE(isomorphic_array<int>(Array_divisors_of_12,Array_1to6));
}

TEST(Array,is_isomorphic_case_of_integer) {
  int Array[6] = {1,2,3,4,5,6};
  int Array2[6] = {1,2,3,4,5,6};

  EXPECT_TRUE(isomorphic_array<int>(Array, Array2));
}

TEST(Array,is_isomorphic_case_of_double) {
  double Array[6] = {1.1,2.2,3.3,4.4,5.5,6.6};
  double Array2[6] = {1.1,2.2,3.3,4.4,5.5,6.6};

  EXPECT_TRUE(isomorphic_array<double>(Array, Array2));
}

TEST(Array,is_isomorphic_case_of_character) {
  char Array[6] = {'a','b','c','d','e','f'};
  char Array2[6] = {'a','b','c','d','e','f'};

  EXPECT_TRUE(isomorphic_array<char>(Array, Array2));
}

/***********************************
          CASE 2 : Node
***********************************/
class Node : public ::testing::Test {
 protected:
  virtual void SetUp() {
    root = new node<int>(1);

    node_size_of_3 = new node<int>(1);
    node_size_of_3->next = new node<int>(2);
    node_size_of_3->next->next = new node<int>(3);

    node_size_of_4 = new node<int>(1);
    node_size_of_4->next = new node<int>(2);
    node_size_of_4->next->next = new node<int>(3);
    node_size_of_4->next->next->next = new node<int>(4);
  }

  virtual void TearDown() {
    /*Generally, this scope must free
    the dynamic memory allocation area*/
  }

  node<int> *root;
  node<int> *node_size_of_3;
  node<int> *node_size_of_4;
};

TEST_F(Node, has_object) {
  node<int>* nodeObject = root;

  EXPECT_TRUE(isomorphic_node<int>(NULL,NULL));
  EXPECT_FALSE(isomorphic_node<int>(nodeObject,NULL));
  EXPECT_FALSE(isomorphic_node<int>(NULL,nodeObject));
}

TEST_F(Node, has_different_size) {
  EXPECT_FALSE(isomorphic_node
    (node_size_of_3,node_size_of_4));
}

TEST_F(Node, has_different_value) {
  node_size_of_3->next->next->next = new node<int>(5);
  EXPECT_FALSE(isomorphic_node
    (node_size_of_3,node_size_of_4));
}

TEST_F(Node, is_isomorphic) {
  node_size_of_3->next->next->next = new node<int>(4);

  EXPECT_TRUE(isomorphic_node
    (node_size_of_3,node_size_of_4));
}


/***********************************
        CASE 3 : Linked List
***********************************/
class Linked_List : public ::testing::Test {
 protected:
   virtual void SetUp() {
     M1 = new linkedList<int>;
     M2 = new linkedList<int>;
   }
   virtual void TearDown() {
     delete M1;
     delete M2;
   }
   linkedList<int>* M1;
   linkedList<int>* M2;
};

TEST_F(Linked_List, hasObject) {
  EXPECT_FALSE(isomorphic_linkedList<int>(M1, NULL));
  EXPECT_FALSE(isomorphic_linkedList<int>(NULL, M2));
  EXPECT_TRUE(isomorphic_linkedList<int>(NULL,NULL));
}

TEST_F(Linked_List, InsertOne) {
  M1->insert(30);
  M2->insert(40);
  EXPECT_FALSE(isomorphic_linkedList(M1,M2));
}

TEST_F(Linked_List, InsertMany) {
  M1->insert(31);
  M2->insert(31);
  M1->insert(32);
  M2->insert(32);
  M1->insert(33);
  M2->insert(43);
  EXPECT_FALSE(isomorphic_linkedList(M1,M2));
}

TEST_F(Linked_List, Search) {
  M1->insert(30);
  M1->insert(31);
  M1->insert(32);
  M1->insert(33);

  M2->insert(40);
  M2->insert(31);
  M2->insert(32);
  M2->insert(43);

  node<int>* N1 = new node<int>(30);
  node<int>* N2 = new node<int>(43);
  node<int>* N1intoM1 = M1->search(30);
  N1intoM1->next = NULL;
  node<int>* N2intoM2 = M2->search(43);
  N2intoM2->next = NULL;
  EXPECT_TRUE(isomorphic_node(N1, N1intoM1));
  EXPECT_TRUE(isomorphic_node(N2, N2intoM2));
}

TEST_F(Linked_List, Update) {
  M1->insert(30);
  M2->insert(40);
  EXPECT_FALSE(isomorphic_linkedList(M1, M2));
  EXPECT_TRUE(M1->update(30, 40));
  EXPECT_FALSE(M1->update(30, 40));
  EXPECT_TRUE(isomorphic_linkedList(M1, M2));
}

TEST_F(Linked_List, Delete) {
  EXPECT_FALSE(M1->_delete(30));
  M1->insert(30);
  EXPECT_FALSE(M1->_delete(40));
  EXPECT_TRUE(M1->_delete(30));
  EXPECT_FALSE(M1->_delete(30));
}

/***********************************
    CASE 4 : Circular Linked List
***********************************/
class Circular_Linked_List : public ::testing::Test {
 protected:
   virtual void SetUp() {
     M1 = new circularlinkedList<double>;
     M2 = new circularlinkedList<double>;
     M3 = new circularlinkedList<int>;
     M4 = new circularlinkedList<int>;
   }
   virtual void TearDown() {
     delete M1;
     delete M2;
     delete M3;
     delete M4;
   }
   circularlinkedList<double>* M1;
   circularlinkedList<double>* M2;
   circularlinkedList<int>* M3;
   circularlinkedList<int>* M4;
};

TEST_F(Circular_Linked_List, hasObject) {
  EXPECT_FALSE(isomorphic_circularlinkedList<int>(M3, NULL));
  EXPECT_FALSE(isomorphic_circularlinkedList<int>(NULL, M4));
  EXPECT_TRUE(isomorphic_circularlinkedList<int>(NULL,NULL));
}

TEST_F(Circular_Linked_List, Insert) {
  EXPECT_TRUE(isomorphic_circularlinkedList(M1,M2));
  M1->insert(1.1);
  M2->insert(1.1);
  EXPECT_TRUE(isomorphic_circularlinkedList(M1,M2));

  M1->insert(2.1);
  EXPECT_FALSE(isomorphic_circularlinkedList(M1,M2));
  M2->insert(2.1);
  EXPECT_TRUE(isomorphic_circularlinkedList(M1,M2));
}

TEST_F(Circular_Linked_List, Search) {
  for(int i=1; i<6; i++) M3->insert(i);
  for(int j=1; j<4; j++) M4->insert(j);
  EXPECT_FALSE(isomorphic_circularlinkedList(M3,M4));

  node<int>* N3intoM3 = M3->search(3);
  N3intoM3->next = M3->root;
  EXPECT_TRUE(isomorphic_circularlinkedList(M3,M4));

  node<int>* Nullity = M3->search(4);
  EXPECT_FALSE(Nullity);
  EXPECT_TRUE(isomorphic_node_iterative(Nullity, (node<int> *)NULL));
}

TEST_F(Circular_Linked_List, Update) {
  for(int i=1; i<6; i++) M3->insert(i);
  for(int j=1; j<6; j++) M4->insert(j+1);
  EXPECT_FALSE(M3->update(-1,10));

  for(int j=1; j<6; j++)
    EXPECT_TRUE(M4->update(j+1,j));

  EXPECT_TRUE(isomorphic_circularlinkedList(M3,M4));
}

TEST_F(Circular_Linked_List, Delete) {
  EXPECT_FALSE(M3->_delete(-1));
  for(int i=1; i<6; i++) M3->insert(i);
  for(int j=1; j<5; j++) M4->insert(j);
  EXPECT_FALSE(M3->_delete(-1));
  EXPECT_TRUE(M3->_delete(5));

  EXPECT_TRUE(isomorphic_circularlinkedList(M3,M4));
}

/***********************************
      CASE 4 : Binary Node
***********************************/
class Binary_Node : public ::testing::Test {
 protected:
  virtual void SetUp() {
    root = new binary_node<int>(1);

    node_size_of_5 = new binary_node<int>(300);
    node_size_of_5->left = new binary_node<int>(200);
    node_size_of_5->left->left = new binary_node<int>(100);
    node_size_of_5->right = new binary_node<int>(400);
    node_size_of_5->right->right = new binary_node<int>(500);

    node_size_of_6 = new binary_node<int>(300);
    node_size_of_6->left = new binary_node<int>(200);
    node_size_of_6->left->left = new binary_node<int>(100);
    node_size_of_6->right = new binary_node<int>(400);
    node_size_of_6->right->left = new binary_node<int>(350);
    node_size_of_6->right->right = new binary_node<int>(500);
  }

  virtual void TearDown() {
    /*Generally, this scope must free
    the dynamic memory allocation area*/
  }

  binary_node<int> *root;
  binary_node<int> *node_size_of_5;
  binary_node<int> *node_size_of_6;
};

TEST_F(Binary_Node, has_object) {
  binary_node<int> *origin = NULL;
  EXPECT_FALSE(origin);
  origin = new binary_node<int>(1);
  EXPECT_TRUE(origin);
  EXPECT_FALSE(origin->left);
  EXPECT_FALSE(origin->right);
}

TEST_F(Binary_Node, has_different_size) {
  EXPECT_FALSE(isomorphic_binarynode(node_size_of_5, node_size_of_6));
  node_size_of_6->right->left=NULL;
  EXPECT_TRUE(isomorphic_binarynode(node_size_of_5, node_size_of_6));
}

TEST_F(Binary_Node, has_different_value) {
  node_size_of_5->right->left=new binary_node<int>(350-100);
  EXPECT_FALSE(isomorphic_binarynode(node_size_of_5, node_size_of_6));
}

TEST_F(Binary_Node, is_isomorphic) {
  node_size_of_5->right->left=new binary_node<int>(350);
  EXPECT_TRUE(isomorphic_binarynode(node_size_of_5, node_size_of_6));
}
