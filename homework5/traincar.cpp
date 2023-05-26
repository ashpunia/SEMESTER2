// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "traincar.h"


//pushing back the new car in the head car 
void PushBack(TrainCar*& head_car, TrainCar* new_car)
{
	if(!head_car)
	{
		head_car = new_car;
		return;
	}
	TrainCar* current_car = head_car;
	while(current_car->next != NULL)
	{
		current_car = current_car->next;
	}
	current_car->next = new_car;
	new_car->prev = current_car;
}
//deleteing all the cars to fix memory leaks 
void DeleteAllCars(TrainCar*& simple)
{
	if(simple == NULL)
	{
		return;
	}

	while(simple->next != NULL)
	{
		simple = simple ->next;
		delete simple->prev;
		simple->prev = NULL;
	}
	delete simple;

}

//count cars and calculate total weight
void TotalWeightAndCountCars(TrainCar* train,int& total_weight,int& num_engines,
							int& num_freight_cars,int& num_passenger_cars,
							int& num_dining_cars,int& num_sleeping_cars)
{
	total_weight = 0;
	num_engines = 0;
	num_freight_cars = 0;
	num_passenger_cars = 0;
	num_dining_cars = 0;
	num_sleeping_cars = 0;

	while(train != NULL)
	{
		if (train->isEngine())
		{
			total_weight+=150;
			num_engines+=1;
		}
		if (train->isFreightCar())
		{
			total_weight+=train->getWeight();
			num_freight_cars+=1;
		}
		if (train->isPassengerCar())
		{
			total_weight+=50;
			num_passenger_cars+=1;
		}
		if (train->isDiningCar())
		{
			total_weight+=50;
			num_dining_cars+=1;
		}
		if (train->isSleepingCar())
		{	
			total_weight+=50;
			num_sleeping_cars+=1;
		}
		train = train->next;
	}
}

//calculating the speed of the train that is passed in 
float CalculateSpeed(TrainCar* train)
{
	float total_horsepower = 0;
	float total_weight = 0;
	while (train!=NULL)
	{
		if (train->isEngine())
		{
			total_weight+=150;
			total_horsepower = 3000;
		}
		if (train->isFreightCar())
		{
			total_weight+=train->getWeight();
		}
		if (train->isPassengerCar())
		{
			total_weight+=50;
		}
		if (train->isDiningCar())
		{
			total_weight+=50;
		}
		if (train->isSleepingCar())
		{	
			total_weight+=50;
		}
		train = train->next;

	}
	float numerator = total_horsepower*550*3600;
	float denominator = 2000*0.02*5280*total_weight;
	float speed = numerator/denominator;
	return speed;
}

//average distance to a dining car for each pasenger car 
float AverageDistanceToDiningCar(TrainCar* train)
{
	float num_passenger_cars = 0;
	float left_counter = 0;
	float right_counter = 0;
	float total_counter = 0;
	while (train != NULL)
	{
		
		if (train->isPassengerCar())
		{
			
			num_passenger_cars+=1;
			TrainCar* search_left = train;
			TrainCar* search_right = train;
			left_counter = 0;
			right_counter = 0;

			//checking in each passenger car and going left and right
			while( search_left != NULL && !search_left->isDiningCar()) 
			{
				if ( search_left != NULL && search_left->isPassengerCar())
				{
					left_counter++;
				}
				search_left = search_left->prev;
			}
			while( search_right != NULL && !search_right->isDiningCar()) 
			{
				if (search_right != NULL && search_right->isPassengerCar())
				{
					right_counter++;
				}
				search_right = search_right->next;
			}
			if (search_left != NULL)
			{
				total_counter+=left_counter;
			}
			if (search_right != NULL)
			{
				total_counter+=right_counter;
			}
		}
		train = train->next;		
	}
	float ratio = (total_counter/num_passenger_cars);
	return ratio;
}

