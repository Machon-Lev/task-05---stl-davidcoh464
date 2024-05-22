"# task-05---stl-davidcoh464"
Exercise requirements:
To meet the requirements of the exercise, the program utilizes specific data structures that effectively support the following actions:

1. Efficient search by cities and different radii:
   - A `multimap` is used to store the city names as keys and the corresponding locations as values. Since there can be multiple cities with the same name, a `multimap` allows for efficient searching of cities and retrieval of their locations.

   - Two `map` containers are employed to store the city locations as keys. One map is sorted based on the y-coordinate, while the other is sorted based on the x-coordinate. This design enables quick retrieval of cities within a specified range in both the x and y dimensions with a time complexity of O(log n). By iterating over the container with the smaller number of members and filtering the results based on the distance function, the overall time complexity is reduced to O(min(|x|, |y|)). This approach effectively handles searches with different radii.

2. Dynamism of the data:
   - The program is designed to accommodate the addition or removal of cities while it is running. This flexibility allows future enhancements where the user can modify the city data dynamically.

By employing a `multimap` for city searches, two sorted `map` containers for efficient range-based searches, and enabling dynamic updates, the selected data structures fulfill the exercise requirements effectively. The chosen design ensures fast search capabilities, supports various radii queries, and allows for future expansion of the program's functionality.
