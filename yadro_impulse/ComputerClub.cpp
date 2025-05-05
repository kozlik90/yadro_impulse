#include "ComputerClub.h"





ComputerClub::ComputerClub(string num, string time, string price_) {
	if (stoi(num) < 1)
		throw "NumberOfTablesError";
	tableNum = stoi(num);
	if (stoi(price_) < 1)
		throw "ErrorPrice";
	price = stoi(price_);
	if (time.length() != 11) {
		throw "ErrorTime";
	}
	int h1, m1, h2, m2;
	h1 = stoi(time.substr(0, 2));
	m1 = stoi(time.substr(3, 2));
	h2 = stoi(time.substr(6, 2));
	m2 = stoi(time.substr(9, 2));
	if (h1 < 0 || h1 > 23 || m1 < 0 || m1 > 59 || h2 < 0 || h2 > 23 || m2 < 0 || m2 > 59 || h1 > h2) {
		throw "ErrorTime";
	}
	workTime = time;
	
}

void ComputerClub::newClient(string time, string client) {
	if (!clients.empty()) {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i] == client)
				throw ComputerClub::Event(time, 13, "YouShallNotPass");
		}
	}
	clients.push_back(client);
	
}

void ComputerClub::takeTable(string time, string client, unsigned number) {
	if (!clients.empty()) {
		for (auto it = busy.begin(); it != busy.end(); it++) {
			if ((*it).second == number) {
				throw ComputerClub::Event(time, 13, "PlaceIsBusy");
				
			}
		}
		bool inClub = false;
		for (auto it = clients.begin(); it != clients.end(); it++) {
			if (*it == client) {
				inClub = true;
				break;
			}
		}
		if (!inClub)
			throw ComputerClub::Event(time, 13, "ClientUnknown");
		busy[client] = number;
		unsigned h = stoi(time.substr(0, 2));
		unsigned m = stoi(time.substr(3, 2));
		sum[number] = h*60 + m;
		clients.pop_front();
		
	}
}

void ComputerClub::wait(string time, string client) {
	if (!clients.empty()) {
		if (busy.size() < tableNum) {
			throw ComputerClub::Event(time, 13, "ICanWaitNoLonger!");
		}
		if (clients.size() > tableNum) {
			throw ComputerClub::Event(time, 11, "ClientLeft");
		}
	}
}

void ComputerClub::clientLeft(string time, string client) {
	unsigned h = stoi(time.substr(0, 2));
	unsigned m = stoi(time.substr(3, 2));
	unsigned res{};
	if (time == workTime.substr(6, 5)) {
		
		for (auto elem = busy.begin(); elem != busy.end();) {
			string name = elem->first;
			res = abs((int)sum[elem->second] - (int)(h * 60 + m));
			sum[elem->second] = res;
			countProfit(elem->second);
			elem = busy.erase(elem);
			clients.push_back(name);
		}
		sort(clients.begin(), clients.end());
		for (auto it = clients.begin(); it != clients.end();) {
			string name = *it;
			it = clients.erase(it);
			if (clients.size() == 0)
				throw ComputerClub::Event(time, 11, name);
			cout << ComputerClub::Event(time, 11, name);

		}
		
	}
	bool inClub = false;
	if (!clients.empty()) {
		
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i] == client) {
				inClub = true;
				break;
			}
		}
	}
	bool onPC = false;
	for (auto it = busy.begin(); it != busy.end(); it++) {
		if ((*it).first == client) {
			onPC = true;
			break;
		}
	}
	if (!inClub && !onPC) {
		throw ComputerClub::Event(time, 13, "ClientUnknown");
	}
	if (inClub && !onPC)
		for (auto it = clients.begin(); it != clients.end(); it++) {
			if (*it == client) {
				it = clients.erase(it);
				break;
			}
		}
	if (onPC) {
		int number = busy[client];
		busy.erase(client);
		res = (int)(h * 60 + m) - (int)sum[number];
		sum[number] = res;
		countProfit(number);
		if (!clients.empty()) {
			string newClient = clients.front();
			takeTable(time, newClient, number);
			throw ComputerClub::Event(time, 12, string(newClient + " " + to_string(number)));
		}
	}
	
}
void ComputerClub::countProfit(int n) {
	profit[n] += sum[n];
 }

void ComputerClub::getProfit() {
	for (auto& elem : profit) {
		unsigned h, m;
		h = elem.second / 60;
		m = elem.second % 60;
		string hour = to_string(h), minute = to_string(m);
		if (h < 10) {
			hour = "0" + to_string(h);
		}
		if (m < 10) {
			minute = "0" + to_string(m);
		}
		unsigned sum = price * h;
		if (m != 0)
			sum = price * (h + 1);
		cout << elem.first << "\t" << sum << "\t" << hour << ":" << minute << endl;
	}
}
