#include "ComputerClub.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	string path = argv[1];
	
	ifstream in(path);
	if (!in.is_open()) {
		cout << "File not open!" << endl;
		return -1;
	}
	try {
		string num{}, time{}, price{};
		getline(in, num);
		getline(in, time);
		getline(in, price);
		ComputerClub club(num, time, price);
		cout << club.getStartTime() << endl;
		string e{};
		ComputerClub::Event event{};
		while (getline(in, e)) {
			try {
				cout << e << endl;
				event.newEvent(e, club);
			}
			catch (char const* msg) {
				if(msg == "FormatError")
					return -1;
				cout << msg << endl;
			}
			catch (ComputerClub::Event& err) {
				cout << err;
			}
		}
		try {
			event.endOfDay(club.getEndTime(), club);
		}
		catch (ComputerClub::Event& err) {
			cout << err;
		}
		cout << club.getEndTime() << endl;
		club.getProfit();
	}
	catch (char const* msg) {
		cout << msg << endl;
	}
	in.close();
	return 0;
}