
// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

//all the functions that need to be implementes
void PushBack(TrainCar*& head_car, TrainCar* new_car);
void DeleteAllCars(TrainCar*& simple);
void TotalWeightAndCountCars(TrainCar* train,int& total_weight,int& num_engines,
										int& num_freight_cars,int& num_passenger_cars,
										int& num_dining_cars,int& num_sleeping_cars);
float CalculateSpeed(TrainCar* Train);
float AverageDistanceToDiningCar(TrainCar* train);
float ClosestEngineToSleeperCar(TrainCar* train);

std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines, TrainCar*& all_freight, float min_speed, int max_cars);
void Separate(TrainCar*& org_train, TrainCar* train2, TrainCar* train3);