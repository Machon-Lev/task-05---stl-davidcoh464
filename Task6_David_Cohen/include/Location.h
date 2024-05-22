#pragma once

/**
 * @brief Represents a location in a two-dimensional coordinate system.
 */
struct Location
{
   double x; /**< The X-coordinate of the location. */
   double y; /**< The Y-coordinate of the location. */

    /**
     * @brief Checks if this location is not equal to another location.
     *
     * @param other The other location to compare.
     * @return true if the locations are not equal, false otherwise.
     */
    bool operator!=(const Location& other) const;

    /**
     * @brief Checks if this location is equal to another location.
     *
     * @param other The other location to compare.
     * @return true if the locations are equal, false otherwise.
     */
    bool operator==(const Location& other) const;

    /**
     * @brief Compares the X-coordinate of this location with the X-coordinate of another location.
     *
     * @param other The other location to compare.
     * @return true if this location is less than the other location based on X-coordinate, false otherwise.
     */
    bool operator<(const Location& other) const;

    /**
     * @brief Functor for comparing two locations based on their X-coordinate.
     */
    struct CompareX
    {
        /**
         * @brief Compares two locations based on their X-coordinate.
         *
         * @param lhs The left-hand side location.
         * @param rhs The right-hand side location.
         * @return true if lhs is less than rhs based on X-coordinate, false otherwise.
         */
        bool operator()(const Location& lhs, const Location& rhs) const;
    };

    /**
     * @brief Functor for comparing two locations based on their Y-coordinate.
     */
    struct CompareY
    {
        /**
         * @brief Compares two locations based on their Y-coordinate.
         *
         * @param lhs The left-hand side location.
         * @param rhs The right-hand side location.
         * @return true if lhs is less than rhs based on Y-coordinate, false otherwise.
         */
        bool operator()(const Location& lhs, const Location& rhs) const;
    };
};
