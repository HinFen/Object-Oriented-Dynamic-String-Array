// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : HiFen Hin Fen Kong
// St.# : #301430181
// Email: hfk@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

//
// These are the only permitted includes: don't include anything else.
//
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <algorithm>       
#include <cassert>

using namespace std;

class str_vec {
  private:
    //class member variables
    int cap;
    int sz;
    string* arr;

  public:

    static const int initial_cap = 10;

    //default constructor
    str_vec() : cap(initial_cap), sz(0), arr(new string[cap]){
    }

    //constructor that fills arr of size n and capacity n with string s
    str_vec(int n, string s){
      //error message when specified size of arr is less than 0
      if(n < 0){
        cmpt::error("\nUnable to create array of negative size\n");
      }else{
        //sets members of the object to the passed in values
        sz = n;
        cap = n;
        arr = new string[cap];
      }

      //fills array with the string s
      for(int i = 0; i < sz; i++){
        arr[i] = s;
      }
    }

    //copy constructor
    str_vec(const str_vec & other) : cap(other.cap), sz(other.sz), arr(new string[cap]){
      for(int i = 0; i < sz; i++){
        arr[i] = other.arr[i];
      }
    }

    //destructor
    ~str_vec(){
      delete[] arr;
    }

    //getter for size
    int size() const{
       return sz;
    }

    //getter for capacity
    int capacity() const{
      return cap;
    }

    //getter for percentage of array used
    double pct_used() const{
      return static_cast<double>(sz)/cap;
    }

    //converts all strings in arr into a single formatted string
    string to_str(){
      string arr_representation;
      arr_representation += "[";
      for(int i = 0; i < sz; i++){
        arr_representation += "\"" + arr[i] + "\"";
        if(i != sz-1){
          arr_representation += ", ";
        }
      }
      arr_representation += "]";

      return arr_representation;
    }

    //prints the string representation of str_vec to cout
    void print(){
      cout << "[";
      for(int i = 0; i < sz; i++){
        cout << "\"" << arr[i] << "\"";
        if(i != sz-1){
          cout << ", ";
        }
      }
      cout << "]";
    }

    //prints the string representation fo str_vec to cout but with and \n at the end
    void println(){
      cout << "[";
      for(int i = 0; i < sz; i++){
        cout << "\"" << arr[i] << "\"";
        if(i != sz-1){
          cout << ", ";
        }
      }
      cout << "]\n";
    }

    //getter for the string at index i
    string get(int i) const{
      if(i > sz-1 || i < 0){
        cmpt::error("\nattempted to get index out of array bounds");
      }
      return arr[i];
    }

    //setter sets the index location i to the copy string s
    void set(int i ,string s){
      if(i > sz-1 || i < 0){
        cmpt::error("\nattempted to set index out of array bounds");
      }
      arr[i] = s;
    }

    //apends string s to right end of the array, resizing as necessary
    void append(string s){
      //doubles the capacity of the underyling array when it is full 
      if(cap <= sz){
        cap *= 2;

        //makes a copy of the array
        string* copy = new string[cap];
        for(int i = 0; i < sz; i++){
          copy[i] = arr[i];
        }

        delete[] arr;
        arr = new string[cap]; 

        //copies back contents to the array
        for(int i = 0; i < sz; i++){
          arr[i] = copy[i];
        }

        //deallocates the copy
        delete[] copy;
      }

      //adds the string s to end of array and increases its size by 1
      arr[sz++] = s;
    }

    //apends string s to left end of the array, resizing as necessary
    void prepend(string s){
      //makes a copy of the array
      string* copy = new string[cap];
      for(int i = 0; i < sz; i++){
        copy[i] = arr[i];
      }

      //doubles the capacity of the underyling array when it is full 
      if(cap <= sz){
        cap *= 2;
        delete[] arr;
        arr = new string[cap];
      }

      //sets the left most index to string s
      arr[0] = s;
      //copies back contents to the array just shifted 1 to the right
      for(int i = 0; i < sz; i++){
        arr[i+1] = copy[i];
      }

      //increases the size by 1
      sz++;
      //deallcotes copy
      delete[] copy;
    }

