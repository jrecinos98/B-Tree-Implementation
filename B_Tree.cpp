#include "B_Tree.h"
#include <bits/stdc++.h>
#include <algorithm> 

namespace Tree{

	TreeNode::TreeNode(bool isLeaf, TreeNode* parent){
		leaf=isLeaf;
		this->parent= parent;

	}

	TreeNode::~TreeNode(){

	}

	bool TreeNode::isFull(){
		if(isLeaf()){
			return users.size() > 2;
		}
		else{
			return keys.size() > 3;
		}
	}
	void TreeNode::insertUser(Person::User* user){
		users.push_back(user);
		
		if(users.size() > 1){
			std::sort(users.begin(), users.end(), userSort);
		}			
			
	}
	void TreeNode::insertKey(int key){
		keys.push_back(key);
		if(keys.size()>1){
			std::sort(keys.begin(), keys.end());
		}
	
	}

	void TreeNode::insertChild(TreeNode* newPath){
		children.push_back(newPath);
		if(children.size() > 1){
			std::sort(children.begin(), children.end(), childrenSort);
		}
	}

	bool userSort(Person::User* u1, Person::User* u2){
	
		return u1->getPerm() < u2->getPerm();
	}

	bool childrenSort(Tree::TreeNode* p1, Tree::TreeNode* p2){
		return p1->getValue(0) < p2->getValue(0);
	}

	void TreeNode::setChild(int index, TreeNode* child){
		children[index]= child;
	}

	int TreeNode::getSize() const{
		if(isLeaf()){
			return users.size();
		}
		else{
			return keys.size();
		}
	}

	int TreeNode::getValue(int index) const{
		if(isLeaf()){
			return users[index]->getPerm();
		}
		else{
			return keys[index];
		}
	}

	/*
		Post-Condition: 
			-If the node is a leaf the node will be split into two with the smalles elemtn placed in the left and the rest on the right
			-If the node is internal then we insert smallest element to the left and update its pointers
			 then we proceed to erase the first element from keys and make right point to it. Return with extra value
	*/
	TreeNode* TreeNode::splitNode(TreeNode* parent){
		TreeNode* left;
		if(isLeaf()){
			left= new TreeNode(true);
			left->insertUser(users[0]);
			//Create a new vector ignoring the first element
			users= std::vector<Person::User*>(users.begin()+1, users.end());
			parent->insertKey(getValue(0));		
		}
		//If it is an internal Node
		else{
			left= new TreeNode(false);
			left->insertKey(keys[0]);
			//Set pointers for the left node and set the children parent
			for(int i =0; i< 2; i++ ){
				left->insertChild(children[i]);
				children[i]->setParent(left);
			}
			parent->insertKey(keys[1]);
			children= std::vector<TreeNode*>(children.begin()+2, children.end());
			//children.erase(children.begin(), children.begin()+2);

			//Erase the elements in the left node from the right node
			//keys.erase(keys.begin());

			keys= std::vector<int>(keys.begin()+2, keys.end());
			

		}
		return left;
	}
	

	BTree::BTree(){
		root= new TreeNode(true);
	}

	BTree::~BTree(){

	}
	void BTree::insertUser(Person::User* user){
		//This is the leaf where the new user belongs
		TreeNode* node= findNode(user->getPerm());

		node->insertUser(user);
		//printTree();
		//We insert and we fix if there was a problem.
		fixTree(node);		
	}
	void BTree::updateRoot(TreeNode* newRoot){
		root= newRoot;
	}

	void BTree::printTree(){
		for(int i =0; i< root->getSize()+1; i++){
			if(i < root->getSize())
				std::cout<<"\nROOT["<<i<<"] = "<<root->getValue(i)<<std::endl;
			if(root->hasChildren()){
			for (int j=0; j< root->getChild(i)->getSize()+1; j++){
				if(j< root->getChild(i)->getSize())
					std::cout<<"CHILD["<<i<<"["<<j<<"]] = "<<root->getChild(i)->getValue(j)<<std::endl;
				if(root->getChild(i)->hasChildren()){
					for(int k=0; k< root->getChild(i)->getChild(j)->getSize(); k++){
						std::cout<<"CHILD's CHILD["<<j<<"["<<k<<"]] = "<<root->getChild(i)->getChild(j)->getValue(k)<<std::endl;
			
					}
				}
			}
		}

		}
	}


	//Make the deletion on the right on splitnode rateher than on fixtree to avoid a bug. either return the value that was deleted or figure out another way.
	void BTree::fixTree(TreeNode* node){
		if(node->isFull()){
			TreeNode* parent= node->getParent();
			//We reached the root
			if(parent ==NULL){
				parent= new TreeNode(false);
				TreeNode* leftNode= node->splitNode(parent);
				TreeNode* rightNode=node;
		
				parent->insertChild(leftNode);
				parent->insertChild(rightNode);
				leftNode->setParent(parent);
				rightNode->setParent(parent);

				updateRoot(parent);
			}
			else{
				TreeNode* leftNode= node->splitNode(parent);
				TreeNode* rightNode=node;
				//parent->insertKey(rightNode->getValue(0));
				//rightNode->fixSplit();
				//Use sorted insertion here. Right already a child so it will be placed correctly
				parent->insertChild(leftNode);

				leftNode->setParent(parent);
				//node->fixSplit();
				
				if(parent->isFull()){
			
					fixTree(parent);
				}			

			}
			//std::cout<<"Path size: "<<parent->getchildrenize()<<std::endl;
		}

	}
	//Returns container where new user belongs regardless of if it is full or not

	TreeNode* BTree::findNode(int perm){
		TreeNode* temp =root;
		while(!temp->isLeaf()){
			//Assume value is bigger.
			int index= temp->getSize();
			//temp= temp->getChild(temp->getSize());
			for(int i=0; i< temp->getSize(); i++){
				if(perm < temp->getValue(i)){
					//std::cout<<"Smaller than: "<<temp->getValue(i)<<std::endl;
					index=i;
					break;
				}
			}
			temp= temp->getChild(index);

		}
		return temp;

	}


	Person::User* BTree::retrieveUser(int perm){
		//printTree();
		TreeNode* temp= findNode(perm);
		for (int i=0; i < temp->getSize(); i++){
			if(perm == temp->getValue(i)){
					return temp->getUser(i);
			}
		}
		return NULL;

		
	}

	bool BTree::userExist(int perm){
		Person::User* user= retrieveUser(perm);
		return user != NULL;

	}

	
}
