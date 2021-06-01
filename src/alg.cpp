// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  std::string tstr;
  std::string str;
  std::map<char, int>mp = { {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1} };

  TStack<char> stack;
  for (int i = 0; i < inf.length(); i++) {
    if (inf[i] >= '0' && inf[i] <= '9') {
      tstr = inf[i];
      str += tstr + " ";
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
    } else if (inf[i] == ')') {
      char top = stack.get();
      stack.pop();
      while (top != '(') {
        tstr = top;
        str += tstr + " ";
        top = stack.get();
        stack.pop();
      }
    } else {
      while (!stack.isEmpty() && mp[stack.get()] >= mp[inf[i]]) {
        tstr = stack.get();
        str += tstr + " ";
        stack.pop();
      }
      stack.push(inf[i]);
    }
  }
  while (!stack.isEmpty()) {
    tstr = stack.get();
    str += tstr + " ";
    stack.pop();
  }
  return str.substr(0, str.length()-1);
}
int eval(std::string pst) {
  std::string tstr;
  TStack<int> stack;
  for (int i = 0; i < pst.length(); i++) {
    if (pst[i] >= '0' && pst[i] <= '9') {
      tstr = pst[i];
      stack.push(pst[i] - '0');
    } else if (pst[i] != ' ') {
      int se = stack.get();
      stack.pop();
      int fi = stack.get();
      stack.pop();
      if (pst[i] == '*') stack.push(fi * se);
      else if (pst[i] == '/') stack.push(fi / se);
      else if (pst[i] == '+') stack.push(fi + se);
      else
        stack.push(fi - se);
    }
  }
  return stack.get();
}
