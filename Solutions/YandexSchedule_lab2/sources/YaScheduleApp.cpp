#include <YaScheduleApp.h>


using json = nlohmann::json;


YaScheduleApp::YaScheduleApp(const std::string& openWeatherApiKey, const std::string& yaScheduleApiKey,
	const std::string& cityFrom, const std::string& cityTo) {
	this->openWeatherClient = new httplib::Client("http://api.openweathermap.org");
	this->yandexScheduleClient = new httplib::Client("http://api.rasp.yandex.net");
	this->cityFrom = cityFrom;
	this->cityTo = cityTo;
	this->openWeatherApiKey = openWeatherApiKey;
	this->yaScheduleApiKey = yaScheduleApiKey;
}


void YaScheduleApp::changeCities(const std::string& cityFrom, const std::string& cityTo) {
	this->schedule.clear();
	this->cityFrom = cityFrom;
	this->cityTo = cityTo;
}


json YaScheduleApp::makeRequest(httplib::Client* client, const std::string& request) {
	if (auto response = client->Get(request)) {
		if (response->status == 200) {
			return json::parse(response->body);
		}
		else {
			std::cout << "Bad request " << response->status << std::endl;
		}
	}
	return *new json;
}


std::vector <std::string> YaScheduleApp::getLatLon(const std::string& city) {
	std::string request = this->openWeatherRequest;
	request += "q=" + city;
	request += "&appid=" + this->openWeatherApiKey;
	json* result = new json(this->makeRequest(this->openWeatherClient, request));
	std::vector <std::string> latLon = { to_string(result[0]["coord"]["lon"]), to_string(result[0]["coord"]["lat"])};
	request.clear();
	delete result;
	return latLon;
}


std::string YaScheduleApp::getCityCode(std::vector <std::string> latLon) {
	std::string request = this->yaCityCodeRequest;
	request += "apikey=" + this->yaScheduleApiKey;
	request += "&lat=" + latLon[1];
	request += "&lng=" + latLon[0];
	std::string code = this->makeRequest(this->yandexScheduleClient, request)["code"].get<std::string>();
	request.clear();
	return code;
}


std::vector <std::vector <std::map <std::string, std::string>>> YaScheduleApp::getScheduleBetweenCities(std::string date) {
	if (this->schedule.size() != 0 && date == "null") {
		return this->schedule;
	}
	else {
		this->schedule.clear();
		std::string request = this->yaScheduleRequest;
		request += "apikey=" + this->yaScheduleApiKey;
		request += "&from=" + this->getCityCode(this->getLatLon(this->cityFrom));
		request += "&to=" + this->getCityCode(this->getLatLon(this->cityTo));
		if (date != "null") {
			request += "&date=" + date;
		}
		json result = this->makeRequest(this->yandexScheduleClient, request);
		std::vector <std::map <std::string, std::string>> race{};
		std::map <std::string, std::string> raceTitle;
		std::map <std::string, std::string> raceNumber;
		std::map <std::string, std::string> departureSattionTitle;
		std::map <std::string, std::string> departureSattionCode;
		std::map <std::string, std::string> arrivalSattionTitle;
		std::map <std::string, std::string> arrivalSattionCode;
		std::map <std::string, std::string> transportType;
		std::map <std::string, std::string> departureDate;
		std::map <std::string, std::string> arrivalDate;
		std::map <std::string, std::string> codeTransportCompany;
		std::map <std::string, std::string> price;
		for (int i = 0; i < result["segments"].size(); i++) {
			race.clear();
			raceTitle["Race Title"] = result["segments"][i]["thread"]["title"].get<std::string>();
			raceNumber["Race Number"] = result["segments"][i]["thread"]["number"].get<std::string>();
			departureSattionTitle["Departure Station Title"] = result["segments"][i]["from"]["title"].get<std::string>();
			departureSattionCode["Departure Station Code"] = result["segments"][i]["from"]["code"].get<std::string>();
			arrivalSattionTitle["Arrival Station Title"] = result["segments"][i]["to"]["title"].get<std::string>();
			arrivalSattionCode["Arrival Station Code"] = result["segments"][i]["to"]["code"].get<std::string>();
			transportType["Transport Type"] = result["segments"][i]["from"]["transport_type"].get<std::string>();
			departureDate["Departure Date"] = result["segments"][i]["departure"].get<std::string>();
			arrivalDate["Arrival Date"] = result["segments"][i]["arrival"].get<std::string>();
			codeTransportCompany["Transport Company Code"] = std::to_string(result["segments"][i]["thread"]["carrier"]["code"].get<int>());
			price["Price"] = to_string(result["segments"][i]["tickets_info"]["places"][0]["prices"]["whole"]) +
				"," + to_string(result["segments"][i]["tickets_info"]["places"][0]["prices"]["cents"]);
			race.push_back(raceTitle);
			race.push_back(raceNumber);
			race.push_back(departureSattionTitle);
			race.push_back(departureSattionCode);
			race.push_back(arrivalSattionTitle);
			race.push_back(arrivalSattionCode);
			race.push_back(transportType);
			race.push_back(departureDate);
			race.push_back(arrivalDate);
			race.push_back(codeTransportCompany);
			race.push_back(price);
			this->schedule.push_back(race);
		}
		raceTitle.clear();
		raceNumber.clear();
		departureSattionTitle.clear();
		departureSattionCode.clear();
		arrivalSattionTitle.clear();
		arrivalSattionCode.clear();
		transportType.clear();
		departureDate.clear();
		arrivalDate.clear();
		codeTransportCompany.clear();
		price.clear();
		race.clear();
		request.clear();
		return this->schedule;
	}
}


std::vector <std::vector <std::map <std::string, std::string>>> YaScheduleApp::findScheduleByTransport(const std::string& transport) {
	std::vector <std::vector <std::map <std::string, std::string>>> scheduleByTransport;
	for (int i = 0; i < this->schedule.size(); i++) {
		if (this->schedule[i][6]["Transport Type"] == transport) {
			scheduleByTransport.push_back(this->schedule[i]);
		}
	}
	return scheduleByTransport;
}


std::vector <std::vector <std::map <std::string, std::string>>> YaScheduleApp::getScheduleByTransport(const std::string& transport,
	std::string date) {
	if (this->schedule.size() != 0 && date == "null") {
		return this->findScheduleByTransport(transport);
	}
	else {
		this->getScheduleBetweenCities(date);
		return this->findScheduleByTransport(transport);
	}
}