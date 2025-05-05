#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;

class ComputerClub {
private:
	unsigned int tableNum;
	string workTime;
	unsigned int price;
	map<unsigned, unsigned> profit;
	map<unsigned, unsigned> sum;
	deque<string> clients;
	map<string, unsigned> busy;

public:
	class Event {
	protected:
		string time;
		string prevTime;
		unsigned id;
		string body;
	public:
		Event() : time{ "00:00" }, id{ 0 }, body{ "" }, prevTime{"00:00"} {};
		Event(string time_, unsigned id_, string body_) : time{ time_ }, id{ id_ }, body{ body_ } {};
		void newEvent(string str, ComputerClub& club);
		void checkFormat(string str, ComputerClub& club);
		void endOfDay(string str, ComputerClub& club);
		friend ostream& operator<<(ostream& stream, const ComputerClub::Event& err);
		
	};
	
	ComputerClub(string num, string time, string price_);
	string getStartTime() { return workTime.substr(0, 5); };
	string getEndTime() { return workTime.substr(6, 5); };
	void newClient(string time ,string client);
	void takeTable(string time, string client, unsigned number);
	void wait(string time, string client);
	void clientLeft(string time, string client);
	void countProfit(int n);
	void getProfit();
};