
#include <iostream>
using namespace std;
#include "user.h"
#include <map>
#include "cards.h"
#include"reservations.h"

#ifndef CLIENT__
#define CLIENT__


class client: public user
{
private:
    map<string,PaymentCard*>cards;
    vector<string>reservations;
public:
    client(){
        type=0;
    }
    ~client(){
        for(auto &x : cards) delete x.second;
        cards.clear();
    }





     void add_card(){
        vector<string>v{"DebitCard","Credit Card"};
        int ch=ShowReadMenu(v,"Card Types");  
            string s;
            while(1){
                cout<<"Enter card number:"; cin>>s;
                if(!cards.count(s)) break;
                cout<<"Card already exist\n";
            }
       if(ch==1)     cards[s]=new DebitCard(s);
       else cards[s]=new CreditCard(s);
     }
     void create_reservation(string s){
        reservations.push_back(s);
     }
     void print_reservations(){
        for(auto x : reservations) cout<<x<<"\n";
     }
     vector<string> cards_info(){
        vector<string>v;
        for(auto x : cards) v.push_back(x.second->ToString());
        return v;
     }
     int getType(){
        return 0;
     }

     map<string,PaymentCard*>getCards() const { return cards; }
     void setCards(const map<string,PaymentCard*>&cards_) { cards = cards_; } 
     
};





#endif
