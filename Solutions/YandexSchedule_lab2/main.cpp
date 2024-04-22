#include <YaScheduleApp.h>
#include <Tools.h>

using namespace Tools;

std::string OW_API_KEY = "��� API Key Open Weather Map";
std::string YA_API_KEY = "��� API Key ������ ����������";


int main() {
	system("chcp 1251");
	std::cout << "������� ����� �����������: ";
	std::string cityFrom; std::cin >> cityFrom;
	std::cout << "������� ����� ����������: ";
	std::string cityTo; std::cin >> cityTo;
	YaScheduleApp* app = new YaScheduleApp(OW_API_KEY, YA_API_KEY, cityFrom, cityTo);
	int choice;
	std::string transport;
	bool flag = true;

	while (flag) {
		showMenu();
		std::cout << "������� ������� ������: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			showSchedule(app->getScheduleBetweenCities(askAvoutDate()));
			break;
		case 2:
			std::cout << "����� ��� ������������� �������� ��� ����������?: ";
			std::cin >> transport;
			showSchedule(app->getScheduleByTransport(transport, askAvoutDate()));
			break;
		case 3:
			std::cout << "������� ����� �����������: "; std::cin >> cityFrom;
			std::cout << "������� ����� ����������: "; std::cin >> cityTo;
			app->changeCities(cityFrom, cityTo);
			break;
		case 4:
			flag = false;
			break;
		}

	}
	return 0;
}