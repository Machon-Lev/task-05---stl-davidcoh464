#include"CityMap.h"

void CityMap::readData(const string& file_path)
{
	std::ifstream inputFile(file_path);
	if (!inputFile)
		throw std::runtime_error("Failed to open file: " + file_path);

	string line;
	string cityName;
	double x, y;
	while (std::getline(inputFile, cityName))
	{
		if (std::getline(inputFile, line))
		{
			std::istringstream iss(line);
			if (iss >> x >> std::ws && iss.peek() == '-' && iss.ignore() && iss >> y)
			{
				Location location(x, y);
				_xLocCityMap[location] = cityName;
				_yLocCityMap[location] = cityName;
				_cityLocMap.insert({ cityName, location });
			}
			else
				throw std::runtime_error("Invalid data format: " + line);
		}
		else
			throw std::runtime_error("Incomplete data: " + cityName);
	}
	if (_xLocCityMap.empty())
		throw std::length_error("The file is empty: " + file_path);
}

void CityMap::createDistanceMap()
{
	// Implementation of L2 - Euclidean distance
	_distanceMap[0] = [](const Location& l1, const Location& l2) -> double {
		return std::sqrt((l1.x - l2.x) * (l1.x - l2.x) + (l1.y - l2.y) * (l1.y - l2.y));
	};
	// Implementation of Linf - Chebyshev distance
	_distanceMap[1] = [](const Location& l1, const Location& l2) -> double {
		return std::max(std::abs(l1.x - l2.x), std::abs(l1.y - l2.y));
	};
	// Implementation of L1 - Manhattan distance
	_distanceMap[2] = [](const Location& l1, const Location& l2) -> double {
		return std::abs(l1.x - l2.x) + std::abs(l1.y - l2.y);
	};
}

CityMap::CityMap(const string& file_path)
{
	readData(file_path);
	createDistanceMap();
}


void CityMap::printSearchResult(const std::vector<std::pair<Location, string>>& near_cities, const Location& city_location)
{
	// Count the number of city that are north to the source city from the near_cities vector
	__int64 numNorthCities = std::count_if(near_cities.begin(), near_cities.end(),
		[&city_location](const auto& pair) {
			return pair.first.y < city_location.y;
		});

	// Print the resulte
	std::cout << "Search result:\n";
	std::cout << near_cities.size() << " city/cities found in the given radius.\n";
	std::cout << numNorthCities << " cities are to the north of the selected city.\n";

	std::vector<string> cities;
	// Transform near_cities vector from vector <pair<Location, string>> into vector <string>
	std::transform(near_cities.begin(), near_cities.end(), std::back_inserter(cities),
		[](const auto& pair) {
			return pair.second;
		});
	// Print the city list
	std::cout << "City list:\n";
	std::copy(cities.begin(), cities.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << std::endl;
}

bool CityMap::cityExist(const string& city_name)
{
	return _cityLocMap.find(city_name) != _cityLocMap.end();
}

std::vector<Location> CityMap::getCityLocations(const string& city_name)
{
	auto location_range = _cityLocMap.equal_range(city_name);
	std::vector<Location> city_locations;
	std::transform(location_range.first, location_range.second, std::back_inserter(city_locations),
		[](const auto& pair) { return pair.second;});
	return city_locations;
}

void CityMap::searchCityRange(const Location& city_location, double radius, int method)
{
	auto distanceFunc = _distanceMap.find(method);
	// Handle input errors
	if (distanceFunc == _distanceMap.end())
		throw std::logic_error("The provided distance method does not exist: " + method);
	if (radius < 0)
		throw std::logic_error("The radius cannot be negative." + std::to_string(radius));

	// Find the start and end iterators for x rectangle
	auto x_start = _xLocCityMap.lower_bound(Location(city_location.x - radius, -DBL_MAX));
	auto x_end = _xLocCityMap.upper_bound(Location(city_location.x + radius, DBL_MAX));

	// Find the start and end iterators for y rectangle
	auto y_start = _yLocCityMap.lower_bound(Location(-DBL_MAX, city_location.y - radius));
	auto y_end = _yLocCityMap.upper_bound(Location(DBL_MAX, city_location.y + radius));

	// Take the smallest rectangle range between x, y 
	if (std::distance(x_start, x_end) > std::distance(y_start, y_end)) {
		x_start = y_start;
		x_end = y_end;
	}

	// Copying all values that are within the given distance from the source city into nearCities vector
	std::vector<std::pair<Location, string>> nearCities;
	std::copy_if(x_start, x_end, std::back_inserter(nearCities), [&](const auto& pair)
		{return (distanceFunc->second(city_location, pair.first) <= radius) && city_location != pair.first;});

	// Sort the cities by distance from the origin city
	std::sort(nearCities.begin(), nearCities.end(),
		[&distanceFunc, &city_location](const std::pair<Location, string>& l1, const std::pair<Location, string>& l2) {
			return distanceFunc->second(city_location, l1.first) <
				distanceFunc->second(city_location, l2.first);
		});
	printSearchResult(nearCities, city_location);
}
