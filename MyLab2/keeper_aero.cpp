#include "keeper_aero.h"
#include <iostream>
#include <fstream>

void KeeperAero::resize(int newCap) {
    if (newCap <= capacity) return;
    AEROFLOT** newItems = new AEROFLOT * [newCap];
    for (int i = 0; i < size; ++i) newItems[i] = items[i];
    for (int i = size; i < newCap; ++i) newItems[i] = nullptr;
    delete[] items;
    items = newItems;
    capacity = newCap;
}

KeeperAero::KeeperAero() : items(nullptr), size(0), capacity(0) {
    resize(4);
    std::cout << "KeeperAero: конструктор по умолчанию\n";
}

KeeperAero::KeeperAero(const KeeperAero& other) : items(nullptr), size(0), capacity(0) {
    resize(other.capacity);
    for (int i = 0; i < other.size; ++i) items[i] = new AEROFLOT(*other.items[i]);
    size = other.size;
    std::cout << "KeeperAero: конструктор копирования\n";
}

KeeperAero& KeeperAero::operator=(const KeeperAero& other) {
    if (this == &other) return *this;
    clear();
    resize(other.capacity);
    for (int i = 0; i < other.size; ++i) items[i] = new AEROFLOT(*other.items[i]);
    size = other.size;
    std::cout << "KeeperAero: оператор присваивания\n";
    return *this;
}

KeeperAero::~KeeperAero() {
    clear();
    delete[] items;
    std::cout << "KeeperAero: деструктор\n";
}

void KeeperAero::insertAt(AEROFLOT* a, int idx) {
    if (idx < 0 || idx > size) throw LabException("Индекс вставки вне диапазона");
    if (size >= capacity) resize(capacity * 2);
    for (int i = size; i > idx; --i) items[i] = items[i - 1];
    items[idx] = a;
    ++size;
}

void KeeperAero::add(AEROFLOT* a) {
    if (!a) throw LabException("Попытка добавить нулевой указатель");
    int pos = 0;
    while (pos < size && items[pos]->getDestination().compare(a->getDestination()) < 0) ++pos;
    insertAt(a, pos);
}

void KeeperAero::removeAt(int index) {
    if (index < 0 || index >= size) throw LabException("Индекс удаления вне диапазона");
    delete items[index];
    for (int i = index; i < size - 1; ++i) items[i] = items[i + 1];
    items[--size] = nullptr;
}

AEROFLOT* KeeperAero::getAt(int index) const {
    if (index < 0 || index >= size) throw LabException("Индекс getAt вне диапазона");
    return items[index];
}

void KeeperAero::clear() {
    for (int i = 0; i < size; ++i) { delete items[i]; items[i] = nullptr; }
    size = 0;
}

void KeeperAero::saveToFile(const std::string& filename) const {
    std::ofstream out(filename.c_str());
    if (!out) throw LabException(std::string("Не удалось открыть файл для записи: ") + filename);
    out << size << '\n';
    for (int i = 0; i < size; ++i) {
        out << items[i]->getDestination() << '\n';
        out << items[i]->getFlightNumber() << '\n';
        out << items[i]->getPlaneType() << '\n';
    }
    out.close();
    std::cout << "Сохранено в файл: " << filename << '\n';
}

void KeeperAero::loadFromFile(const std::string& filename) {
    std::ifstream in(filename.c_str());
    if (!in) throw LabException(std::string("Не удалось открыть файл для чтения: ") + filename);
    clear();
    int n = 0;
    in >> n;
    std::string dummy; std::getline(in, dummy);
    resize(n > 4 ? n : 4);
    for (int i = 0; i < n; ++i) {
        std::string dest, num, type;
        std::getline(in, dest);
        std::getline(in, num);
        std::getline(in, type);
        AEROFLOT* a = new AEROFLOT(dest, num, type);
        add(a);
    }
    in.close();
    std::cout << "Загружено из файла: " << filename << '\n';
}
