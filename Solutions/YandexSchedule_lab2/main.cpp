#include <YaScheduleApp.h>
#include <Tools.h>

using namespace Tools;

std::string OW_API_KEY = "Ваш API Key Open Weather Map";
std::string YA_API_KEY = "Ваш API Key Яндекс Расписания";


int main() {
	system("chcp 1251");
	std::cout << "Введите пункт отправления: ";
	std::string cityFrom; std::cin >> cityFrom;
	std::cout << "Введите пункт назначения: ";
	std::string cityTo; std::cin >> cityTo;
	YaScheduleApp* app = new YaScheduleApp(OW_API_KEY, YA_API_KEY, cityFrom, cityTo);
	int choice;
	std::string transport;
	bool flag = true;

	while (flag) {
		showMenu();
		std::cout << "Введите варинат ответа: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			showSchedule(app->getScheduleBetweenCities(askAvoutDate()));
			break;
		case 2:
			std::cout << "Какой вид транспортного средства вас интересует?: ";
			std::cin >> transport;
			showSchedule(app->getScheduleByTransport(transport, askAvoutDate()));
			break;
		case 3:
			std::cout << "Введите пункт отправления: "; std::cin >> cityFrom;
			std::cout << "Введите пункт назначения: "; std::cin >> cityTo;
			app->changeCities(cityFrom, cityTo);
			break;
		case 4:
			flag = false;
			break;
		}

	}
	return 0;
}