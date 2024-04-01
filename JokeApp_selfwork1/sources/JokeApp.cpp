#include "JokeApp.h"


using json = nlohmann::json;


JokeApp::JokeApp(const std::string clientUrl) {
	this->cli = new httplib::Client(clientUrl);
}


json JokeApp::makeRequest(const std::string& request) {
	this->request = request;
	if (auto response = this->cli->Get(this->request)) {
		if (response->status == 200) {
			return json::parse(response->body);
		}
		else {
			std::cout << "Http Request error: " << response->status << std::endl;
			return -1;
		}
	}
	std::cout << "Bad request" << std::endl;
	return -1;
}


json JokeApp::getRandomJoke() {
	this->request = "/random_joke";
	return this->makeRequest(this->request);
}


json JokeApp::getRandomTenJokes() {
	this->request = "/random_ten";
	return this->makeRequest(this->request);
}


json JokeApp::getRandomJokeByType(const std::string type) {
	this->request = "/jokes/"+type+"/ random";
	return this->makeRequest("/random_joke");
}


void JokeApp::showJoke(const json& joke) {
	std::cout << joke["setup"] << std::endl;
	std::cout << joke["punchline"] << std::endl << std::endl;
}


void JokeApp::showRandomJoke() {
	json *result = new json(this->getRandomJoke());
	this->showJoke(result[0]);
	delete result;
}


void JokeApp::showRandomTenJokes() {
	json* result = new json(this->getRandomTenJokes());
	for (int i = 0; i < result->size(); i++) {
		this->showJoke(result[0][i]);
	}
	delete result;
}


void JokeApp::showRandomJokeByType(const int type) {
	json* result = new json(this->getRandomJokeByType(this->types[type-1]));
	this->showJoke(result[0]);
	delete result;
}