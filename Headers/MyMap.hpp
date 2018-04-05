#ifndef PRAC1_MYMAP_H
#define PRAC1_MYMAP_H

#include <list>
#include "Container.hpp"

class Point {
private:
    double x;
    double y;
public:

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    bool operator!=(Point const &other) const { return !(*this == other); }

    bool operator==(Point const &other) const { return (x == other.x) && (y == other.y); }

    friend std::ostream &operator<<(std::ostream &stream, const Point &cur) {
        return stream << cur.x << "," << cur.y;
    }
};

class Region {
public:
    /// @brief Construct new Region with name and a point's coordinates
    /// \param str region name
    /// \param a is x position
    /// \param b is y position
    Region(const char *str, const double a, const double b) : regionName(str) {
        coordinatesList.emplace_back(a, b);
    }


    /// @brief Construct new Region with name and a list of coordinates
    /// \param str region name
    /// \param list initializer list
    Region(std::string str, std::initializer_list<Point> list) : regionName(str), coordinatesList(list) {}

    bool operator!=(Region const &other) const {
        return (regionName != other.regionName) || (coordinatesList != other.coordinatesList);
    }

    bool operator==(Region const &other) const { return !(*this != other); }

    ///@brief Describe region
    friend std::ostream &operator<<(std::ostream &stream, const Region &cur) {
        stream << cur.regionName << " ";
        for (auto i: cur.coordinatesList) {
            stream << i << " ";
        }
        return stream;
    }

    std::string get_name() const { return regionName; }

private:

    std::string regionName;
    std::list<Point> coordinatesList;
};


class MyMap : public Container<std::list<Region>::iterator, std::list<Region>::const_iterator> {
public:
    ///@brief Construct empty map
    MyMap() : regionsList() {}

    ///@brief Construct map with list of regions
    MyMap(std::initializer_list<Region> list) : regionsList(list) {}

    ///@brief Construct region and add in map
    void addNewInMap(const char *str, double a = 0, double b = 0) {

        regionsList.emplace_back(str, a, b);
    }

    ///@brief Copy
    void addNewInMap(const Region &ob) {

        regionsList.push_back(ob);
    }

    ///@brief Move constructor (deleting temporary object rvalue)
    void addNewInMap(Region &&ob) {
        regionsList.push_back(ob);
    }

    iterator begin() override { return regionsList.begin(); }

    iterator end() override { return regionsList.end(); }

    const_iterator begin() const override { return regionsList.cbegin(); }

    const_iterator end() const override { return regionsList.cend(); }

private:
    std::list<Region> regionsList;
};

#endif