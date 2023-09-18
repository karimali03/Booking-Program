

using namespace std;
#include <map>
#include "reservations.h"

#ifndef Hotels__
#define Hotels__


class Hotel : public Reservation {
private:
	string city;
    string stars;
    string date;
    int days;
public:
	string ToString() const {
		ostringstream oss;
		oss << "Hotel: " << name <<" rating :"<<stars<<" Cost per day: " << cost/days << " Date: " << date;
		return oss.str();
	}

	double TotalCost() const { return cost*days; }
	void setTotalCost(double totalCost) { cost=totalCost; }
    
	string getDate() const { return date; }
	void setDate(const string &date_) { date = date_; }

	int getDays() const { return days; }
	void setDays(int days_) { days = days_; }

	string getStars() const { return stars; }
	void setStars(const string &stars_) { stars = stars_; }

	string getCity() const { return city; }
	void setCity(const string &city_) { city = city_; }

      
};

class Hotel_manager {
private:
  map<string,vector<Reservation*>>hotels;
public:
   Hotel_manager(){
    load_data();
   }
   ~Hotel_manager(){
      clear();
   }
   void clear(){
      for(auto &x : hotels) for(auto &y : x.second) delete y;
      hotels.clear();
   }
   void load_data(){
      clear();
     for(auto  y: Hotels_names){
        vector<string>v=ReadFileLines(y);
          y=y.substr(0,y.size()-4);
         for(auto & x : v){
         vector<string>z=SplitString(x);
         Hotel* new_hotel=new Hotel();
         new_hotel->setName(y);
         new_hotel->setCity(z[0]);
         new_hotel->setDate(z[2]);
         new_hotel->setDays(1);
         new_hotel->setStars(z[1]);
         new_hotel->setTotalCost(stoi(z.back(),0,10));
         hotels[z[0]].push_back(new_hotel);
      }
      }
   }
   vector<string> list_trips(string city,string date){
     vector<string> v;
     for(auto &x : hotels[city]){
        if(x->getDate()==date){
            v.push_back(x->ToString());
        }
     }
     return v;
   }

    Reservation* find(string city,string date,int idx){
     for(auto &x : hotels[city]){
        if(x->getDate()==date) idx--;
        if(!idx) return x;
     }
     return {};
   }


};



#endif 
