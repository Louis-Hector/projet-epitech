/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-6
** File description:
** Logger
*/

#include "Logger.hpp"

namespace nts {
    Logger::Logger()
    {
        _pins = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {}};
    }

    Logger::~Logger()
    {
    }

    void Logger::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate clockState = getLink(9);
        Tristate inhibitState = getLink(10);
        if (_prevClock == Tristate::False && clockState == Tristate::True && inhibitState == Tristate::False) {
            char result = 0;
            for (std::size_t i = 1; i <= 8; i++) {
                Tristate statePin = getLink(i);
                if (statePin == Tristate::Undefined)
                    return;
                if (statePin == Tristate::True)
                    result += (pow(2, i - 1));
            }
            std::ofstream file("log.bin", std::ios::binary | std::ios::app);
            if (!file.is_open()) {
                return;
            }
            file.write(reinterpret_cast<const char*>(&result), sizeof(result));
            file.close();
            _prevClock = clockState;
            return;
        }
        _prevClock = clockState;
        return;
    }

    Tristate Logger::compute(std::size_t pin)
    {
        (void) pin;
        if (_pin_compute[pin] == true)
            return _pin_value[pin];
        _pin_compute[pin] = true;
        _pin_value[pin] = Tristate::Undefined;
        return _pin_value[pin];
    }
}
