
#include "tools.h"
#include "Flights.h"
#include "hotels.h"
#include "users_manager.h"
#include "client_view.h"
#include "admin_view.h"


class Booking_program
{
private:
    users_manager* users;
	Hotel_manager* hmn;
	Flight_manager* fmn;
public:
    Booking_program(){
        load_data();
        users=new users_manager();
		hmn=new Hotel_manager();
		fmn=new Flight_manager();
    }
    ~Booking_program(){
        if(users) delete users;
        users=nullptr;
		if(hmn) delete hmn;
		hmn=nullptr;
		if(fmn) delete fmn;
		fmn=nullptr;
    }
    void run(){
       while(1){
        users->acsess();
        if(users->activeUser()->getType()){
            	auto view=new admin_view(dynamic_cast<admin*>(users->activeUser()));
			view->welcome();
			view->display(users,fmn,hmn);
        }
        else{
			auto view=new client_view(dynamic_cast<client*>(users->activeUser()));
			view->welcome();
			view->display(fmn,hmn);
        }
    }
    }
};




int main(){
    Booking_program program;
    program.run();
   
    return 0;
}
