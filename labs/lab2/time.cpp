#include <iostream>
#include "time.h"


Time :: Time(){ //default
	hour = 0;
	min = 0;
	sec = 0;
}

Time :: Time(int aHour, int aMin, int aSec){
	hour = aHour;
	min = aMin;
	sec = aSec;
}

int Time::getHour() const {
  return hour;
}

int Time::getMinute() const {
  return min;
}
	
int Time::getSecond() const {
  return sec;
}

void Time :: setHour(int h){
	hour = h;
}

void Time :: setMinute(int m){
	min = m;
}

void Time :: setSecond(int s){
	sec = s;
}
 
void Time::PrintAMPM(){
	int th = hour;
	bool pm = false;
	if ((hour == 0) && (min == 0)&& (sec == 0)){
		th = 12;
		pm = false;
	}
	if (hour > 12){
		th = hour - 12;
			pm = true;
		}
	
	 if (hour == 12){
	// 		hour = 12;
			pm = true;
	 	}
	
		if (th < 10 ){
			std::cout<<"0"<<th<<":";
		} else{
			std::cout<<th<<":";
		}
		if (min<10){
			std::cout<<"0"<<min<<":";
		}else{
			std::cout<<min<<":";
		}
		if (sec<10){
			std::cout<<"0"<<sec<<":";
		}else{
			std::cout<<sec<<":";
		}
		if (pm){
			std::cout<<"pm"<<std::endl;
		}else{
			std::cout<<"am"<<std::endl;
		}

		//std::cout<<hour<<":"<<min<<":"<<sec<<" am"<<std::endl;
}


bool IsEarlierThan(const Time& t1, const Time& t2)
{
		if (t1.getHour() < t2.getHour()){
			return true;
		}
		else if ((t1.getHour() == t2.getHour()) && (t1.getMinute() < t2.getMinute())){
			return true; 
		} 
		else if((t1.getHour() == t2.getHour()) && (t1.getMinute() == t2.getMinute())&&(t1.getSecond() < t2.getSecond())){
		return true;
		}
	else{
		return false;
	}
}
