#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};

template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}

template <class T>
void reverse(Node<T>* &input) {
  Node<T> *current = input;
   Node<T> *prev = NULL;
   Node<T> *temp = NULL;
   while (current != NULL) {
     temp = current->ptr;
     current->ptr = prev;
     prev = current;
     current = temp;
     }
     input = prev;

}

int main() {

  // manually create a linked list of notes with 4 elements
  //testing 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");

  Node<std::string>* my_list1 = new Node<std::string>; 
  my_list1->value = "hey"; 
  my_list1->ptr = new Node<std::stringstd::string>;
  my_list1->ptr->value = "what's";
  my_list1->ptr->ptr = new Node<std::string>;
  my_list1->ptr->ptr->value = "going";
  my_list1->ptr->ptr->ptr = new Node<std::string>;
  my_list1->ptr->ptr->ptr->value = "on";
  my_list1->ptr->ptr->ptr->ptr = NULL;

  print(my_list1,"my_list before");
  reverse(my_list1);
  print(my_list1,"my_list after ");

  Node<int>* my_list2 = new Node<int>; 
  // my_list2->value = 1; 
  // my_list2->ptr = new Node<int>;
  // my_list2->ptr->value = 2;
  // my_list2->ptr->ptr = NULL;

  print(my_list2,"my_list before");
  reverse(my_list2);
  print(my_list2,"my_list after ");


  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in Checkpoint 2!

}

// ===========================================================================
