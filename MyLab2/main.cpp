#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <iterator>
#include "keeper_aero.h"
#include "exceptions.h"
#include "string_utils.h"
#include <vector>

// вспомогательная функция: разбить текст на предложения (заканчиваются на . ! ?)
static std::vector<std::string> splitIntoSentences(const std::string& text) {
    std::vector<std::string> out;
    std::string cur;
    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        cur.push_back(c);
        if (c == '.' || c == '!' || c == '?') {
            // добавляем возможные пробелы/кавычки и т.д.
            size_t j = i + 1;
            while (j < text.size() && (text[j] == '"' || text[j] == '\'' || text[j] == ')' ||
                text[j] == ' ' || text[j] == '\n' || text[j] == '\r' || text[j] == '\t')) {
                cur.push_back(text[j]);
                ++j;
            }
            out.push_back(cur);
            cur.clear();
            i = j - 1;
        }
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

// читаем из файла первые три предложения (в порядке их появления) и выводим в обратном порядке
static void part2_file_three_sentences_reverse() {
    std::cout << "Введите имя входного файла: ";
    std::string fname; std::getline(std::cin, fname);
    std::ifstream in(fname.c_str());
    if (!in) {
        std::cout << "Не удалось открыть файл " << fname << '\n';
        return;
    }
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    auto sentences = splitIntoSentences(content);
    // выбираем первые 3 предложения (если меньше — сообщаем)
    if (sentences.size() < 3) {
        std::cout << "В файле найдено менее 3 предложений (" << sentences.size() << ").\n";
        // всё равно выведем что есть, в обратном порядке
        for (int i = static_cast<int>(sentences.size()) - 1; i >= 0; --i) {
            std::cout << sentences[i] << '\n';
        }
        return;
    }
    std::cout << "\nТри первых предложения в обратном порядке:\n\n";
    for (int i = 2; i >= 0; --i) { // 2,1,0
        std::cout << sentences[i] << '\n';
    }
}

static void part1_interactive() {
    KeeperAero k;
    int choice = -1;
    while (choice != 0) {
        try {
            std::cout << "\n--- Меню (AEROFLOT) ---\n";
            std::cout << "1. Добавить запись рейса\n";
            std::cout << "2. Показать все записи\n";
            std::cout << "3. Удалить по индексу\n";
            std::cout << "4. Сохранить в файл\n";
            std::cout << "5. Загрузить из файла\n";
            std::cout << "6. Показать пункты назначения и номера рейсов по введённому типу самолёта\n";
            std::cout << "0. Выйти в главное меню\n";
            std::cout << "Выберите пункт: ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неверный ввод\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == 1) {
                AEROFLOT* a = new AEROFLOT();
                std::cin >> *a;
                k.add(a);
                std::cout << "Запись добавлена.\n";
            }
            else if (choice == 2) {
                int n = k.getSize();
                std::cout << "Всего записей: " << n << '\n';
                for (int i = 0; i < n; ++i) {
                    std::cout << i << ": " << *k.getAt(i) << '\n';
                }
            }
            else if (choice == 3) {
                int idx; std::cout << "Индекс для удаления: "; std::cin >> idx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                k.removeAt(idx);
                std::cout << "Удалено.\n";
            }
            else if (choice == 4) {
                std::string fname; std::cout << "Имя файла для сохранения: "; std::getline(std::cin, fname);
                k.saveToFile(fname);
            }
            else if (choice == 5) {
                std::string fname; std::cout << "Имя файла для загрузки: "; std::getline(std::cin, fname);
                k.loadFromFile(fname);
            }
            else if (choice == 6) {
                std::string plane; std::cout << "Введите тип самолёта: "; std::getline(std::cin, plane);
                bool found = false;
                for (int i = 0; i < k.getSize(); ++i) {
                    AEROFLOT* a = k.getAt(i);
                    // сравнение без учёта регистра
                    if (iequals(a->getPlaneType(), plane)) {
                        std::cout << "Пункт назначения: " << a->getDestination() << "; Номер рейса: " << a->getFlightNumber() << '\n';
                        found = true;
                    }
                }
                if (!found) std::cout << "Рейсов с типом самолёта \"" << plane << "\" не найдено.\n";
            }
            else if (choice == 0) {
                break;
            }
            else {
                std::cout << "Неизвестный пункт\n";
            }
        }
        catch (const LabException& ex) {
            std::cout << "Ошибка: " << ex.what() << '\n';
        }
        catch (const std::exception& ex) {
            std::cout << "std::exception: " << ex.what() << '\n';
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int top = -1;
    while (top != 0) {
        std::cout << "\n=== Лабораторная №2 — Задание 5 ===\n";
        std::cout << "1. Часть 1 (AEROFLOT и стандартные потоки)\n";
        std::cout << "2. Часть 2 (файловые/строковые потоки — 3 предложения в обратном порядке)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите пункт: ";
        if (!(std::cin >> top)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (top == 1) part1_interactive();
        else if (top == 2) part2_file_three_sentences_reverse();
        else if (top == 0) break;
        else std::cout << "Неизвестный пункт\n";
    }
    return 0;
}
