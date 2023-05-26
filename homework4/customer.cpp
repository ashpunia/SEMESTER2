#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include "customer.h"
#include "inventory.h"

//default constructor
Customer::Customer()
{
	m_cus_id = "";
	m_action = "";
	m_time = 0;
	m_quantity = 0;
	m_inv_id = "";
	m_customer_name = "";
}
//constructor
Customer::Customer(const std::string& cus_id, const std::string& action, const int& time, const int& quantity, 
	        	const std::string& inv_id, const std::string& customer_name)
{
	m_cus_id = cus_id;
	m_action = action;
	m_time = time;
	m_quantity = quantity;
	m_inv_id = inv_id;
	m_customer_name = customer_name;
}
//printing my object
void Customer::print_customer(const Customer& c,std::ofstream& out_str)
{
	out_str<<m_cus_id<<" "<<m_customer_name<<std::endl;
	//std::cout<<m_rented_items.size();
	std::list<Inventory>::iterator c_iterator = m_rented_items.begin();
	while (c_iterator!= m_rented_items.end()){
	//	out_str<<c_iterator->get_id()<<std::endl;
		out_str<<"Rental: "<<c_iterator->get_id()<<" ("<<c_iterator->get_quantity()<<") "<<std::endl;
		c_iterator++;
	}
	
}

//adding items to my rented items list
void Customer::add_rented_items(const Inventory& item)
{
	m_rented_items.push_back(item);
}
//removing rented items from my list when returned
void Customer::remove_rented_items(const Inventory& item)
{
	std::list<Inventory>::iterator p;
	for (p = m_rented_items.begin(); p != m_rented_items.end(); p++)
	{
		if (p->get_id() == item.get_id())
		{
			m_rented_items.erase(p);
		}
	}
}
//accessing the my list
std::list<Inventory> Customer::get_list() 
{
	return m_rented_items;
}
//accesing the customer id
std::string Customer::get_cus_id() const
{
	return m_cus_id;
}
//accesing the customer action
std::string Customer::get_action() const
{
	return m_action;
}
//accesing the timestamp
int Customer::get_time() const
{
	return m_time;
}
//accesing the item quantity
int Customer::get_quantity() const
{
	return m_quantity;
}
//accesing the item id
std::string Customer::get_inv_id() const
{
	return m_inv_id;
}
//accesing the customer name
std::string Customer::get_customer_name() const
{
	return m_customer_name;
}

//SETTERS
//setting the customer id
void Customer::set_cus_id(const std::string& c_id)
{
	m_cus_id = c_id;
}
//setting the action
void Customer::set_action(const std::string& action)
{
	m_action = action;
}
//setting the time
void Customer::set_time(const int& time)
{
	m_time = time;
}
//setting the quantity
void Customer::set_quantity(const int& q)
{
	m_quantity = q;
}
//setting the item id
void Customer::set_inv_id(const std::string& i_id)
{
	m_inv_id = i_id;
}
//setting the customer name
void Customer::set_customer_name(const std::string& customer_name)
{
	m_customer_name = customer_name;
}