    //appends all strings from the str_vec parameter into the calling object
    void append(str_vec other){
      //makes a copy of the array
      string* copy = new string[cap];
      for(int i = 0; i < sz; i++){
        copy[i] = arr[i];
      }

      //doubles the capacity of the underyling array until it can hold all the strings
      while(cap <= (sz + other.sz)){
        cap *= 2;
        delete[] arr;
        arr = new string[cap];
      }

      int strings = 0;
      //copies back contents to the array 
      for(int i = 0; i < sz; i++){
        arr[i] = copy[i];
        strings++;
      }

      //appends strings from other increasing sz for each added string
      for(int i = 0; i < other.size(); i++){
        arr[strings+i] = other.get(i);
        sz++;
      }

      //deallcoates the copy arr
      delete[] copy;
    }

    //reverses the the order of the elements in the array
    void reverse(){
      string* copy = new string[cap];
      
      //copies the array
      for(int i = 0; i < sz; i++){
        copy[i] = arr[i];
      }

      int idx = 0;
      int last_idx = sz-1;

      //copies back the strings in reverse order
      for(int i = last_idx; i >= 0; i--){
        arr[idx] = copy[i];
        idx++;
      }

      //deallocates the copy
      delete[] copy;
    }

    //sorts the array
    void sort(){
      //using std::sort with pointer arithmitic to sort array
      std::sort(arr, arr + sz);
    }

    //removes all elements from the array and sets the size to 0
    void clear(){
      string empty = "";
      //using std::fill and pointer arithmitic to clear the elements of the array
      std::fill(arr, arr + sz, empty);
      //sets the size of the array to 0
      sz = 0;
    }

    //resizes the underlying array so the capapcity and the size are the same
    void squish(){
      //copies the elements of the array
      string* copy = new string[cap];
      for(int i = 0; i < sz; i++){
        copy[i] = arr[i];
      }

      //shrinks the array capacity to match the size
      cap = sz;
      //deallocates and reallcates the array
      delete[] arr;
      arr = new string[cap];

      //copies elements back into resized array
      for(int i = 0; i < sz; i++){
        arr[i] = copy[i];
      }

      //deallcates the copy
      delete[] copy;
    }

}; // class str_vec

//checks the 2 str_vec have same elements in the same order and returns true if they are
bool operator==(const str_vec & a, const str_vec & b){
  //returns false if they have a different amount of elements
  if(a.size() != b.size()){
    return false;
  }

  //checks that the contents of the array are the same and in the same order
  for(int i = 0; i < a.size(); i++){
    if(a.get(i) != b.get(i)){
      return false;
    }
  }

  return true;
}

//returns true if the 2 str_vec objects do not contain the same elements in the same order
bool operator!=(const str_vec & a, const str_vec & b){
  //returns false if they have a different amount of elements
  if(a.size() != b.size()){
    return true;
  }

  //checks that the contents of the array are the same and in the same order
  for(int i = 0; i < a.size(); i++){
    if(a.get(i) != b.get(i)){
      return true;
    }
  }

  return false;
}

//tests for default constructor
void default_constructor_test(){
  cout << "\nTesting default constructor...";

  //constructs object with default constructor
  str_vec test_case;

  //tests if the default constructor creates the object with proper member values
  assert(test_case.size() == 0);
  assert(test_case.capacity() == 10);

  cout << "\nDefault constructor has passed all tests";
  }

//tests for fill constructor
void fill_constructor_test(){
  cout << "\nTesting fill constructor...";

  //arguments to pass into the fill constructor
  int n = 11;
  string s = "hi";

  str_vec test_case(n, s);

  //tests if parameters of the object constructed are as specified by passed in values
  assert(test_case.size() == 11);
  assert(test_case.capacity() == 11);

  //tests that the array was filled with the specified string
  for(int i = 0; i < test_case.size(); i++){
    assert(test_case.get(i) == s);
  }

  cout << "\nFill constructor has passed all tests";
}

