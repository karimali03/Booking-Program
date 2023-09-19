
#include <iostream>
#include "user.h"
#include "client.h"
#include <map>
#include "tools.h"
#include "admin.h"

using namespace std;

#ifndef USER_manager__
#define USER_manager__

class users_manager
{

private:
    map<string,user*>users;
    user* active_user;
public:
    users_manager():active_user(nullptr){
        load_data();
    };
    ~users_manager(){
        if(active_user) delete active_user;
        for(auto & x : users) delete x.second;
        users.clear();
        active_user=nullptr;
    };
    void users_data(){
        for(auto x: users){
            vector<string>v=x.second->Profile();
            for(auto y : v) cout<<y<<" ";
            cout<<"\n";
        }
    }
    void sign_in(){
            while(1){
                string n,p;
                cout<<"Enter user name && password: "; cin>>n>>p;
                if(users.count(n) && users[n]->getPassword()==p){
                    active_user=users[n];
                    return;
                }
                cout<<"Wrong user name or password\n\n";
            }
    }
    void sign_up(){
        user* new_user=new client();
        string s; 
         string nu;
        while(1){
            cout<<"enter user name (space not allowed): "; cin>>s;
            if(!users.count(s)) break;
            cout<<"User name is already taken\n\n";
        }
        nu+=s,nu+=",";
        new_user->setUserName(s);
        cout<<"Enter password (space not allowed): ";  cin>>s;
         nu+=s,nu+=",";
        new_user->setPassword(s);
        cout<<"Enter your name: "; getline(cin,s);getline(cin,s);
          nu+=s,nu+=",";
        new_user->setName(s);
          nu+='0';
        users[new_user->userName()]=new_user;  
        active_user=new_user;
        vector<string>v{nu};
        WriteFileLines("users.txt",v);
    }

    void load_data(){
        vector<string>lines=ReadFileLines("users.txt");
        for(auto & x : lines){
            vector<string>data=SplitString(x);
                if(data.back()=="1"){
                    user* new_admin=new admin();
                    new_admin->setName(data[2]);
                    new_admin->setUserName(data[0]);
                    new_admin->setPassword(data[1]);
                    users[data[0]]=new_admin;
                }
                else{
                    user* new_client=new client();
                    new_client->setName(data[2]);
                    new_client->setUserName(data[0]);
                    new_client->setPassword(data[1]);
                    users[data[0]]=new_client;
                }
        }
    }
    
    void acsess(){
        vector<string>v{"Sign in","Sign up"};
        int ch=ShowReadMenu(v,"Menu");
        if(ch==1) sign_in();
        else sign_up();
    }

    user* activeUser() const { return active_user; }
    void setActiveUser(user* activeUser) { active_user = activeUser; }
};







#endif
