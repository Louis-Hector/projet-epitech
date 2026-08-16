/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** PpmWriter
*/

#include "PpmWriter.hpp"
#include <algorithm>
#include <cmath>

namespace RayTracer {

static int to_ppm_channel(double linear_component)
{
    const double normalized = std::clamp(linear_component / 255.0, 0.0, 1.0);
    const double gamma_corrected = std::sqrt(normalized);

    return static_cast<int>(255.999 * gamma_corrected);
}

void PpmWriter::write(const Image &image, std::ostream &output) const
{
    output << "P3\n" << image.getWidth() << ' ' << image.getHeight() << "\n255\n";
    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            const Color color = image.getPixel(x, y).clamped();

            output << to_ppm_channel(color._r) << ' ' << to_ppm_channel(color._g) << ' ' << to_ppm_channel(color._b) << '\n';
        }
    }
}

}
