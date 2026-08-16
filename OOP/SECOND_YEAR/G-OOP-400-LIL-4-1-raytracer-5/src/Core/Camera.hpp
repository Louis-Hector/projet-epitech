/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {

class Camera
{
    private:
        Math::Point3D _origin;
        Math::Vector3D _rotation;
        double _fov;
        int _width;
        int _height;
    public:
        Camera();
        Camera(const Math::Point3D &origin, const Math::Vector3D &rotation, double fov, int width, int height);
        Camera(const Camera &) = default;
        Camera &operator=(const Camera &) = default;
        ~Camera() = default;

        void moveCamera(Math::Vector3D);
        void rotateCamera(Math::Vector3D);
        Math::Vector3D getForward() const;
        Math::Vector3D getRight() const;
        int getWidth() const;
        int getHeight() const;
        Ray ray(double u, double v) const;
};

}

#endif /* !CAMERA_HPP_ */
