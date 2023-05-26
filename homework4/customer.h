#ifndef __customer_h_
#define __customer_h_

#include <iostream>
#include <list>
#include <string>
#include "inventory.h"

class Inventory;
class Customer{
public:
	Customer();
	Customer(const std::string& cus_id, const std::string& action, 
			const int& time, const int& quantity,const std::string& inv_id, 
			const std::string& customer_name);

	//ACCESSORS
	std::string get_cus_id() const;
	std::string get_action() const;
	int get_time() const;
	int get_quantity() const;
	std::string get_inv_id() const;
	std::string get_customer_name() const;
	std::list<Inventory> get_list(); 

	//SETTERS
	void set_cus_id(const std::string& c_id);
	void set_action(const std::string& action);
	void set_time(const int& time);
	void set_quantity(const int& q);
	void set_inv_id(const std::string& i_id);
	void set_customer_name(const std::string& customer_name);


	void add_rented_items(const Inventory& item);
	void remove_rented_items(const Inventory& item);
	void print_customer(const Customer& c,std::ofstream& out_str);

private:
	std::string m_cus_id;
	std::string m_action;
	int m_time;
	int m_quantity;
	std::string m_inv_id;
	std::string m_customer_name;
	std::list<Inventory> m_rented_items;

};

#endif