
#include <iostream>
#include <string>

#include "kdtree.h"


typedef Point<int, 2>  Point2d;
typedef KDTree<int, 2> Tree2d;

// Test 1:
// Insere um conjunto de pontos na KDTree e
// busca por ponto mais proximo.

int main()
{

    Point2d points[] = { { 2, 3 }, { 5, 4 }, { 9, 6 }, { 4, 7 }, { 8, 1 }, { 7, 2 } };
    Point2d point    = { 9, 2 };
    Point2d result   = { 8, 1 };

    Tree2d tree;
    for(auto it = std::begin(points); it != std::end(points); ++it)
        tree.insert(*it);

   
    Point2d best = tree.nearest(point);
 
    std::cout << "Ponto mais proximo:\n";
    std::cout << "Ponto: " << best << '\n';
    std::cout << "Distancia: " << best.get_distance(point) << '\n';
    
    if(best == result)
        return 0;
        
    return -1;
}
