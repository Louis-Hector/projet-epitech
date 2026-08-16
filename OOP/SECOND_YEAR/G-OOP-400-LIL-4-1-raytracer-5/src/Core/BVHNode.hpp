/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** BVHNode
*/

#ifndef BVHNODE_HPP_
#define BVHNODE_HPP_

#include "AABB.hpp"
#include "IPrimitive.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include <memory>
#include <vector>

namespace RayTracer {

static constexpr int LEAF_SIZE = 4;
static constexpr std::size_t BVH_BIN_COUNT = 8;

struct SAHBin
{
    AABB box;
    std::size_t count = 0;
    bool has_box = false;
};

class BVHNode
{
    private:
        AABB _box;
        std::unique_ptr<BVHNode> _left;
        std::unique_ptr<BVHNode> _right;
        std::vector<const IPrimitive *> _primitives;

        int longestAxis() const;
        double axisExtent(int axis) const;
        bool isLeaf() const;
        bool hitLeaf(const Ray &ray, Intersection &intersection, double max_distance) const;
    public:
        explicit BVHNode(std::vector<const IPrimitive *> primitives);
        bool hit(const Ray &ray, Intersection &intersection, double max_distance) const;
        const AABB &getBox() const;
};

}

#endif /* !BVHNODE_HPP_ */
