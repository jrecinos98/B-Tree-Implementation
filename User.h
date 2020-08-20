#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

namespace Person{
  class User{
  public:
    User(int perm_number=0, std::string name="", std::string genre1="", std::string genre2="", int location=0);
    ~User();
    int getPerm() const{return perm_number;}
    std::string getName() const{return name;}
    std::string getFirstGenre() const {return genre1;}
    std::string getSecondGenre() const {return genre2;}
    int getIndex() const {return location;}
  private:
    std::string name;
    std::string genre1;
    std::string genre2;
    int perm_number;
    int location;
    
  };

  std::ostream& operator << (std::ostream& out, const User& u);
}
#endif
