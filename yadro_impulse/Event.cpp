#include "ComputerClub.h"

void ComputerClub::Event::checkFormat(string str, ComputerClub & club) {

	if ((str.length() < 15 || str.length() > 17) && str != club.getEndTime())
		throw "FormatError";

	string time, body;
	unsigned id;
	time = str.substr(0, 5);
	id = stoi(str.substr(6, 1));
	body = str.substr(8);

	unsigned h = stoi(time.substr(0, 2));
	unsigned m = stoi(time.substr(3, 2));
	if (h < 0 || h > 23 || m < 0 || m > 59) {
		throw "FormatError";
	}

	if (time[2] != ':')
		throw "FormatError";

	int openTime = stoi(club.getStartTime().substr(0, 2)) * 60 + stoi(club.getStartTime().substr(3, 2));
	int closeTime = stoi(club.getEndTime().substr(0, 2)) * 60 + stoi(club.getEndTime().substr(3, 2));
	int t = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
	int tPrev = stoi(prevTime.substr(0, 2)) * 60 + stoi(prevTime.substr(3, 2));
	if (t < tPrev || t > closeTime)
		throw "FormatError";

	string name = body;
	if (id == 2)
		name = body.substr(0, name.length() - 2);
	for (int i = 0; i < name.length(); i++) {
		if ((name[i] < 'a' || name[i] > 'z') && (name[i] < '0' || name[i] > '9') && name[i] != '_' && name[i] != '-')
			throw "FormatError";
	}

	
}

void ComputerClub::Event::newEvent(string str, ComputerClub& club) {
	checkFormat(str, club);
	if (str == club.getEndTime()) {
		time = str;
		id = 11;
		body = "";
	}
	else {
		time = str.substr(0, 5);
		id = stoi(str.substr(6, 1));
		body = str.substr(8);
	}
	
	switch (id) {
	case 1: {
		unsigned currentTime = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
		unsigned clubOpenTime = stoi(club.getStartTime().substr(0, 2)) * 60 + stoi(club.getStartTime().substr(3, 2));
		unsigned clubCloseTime = stoi(club.getEndTime().substr(0, 2)) * 60 + stoi(club.getEndTime().substr(3, 2));
		if (currentTime < clubOpenTime || currentTime > clubCloseTime) {
			throw ComputerClub::Event(time ,13, "NotOpenYet");
		}
		club.newClient(time, body);
		break;
	}
	case 2: {
		string name = body;
		name = body.substr(0, name.length() - 2);
		unsigned num = stoi(body.substr(name.length()));
		club.takeTable(time, name, num);
		break;
	}
	case 3: {
		club.wait(time, body);
		break;
	}
	case 4: {
		club.clientLeft(time, body);
		break;
	}
	case 11: {
		club.clientLeft(time, body);
		break;
		
	}
	}
	
}

void ComputerClub::Event::endOfDay(string str, ComputerClub& club) {
	time = str;
	id = 11;
	body = "";
	club.clientLeft(time, body);
}

ostream& operator<<(ostream& stream, const ComputerClub::Event& err) {
	stream << err.time << " " << err.id << " " << err.body << endl;
	return stream;
}