
#include<iostream>
using namespace std;
#include <sstream>

#ifndef Cards
#define Cards

class PaymentCard {
protected:
	string owner_name;
	string card_number;
	string expiry_date;
	int security_code;	
public:
    PaymentCard(string card_num){
         SetCardNumber(card_num);
        string s;
        int num;
        cout<<"Enter name on card: "; cin>>s;
        SetOwnerName(s);
        cout<<"Enter expiry_date [dd,mm,yy]: "; cin>>s;
        SetExpiryDate(s);
        cout<<"Enter Security Code: "; cin>>num;
        SetSecurityCode(num);
    }
	const string& GetCardNumber() const {
		return card_number;
	}

	void SetCardNumber(const string& cardNumber) {
		card_number = cardNumber;
	}

	const string& GetExpiryDate() const {
		return expiry_date;
	}

	void SetExpiryDate(const string& expiryDate) {
		expiry_date = expiryDate;
	}

	const string& GetOwnerName() const {
		return owner_name;
	}

	void SetOwnerName(const string& ownerName) {
		owner_name = ownerName;
	}

	int GetSecurityCode() const {
		return security_code;
	}

	void SetSecurityCode(int securityCode) {
		security_code = securityCode;
	}

	virtual string ToString() const {
		ostringstream oss;
		oss << "Owner: " << owner_name << " Card number: " << card_number << " Expiry date: " << expiry_date;
		return oss.str();
	}
	void Completepayment(){
		cout<<"Money withdraw confirmed\n";
		cout<<"Reservation Confirmed\n";
	}
	virtual PaymentCard* Clone() const = 0;

	virtual ~PaymentCard() {
	}
};

class DebitCard: public PaymentCard {
protected:
	string billing_address;

public:
    DebitCard(string card_num): PaymentCard(card_num){
        string s;
        cout<<"Enter Billing address: "; cin>>s;
        SetBillingAddress(s);
    }
	const string& GetBillingAddress() const {
		return billing_address;
	}

	void SetBillingAddress(const string& billingAddress) {
		billing_address = billingAddress;
	}

	virtual PaymentCard* Clone() const override {
		return new DebitCard(*this);
	}

	virtual string ToString() const {
		ostringstream oss;
		oss << "[Debit Card]: " << PaymentCard::ToString() << " Billing Address: " << billing_address;
		return oss.str();
	}
};

class CreditCard: public PaymentCard {

public:
    CreditCard(string num):PaymentCard(num){

    }
	virtual string ToString() const override {
		ostringstream oss;
		oss << "[Credit Card]: " << PaymentCard::ToString();
		return oss.str();
	}
	virtual PaymentCard* Clone() const override {
		return new CreditCard(*this);
	}
};


#endif 
