#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>

using uint = unsigned int;
void ExtractMorningTemp(const std::string& src, std::vector<float>& dst, const std::pair<uint, uint>& range);
std::string FloatToFormatStr(float num, uint d_after_dot);

int main() {
	sf::Http http("http://api.openweathermap.org");
	sf::Http::Request request;
	request.setMethod(sf::Http::Request::Get);
	const std::string request_str = "data/2.5/onecall?lat=55.031680&lon=82.928000&units=metric&"
		"exclude=current,minutely,hourly,alerts&appid=762ee04723199b0dcfe3788fbeecb33b";
	request.setUri(request_str);

	sf::Http::Response response = http.sendRequest(request);
	if (response.getStatus() == 200) {
		uint days = 5;
		std::string response_str = response.getBody();
		std::vector<float> temperature;
		ExtractMorningTemp(response_str, temperature, { 0, days });
		std::cout << "Morning forecast temperature in Novosibirsk(55" 
			<< static_cast<char>(248) << ' ' << "N, "
			<< "83" << static_cast<char>(248) << ' ' << "E):\n\n"
			<< "Average temperature: " 
			<< FloatToFormatStr(std::accumulate(temperature.begin(), temperature.end(), 0.0f) / days, 2) 
			<< ' ' << static_cast<char>(248) << "C\n"
			<< "Maximum temperature: " 
			<< FloatToFormatStr(*std::max_element(temperature.begin(), temperature.end()), 2) 
			<< ' ' << static_cast<char>(248) << "C\n";
	}
	else {
		std::cout << "Error occured: \n";
		std::cout << "status: " << response.getStatus() << "\n";
		std::cout << "body: " << response.getBody() << std::endl;
	}
	std::cin.get();
	return 0;
}

void ExtractMorningTemp(const std::string& src, std::vector<float>& dst, const std::pair<uint, uint>& range) {
	uint from = range.first;
	uint to = range.second;
	size_t pos = 0;
	for (uint cur = 0; cur < to - from; ++cur) {
		pos = src.find("morn", pos);
		std::string temp_str = src.substr(pos + 6, 6);
		dst.push_back(std::stof(temp_str));
		pos += 6;
	}
}

std::string FloatToFormatStr(float num, uint d_after_dot) {
	std::string str = std::to_string(num);
	return str.substr(0, str.find('.') + d_after_dot + 1);
}
