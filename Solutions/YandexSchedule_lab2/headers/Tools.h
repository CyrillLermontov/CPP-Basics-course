#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace Tools {
	void showMenu();

	void showSchedule(std::vector <std::vector <std::map <std::string, std::string>>> schedule);

	std::string askAvoutDate();
}