#ifndef EXPEDIA_FLIGHTS_API_H_
#define EXPEDIA_FLIGHTS_API_H_


using namespace std;
#include <map>
#include "reservations.h"
#include "tools.h"


class Flight : public Reservation {
private:
	string city_from;
    string city_to;
    string class_type;
    string date;

public:
	string ToString() const {
		ostringstream oss;
		oss << "Airline: " << name <<" Type :"<<class_type<<" Cost: " << cost << " Date " << date;
		return oss.str();
	}
    
	double TotalCost() const { return cost; }
	void setTotalCost(double totalCost) { cost=totalCost; }

	string cityFrom() const { return city_from; }
	void setCityFrom(const string &cityFrom) { city_from = cityFrom; }

	string classType() const { return class_type; }
	void setClassType(const string &classType) { class_type = classType; }

	string cityTo() const { return city_to; }
	void setCityTo(const string &cityTo) { city_to = cityTo; }

	string getDate() const { return date; }
	void setDate(const string &date_) { date = date_; }

      
};

class Flight_manager {
private:
  map<string,vector<Reservation*>>flights;
public:
   Flight_manager(){
    load_data();
   }
   ~Flight_manager(){
      clear();
   }
   void clear(){
     for(auto &x : flights) for(auto &y : x.second) delete y;
     flights.clear();
   }
   void load_data(){
      clear();
      for(auto y: flights_companies){
      cout<<y<<"\n";   
      vector<string>v=ReadFileLines(y);
      y=y.substr(0,y.size()-4);
      for(auto & x : v){
         vector<string>z=SplitString(x);
         Flight* new_flight=new Flight();
         new_flight->setName(y);
         new_flight->setCityFrom(z[0]);
         new_flight->setCityTo(z[1]);
         new_flight->setDate(z[3]);
         new_flight->setClassType(z[2]);
         new_flight->setTotalCost(stoi(z[4],0,10));
         string trip=new_flight->cityFrom()+"-"+new_flight->cityTo();
         flights[trip].push_back(new_flight);
      }
      }
   }
   vector<string> list_trips(string from,string to,string date){
     string trip=from+"-"+to;
     vector<string> v;
     for(auto &x : flights[trip]){
        if(x->getDate()==date){
            v.push_back(x->ToString());
        }
     }
     return v;
   }
    Reservation* find(string from,string to,string date,int idx){
     string trip=from+"-"+to;
     for(auto &x : flights[trip]){
        if(x->getDate()==date) idx--;
        if(!idx) return x;
     }
     return {};
   }


};



#endif 
