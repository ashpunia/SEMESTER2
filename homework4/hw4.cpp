#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <list>

#include "customer.h"
#include "inventory.h"

//renting the items
void rent(std::list<Customer>& clist, std::list<Inventory>& invlist)
{
	std::list<Customer>::iterator cus = clist.begin();
	while (cus != clist.end())
	{
		if ((*cus).get_action() == "rent")
		{
			std::list<Inventory>::iterator inv = invlist.begin();
			while(inv != invlist.end())
			{
				if (cus->get_inv_id() == inv->get_id())
				{
					//std::cout<<inv->get_item_name()<<std::endl;
					cus->add_rented_items(*inv);
					inv->sub_quantity();
				}
			inv++;
			}
		}
		cus++;
	}
}
//returning items
void return_items(std::list<Customer>& clist, std::list<Inventory>& invlist)
{
	std::list<Customer>::iterator cus = clist.begin();
	while (cus != clist.end())
	{
		if ((*cus).get_action() == "return")
		{
			std::list<Inventory>::iterator inv = invlist.begin();
			while(inv != invlist.end())
			{
				if (cus->get_inv_id() == inv->get_id())
				{
					//std::cout<<inv->get_item_name()<<std::endl;
					cus->remove_rented_items(*inv);
					inv->add_quantity();

				}
			inv++;
			}
		}
		cus++;
	}
}

//parsing the inventory files and making the inventory objects 
void parsing_inv(const std::string& file, std::list<Inventory>& inventory_list)
{
	std::ifstream in_str(file);
	
	//checking if my input file opens
	if (!in_str.good()) 
	{
    std::cerr << "Can't open " << file << " to read.\n";
    exit(1);
  	}
  	std::string t_id;
  	int t_quantity;
  	std::string t_name;
  	std::list<Inventory>::iterator iteratorinv = inventory_list.begin() ;
	
	while (in_str >> t_id >> t_quantity >> t_name)
	{
		//error messages
		if (t_id[0] != 'T' || t_quantity == 0)
		{
			std::cout << "Invalid Inventory ID" << t_id << "found in the inventory file"<<std::endl;
			continue;
		}
		//setting my objects
		iteratorinv = inventory_list.begin() ;
		Inventory intemp;
		intemp.set_id(t_id);
		intemp.set_quantity(t_quantity);
		intemp.set_item_name(t_name);
		while (iteratorinv != inventory_list.end())
		{
			if (inventory_list.size() == 0)
			{
				inventory_list.insert(iteratorinv,intemp);
				//break;
			}
			else if (t_id < (*iteratorinv).get_id())
			{
				inventory_list.insert(iteratorinv,intemp);
				break;
			}

			iteratorinv++;
		}
		if(iteratorinv == inventory_list.end())
		{
			inventory_list.insert(iteratorinv, intemp);
		}
	}	
	
}

//parsing the customer file and making the customer objects
void parsing_cus(const std::string& file, std::list<Customer>& customer_list)
{
	std::ifstream in_str(file);
	
	//checking if my input file opens
	if (!in_str.good()) 
	{
    std::cerr << "Can't open " << file << " to read.\n";
    exit(1);
  	}

  	std::string t_cid;
  	std::string t_action;
  	int t_time;
  	int t_quantity;
  	std::string t_invid;
  	std::string t_cus_name;
  	//error checking 
  	std::list<Customer>::iterator iterator_cus = customer_list.begin();
	while (in_str >> t_cid >> t_action >> t_time>> t_quantity >> t_invid >> t_cus_name)
	{
		if (t_cid[0] != 'C' || t_quantity == 0)
		{
			std::cout << "Invalid Customer ID" << t_cid << "found in the inventory file"<<std::endl;
			continue;
		}
		//making my objects
		iterator_cus = customer_list.begin();
		Customer cstemp;
		cstemp.set_cus_id(t_cid);
		cstemp.set_action(t_action);
		cstemp.set_time(t_time);
		cstemp.set_quantity(t_quantity);
		cstemp.set_inv_id(t_invid);
		cstemp.set_customer_name(t_cus_name);
		while (iterator_cus != customer_list.end())
		{
			if (customer_list.size() == 0)
			{
				customer_list.insert(iterator_cus,cstemp);
			}
			else if ((t_cid < (*iterator_cus).get_cus_id()) && (t_cid != (*iterator_cus).get_cus_id()))
			{
				customer_list.insert(iterator_cus,cstemp);
				break;
			}

			iterator_cus++;
		}
		if(iterator_cus == customer_list.end())
		{
			customer_list.insert(iterator_cus, cstemp);
		}
	}	
}
int main(int argc, char* argv[])
{
	//assigning variables to the input
	std::string inv_ifile = argv[1];
	std::string cus_ifile = argv[2];
	std::string inv_ofile = argv[3];

	//error checking the input
	if (argc < 5)
	{
		std::cout<<"invalid number of input arguments given"<<std::endl;
	}
	//opening two files (one for customers and one for inventory)
	std::ofstream out_str(cus_ofile);
	std::ofstream inv_out_str(inv_ofile);
	
	//making my object files and parsing
	std::list<Inventory> inventory_list;
	parsing_inv(inv_ifile,inventory_list);
	std::list<Customer> customer_list;
	parsing_cus(cus_ifile, customer_list);

	//renting and returning items
	rent(customer_list,inventory_list);
	return_items(customer_list,inventory_list);
	
	//printing my customer objects
	std::list<Customer>::iterator ci = customer_list.begin();
	while (ci!= customer_list.end())
	{
		ci->print_customer(*ci, out_str);
		out_str<<std::endl;
		ci++;
	}

	//printing my inventory objects
	std::list<Inventory>::iterator invi = inventory_list.begin();
	while (invi != inventory_list.end())
	{
		invi->print_items(*invi, inv_out_str);
		inv_out_str<<std::endl;
		invi++;
	}
	
	//pending list- customer ids/ item ids/timestamps 

}
