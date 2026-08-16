/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** MathUtils
*/

#ifndef MATHUTILS_HPP_
#define MATHUTILS_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

namespace Math {

Vector3D normalize(const Vector3D &vector);
Vector3D reflect(const Vector3D &incident_direction, const Vector3D &surface_normal);
Vector3D refract(const Vector3D &incident_direction, const Vector3D &surface_normal, double eta_ratio);
double reflectance(double cosine, double refraction_index);
double randomDouble();
double randomDouble(double min, double max);
Vector3D randomVector(double min, double max);
Vector3D randomUnitVector();
double evalQuartic(double A, double B, double C, double D, double E, double x);
double evalCubic(double A, double B, double C, double D, double x);
std::vector<double> resolve_exp3(double A, double B, double C, double D);
std::vector<double> resolve_exp4(double A, double B, double C, double D, double E);
void change_rotate(Math::Point3D &point, double r_x, double r_y, double r_z);
void change_rotate(Math::Vector3D &vector, double r_x, double r_y, double r_z);
}

#endif /* !MATHUTILS_HPP_ */
