#include <iostream>
#include "Graph.h"

namespace Graph{
	List::List(){
		//Initialize userList

	}
	List::~List(){

	}

	//What if friend already has some of the added friends and already exists on the list??
	void List::updateFriendList(int index, int newPerm){
		Graph::LinkList* friends= getFriends(index);
		friends->insert(newPerm);

	}

	void List::insertNew(Graph::LinkList *userFriends){
		userList.push_back(userFriends);
	}
	bool List::isFriend(int index, int friendPerm){
		return userList.at(index)->isFriend(friendPerm);
	}

	LinkList::LinkList(Graph::Vertex *head){
		this->head= head;
	}
	void LinkList::insert(int perm){

		if(this->head == NULL){
			head = new Graph::Vertex(perm);
			tail= head;
		}
		else{
			tail->setNext(new Graph::Vertex(perm));
			tail= tail->getNext();
		}
	}
	bool LinkList::isFriend(int permNum){
		Graph::Vertex *it= getHead();
		while(it != NULL){
			if(it->getPerm() == permNum){
				return true;
			}
			it= it->getNext();
		}
		return false;
	}

	Graph::Vertex* LinkList::getFirstFriend() const{
		if(head != NULL){
			return head->getNext();
		}
		return NULL;
	}

	Vertex::Vertex(int perm, Graph::Vertex *nextUser){
		this->userPerm= perm;
		this-> nextUser= nextUser;
	}


	std::ostream& operator << (std::ostream& out, const LinkList& L){
		Graph::Vertex *temp= L.getHead();
		while(temp != NULL){
			out<<" "<<temp->getPerm();
			if(temp->getNext()!=NULL){
				out<<" ->";
			}
			temp= temp->getNext();
		}
		return out;

	}
	std::ostream& operator << (std::ostream& out, const List& L){
		for(int i =0; i< L.getSize(); i++){
			std::cout<< *L.getFriends(i)<<std::endl<<std::endl;
		}
	}


}
