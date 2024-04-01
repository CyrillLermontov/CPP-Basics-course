#include "JokeApp.h"
#include "JokeTools.h"


using namespace JokeTools;


int main() {
	setlocale(LC_ALL, "RUS");
	JokeApp *app = new JokeApp("http://official-joke-api.appspot.com");

	int choice;
	bool flag = true;

	while (flag) {
		showMenu();
		std::cout << "¬ведите вариант ответа: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			app->showRandomJoke();
			break;
		case 2:
			app->showRandomTenJokes();
			break;
		case 3:
			showTypeMenu();
			int typeChoice; std::cin >> choice;
			app->showRandomJokeByType(choice);
			break;
		case 4:
			flag = false;
			break;
		}
	}
	delete app;
	return 0;
}