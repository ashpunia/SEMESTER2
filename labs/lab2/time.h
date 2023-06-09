class Time{
public: 
	Time();
	Time(int aHour, int aMin, int aSec);

	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	void setHour(int h);
	void setMinute(int m);
	void setSecond(int s);
	void PrintAMPM();

private:
	int hour;
	int min;
	int sec;
};

bool IsEarlierThan(const Time& t1, const Time& t2);
