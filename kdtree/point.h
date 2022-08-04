#ifndef POINT_H__
#define POINT_H__

#include <algorithm>
#include <array>
#include <iostream>
#include <cmath>

// Implementation of a point in n-dimensional space.

template <typename T, size_t dim>
class Point {
    public:
        Point(); // Default constructor.
        Point(const std::array<T, dim>& coords);
        Point(std::initializer_list<T> list);
        bool operator==(const Point<T, dim>& other) const;

        T get(size_t i) const; // Get the i-th coordinate.
        double get_distance(const Point<T,dim>& point) const; // Get the distance to another point.
    private:
        std::array<T, dim> _coords;
};

template <typename T, size_t dim>
Point<T, dim>::Point() {
    for (size_t i = 0; i < dim; i++) {
        _coords[i] = 0;
    }
}

template <typename T, size_t dim>
Point<T, dim>::Point(const std::array<T, dim>& coords) {
    _coords = coords;
}


template <typename T, size_t dim>
Point<T,dim>::Point(std::initializer_list<T> list) 
{
    size_t n = std::min(dim, list.size());
    std::copy_n(list.begin(), n, _coords.begin());
}


template <typename T, size_t dim>
T Point<T, dim>::get(size_t i) const {
    return _coords[i];
}   

template <typename T, size_t dim>
double Point<T, dim>::get_distance(const Point<T,dim>& point) const {
    double distance = 0;
    for (size_t i = 0; i < dim; i++) {
        double d = get(i) - point.get(i);
        distance += d * d;
    }
    return std::sqrt(distance);
}

template <typename T, size_t dim>
bool Point<T, dim>::operator==(const Point<T, dim>& other) const {
    for (size_t i = 0; i < dim; i++) {
        if (get(i) != other.get(i)) {
            return false;
        }
    }
    return true;
}



template <typename T, size_t dim>
std::ostream& operator<<(std::ostream& out, const Point<T, dim>& pt) {
    out << '(';
    for (size_t i = 0; i < dim; ++i) {
        if (i > 0)
            out << ", ";
        out << pt.get(i);
    }
    out << ')';
    return out;
}





#endif /* POINT_H__ */