//returning the closest distance from an engine to a sleep car in the given train
float ClosestEngineToSleeperCar(TrainCar* train)
{
	float left_counter = 0;
	float right_counter = 0;
	float total_counter = 0;
	float temp_counter = 0;
	while (train != NULL)
	{
		
		if (train->isEngine())
		{
			TrainCar* search_left = train;
			TrainCar* search_right = train;
			

			while(search_left != NULL && !search_left->isSleepingCar()) 
			{
				if (search_left != NULL && !search_left->isEngine())
				{
					left_counter++;
				}
				search_left = search_left->prev;
			}
			while(search_right != NULL && !search_right->isSleepingCar()) 
			{
				if (search_right != NULL && !search_right->isEngine())
				{
					right_counter++;
				}
				search_right = search_right->next;
			}
			if(left_counter == 0)
			{
				temp_counter = right_counter;
			}
			else if(right_counter == 0)
			{
				temp_counter = left_counter;
				
			}
			else if (right_counter>left_counter)
			{
				temp_counter = left_counter;
			}
			else
			{
				temp_counter = right_counter;
			}
			if (total_counter == 0)
			{
				total_counter = temp_counter;
			}
			else if (temp_counter <= total_counter)
			{
				total_counter = temp_counter;
			}
		}
		train = train->next;		
	}
	return total_counter + 1;
}
//making multiple trains based on engines and min speed and max cars
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines, TrainCar*& all_freight, float min_speed, int max_cars)
{
	//what we are returning 
	std::vector<TrainCar*> trains;

	//looping through until the end of freights or the end of the engines
	while(all_freight != NULL && all_engines != NULL)
	{

		int num_cars = 0;

		TrainCar* current_train = NULL;
		//test the load
		TrainCar* test_train = NULL;
		//engine on both trains
		PushBack(current_train, TrainCar::MakeEngine());
		PushBack(test_train, TrainCar::MakeEngine());
		//incrementing the engines
		if(all_engines->next == NULL)
		{
			delete all_engines;
			all_engines = NULL;
		}
		else
		{
			all_engines = all_engines->next;
		}
		//if there are no more engines
		if(all_engines != NULL)
		{
			delete all_engines->prev;
			all_engines->prev = NULL;
		}
		//looping until max cars or all freights are used
		while(all_freight != NULL && num_cars <= max_cars)
		{
			//freight on the test car, if the speed is correct...
			PushBack(test_train, TrainCar::MakeFreightCar(all_freight->getWeight()));
			if(CalculateSpeed(test_train) >= min_speed)
			{
				//...add it to the current train
				PushBack(current_train, TrainCar::MakeFreightCar(all_freight->getWeight()));
				num_cars++;
			}
			else
			{	
				//if it's not the correct speed, exit the loop
				break;
			}
			//incrementing the freight trains
			if(all_freight->next == NULL)
			{
				//deleting the 
				delete all_freight;
				all_freight = NULL;
			}
			else
			{
				all_freight = all_freight->next;
			}
			
			//when there are no more freight cars 
			if(all_freight != NULL)
			{
				delete all_freight->prev;
				all_freight->prev = NULL;
			}
		}
		//going back to the head of the train
		while(current_train->prev != NULL)
		{
			current_train = current_train->prev;
		}
		//push back that train to my vector and start to make another train
		trains.push_back(current_train);

		DeleteAllCars(test_train);
	}
	return trains;
}

//would do seperate like this but didn't get enough time to completely finish the logic...sorry :(
void Separate(TrainCar*& org_train, TrainCar* train1, TrainCar* train2)
{
	// int num_cars = 0;
	// TrainCar* p  = org_train;
	// int threshhold = 0;
	// int t1_new_num = 0; 
	// int t2_new_num = 0; 

	// while(org_train != NULL)
	// {
		
	// 	num_cars++;
	// 	org_train = org_train->next;
	// }
	// if (num_cars % 2 == 0)
	// {
	// 	threshhold = num_cars/2;
	// }
	// else
	// {
	// 	threshhold = (num_cars/2) -1;
	// }
	
	// while(org_train != NULL)
	// {
		
	// 	if (p->isEngine())
	// 	{
	// 		PushBack(train1,p);
	// 		t1_new_num++;
	// 		p = p->next;
	// 		if (p->isEngine())
	// 		{
	// 			PushBack(train2,p);
	// 			t2_new_num++;
	// 			p = p->next;
	// 		}
	// 		else
	// 		{
	// 			while(t1_new_num<threshhold)
	// 			{
	// 				PushBack(train1,p);
	// 				//p = p->next;
	// 				if (p->isEngine())
	// 				{
	// 					PushBack(train2,p);
	// 					t2_new_num++;
	// 					p = p->next;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		while(t1_new_num<threshhold)
	// 		{
	// 			PushBack(train1,p);
	// 			p = p->next;
	// 		}
			
	// 	}
	// 	PushBack(train2,p);
	// 	p = p->next;

	// }
	// org_train = NULL;
	// train1->prev = NULL;
}

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//
