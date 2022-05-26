// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

bool search(const char &sym, const std::string &string);
std::string searchRoot(const char* filename) {
  std::string middle_of_alph = "fghijklmnopqrstuFGHIJKLMNOPQRSTU";
  std::string word = "";
  std::ifstream fin(filename);
  if (!fin) {
    std::cout << "File error!" << std::endl;
    return word;
  }
  std::string temp;
  while (getline(fin, temp)) {
    std::stringstream words(temp);
    while (words >> word) {
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      for (int i = 0; i < middle_of_alph.size(); ++i) {
        if (word[0] == middle_of_alph[i]) {
          fin.close();
          return word;
        }
      }
    }
  }
  fin.close();
  return word;
}
bool search(const char &sym, const std::string &string) {
  for (int i = 0; i < string.size(); ++i) {
    if (sym == string[i]) {
      return true;
    }
  }
  return false;
}
BST<std::string> makeTree(const char* filename) {
  // поместите сюда свой код
  std::string root_val = searchRoot(filename);
  BST<std::string> tree;
  tree.add(root_val);
  tree.root->num--;
  std::ifstream fin(filename);
  if (!fin) {
    std::cout << "File error!" << std::endl;
    return tree;
  }
  std::string word = "";
  std::string temp_string;
  std::string eng_alphabet = "abcdefghijklmnopqrstuvwxyz";
  eng_alphabet += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  while (getline(fin, temp_string)) {
    for (int i = 0; i < temp_string.size(); ++i) {
      word += temp_string[i];
      if (!(search(temp_string[i], eng_alphabet))) {
        word.resize(word.size() - 1);
        if (!(word.empty())) {
          std::transform(word.begin(), word.end(), word.begin(), tolower);
          tree.add(word);
          word = "";
        }
      }
    }
    if (search(word[word.size() - 1], eng_alphabet)) {
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      tree.add(word);
      word = "";
    }
  }
  fin.close();
  return tree;
}
