#ifndef B_TREE_H
#define B_TREE_H
#include <iostream>
#include <vector>
#include "User.h"

namespace Tree{
	
  class TreeNode{
  public:
  	TreeNode(bool isLeaf=false, TreeNode* parent= NULL);
    //TreeNode(bool isLeaf, TreeNode* parent, std::vector<Person::User*> u);
  	~TreeNode(); 
  	int getValue(int index) const;
    TreeNode* getChild(int index) const {return children[index];}
    int getSize() const;
    bool isLeaf() const {return leaf;}
    Person::User* getUser(int index) const {return users[index];}


    void insertUser(Person::User* newNode);
    TreeNode* getParent(){return parent;}
  	bool isFull();
    TreeNode* splitNode(TreeNode* parent);
    void fixSplit(){keys.erase(keys.begin());}
    void insertChild(TreeNode* newPath);
    void insertKey(int key);
    void setParent(TreeNode* parent){this->parent= parent;}
    void setChild(int index, TreeNode* child);
    bool hasChildren(){return children.size()>0;}
    int getChildrenSize(){ return children.size();}
  private:
  	std::vector<TreeNode*> children;
  	std::vector<int> keys;

  	TreeNode* parent;
  	bool leaf;

  	std::vector<Person::User*> users;
    
  };

  class BTree{
  public:
    BTree();
    ~BTree();
    void insertUser(Person::User* user);
    bool userExist(int perm);
    Person::User* retrieveUser(int perm);
    int userIndex(int perm);
    void printTree();
  private:
  	TreeNode * root;

  	//Returns the container where the new user should be added.
  	TreeNode* findNode(int perm);
    void setRightChild(TreeNode* parent, TreeNode* rightChild, int index);
    void fixTree(TreeNode* node);
    void updateRoot(TreeNode* newRoot);

    
  };

  /*class UserSort{
  public:
  	bool operator() (Person::User* u1, Person::User* u2){
  		return u1->getPerm() < u2->getPerm();
  	}
  };*/
  bool userSort(Person::User* u1, Person::User* u2);
  bool childrenSort(Tree::TreeNode* p1, Tree::TreeNode* p2);

}
#endif
