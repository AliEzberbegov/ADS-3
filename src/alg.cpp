// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int sequence(char value) {
    switch (value) {
      case '(': return 0;
          break;
      case ')': return 1;
          break;
      case '+': return 2;
          break;
      case '-': return 2;
          break;
      case '*': return 3;
          break;
      case '/': return 3;
          break;
      default: return -1;
    }
}

std::string infx2pstfx(std::string inf) {
Tstack <char> MyStack;
int prioritet;
char arr;
char begin = 0;

std::string total;
for (int i = 0; i < inf.length(); i++) {
   arr = inf[i];
   prioritet = sequence(arr);
   if (prioritet > -1) {
            if ((prioritet == 0 || prioritet > sequence(begin) || MyStack.isEmpty()) && arr != ')') {
                if (MyStack.isEmpty())
                    begin = arr;
                    MyStack.push(arr);
            }
            else if (arr == ')') {
                while (MyStack.get() != '(') {
                    total.push_back(MyStack.get());
                    total.push_back(' ');
                    MyStack.pop();
                }
                MyStack.pop();
                if (MyStack.isEmpty())
                    begin = 0;
            }
            else {
                while (!MyStack.isEmpty() && sequence(MyStack.get()) >= prioritet) {
                    total.push_back(MyStack.get());
                    total.push_back(' ');
                    MyStack.pop();
                }
                if (MyStack.isEmpty())
                    begin = inf[i];
                    MyStack.push(inf[i]);
            }
        }
        else {
            total.push_back(arr);
            total.push_back(' ');
        }
    }
    while (!MyStack.isEmpty()) {
        total.push_back(MyStack.get());
        total.push_back(' ');
        MyStack.pop();
  }
  total.erase(total.end() - 1, total.end());
  return total;
}

int eval(std::string pst) {
  TStack <int> MyStack2;
  int amount;
  for (int i = 0; i < pst.length(); i++) {
    if (pst[i] >= '0' && pst[i] <= '9') {
        MyStack2.push(pst[i] - '0');
    }
    else if (pst[i] != ' ') {
      int val2 = MyStack2.get();
      MyStack2.pop();
      int val1 = MyStack2.get();
      MyStack2.pop();
      switch(pst[i]) {
        case '*': MyStack2.push(val1 * val2);
            break;
        case '/': MyStack2.push(val1 / val2);
            break;
        case '+': MyStack2.push(val1 + val2);
            break;
        case '-': MyStack2.push(val1 - val2);
            break;
        default: return -1;
      }
    }
  }
  amount = MyStack2.get();
  return amount;
}
