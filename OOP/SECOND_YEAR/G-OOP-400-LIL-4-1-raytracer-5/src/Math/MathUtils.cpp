/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** MathUtils
*/

#include "MathUtils.hpp"
#include <cmath>
#include <random>

namespace Math {

Vector3D normalize(const Vector3D &vector)
{
    const double length = vector.length();

    if (length == 0.0)
        return Vector3D();
    return vector / length;
}

Vector3D reflect(const Vector3D &incident_direction, const Vector3D &surface_normal)
{
    return incident_direction - surface_normal * (2.0 * incident_direction.dot(surface_normal));
}

Vector3D refract(const Vector3D &incident_direction, const Vector3D &surface_normal, double eta_ratio)
{
    const double cos_theta = std::fmin((incident_direction * -1.0).dot(surface_normal), 1.0);
    const Vector3D refracted_perpendicular = (incident_direction + surface_normal * cos_theta) * eta_ratio;
    const Vector3D refracted_parallel = surface_normal * -std::sqrt(std::fabs(1.0 - refracted_perpendicular.dot(refracted_perpendicular)));

    return refracted_perpendicular + refracted_parallel;
}

double reflectance(double cosine, double refraction_index)
{
    double base_reflectance = (1 - refraction_index) / (1 + refraction_index);

    base_reflectance = base_reflectance * base_reflectance;
    return base_reflectance + (1 - base_reflectance) * std::pow((1 - cosine), 5);
}

double randomDouble()
{
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}

Vector3D randomVector(double min, double max)
{
    return Vector3D(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

Vector3D randomUnitVector()
{
    while (true) {
        const Vector3D point = randomVector(-1.0, 1.0);
        const double length_squared = point.dot(point);

        if (1e-160 < length_squared && length_squared <= 1.0)
            return point / std::sqrt(length_squared);
    }
}

double evalQuartic(double A, double B, double C, double D, double E, double x)
{
    return (((A * x + B) * x + C) * x + D) * x + E;
}

double evalCubic(double A, double B, double C, double D, double x)
{
    return ((A * x + B) * x + C) * x + D;
}

std::vector<double> resolve_exp3(double A, double B, double C, double D)
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

std::vector<double> resolve_exp4(double A, double B, double C, double D, double E)
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

void change_rotate(Math::Point3D &point, double r_x, double r_y, double r_z)
{
    double radiant_x = r_x * M_PI / 180.0;
    double radiant_y = r_y * M_PI / 180.0;
    double radiant_z = r_z * M_PI / 180.0;
    double x = point._x;
    double y = point._y;
    double z = point._z;

    point._y = cos(radiant_x) * y - sin(radiant_x) * z;
    point._z = sin(radiant_x) * y + cos(radiant_x) * z;
    y = point._y;
    z = point._z;
    point._x = cos(radiant_y) * x + sin(radiant_y) * z;
    point._z = -sin(radiant_y) * x + cos(radiant_y) * z;
    x = point._x;
    y = point._y;
    z = point._z;
    point._x = cos(radiant_z) * x - sin(radiant_z) * y;
    point._y = sin(radiant_z) * x + cos(radiant_z) * y;
}

void change_rotate(Math::Vector3D &vector, double r_x, double r_y, double r_z)
{
    double radiant_x = r_x * M_PI / 180.0;
    double radiant_y = r_y * M_PI / 180.0;
    double radiant_z = r_z * M_PI / 180.0;
    double x = vector._x;
    double y = vector._y;
    double z = vector._z;

    vector._y = cos(radiant_x) * y - sin(radiant_x) * z;
    vector._z = sin(radiant_x) * y + cos(radiant_x) * z;
    y = vector._y;
    z = vector._z;
    vector._x = cos(radiant_y) * x + sin(radiant_y) * z;
    vector._z = -sin(radiant_y) * x + cos(radiant_y) * z;
    x = vector._x;
    y = vector._y;
    z = vector._z;
    vector._x = cos(radiant_z) * x - sin(radiant_z) * y;
    vector._y = sin(radiant_z) * x + cos(radiant_z) * y;
}

}
