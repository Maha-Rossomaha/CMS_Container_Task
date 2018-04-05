#include <iostream>
#include <algorithm>
#include "MyMap.hpp"
#include "FibIterator.hpp"
#include "FileIterator.hpp"

template<typename ContainerT>
void
printCont(const ContainerT &ob) {
    for (const auto &c: ob) {
        std::cout << "\t" << c << std::endl;
    }
}

int
main() {
    std::cout << "\nEmpty map:\n";
    MyMap map0;
    printCont(map0);

    std::cout << "\nFor map:\n";
    MyMap map1;
    map1.addNewInMap("London", 0, 0);
    map1.addNewInMap(Region("Tokyo", {{1, 2},
                                      {2, 3}}));

    Region qliver{"Liverpool", {{1, 2}, {2, 3}, {1, 2}, {2, 3}, {1, 2}, {2, 3}}};
    map1.addNewInMap(qliver);
    printCont(map1);

    std::cout << "\nFor not-empty map\n";
    MyMap map2 = {{"Kirov",  1.5, 0},
                  {"Moscow", 1.0, 1.0},
                  {"Tokyo",  {{1, 2}, {2, 3}}}};

    map2.addNewInMap("London", 0, 0);
    Region liver{"Liverpool", {{1, 2}, {2, 3}, {1, 2}, {2, 3}, {1, 2}, {2, 3}}};
    map2.addNewInMap(liver);
    printCont(map2);

    std::cout << "\nFibonacci numbers\n";
    FibNums fibSeq;
    printCont(fibSeq);

    try {
        std::cout << "\nCreating fake error\n";
        std::string name("1.txt");
        FileNumberContainer file(name);

        printCont(file);
    } catch (std::runtime_error &e) {
        std::cout << "\t(FAKE)Caught exception: " << e.what() << std::endl;
    }

    try {
        std::cout << "\nCreating file Container\n";
        std::string name("Tests/2.txt");
        FileNumberContainer file(name);

        printCont(file);
    } catch (std::runtime_error &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // ALGORITHM
    std::cout << "\nALGORITHM functions\n\n";

    MyMap map3 = {{"Kirov",  1.5, 0},
                  {"Moscow", 1.0, 1.0}};

    Region Moscow{"Moscow", 1.0, 1.0};

    if (std::find(map3.begin(), map3.end(), Moscow) != map3.end()) {
        std::cout << "\tThere is Moscow in map3\n\n";
    } else { std::cout << "\tThere is no such Moscow in map3\n\n"; }

    if (std::find(fibSeq.begin(), fibSeq.end(), 964) != fibSeq.end()) {
        std::cout << "\t964 is Fibonacci number\n\n";
    } else {
        std::cout << "\t964 isn't Fibonacci number\n\n";
    }

    try {
        std::string name("Tests/3.txt");
        FileNumberContainer file(name);

        if (std::find(file.begin(), file.end(), 5) != file.end()) {
            std::cout << "\t5 is in the 3.txt file\n";
        } else {
            std::cout << "\t5 isn't in the 3.txt file\n";
        }
    } catch (std::runtime_error &e) {
        std::cout << "Caught exception: " << e.what() << "\nLet continue without AVOST\n";
    }

    // Predicate
    std::cout << "\nPREDICATE functions\n\n";

    MyMap map4 = {{"Kirov",     1.5, 0},
                  {"Moscow",    1.0, 1.0},
                  {"Volgograd", 1.7, 1.92}};

    std::cout << "\t" << *map4.filter([](auto &it) {
        return it.get_name() == "Moscow";
    }) << "== Moscow in map4\n";

    std::cout << "\n\tThese numbers in Fibonacci numbers are even\n";
    auto it = fibSeq.filter([](auto &i) { return i % 2 == 0; });

    for (; it.iter != fibSeq.end(); ++it) {
        std::cout << "\t\t" << it.operator*() << std::endl;
    }

    try {
        std::cout << "\n\tThese numbers in file 4.txt are divided by 5\n";
        std::string name("Tests/4.txt");
        FileNumberContainer file(name);

        auto iterator = file.filter([](auto &i) { return i % 5 == 0; });
        for (; iterator.iter != file.end(); ++iterator) {
            std::cout << "\t\t" << iterator.operator*() << std::endl;
        }
    } catch (std::runtime_error &e) {
        std::cout << "Caught exception: " << e.what() << "\nLet continue without AVOST\n";
    }
    return 0;
}