
#include <random>

#include "kdtree.h"
#include "point.h"


// Neste teste trabalhamos um um espaço tridimensional

typedef Point<double, 3>  Point3d;
typedef KDTree<double, 3> Tree3d;

// classe que gera pontos aleatorios.

class random_point_generator {
    
    // Os pontos gerados terão coordenadas dentro do intervalo [min,max]
    random_point_generator(double min, double max)
        : engine_(std::random_device()()), distribution_(min, max) {}
 
    Point3d operator()() {
        double x = distribution_(engine_);
        double y = distribution_(engine_);
        double z = distribution_(engine_);
        return Point3d({x, y, z});
    }
 
    std::mt19937 engine_;
    std::uniform_real_distribution<double> distribution_;
};

void test_random(size_t count) {
    // Cria o gerador
    random_point_generator rpg(0.01, 1);
    
    Tree3d tree;
    std::vector<Point3d> points(count);
    for (size_t i = 0; i < count; ++i) {
        points[i] = rpg();
        tree.insert(points[i]);
    }
    
    Point3d pt(rpg());
    Point3d n = tree.nearest(pt);
 
    std::cout << "Random data (" << count << " points):\n";
    std::cout << "point: " << pt << '\n';
    std::cout << "nearest point: " << n << '\n';
    std::cout << "distance: " << n.get_distance(pt) << '\n';

    // testa  um ponto que sabidamente existe na kdtree
    if(!tree.contains(points[count/2])) exit(-1);

    // testa um ponto que sabidamente não existe na kdtree
    if(tree.contains(Point3d({0,0,0}))) exit(-1);
    
}

int main() {
    test_random(100);
    return 0;
}
