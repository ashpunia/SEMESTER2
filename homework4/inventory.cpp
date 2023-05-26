#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include "inventory.h"

//default constructor
Inventory::Inventory()
{
	m_id = "";
	m_quantity = 0;
	m_item_name = "";
}
//constructor
Inventory::Inventory(const std::string& id, const int& quantity, const std::string& item_name)
{
	m_id = id;
	m_quantity = quantity;
	m_item_name = item_name;
}
//printing the inventory
void Inventory::print_items(const Inventory& i, std::ofstream& inv_out_str)
{
	inv_out_str<<m_id<<" "<<m_quantity<<" available "<<m_item_name<<std::endl;


}
//modifiers 
//subtracting quantity
void Inventory::sub_quantity()
{
	m_quantity--;
}
//adding the quantity
void Inventory::add_quantity()
{
	m_quantity++;
}
//getters
//accessing my id
std::string Inventory::get_id() const
{
	return m_id;
}
//accesing my quantity
int Inventory::get_quantity() const
{
	return m_quantity;
}
//accesing my item name
std::string Inventory::get_item_name() const
{
	return m_item_name;
}
//setters
//setting my item id 
void Inventory::set_id(const std::string& set_id)
{
	m_id = set_id;
}
//accesing my quantity
void Inventory::set_quantity(const int& set_quantity)
{
	m_quantity = set_quantity;
}
//accessing my item name
void Inventory::set_item_name(const std::string& set_item_name)
{
	m_item_name = set_item_name;
}