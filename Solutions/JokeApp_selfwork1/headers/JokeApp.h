#pragma once
#include <httplib.h>
#include <nlohmann/json.hpp>


class JokeApp {
	httplib::Client* cli;
	std::string request;
	std::vector <std::string> types{ "general", "programming", "knock-knock", "dad" };

public:
	JokeApp(const std::string clientUrl);

	nlohmann::json makeRequest(const std::string& request);

	nlohmann::json getRandomJoke();

	nlohmann::json getRandomTenJokes();

	nlohmann::json getRandomJokeByType(const std::string type);

	void showJoke(const nlohmann::json& joke);

	void showRandomJoke();

	void showRandomTenJokes();

	void showRandomJokeByType(const int type);
};
