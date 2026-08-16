/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** BVHNode
*/

#include "BVHNode.hpp"
#include "MathConstants.hpp"
#include <algorithm>
#include <limits>

namespace RayTracer {

static AABB buildNodeBox(const std::vector<const IPrimitive *> &primitives)
{
    AABB node_box;
    AABB primitive_box;
    bool has_box = false;

    for (const IPrimitive *primitive : primitives) {
        if (primitive == nullptr || !primitive->boundingBox(primitive_box))
            continue;
        if (!has_box) {
            node_box = primitive_box;
            has_box = true;
        } else {
            node_box = AABB::surroundingBox(node_box, primitive_box);
        }
    }
    return node_box;
}

static double primitiveCentroidOnAxis(const IPrimitive &primitive, int axis)
{
    AABB primitive_box;
    const Math::Point3D center = (primitive.boundingBox(primitive_box), primitive_box.centroid());

    if (axis == 0)
        return center._x;
    if (axis == 1)
        return center._y;
    return center._z;
}

static double boxAxisMin(const AABB &box, int axis)
{
    if (axis == 0)
        return box.min._x;
    if (axis == 1)
        return box.min._y;
    return box.min._z;
}

static double boxAxisMax(const AABB &box, int axis)
{
    if (axis == 0)
        return box.max._x;
    if (axis == 1)
        return box.max._y;
    return box.max._z;
}

static double boxSurfaceArea(const AABB &box)
{
    const double size_x = box.max._x - box.min._x;
    const double size_y = box.max._y - box.min._y;
    const double size_z = box.max._z - box.min._z;

    return 2.0 * ((size_x * size_y) + (size_x * size_z) + (size_y * size_z));
}

static void addPrimitiveToBin(SAHBin &bin, const IPrimitive &primitive)
{
    AABB primitive_box;

    primitive.boundingBox(primitive_box);
    if (!bin.has_box) {
        bin.box = primitive_box;
        bin.has_box = true;
    } else {
        bin.box = AABB::surroundingBox(bin.box, primitive_box);
    }
    bin.count++;
}

static std::size_t pickBinIndex(double centroid, double axis_min, double axis_max)
{
    const double normalized = (centroid - axis_min) / (axis_max - axis_min);
    const double scaled = normalized * static_cast<double>(BVH_BIN_COUNT);
    const std::size_t raw_index = static_cast<std::size_t>(scaled);

    return std::min(raw_index, BVH_BIN_COUNT - 1);
}

static std::vector<SAHBin> buildBins(const std::vector<const IPrimitive *> &primitives, const AABB &node_box, int axis)
{
    std::vector<SAHBin> bins(BVH_BIN_COUNT);
    const double axis_min = boxAxisMin(node_box, axis);
    const double axis_max = boxAxisMax(node_box, axis);

    for (const IPrimitive *primitive : primitives) {
        const double centroid = primitiveCentroidOnAxis(*primitive, axis);
        const std::size_t bin_index = pickBinIndex(centroid, axis_min, axis_max);

        addPrimitiveToBin(bins[bin_index], *primitive);
    }
    return bins;
}

static void buildPrefixBins(const std::vector<SAHBin> &bins, std::vector<AABB> &left_boxes, std::vector<std::size_t> &left_counts)
{
    AABB current_box;
    bool has_box = false;
    std::size_t current_count = 0;

    for (std::size_t index = 0; index + 1 < BVH_BIN_COUNT; index++) {
        if (bins[index].has_box) {
            current_box = has_box ? AABB::surroundingBox(current_box, bins[index].box) : bins[index].box;
            has_box = true;
        }
        current_count += bins[index].count;
        left_boxes[index] = current_box;
        left_counts[index] = current_count;
    }
}

static void buildSuffixBins(const std::vector<SAHBin> &bins, std::vector<AABB> &right_boxes, std::vector<std::size_t> &right_counts)
{
    AABB current_box;
    bool has_box = false;
    std::size_t current_count = 0;

    for (std::size_t index = BVH_BIN_COUNT - 1; index > 0; index--) {
        if (bins[index].has_box) {
            current_box = has_box ? AABB::surroundingBox(current_box, bins[index].box) : bins[index].box;
            has_box = true;
        }
        current_count += bins[index].count;
        right_boxes[index - 1] = current_box;
        right_counts[index - 1] = current_count;
    }
}

static std::size_t selectBestSplitBin(const std::vector<AABB> &left_boxes, const std::vector<AABB> &right_boxes,
    const std::vector<std::size_t> &left_counts, const std::vector<std::size_t> &right_counts)
{
    double best_cost = std::numeric_limits<double>::infinity();
    std::size_t best_split = (BVH_BIN_COUNT - 1) / 2;

    for (std::size_t index = 0; index + 1 < BVH_BIN_COUNT; index++) {
        if (left_counts[index] == 0 || right_counts[index] == 0)
            continue;
        const double cost = boxSurfaceArea(left_boxes[index]) * static_cast<double>(left_counts[index]) +
            boxSurfaceArea(right_boxes[index]) * static_cast<double>(right_counts[index]);
        if (cost < best_cost) {
            best_cost = cost;
            best_split = index;
        }
    }
    return best_split;
}

static std::size_t evaluateBestSplitBin(const std::vector<SAHBin> &bins)
{
    std::vector<AABB> left_boxes(BVH_BIN_COUNT - 1);
    std::vector<AABB> right_boxes(BVH_BIN_COUNT - 1);
    std::vector<std::size_t> left_counts(BVH_BIN_COUNT - 1, 0);
    std::vector<std::size_t> right_counts(BVH_BIN_COUNT - 1, 0);

    buildPrefixBins(bins, left_boxes, left_counts);
    buildSuffixBins(bins, right_boxes, right_counts);
    return selectBestSplitBin(left_boxes, right_boxes, left_counts, right_counts);
}

static std::size_t chooseSplitBin(const std::vector<const IPrimitive *> &primitives, const AABB &node_box, int axis)
{
    const std::vector<SAHBin> bins = buildBins(primitives, node_box, axis);
    return evaluateBestSplitBin(bins);
}

static std::pair<std::vector<const IPrimitive *>, std::vector<const IPrimitive *>> splitPrimitivesByMedian(
    std::vector<const IPrimitive *> primitives, int axis)
{
    std::sort(primitives.begin(), primitives.end(), [axis](const IPrimitive *left, const IPrimitive *right) {
        return primitiveCentroidOnAxis(*left, axis) < primitiveCentroidOnAxis(*right, axis);
    });
    const std::size_t middle = primitives.size() / 2;
    return {std::vector<const IPrimitive *>(primitives.begin(), primitives.begin() + middle),
        std::vector<const IPrimitive *>(primitives.begin() + middle, primitives.end())};
}

static std::pair<std::vector<const IPrimitive *>, std::vector<const IPrimitive *>> splitPrimitivesByBin(
    const std::vector<const IPrimitive *> &primitives, const AABB &node_box, int axis, std::size_t split_bin)
{
    const double axis_min = boxAxisMin(node_box, axis);
    const double axis_max = boxAxisMax(node_box, axis);
    std::vector<const IPrimitive *> left_primitives;
    std::vector<const IPrimitive *> right_primitives;

    left_primitives.reserve(primitives.size());
    right_primitives.reserve(primitives.size());
    for (const IPrimitive *primitive : primitives) {
        const double centroid = primitiveCentroidOnAxis(*primitive, axis);
        const std::size_t bin_index = pickBinIndex(centroid, axis_min, axis_max);

        if (bin_index <= split_bin)
            left_primitives.push_back(primitive);
        else
            right_primitives.push_back(primitive);
    }
    return {std::move(left_primitives), std::move(right_primitives)};
}

static std::pair<std::vector<const IPrimitive *>, std::vector<const IPrimitive *>> splitPrimitives(
    std::vector<const IPrimitive *> primitives, const AABB &node_box, int axis)
{
    const double axis_min = boxAxisMin(node_box, axis);
    const double axis_max = boxAxisMax(node_box, axis);

    if (axis_max - axis_min <= EPSILON)
        return splitPrimitivesByMedian(std::move(primitives), axis);
    const std::size_t split_bin = chooseSplitBin(primitives, node_box, axis);
    auto [left_primitives, right_primitives] = splitPrimitivesByBin(primitives, node_box, axis, split_bin);
    if (left_primitives.empty() || right_primitives.empty()) {
        return splitPrimitivesByMedian(std::move(primitives), axis);
    }
    return {std::move(left_primitives), std::move(right_primitives)};
}

static std::pair<const BVHNode *, const BVHNode *> orderChildrenByEntryDistance(
    const BVHNode *left, const BVHNode *right, const Ray &ray, double max_distance)
{
    if (left == nullptr)
        return {right, nullptr};
    if (right == nullptr)
        return {left, nullptr};
    const double left_distance = left->getBox().entryDistance(ray, 0.0, max_distance);
    const double right_distance = right->getBox().entryDistance(ray, 0.0, max_distance);
    if (left_distance <= right_distance)
        return {left, right};
    return {right, left};
}

BVHNode::BVHNode(std::vector<const IPrimitive *> primitives) : _box(buildNodeBox(primitives)), _left(), _right(), _primitives()
{
    if (primitives.size() <= LEAF_SIZE || axisExtent(longestAxis()) <= EPSILON) {
        _primitives = std::move(primitives);
        return;
    }
    const auto [left_primitives, right_primitives] = splitPrimitives(std::move(primitives), _box, longestAxis());
    _left = std::make_unique<BVHNode>(left_primitives);
    _right = std::make_unique<BVHNode>(right_primitives);
}

int BVHNode::longestAxis() const
{
    const double size_x = axisExtent(0);
    const double size_y = axisExtent(1);
    const double size_z = axisExtent(2);

    if (size_x >= size_y && size_x >= size_z)
        return 0;
    if (size_y >= size_z)
        return 1;
    return 2;
}

double BVHNode::axisExtent(int axis) const
{
    if (axis == 0)
        return _box.max._x - _box.min._x;
    if (axis == 1)
        return _box.max._y - _box.min._y;
    return _box.max._z - _box.min._z;
}

bool BVHNode::isLeaf() const
{
    return _left == nullptr && _right == nullptr;
}

bool BVHNode::hitLeaf(const Ray &ray, Intersection &intersection, double max_distance) const
{
    bool found_intersection = false;
    double closest_distance = std::min(intersection.distance, max_distance);

    for (const IPrimitive *primitive : _primitives) {
        Intersection current_intersection;

        if (primitive->hit(ray, current_intersection) && current_intersection.distance > EPSILON &&
            current_intersection.distance < closest_distance) {
            intersection = current_intersection;
            closest_distance = current_intersection.distance;
            found_intersection = true;
        }
    }
    return found_intersection;
}

bool BVHNode::hit(const Ray &ray, Intersection &intersection, double max_distance) const
{
    const double closest_distance = std::min(intersection.distance, max_distance);

    if (!_box.hit(ray, 0.0, closest_distance))
        return false;
    if (isLeaf())
        return hitLeaf(ray, intersection, max_distance);
    const auto [first_child, second_child] = orderChildrenByEntryDistance(_left.get(), _right.get(), ray, closest_distance);
    bool found_intersection = false;
    if (first_child != nullptr)
        found_intersection = first_child->hit(ray, intersection, max_distance);
    if (second_child == nullptr)
        return found_intersection;
    if (!second_child->getBox().hit(ray, 0.0, std::min(intersection.distance, max_distance)))
        return found_intersection;
    return second_child->hit(ray, intersection, max_distance) || found_intersection;
}

const AABB &BVHNode::getBox() const
{
    return _box;
}

}
