#pragma once
#include <iostream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>


class WebApp {
	httplib::Client *cli;
	std::string API;
	std::string request;
	nlohmann::json result;
	std::string cityName;
public:
	void setCityName(std::string& cityName);

	WebApp();

	WebApp(std::string client, std::string API, std::string cityName);

	nlohmann::json getResult(std::string request);

	nlohmann::json getCurrentWeather();

	nlohmann::json getFiveDaysForecast();
};
