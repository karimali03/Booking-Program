#include <iostream>
#include <map>
#include "tools.h"
#include "users_manager.h"


class admin_view
{
private:
    admin* user;
public:
    admin_view(admin* user):user(user){
    }
    ~admin_view(){
        if(user) delete user;
        user=nullptr;
    }

    void welcome(){
        cout<<"Welcome "<<user->getName()<<" | Admin View \n\n";
    }
    void display(users_manager* mn,Flight_manager* fmn,Hotel_manager* hmn){
        vector<string>v{"Add Agency","view users","Log out"};
        while(1){
        int ch=ShowReadMenu(v,"menu");
        if(ch==1){
            agency_menu(fmn,hmn);
        }
        else if(ch==2){
            mn->users_data();
            cout<<"\n";
        }
        else break;
        }
    }
    void agency_menu(Flight_manager* fmn,Hotel_manager* hmn){
        vector<string>v{"Flight Company","Hotel"};
        int ch=ShowReadMenu(v,"Menu");
        string path;
        cout<<"Enter Comany Name: ";  cin>>path;
        path+=".txt";
        cout<<path<<"\n";
        if(ch==1){
            flights_companies.push_back(path);
            fmn->load_data();
        }
        else {
            Hotels_names.push_back(path);
             hmn->load_data();
        }
    }
};