//tests for the copy constructor
void copy_constructor_test(){
  cout << "\nTesting copy constructor...";

  int n = 5;
  string s = "<empty>";

  str_vec test_case_1(n,s);
  str_vec test_case_2(test_case_1);

  ///tests size is the same
  assert(test_case_2.size() == test_case_1.size());
  //tests capacity is the same
  assert(test_case_2.size() == test_case_1.size());
  //tests contents of the array are the same
  for(int i = 0; i < test_case_2.size(); i++){
    assert(test_case_2.get(i) == test_case_1.get(i));
  }

  cout << "\nCopy constructor has passed all tests";
}

//tests the destructor
void destructor_test(){
  cout << "\nTesting destructor...";
  //destructor will be called automatically and valgring will check if there's any memory leaks
  cout << "\nDestructor passed all tests";
}

//tests the size getter
void get_size_test(){
  cout << "\nTesting get size method...";

  int n = 5;
  string s = "cat";

  str_vec test_case_1;
  str_vec test_case_2(n, s);

  //test case 1 for get size
  assert(test_case_1.size() == 0);
  //test case 2 for get size
  assert(test_case_2.size() == n);

  cout << "\nGet size method has passed all tests";
}

//tests the capacity getter
void get_capacity_test(){
  cout << "\nTesting get capacity method...";

  int n = 5;
  string s = "cat";

  str_vec test_case_1;
  str_vec test_case_2(n, s);

  //test case 1 for get capacity
  assert(test_case_1.capacity() == 10);
  //test case 2 for get capacity
  assert(test_case_2.capacity() == n);

  cout << "\nGet capacity method has passed all tests";
}

//tests the pct_used method
void get_pct_used_test(){
  cout << "\nTesting get pct_used method...";

  int n = 5;
  string s = "cat";

  str_vec test_case_1;
  str_vec test_case_2(n, s);

  //testing when 0 percent of the array is used
  assert(test_case_1.pct_used() == 0.0);
  //testing with some of the array used
  test_case_1.append("cat");
  assert(test_case_1.pct_used() == 0.1);
  //testing when 100 percent of the array is used
  assert(test_case_2.pct_used() == 1.0);

  cout << "\nGet pct_used method has passed all tests";
}

//tests the to_str method
void to_str_test(){
  cout << "\nTesting to_str method...";

  int n = 1;
  int n_2 = 2;
  int n_3 = 3;
  string s = "cat";

  str_vec test_case_1;
  str_vec test_case_2(n, s);
  str_vec test_case_3(n_2, s);
  str_vec test_case_4(n_3, s);

  //testing for an empty string array
  assert(test_case_1.to_str() == "[]");
  //testing for an array of 1 string
  assert(test_case_2.to_str() == "[\"cat\"]");
  //testing for an array of 2 strings
  assert(test_case_3.to_str() == "[\"cat\", \"cat\"]");
  //testing for an array of 3 strings
  assert(test_case_4.to_str() == "[\"cat\", \"cat\", \"cat\"]");
  
  cout << "\nto_str method has passed all tests";  
}

//tests print method
void print_test(){
  cout << "\nTesting print method...";

  int n = 5;
  string s = "cat";

  str_vec test_case_1(n, s);

  test_case_1.print();
  
  cout << "\nPrint method has passed all tests";
}

//tests print_ln method
void print_ln_test(){
  cout << "\nTesting print_ln method...";

  int n = 5;
  string s = "cat";

  str_vec test_case_1(n, s);

  test_case_1.println();

  cout << "\nPrint_ln method has passed all tests";
}

//tests the get method
void get_method_test(){
  cout << "\nTesting get method...";

  int n = 5;
  string s = "cat";

  str_vec test_case_2(n, s);

  //test get
  for(int i = 0; i < test_case_2.size(); i++){
    assert(test_case_2.get(i) == "cat");
  }

  cout << "\nGet method has passed all tests";
}

