#ifndef GRAPH_H
#define GRAPH_H

#include "User.h"
#include "Graph.h"
#include <vector>

namespace Graph{

  class Vertex{
  public:
  	Vertex(int perm, Graph::Vertex *nextUser= NULL);
  	~Vertex();
  	int getPerm()const{return userPerm;}
  	void setNext(Graph::Vertex *next){ nextUser= next;}
  	Graph::Vertex* getNext() const {return nextUser;}
  private:
  	Vertex *nextUser;
  	int userPerm;
  };

  class LinkList{
  public:
  	LinkList(Graph::Vertex *head = NULL);
  	~LinkList();
  	void insert(int perm);
  	Graph::Vertex *getHead() const {return head;}
    Graph::Vertex *getFirstFriend() const;
  	bool isFriend(int permNum);
  private:
  	Graph::Vertex* head;
  	Graph::Vertex* tail;

  };

  class List{
  public:
    List();
    ~List();
    void updateFriendList(int index, int newPerm);
    void insertNew(Graph::LinkList *userFriends);
    int getSize() const{return userList.size();}
    Graph::LinkList* getFriends(int index) const {return userList.at(index);}
    bool isFriend(int index, int friendPerm);
    
  private:
  	std::vector<Graph::LinkList*> userList;
    
  };

  std::ostream& operator << (std::ostream& out, const LinkList& L);
  std::ostream& operator << (std::ostream& out, const List& L);
}
#endif
