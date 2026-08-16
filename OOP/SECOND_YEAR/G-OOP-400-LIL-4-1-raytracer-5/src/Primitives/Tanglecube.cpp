/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-5
** File description:
** Tanglecube
*/

#include "Tanglecube.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

namespace RayTracer {

Tanglecube::Tanglecube(/* args */) : _scale(1.0)
{
}

Tanglecube::Tanglecube(Math::Point3D origin, double scale, const IMaterial *material) :
    _origin(origin), _scale(scale), _material(material)
{
}

static double evalQuartic(double A, double B, double C, double D, double E, double x)
{
    return (((A * x + B) * x + C) * x + D) * x + E;
}

static std::vector<double> resolve_exp3(double A, double B, double C, double D)
{
    std::vector<double> roots = {};

    if (std::fabs(A) < 1e-8)
        return roots;
    double normal_b = B / A;
    double normal_c = C / A;
    double normal_d = D / A;
    double card_p = normal_c - (normal_b * normal_b) / 3;
    double card_q = (2 * normal_b * normal_b * normal_b) / 27 - (normal_b * normal_c) / 3 + normal_d;
    double discriminant = (card_q * card_q) / 4.0 + (card_p * card_p * card_p) / 27.0;
    if (discriminant > 0) {
        double s1 = std::cbrt(-card_q / 2 + std::sqrt(discriminant));
        double s2 = std::cbrt(-card_q / 2 - std::sqrt(discriminant));
        roots.push_back(s1 + s2 - normal_b / 3.0);
    } else {
        double amplitude = 2.0 * std::sqrt(-card_p / 3.0);
        double s3 = -card_q / (2.0 * std::sqrt(-(card_p / 3.0) * (card_p / 3.0) * (card_p / 3.0)));
        roots.push_back((amplitude * std::cos(std::acos(s3) / 3.0)) - normal_b / 3.0);
        roots.push_back((amplitude * std::cos((std::acos(s3) + 2.0 * M_PI) / 3.0)) - normal_b / 3.0);
        roots.push_back((amplitude * std::cos((std::acos(s3) + 4.0 * M_PI) / 3.0)) - normal_b / 3.0);
    }
    return roots;
}

static std::vector<double> resolve_exp4(double A, double B, double C, double D, double E)
{
    std::vector<double> roots = {};
    std::vector<double> intervals = resolve_exp3(4 * A, 3 * B, 2 * C, D);

    intervals.push_back(1e-3);
    intervals.push_back(1e3);
    std::sort(intervals.begin(), intervals.end());
    for (std::size_t i = 0; i + 1 < intervals.size(); i++) {
        double vl = evalQuartic(A, B, C, D, E, intervals[i]);
        double vr = evalQuartic(A, B,C, D, E, intervals[i + 1]);
        if (vl * vr > 0)
            continue;
        double inter_r = intervals[i + 1];
        double inter_l = intervals[i];
        for (int j = 0; j < 50; j++) {
            double vm = evalQuartic(A, B, C, D, E, (0.5 * (inter_l + inter_r)));
            if (vl * vm <= 0) {
                inter_r = (0.5 * (inter_l + inter_r));
                vr = vm;
            } else {
                inter_l = (0.5 * (inter_l + inter_r));
                vl = vm;
            }
        }
        double root = 0.5 * (inter_l + inter_r);
        bool doublon = false;
        for (const auto value : roots)
            if (std::fabs(value - root) < 1e-6)
                doublon = true;
        if (doublon == false)
            roots.push_back(root);
    }
    return roots;
}

static std::vector<double> getRoots(Math::Vector3D new_point, const Ray &ray)
{
    double Ox = new_point._x;
    double Oy = new_point._y;
    double Oz = new_point._z;
    double Dx = ray._direction._x;
    double Dy = ray._direction._y;
    double Dz = ray._direction._z;
    double Ox2 = Ox * Ox;
    double Oy2 = Oy * Oy;
    double Oz2 = Oz * Oz;
    double Dx2 = Dx * Dx;
    double Dy2 = Dy * Dy;
    double Dz2 = Dz * Dz;
    double A = Dx2 * Dx2 + Dy2 * Dy2 + Dz2 * Dz2;
    double B = 4 * (Ox * Dx2 * Dx + Oy * Dy2 * Dy + Oz * Dz2 * Dz);
    double C = 6 * (Ox2 * Dx2 + Oy2 * Dy2 + Oz2 * Dz2) - 5 * (Dx2 + Dy2 + Dz2);
    double D = 4 * (Ox2 * Ox * Dx + Oy2 * Oy * Dy + Oz2 * Oz * Dz) - 10 * (Ox * Dx + Oy * Dy + Oz * Dz);
    double E = (Ox2 * Ox2 + Oy2 * Oy2 + Oz2 * Oz2) - 5 * (Ox2 + Oy2 + Oz2) + 11.8;
    return resolve_exp4(A, B, C, D, E);
}

bool Tanglecube::hit(const Ray &ray, Intersection &intersection) const
{
    Math::Vector3D new_point = (ray._origin - _origin) / _scale;
    Ray scaled_ray(Math::Point3D(), ray._direction / _scale);
    std::vector<double> roots = getRoots(new_point, scaled_ray);
    double min_root = 1e60;
    for (double root : roots)
        if (root > 1e-6 && root < min_root)
            min_root = root;
    if (min_root == 1e60)
        return false;
    Math::Vector3D p_l= new_point + scaled_ray._direction * min_root;
    Math::Point3D p_hit(p_l._x * _scale + _origin._x, p_l._y * _scale + _origin._y, p_l._z * _scale + _origin._z);
    Math::Vector3D normal(4 * p_l._x * p_l._x * p_l._x - 10 * p_l._x, 4 * p_l._y * p_l._y * p_l._y - 10 * p_l._y,
        4 * p_l._z * p_l._z * p_l._z - 10 * p_l._z);
    double len = normal.length();
    if (len > EPSILON) {
        normal._x /= len;
        normal._y /= len;
        normal._z /= len;
    }
    intersection.distance = min_root;
    intersection.material = _material;
    intersection.position = p_hit;
    intersection.surface_normal = normal;
    return true;
}

bool Tanglecube::boundingBox(AABB &box) const
{
    const double extent = _scale * 2.0;

    box = AABB(Math::Point3D(_origin._x - extent, _origin._y - extent, _origin._z - extent),
        Math::Point3D(_origin._x + extent, _origin._y + extent, _origin._z + extent));
    return true;
}

}
