/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** PpmWriter
*/

#ifndef PPMWRITER_HPP_
#define PPMWRITER_HPP_

#include <ostream>
#include "Image.hpp"

namespace RayTracer {

class PpmWriter
{
    public:
        PpmWriter() = default;
        ~PpmWriter() = default;

        void write(const Image &image, std::ostream &output) const;
};

}

#endif /* !PPMWRITER_HPP_ */
