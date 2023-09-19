#ifndef view_c__
#define view_c__

#include <iostream>
#include "user.h"
#include "client.h"
#include <map>
#include "tools.h"
#include <vector>
#include "reservations.h"
#include "Flights.h"
#include "hotels.h"

using namespace std;

class client_view
{
private:
    client* user;
public:
    client_view(client* user):user(user){
    }
    ~client_view(){
        if(user) delete user;
        user=nullptr;
    }
    void welcome(){
        cout<<"Welcome "<<user->getName()<<" | User View \n\n";
    }
    void display(Flight_manager* fmn,Hotel_manager* hmn){
        while(1){
        vector<string>s{"View Profile","Make Itinerary","List my Itineraries"
        ,"Add payment Card","Logout"};
        int ch=ShowReadMenu(s,"Menu");
        if(ch==1){
          vector<string>v=user->Profile();
          cout<<v[0]<<v[1]<<"\n";
          cout<<v[2]<<v[3]<<"\n\n";
        }
        else if(ch==2) {
            if(user->getCards().empty()){
                cout<<"Please add Payment Card First\n";
                continue;
            }
            itinerary_menu(fmn,hmn);
            }
        else if(ch==3){
            user->print_reservations();
        }
        else if(ch==4){
          user->add_card();
        }
        else break;
        }
    }
    void itinerary_menu(Flight_manager* fmn,Hotel_manager* hmn){
        ItineraryReservation* reservation=new ItineraryReservation();
        while(1){
        vector<string>v{"Add Flight","Add hotel","Done","Cancel"};
        int ch=ShowReadMenu(v,"Menu");
        if(ch==1) reservation->AddReservation(Flight_menu(fmn));
        else if(ch==2) reservation->AddReservation(Hotel_menu(hmn));
        else if(ch==3){
            user->create_reservation(reservation->ToString());
            break;
        }
        else {
            break;
        }
        }
    }
    Reservation* Flight_menu(Flight_manager* fmn){
        while(1){
        string date=ReadDate();
        string from,to;
        cout<<"Enter City from: "; getline(cin,from);getline(cin,from);
        cout<<"Enter City to: "; getline(cin,to);
        vector<string> v=fmn->list_trips(from,to,date);
        if(v.empty()){
            cout<<"This Trip is not avilable\n\n";
            continue;
        }
        int ch=ShowReadMenu(v);
        payment_menu();
        return fmn->find(from,to,date,ch);
    }
    }
    Reservation* Hotel_menu(Hotel_manager* hmn){
     while(1){
        string date=ReadDate();
        string city;
        cout<<"Enter City: "; getline(cin,city);getline(cin,city);
        vector<string> v=hmn->list_trips(city,date);
        if(v.empty()){
            cout<<"This Trip is not avilable\n\n";
            continue;
        }
        int ch=ShowReadMenu(v);
        payment_menu();
        return hmn->find(city,date,ch);
     }
    }
    void payment_menu(){
        vector<string>v;
        for(auto x: user->getCards()){
            v.push_back(x.second->ToString());
        }
        int ch=ShowReadMenu(v,"Select a payment Choice");
        auto x=user->getCards();
        x.begin()->second->Completepayment();
    }
};


#endif
