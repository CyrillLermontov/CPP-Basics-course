#include "JokeTools.h"

void JokeTools::showMenu() {
	std::cout << "Меню: " << std::endl;
	std::cout << "1 - Получить случайную шутку" << std::endl;
	std::cout << "2 - Получить 10 случайных шуток" << std::endl;
	std::cout << "3 - Получить случайную шутку по задданной теме" << std::endl;
	std::cout << "4 - Выйти" << std::endl << std::endl;
}


void JokeTools::showTypeMenu() {
	std::cout << "1 - Основные" << std::endl;
	std::cout << "2 - Про программирование" << std::endl;
	std::cout << "3 - Тук-Тук" << std::endl;
	std::cout << "3 - Про папу" << std::endl;
}