//tests the set method
void set_method_test(){
  cout << "\nTesting set method...";

  int n = 5;
  string s = "cat";
  string s_2 = "dog";

  str_vec test_case_1(n, s);

  //test that set on individual index
  test_case_1.set(0, s_2);
  assert(test_case_1.get(0) == "dog");

  //test that set works on whole array
  for(int i = 0; i < test_case_1.size(); i++){
    test_case_1.set(i, s_2);
  }
  for(int i = 0; i < test_case_1.size(); i++){
    assert(test_case_1.get(i) == "dog");
  }

  cout << "\nSet method has passed all tests";
}

//tests the append method
void append_test(){
  cout << "\nTesting append method...";

  int n = 9;
  int n_2 = 10;
  string s = "cat";
  string s_2 = "dog";

  str_vec test_case_1(n, s);
  str_vec test_case_2(n_2, s);
  str_vec test_case_3;

  test_case_1.append(s_2);
  test_case_2.append(s_2);
  test_case_3.append(s);

  //tests that size increases properly
  assert(test_case_1.size() == 10);
  assert(test_case_2.size() == 11);
  assert(test_case_3.size() == 1);
  //tests that underlying array is only resized as neccessary
  assert(test_case_1.capacity() == 18);
  assert(test_case_2.capacity() == 20);
  assert(test_case_3.capacity() == 10);
  //test that string s was appended to the right side properly
  assert(test_case_1.get(n) == s_2);
  assert(test_case_2.get(n_2) == s_2);
  assert(test_case_3.get(0) == s);

  cout << "\nAppend method has passed all tests"; 
}

//tests the prepend method
void prepend_test(){
cout << "\nTesting prepend method...";

  int n = 9;
  int n_2 = 10;
  string s = "cat";
  string s_2 = "dog";

  str_vec test_case_1(n, s);
  str_vec test_case_2(n_2, s);
  str_vec test_case_3;

  test_case_1.prepend(s_2);
  test_case_2.prepend(s_2);
  test_case_3.prepend(s);

  //tests that size increases properly
  assert(test_case_1.size() == 10);
  assert(test_case_2.size() == 11);
  assert(test_case_3.size() == 1);
  //tests that underlying array is only resized as neccessary
  assert(test_case_1.capacity() == 18);
  assert(test_case_2.capacity() == 20);
  assert(test_case_3.capacity() == 10);
  //test that string s was appended to the right side properly
  assert(test_case_1.get(0) == s_2);
  assert(test_case_2.get(0) == s_2);
  assert(test_case_3.get(0) == s);

  cout << "\nPrepend method has passed all tests";
}

//tests the append method that appends all string from another object
void append_str_vec_test(){
  cout << "\nTesting append_str_vec method...";

  int n = 1;
  int n_2 = 3;
  int n_3 = 5;
  string s = "cat";
  string s_2 = "dog";

  str_vec test_case_1(n, s);
  str_vec test_case_2(n_2, s_2);
  str_vec test_case_3(n_3, s_2);
  str_vec test_case_4(n, s);

  test_case_1.append(test_case_2);
  test_case_2.append(test_case_2);
  test_case_4.append(test_case_3);

  //tests that size increases properly
  assert(test_case_1.size() == 4);
  //tests that underlying array is only resized as neccessary
  assert(test_case_1.capacity() == 8);
  assert(test_case_4.capacity() == 8);
  //tests that strings were appended properly
  for(int i = 0; i < test_case_1.size(); i++){
    if(i == 0){
      assert(test_case_1.get(i) == "cat");
    }else{
      assert(test_case_1.get(i) == "dog");
    }
  }

  //tests for self appending
  assert(test_case_2.size() == 6);
  assert(test_case_2.capacity() == 12);
  for(int i = 0; i < test_case_2.size(); i++){
    assert(test_case_2.get(i) == "dog");
  }

  cout << "\nAppend_str_vec method has passed all tests";
}

//tests for the reverse method
void reverse_test(){
  cout << "\nTesting reverse method...";

  str_vec test_case_1;
  str_vec test_case_2;
  test_case_1.append("a");
  test_case_1.append("b");
  test_case_1.append("c");
  test_case_1.append("d");
  test_case_2.append("a");

  string reversed[] = {"d", "c", "b", "a"};

  test_case_1.reverse();
  test_case_2.reverse();

  //tests that order of elements was reversed in the array properly
  for(int i = 0; i < test_case_1.size(); i++){
    assert(test_case_1.get(i) == reversed[i]);
  }
  //tests reverse works properly on 1 string in the array
  assert(test_case_2.get(0) == "a");

  cout << "\nReverse method has passed all tests";
}

