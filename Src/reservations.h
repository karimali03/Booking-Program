#include <sstream>
#include <iostream>
#include <vector>
#include "tools.h"
using namespace std;

#ifndef reser__
#define reser__
class Reservation {
protected:
  string name;
  string date;	
  double cost;
public:
     Reservation(){};

	virtual double TotalCost() const = 0;

	virtual string ToString() const = 0;

	virtual string getDate() const = 0;

	virtual ~Reservation() {
	}

	string getName() const { return name; }
	void setName(const string &name_) { name = name_; }
};


class ItineraryReservation: public Reservation {
protected:
	vector<Reservation*> reservations;
public:
	ItineraryReservation(){
        setDate();
	}

	ItineraryReservation(const ItineraryReservation& another_reservation) {	
		for (Reservation* reservation : another_reservation.GetReservations())
			AddReservation(reservation);
	}

	void AddReservation(Reservation* reservation) {
		reservations.push_back(reservation);
        setDate();
	}

	virtual double TotalCost() const {
		double cost = 0;

		for (const Reservation* reservation : reservations)
			cost += reservation->TotalCost();

		return cost;
	}

	~ItineraryReservation() {
		Clear();
	}

	const vector<Reservation*>& GetReservations() const {
		return reservations;
	}

	void Clear() {
		for ( Reservation* reservation : reservations)
			delete reservation;
		reservations.clear();
	}

	virtual string ToString() const override {
		ostringstream oss;

		oss <<"**********************************************\n";
        oss<<"Check out at : "<<getDate()<<"\n\n";
		oss << "Itinerary of " << reservations.size() << " sub-reservations\n";
		for (Reservation* reservation : reservations)
			oss << reservation->ToString() << "\n";

		oss << "Total Itinerary cost: " << TotalCost() << "\n";
		oss <<"**********************************************\n";
		return oss.str();
	}

	string getDate() const { return date; }
	void setDate() { date= GetCurrentTimeDate(); }

};


#endif 
