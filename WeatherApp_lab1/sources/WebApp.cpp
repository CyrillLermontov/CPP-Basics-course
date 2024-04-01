#include "WebApp.h"


using json = nlohmann::json;


WebApp::WebApp(std::string client, std::string API, std::string cityName) {
	this->cli = new httplib::Client(client);
	this->API = API;
	this->cityName = cityName;
}


void WebApp::setCityName(std::string& cityName) {
	this->cityName = cityName;
}


json WebApp::getResult(std::string request) {
	return json::parse(this->cli->Get(request)->body);
}


json WebApp::getCurrentWeather() {
	this->request = "/data/2.5/weather?";
	this->request += "q=" + this->cityName;
	this->request += "&appid=" + this->API;
	return this->getResult(request);
}


json WebApp::getFiveDaysForecast() {
	this->request = "/data/2.5/forecast?";
	this->request += "q=" + this->cityName;
	this->request += "&appid=" + this->API;
	return this->getResult(request);
}
