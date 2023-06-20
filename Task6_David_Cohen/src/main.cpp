#include "CityMap.h"
using std::cout, std::cin, std::endl;

// Function declarations
void getCityName(string& cityName);
void getSpecificLocation(std::vector<Location>& locations, const string& cityName);

int main()
{
    // Create a CityMap object and read data from file
    CityMap cityMap("data.txt");

    string cityName;
    getCityName(cityName);
    double radius;
    int norm;

    while (cityName != "0")
    {
        // Check if the entered city exists in the city map
        if (!cityMap.cityExist(cityName))
        {
            cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again.\n";
            getCityName(cityName);
            continue;
        }

        // Get the locations associated with the city name
        std::vector<Location> locations = cityMap.getCityLocations(cityName);

        // If there are multiple locations, prompt the user to select a specific one
        if (locations.size() > 1)
            getSpecificLocation(locations, cityName);

        cout << "Please enter the wanted radius:\n";
        cin >> radius;
        cout << "Please enter the wanted norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):\n";
        cin >> norm;

        try
        {
            // Search for cities within the specified radius using the selected norm
            cityMap.searchCityRange(locations[0], radius, norm);
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }

        getCityName(cityName);
    }

    return 0;
}

// Prompt the user to enter a city name
void getCityName(string& cityName)
{
    cout << "Please enter selected city name (with line break after it):\n";
    cin >> std::ws; // Ignore white spaces
    std::getline(cin, cityName);
}

// Prompt the user to select a specific location from a list of locations
void getSpecificLocation(std::vector<Location>& locations, const string& cityName)
{
    cout << "There are several cities with the name " << cityName << " in different places.\n";
    int getIndex = -1;

    while(true){
        cout << "Select the specific location from the list below:\n";
        for (int i = 0; i < locations.size(); ++i)
            cout << i << ": {" << locations[i].x << ", " << locations[i].y << "} \t";
        cout << endl;

        cin >> getIndex;
        if (getIndex < locations.size() && getIndex >= 0)
            break;
        cout << "Wrong index Please try again\n";
    }
    // Saving the desired location at the beginning of the vector
    locations[0] = locations[getIndex];
}