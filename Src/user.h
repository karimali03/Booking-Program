#ifndef USER__
#define USER__

#include <iostream>
using namespace std;




class user
{
protected:
    string user_name;
    string name;
    string password;
    int type;

public:
    user(){};
    virtual ~user(){};
   
    vector<string> Profile() const {
        vector<string>v{"User Name: ",user_name,"Name : ",name,"Acsess"};
        if(type) v.push_back("Admin");
        else v.push_back("User");
		return v;
	}

    string userName() const { return user_name; }
    void setUserName(const string &userName) { user_name = userName; }

    string getName() const { return name; }
    void setName(const string &name_) { name = name_; }

    string getPassword() const { return password; }
    void setPassword(const string &password_) { password = password_; }

    virtual int getType() const { return type; }
    virtual void setType(const int &type_) { type = type_; }
};


#endif
