#ifndef AEROFLOT_H
#define AEROFLOT_H

#include <string>
#include <iostream>

class AEROFLOT {
    std::string destination; // пункт назначения
    std::string flightNumber; // номер рейса (строка, т.к. могут быть буквы)
    std::string planeType;   // тип самолёта
public:
    AEROFLOT();
    AEROFLOT(const std::string& dest, const std::string& num, const std::string& type);
    AEROFLOT(const AEROFLOT& other);
    ~AEROFLOT();

    // set/get
    void setDestination(const std::string& s); std::string getDestination() const;
    void setFlightNumber(const std::string& s); std::string getFlightNumber() const;
    void setPlaneType(const std::string& s); std::string getPlaneType() const;

    // перегрузка ввода/вывода
    friend std::istream& operator>>(std::istream& in, AEROFLOT& a);
    friend std::ostream& operator<<(std::ostream& out, const AEROFLOT& a);
};

#endif // AEROFLOT_H
