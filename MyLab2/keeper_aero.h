#ifndef KEEPER_AERO_H
#define KEEPER_AERO_H

#include "aeroflot.h"
#include "exceptions.h"
#include <string>

class KeeperAero {
    AEROFLOT** items;
    int size;
    int capacity;

    void resize(int newCap);

public:
    KeeperAero();
    KeeperAero(const KeeperAero& other);
    KeeperAero& operator=(const KeeperAero& other);
    ~KeeperAero();

    // вставка в алфавитном порядке по названию пункта назначения
    void add(AEROFLOT* a); // владеет объектом
    void insertAt(AEROFLOT* a, int idx);
    void removeAt(int index);
    int getSize() const { return size; }
    AEROFLOT* getAt(int index) const;

    void clear();

    // (опционально) сохранить/загрузить в простой текстовый формат
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // KEEPER_AERO_H