void sort_test(){
  cout << "\nTesting sort method...";

  str_vec test_case_1;
  test_case_1.append("d");
  test_case_1.append("b");
  test_case_1.append("a");
  test_case_1.append("c");

  string sorted[] = {"a", "b", "c", "d"};

  test_case_1.sort();

  //tests that elements of the array were sorted properly
  for(int i = 0; i < test_case_1.size(); i++){
    assert(test_case_1.get(i) == sorted[i]);
  }

  cout << "\nSort method has passed all tests";
}

//tests for clear method
void clear_test(){
  cout << "\nTesting sort method...";

  int n = 10;
  string s = "cat";
  
  str_vec test_case_1(n, s);

  test_case_1.clear();

  //checks that capacity of the array remains the same
  assert(test_case_1.capacity() == 10);
  //tests that the size gets set to 0
  assert(test_case_1.size() == 0);
  
  cout << "\nClear method has passed all tests";
}

//tests the squish method
void squish_test(){
  cout << "\nTesting squish method...";
  
  int n = 6;
  string s = "a";
  str_vec test_case_1;
  str_vec test_case_2(n, s);

  test_case_1.append(s);
  test_case_2.append(s);
  test_case_1.squish();
  test_case_2.squish();

  //checks that capacity of the array is resized to be the same as the size
  assert(test_case_1.capacity() == test_case_1.size());
  //tests that the size remains the same
  assert(test_case_1.size() == 1);
  assert(test_case_2.size() == 7);
  //tests that the elements of the array are the same
  assert(test_case_1.get(0) == s);
  for(int i = 0; i < test_case_2.size(); i++){
    assert(test_case_2.get(i) == s);
  }

  cout << "\nSquish method has passed all tests";
}

//tests the overloaded== operator
void equals_operator_test(){
  cout << "\nTesting operator== function...";

  int n = 5;
  string s = "cat";
  string s_2 = "dog";

  str_vec test_case_1;
  str_vec test_case_2;
  str_vec test_case_3(n, s);
  str_vec test_case_4(n, s);
  str_vec test_case_5(n, s_2);
 
  //tests when comparing str_vec that are identical
  assert((test_case_1 == test_case_2) == true);
  assert((test_case_3 == test_case_4) == true);
  //tests when comparing str_vec sizes that have different arrays
  assert((test_case_1 == test_case_4) == false);
  assert((test_case_4 == test_case_5) == false);

  cout << ("\noperator== function has passed all tests");
}

//tests the overloaded!= operator
void not_equals_operator_test(){
  cout << "\nTesting operator!= function";

  int n = 5;
  string s = "cat";
  string s_2 = "dog";

  str_vec test_case_1;
  str_vec test_case_2;
  str_vec test_case_3(n, s);
  str_vec test_case_4(n, s);
  str_vec test_case_5(n, s_2);
 
  //tests when comparing str_vec that are identical
  assert((test_case_1 != test_case_2) == false);
  assert((test_case_3 != test_case_4) == false);
  //tests when comparing str_vec sizes that have different arrays
  assert((test_case_1 != test_case_4) == true);
  assert((test_case_4 != test_case_5) == true);

  cout << ("\noperator!= function has passed all tests");
}

int main() {
  cout << "Assignment 2 ... \n";

  default_constructor_test();
  fill_constructor_test();
  copy_constructor_test();
  destructor_test();
  get_size_test();
  get_capacity_test();
  get_pct_used_test();
  to_str_test();
  print_test();
  print_ln_test();
  get_method_test();
  set_method_test();
  append_test();
  prepend_test();
  append_str_vec_test();
  reverse_test();
  sort_test();
  clear_test();
  squish_test();
  equals_operator_test();
  not_equals_operator_test();
}