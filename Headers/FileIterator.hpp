#ifndef PRAC1_FILEITERATOR_H
#define PRAC1_FILEITERATOR_H

#include <iterator>
#include <fstream>
#include "Container.hpp"

class Number {
private:
    // There should be non-const and non-static variable
    // for work with numbers in const container
    mutable int foundNumber;
public:
    Number(int initialValue = 0) : foundNumber(initialValue) {}

    ///@brief Operator % for numbers in file for predicate
    template<typename T>
    T operator%(T x) const { return foundNumber % x; }

    bool operator!=(Number const &other) const { return (foundNumber != other.foundNumber); }

    bool operator==(Number const &other) const { return (foundNumber == other.foundNumber); }

    ///@brief Found if the character is number
    static bool is_number(char ch) { return (ch >= '0') && (ch <= '9'); }

    // Read file, change foundNumber while read character is number
    friend std::istream &operator>>(std::istream &stream, const Number &ob) {
        ob.foundNumber = 0;
        char ch = ' ';
        do {// Read new character while it is not a number
            // and not eof and not a reading error
            stream.get(ch);
        } while (!is_number(ch) && stream.good());

        // Read new character while it is a number
        // and not eof and not a reading error
        for (; is_number(ch) && stream.good(); stream.get(ch)) {
            ob.foundNumber = ob.foundNumber * 10 + ch - '0';
        }
        return stream;
    }

    auto &operator*() {
        return foundNumber;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Number &ob) {
        return stream << ob.foundNumber;
    }
};

class FileNumberContainer : public Container<std::istream_iterator<Number>, std::istream_iterator<const Number>> {
public:
    ///@brief Constructor saves file name and open it
    /// and throw exception if it wasn't open
    explicit FileNumberContainer(const std::string &str) : name(str), stream(str) {
        if (!stream.is_open()) throw std::runtime_error("file exception: " + std::to_string(errno));
    }

    iterator begin() override { return iterator(stream); }

    iterator end() override { return iterator(); }

    const_iterator begin() const override {
        return std::istream_iterator<const Number>(stream);
    }

    const_iterator end() const override { return std::istream_iterator<const Number>(); }

private:
    std::string name;
    //stream is mutable because we need to realize const overload for const begin|end
    mutable std::fstream stream;
};

#endif