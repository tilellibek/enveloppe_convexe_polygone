#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>

// Définition de la classe Point
class Point {
private:
    double x, y;

public:
    Point(double _x, double _y) : x(_x), y(_y) {}
    double getX() const { return x; }
    double getY() const { return y; }
};

// Définition de la classe Vecteur
class Vecteur {
private:
    Point p0, p1;

public:
    Vecteur(const Point& _p0, const Point& _p1) : p0(_p0), p1(_p1) {}
    double calculPente() const {
        if (p1.getX() - p0.getX() == 0) return std::numeric_limits<double>::infinity();
        return (p1.getY() - p0.getY()) / (p1.getX() - p0.getX());
    }
};

// Définition de la classe NuagePoints
class NuagePoints {
private:
    std::vector<Point> points;

public:
    NuagePoints() {}
    NuagePoints(const std::vector<Point>& _points) : points(_points) {}

    // Méthode pour générer un nuage de points aléatoires
    void genereNuagePointAlea(int nbPoints, int borneX, int borneY) {
        for (int i = 0; i < nbPoints; ++i) {
            double x = rand() % (borneX + 1);
            double y = rand() % (borneY + 1);
            points.push_back(Point(x, y));
        }
    }

    // Autres méthodes pour gérer les points
    // ...

    // Méthode pour afficher les coordonnées des points du nuage
    void afficherCoordonnees() const {
        for (const Point& p : points) {
            std::cout << "(" << p.getX() << ", " << p.getY() << ")\n";
        }
    }
};

// Définition de la classe Polygone
class Polygone {
private:
    NuagePoints contour;

public:
    Polygone(const NuagePoints& _contour) : contour(_contour) {}

    // Méthode pour trier les points en ordre polaire
    void triPolaire() {
        // Implémentation de l'algorithme de tri polaire
        // ...
    }

    // Méthode pour afficher graphiquement les points
    void printGraphique() const {
        const std::vector<Point>& points = contour.getPoints();
        std::ofstream output("Points.ps");
        output << "%!PS-Adobe-3.0" << std::endl;
        output << std::endl;

        // Écrire le code pour tracer les points dans le fichier postscript
        // ...

        output.close();
    }
};

// Fonction pour calculer l'orientation de trois points
int orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
                 (q.getX() - p.getX()) * (r.getY() - q.getY());

    if (val == 0) return 0;  // Colinéaire
    return (val > 0) ? 1 : 2; // 1 pour sens horaire, 2 pour sens anti-horaire
}

// Fonction de comparaison pour trier les points selon leur angle polaire
bool compare(const Point& p1, const Point& p2) {
    // Trouver l'orientation pour le tri
    int o = orientation(Point(0, 0), p1, p2);
    if (o == 0) {
        // Si les points sont colinéaires, le plus proche de (0, 0) vient en premier
        return (p1.getX() * p1.getX() + p1.getY() * p1.getY()) <
               (p2.getX() * p2.getX() + p2.getY() * p2.getY());
    }
    return (o == 2); // Tri en sens anti-horaire
}

// Algorithme de Graham pour trouver l'enveloppe convexe
std::vector<Point> convexHull(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) return std::vector<Point>(); // Au moins 3 points sont nécessaires pour former une enveloppe convexe

    // Trouver le point le plus bas (le plus à gauche en cas d'égalité)
    int ymin = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].getY() < points[ymin].getY() || (points[i].getY() == points[ymin].getY() && points[i].getX() < points[ymin].getX())) {
            ymin = i;
        }
    }

    // Échanger le point le plus bas avec le premier point
    std::swap(points[0], points[ymin]);

    // Trier les autres points selon l'angle polaire par rapport au premier point
    std::sort(points.begin() + 1, points.end(), compare);

    // Créer une pile pour stocker les points de l'enveloppe convexe
    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);

    // Parcourir les autres points pour construire l'enveloppe convexe
    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && orientation(hull.top(), hull.top(), points[i]) != 2) {
            hull.pop(); // Retirer les points qui ne contribuent pas à l'enveloppe convexe
        }
        hull.push(points[i]);
    }

    // Convertir la pile en vecteur de points
    std::vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    std::reverse(result.begin(), result.end()); // Inverser l'ordre pour avoir les points dans le bon sens
    return result;
}

int main() {
    // Créer un nuage de points
    NuagePoints nuagePoints;
    nuagePoints.genereNuagePointAlea(10, 100, 100);

    // Obtenir les points de l'enveloppe convexe
    std::vector<Point> points = nuagePoints.getPoints();
    std::vector<Point> enveloppeConvexe = convexHull(points);

    // Afficher les coordonnées des points de l'enveloppe convexe
    std::cout << "Points on the Convex Hull:\n";
    for (const Point& p : enveloppeConvexe) {
        std::cout << "(" << p.getX() <<
