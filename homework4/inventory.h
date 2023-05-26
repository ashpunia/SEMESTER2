#ifndef __inventory_h_
#define __inventory_h_

#include <iostream>
#include <list>
#include <string>
#include "customer.h"
class Customer;
class Inventory
{

public:
	Inventory();
	Inventory(const std::string& id, const int& quantity, const std::string& item_name);

	//ACCESSORS 
	std::string get_id() const;
	int get_quantity() const;
	std::string get_item_name() const;

	//SETTERS
	void set_id(const std::string& set_id);
	void set_quantity(const int& set_quantity);
	void set_item_name(const std::string& set_item_name);

	void sub_quantity();
	void add_quantity();

	void print_items(const Inventory& i, std::ofstream& inv_out_str);

	
private:
	std::string m_id;
	int m_quantity;
	std::string m_item_name;

};

#endif