#include "aeroflot.h"
#include <iostream>

AEROFLOT::AEROFLOT() : destination(""), flightNumber(""), planeType("") {
    std::cout << "AEROFLOT: конструктор по умолчанию\n";
}

AEROFLOT::AEROFLOT(const std::string& dest, const std::string& num, const std::string& type)
    : destination(dest), flightNumber(num), planeType(type) {
    std::cout << "AEROFLOT: параметрический конструктор\n";
}

AEROFLOT::AEROFLOT(const AEROFLOT& other)
    : destination(other.destination), flightNumber(other.flightNumber), planeType(other.planeType) {
    std::cout << "AEROFLOT: конструктор копирования\n";
}

AEROFLOT::~AEROFLOT() {
    std::cout << "AEROFLOT: деструктор\n";
}

void AEROFLOT::setDestination(const std::string& s) { destination = s; }
std::string AEROFLOT::getDestination() const { return destination; }
void AEROFLOT::setFlightNumber(const std::string& s) { flightNumber = s; }
std::string AEROFLOT::getFlightNumber() const { return flightNumber; }
void AEROFLOT::setPlaneType(const std::string& s) { planeType = s; }
std::string AEROFLOT::getPlaneType() const { return planeType; }

std::istream& operator>>(std::istream& in, AEROFLOT& a) {
    std::cout << "Введите пункт назначения рейса: ";
    std::getline(in >> std::ws, a.destination);
    std::cout << "Введите номер рейса: ";
    std::getline(in, a.flightNumber);
    std::cout << "Введите тип самолёта: ";
    std::getline(in, a.planeType);
    return in;
}

std::ostream& operator<<(std::ostream& out, const AEROFLOT& a) {
    out << "Пункт назначения: " << a.destination
        << "; Номер рейса: " << a.flightNumber
        << "; Тип самолёта: " << a.planeType;
    return out;
}
