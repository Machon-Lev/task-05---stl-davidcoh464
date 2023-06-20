#pragma once
#include "Location.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using std::string, std::map, std::multimap;

/**
 * CityMap class represents a map of cities with their corresponding locations.
 * It provides methods for reading city data from a file, searching cities within a radius,
 * and retrieving information about cities.
 */
class CityMap
{
    map<Location, string, Location::CompareX> _xLocCityMap;   // Map sorted by X-coordinate
    map<Location, string, Location::CompareY> _yLocCityMap;   // Map sorted by Y-coordinate
    multimap<string, Location> _cityLocMap;                   // Multimap for city-name to location mapping
    map<int, double (*)(const Location&, const Location&)> _distanceMap;   // Map of distance calculation functions

    /**
     * Reads city data from a file and populates the internal data structures.
     * Throws an exception if there are any errors while reading the file.
     *
     * @param file_path The path to the file containing city data.
     */
    void readData(const string& file_path);

    /**
     * Creates the distance map with different distance calculation functions.
     */
    void createDistanceMap();

    /**
     * Prints the names of cities within the given range of locations.
     *
     * @param near_cities A vector of city locations and names.
     * @param city_location The source city location.
     */
    void printSearchResult(const std::vector<std::pair<Location, string>>& near_cities, const Location& city_location);

public:
    /**
     * Constructs a CityMap object by reading city data from a file and initializing internal data structures.
     *
     * @param file_path The path to the file containing city data.
     * @throws std::runtime_error if the file cannot be opened or there are errors while reading the data.
     * @throws std::length_error if the file is empty.
     */
    CityMap(const string& file_path);

    /**
     * Checks if a city with the given name exists in the map.
     *
     * @param city_name The name of the city to check.
     * @return true if the city exists, false otherwise.
     */
    bool cityExist(const string& city_name);

    /**
     * Retrieves the locations of all cities with the given name.
     *
     * @param city_name The name of the city to retrieve locations for.
     * @return A vector of Location objects representing the city locations.
     */
    std::vector<Location> getCityLocations(const string& city_name);

    /**
     * Searches for cities within a given radius from a specified location using a distance calculation method.
     * Prints the search results, including the number of cities found, the number of cities to the north,
     * and the list of cities within the radius.
     *
     * @param city_location The location of the city to search around.
     * @param radius The search radius.
     * @param method The distance calculation method to use.
     * @throws std::logic_error if the distance method is invalid or the radius is negative.
     */
    void searchCityRange(const Location& city_location, double radius, int method);
};
