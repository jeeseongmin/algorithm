#include <iostream>
#include <vector>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

template<typename T>
struct Stack{
   vector<T> item;
};
template<typename T>
using stack = Stack<T>*;

template<typename T>
stack newStack<T>(){
   stack<T> s = new Stack<T>;
   return s;
}

template<typename T>
void free(stack<T> s){
   delete s;
}
template<typename T>
int size(stack<T> s) {
   return s->item.size();
}
template<typename T>
bool empty(stack<T> s) {
   return s->item.empty();
}
template<typename T>
void pop(stack<T> s) {
   s->item.pop_back();
}
template<typename T>
T top(stack<T> s){
   return s->item.back();
}
template<typename T>
void push(stack<T> s, string item){
   s->item.push_back(item);
   DPRINT(cout << "[size = " << size(s) << ", capacity = " << s->item.capacity() << "]" << endl;);
}
template<typename T>
void printStack(stack<T> s){
   if (empty(s)) return;
   string x = top(s);
   cout << x << ' ';
   pop(s);
   printStack(s);
   push(s,x);
}
template<typename T>
void printStack_fromBottom(stack<T> s){
   if (empty(s)) return;
   string x = top(s);
   pop(s);
   printStack_fromBottom(s);
   cout << x << ' ';
   push(s,x);
}

int main(){
   stack newStack<string>();
   void free(stack<string> s);
   int size(stack<string> s);
   void pop(stack<string> s);
   string top(stack<string> s);
   void push(stack<string> s, string item);
   void printStack(stack<string> s);
   void printStack_fromBottom(stack<string> s);
   // int list[] = {1,2,3,4,5,0,6,0,0,7,0,0,0,8};
   string list[] = {"to","be","or","not","to","-","be", \
                              "-","-","that","-","-","-","is"};
   stack<string> s = newStack<string>();
   for(auto item : list){
      if(item != "-")
         push(s,item);
      else{
         cout << top(s) << ' ';
         pop(s);
      }
   }
   cout << "\nsize: " << size(s);
   cout << "\ntop : " << top(s);
   cout << "\nstack T: "; printStack(s);
   cout << "\nstack B: "; printStack_fromBottom(s);
   cout << "\nHappy Coding";
   free(s);
}