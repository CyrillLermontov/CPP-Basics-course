#include "Tools.h"


void Tools::showMenu() {
	std::cout << "1 - Посмотреть погоду." << std::endl;
	std::cout << "2 - Посмотреть прогноз на 5 дней." << std::endl;
	std::cout << "3 - Ввести новый город." << std::endl;
	std::cout << "4 - Выход" << std::endl;
}


void Tools::showCurrentWeather(nlohmann::json data) {
	std::cout << "Погода: " << data["weather"][0]["main"] << std::endl;
	std::cout << "Температура: " << (int)(data["main"]["temp"].get<double>() - 273.15) << std::endl;
}


void Tools::showFiveDaysForecast(nlohmann::json data) {
	int i = 0;
	int j = i + 1;

	std::string dateDay;
	std::string dateDayJ;
	int counter = 0;
	double sum = 0;

	while (i < data["list"].size()) {
		dateDay = data["list"][i]["dt_txt"].get<std::string>().substr(8, 2);
		counter = 1;
		sum = data["list"][i]["main"]["temp"].get<double>() - 273.15;
		dateDayJ = data["list"][j]["dt_txt"].get<std::string>().substr(8, 2);
		while (dateDay == dateDayJ && j < data["list"].size()) {
			counter++;
			sum += data["list"][j]["main"]["temp"].get<double>() - 273.15;
			dateDayJ = data["list"][j]["dt_txt"].get<std::string>().substr(8, 2);
			j++;
		}
		std::cout << data["list"][i]["dt_txt"].get<std::string>().substr(0, 10);
		std::cout << " Average Temp: " << (int)(sum / counter) << std::endl;
		i = j;
		j = i + 1;
	}

	/*for (int i = 0; i < data["list"].size(); i++) {
		std::cout << data["list"][i]["dt_txt"];
		std::cout << " " << data["list"][i]["weather"][0]["main"];
		std::cout << " Temp: " << (int)(data["list"][i]["main"]["temp"].get<double>() - 273.15) << std::endl;
	}*/
}
