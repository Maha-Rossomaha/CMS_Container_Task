#ifndef PRAC1_FIBITERATOR_H
#define PRAC1_FIBITERATOR_H

#include <climits>
#include <cstddef>
#include "Container.hpp"

// Counting new Fibonacci number.
// Long used to see when new number is bigger than INT_MAX
long
newFibonacci(long prevNum, long lastNum) {
    return (prevNum + lastNum);
}

template<typename T = int>
class FibIterator {
public:
    typedef std::input_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;

    explicit FibIterator(bool newFlag, const int i = 1, const int k = 0) : prevNumber(k), curNumber(i),
                                                                           endFlag(newFlag) {}

    bool operator!=(FibIterator const &other) const {
        return ((curNumber != other.curNumber) && (endFlag != other.endFlag));
    }

    bool operator==(FibIterator const &other) const {
        return ((curNumber == other.curNumber) && (endFlag == other.endFlag));
    }

    ///@brief Incrementation counts new Fibonacci number
    /// and checks if it is bigger than we need
    FibIterator &operator++() {
        long check;
        long savePrev = curNumber;
        if ((check = newFibonacci(prevNumber, curNumber)) >= SHRT_MAX) {
            endFlag = true;
            return *this;
        } else curNumber = check;
        prevNumber = savePrev;
        return *this;
    }

    auto &operator*() {
        return curNumber;
    }

private:
    long prevNumber;
    long curNumber;
    bool endFlag;
};

class FibNums : public Container<FibIterator<int>, FibIterator<const int>> {
public:
    iterator begin() override { return FibIterator<int>(false); }

    iterator end() override { return FibIterator<int>(true, SHRT_MAX); }

    const_iterator begin() const override { return FibIterator<const int>(false); }

    const_iterator end() const override { return FibIterator<const int>(true, SHRT_MAX); }
};

#endif