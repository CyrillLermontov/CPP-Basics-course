#pragma once
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>


class YaScheduleApp {
	httplib::Client* openWeatherClient;
	httplib::Client* yandexScheduleClient;
	std::string cityFrom;
	std::string cityTo;
	std::string openWeatherRequest = "/data/2.5/weather?";
	std::string yaCityCodeRequest = "/v3.0/nearest_settlement/?";
	std::string yaScheduleRequest = "/v3.0/search/?";
	std::string openWeatherApiKey;
	std::string yaScheduleApiKey;
	std::vector <std::vector <std::map <std::string, std::string>>> schedule;
public:
	YaScheduleApp(const std::string& openWeatherApiKey, const std::string& yaScheduleApiKey,
		const std::string& cityFrom, const std::string& cityTo);

	std::vector <std::vector <std::map <std::string, std::string>>> getScheduleBetweenCities(std::string date);

	std::vector <std::vector <std::map <std::string, std::string>>> getScheduleByTransport(const std::string& transport,
		std::string date);

	void changeCities(const std::string& cityFrom, const std::string& cityTo);
private:
	nlohmann::json makeRequest(httplib::Client* client, const std::string& request);

	std::vector <std::string> getLatLon(const std::string& city);

	std::string getCityCode(std::vector <std::string> latLon);

	std::vector <std::vector <std::map <std::string, std::string>>> findScheduleByTransport(const std::string& transport);
};