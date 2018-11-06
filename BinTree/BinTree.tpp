#pragma once
#include "Display.h"
using namespace Tree;

typedef unsigned int uint;

template<class T>
BinTree<T>::BinTree(const BinTree<T>& tree)
{
  this->data = tree.data;
  if(tree.has_left_child()) this->lftChild = new BinTree<T>(*(tree.get_left_tree()));
  if(tree.has_right_child()) this->rgtChild = new BinTree<T>(*(tree.get_right_tree()));
}

template<class T>
const BinTree<T>* BinTree<T>::get_spec_node(std::string path, char lc, char rc)const
{
  auto res = this;
  std::string used_path = "";
  for(auto it = path.begin(); it != path.end(); ++it)
  {
    if(*it == lc){
      used_path += lc;
      if(res->has_left_child()) res = res.get_left_tree();
      else throw std::logic_error("Left child doesn't exsit at request: " + used_path);
    }else if(*it == rc){
      used_path += rc;
      if(res->has_right_child()) res = res.get_right_tree();
      else throw std::logic_error("Right child doesn't exsit at request: " + used_path);
    }else throw std::logic_error("Request path character is illegal.");
  }
  return res;
}

template<class T>
void BinTree<T>::update_left_tree(const BinTree<T>& lft_t)
{
  if(this->lftChild == nullptr)
    throw std::logic_error("Can't update while left node exists!");
  else *(this->lftChild) = lft_t;
}

template<class T>
void BinTree<T>::update_right_tree(const BinTree<T>& rgt_t)
{
  if(this->rgtChild == nullptr)
    throw std::logic_error("Can't update while right node exists!");
  *(this->rgtChild) = rgt_t;
}

template<class T>
void BinTree<T>::update_spec_node(std::string path, T val, char lc, char rc)
{
  auto target = this;
  std::string used_path = "";
  for(auto it = path.begin(); it != path.end(); ++it)
  {
    if(*it == lc){
      used_path += lc;
      if(target->has_left_child()) target = target.get_left_tree();
      else throw std::logic_error("Left child doesn't exsit at request: " + used_path);
    }else if(*it == rc){
      used_path += rc;
      if(target->has_right_child()) target = target.get_right_tree();
      else throw std::logic_error("Right child doesn't exsit at request: " + used_path);
    }else throw std::logic_error("Request path character is illegal.");
  }
  target->data = val;
}

template<class T>
void BinTree<T>::insert_left_tree(const BinTree<T>& lft_t)
{
  if(this->lftChild != nullptr)
    throw std::logic_error("Can't insert while left node exists!");
  this->lftChild = new BinTree<T>(lft_t);
}

template<class T>
void BinTree<T>::insert_right_tree(const BinTree<T>& rgt_t)
{
  if(this->rgtChild != nullptr)
    throw std::logic_error("Can't insert while right node exists!");
  this->rgtChild = new BinTree<T>(rgt_t);
}

template<class T>
void BinTree<T>::insert_spec_node(std::string path, T val, char lc, char rc)
{
  auto parent = this;
  std::string used_path = "", p_path = path.substr(0, path.size()-1);
  for(auto it = p_path.begin(); it != p_path.end(); ++it)
  {
    if(*it == lc){
      used_path += lc;
      if(parent->has_left_child()) parent = parent.get_left_tree();
      else throw std::logic_error("Can't insert node without parent: " + used_path);
    }else if(*it == rc){
      used_path += rc;
      if(parent->has_right_child()) parent = parent.get_right_tree();
      else throw std::logic_error("Can't insert node without parent: " + used_path);
    }else throw std::logic_error("Request path character is illegal.");
  }
  if(path.back() == lc) parent->insert_left_tree();
  else if(path.back() == rc) parent->insert_right_tree();
  else throw std::logic_error("Request path character is illegal.");
}

template<class T>
void BinTree<T>::release_self_node()
{
  if(this->lftChild != nullptr) this->release_left_tree();
  if(this->rgtChild != nullptr) this->release_right_tree();
}

template<class T>
void BinTree<T>::release_left_tree()
{
  if(this->lftChild != nullptr)
  {
    this->lftChild->release_self_node();
    delete this->lftChild;
    this->lftChild = nullptr;
  }else throw std::logic_error("Release left tree doesn't exsit!");
}

template<class T>
void BinTree<T>::release_right_tree()
{
  if(this->rgtChild != nullptr)
  {
    this->rgtChild->release_self_node();
    delete this->rgtChild;
    this->rgtChild = nullptr;
  }else throw std::logic_error("Release right tree doesn't exsit!");
}

template<class T>
uint BinTree<T>::count_node_number()const{
  uint cnt = 1;
  if(this->has_left_child()) cnt += this->lftChild->count_node_number();
  if(this->has_right_child()) cnt += this->rgtChild->count_node_number();
  return cnt;
}

template<class T>
uint BinTree<T>::depth()const{
  uint result = 1;
  if(this->has_left_child()){
    auto lft_depth = this->lftChild->depth() + 1;
    result = (result > lft_depth) ? result : lft_depth;
  }
  if(this->has_right_child()){
    auto rgt_depth = this->rgtChild->depth() + 1;
    result = (result > rgt_depth) ? result : rgt_depth;
  }
  return result;
}

template<class T>
void BinTree<T>::display(std::ostream& out)const{
  out << Display::BinTreeMap<T>(this);
}

template<class T>
std::ostream& operator<<(std::ostream& out, BinTree<T> bt){
  return out << Display::BinTreeMap<T>(&bt);
}
