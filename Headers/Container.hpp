#ifndef PRAC1_CONTAINER_H
#define PRAC1_CONTAINER_H

template<typename It, typename It_const>
class Container {
public:
    // for using in inheritance
    typedef It iterator;
    typedef It_const const_iterator;

    virtual iterator begin() = 0;

    virtual iterator end() = 0;

    virtual const_iterator begin() const = 0;

    virtual const_iterator end() const = 0;

///
/// \tparam PredicateT Predicator function for filtering
/// \tparam IteratorT Iterator for user's types
    template<typename PredicateT, typename IteratorT>
    struct PredIter {
    public:
        PredicateT &predicator;
        IteratorT iter;
        IteratorT iter_last;

        PredIter(IteratorT it, IteratorT end, PredicateT &predic) : predicator(predic), iter(it), iter_last(end) {
            for (; !predicator(*iter) && iter != iter_last; ++iter);   // skip until first predicate
        }

///
/// \return skip until first predicate
        PredIter &operator++() {
            for (++iter; !predicator(*iter) && iter != iter_last; ++iter);
            return *this;
        }

        auto &operator*() {
            return *iter;
        }

        auto operator->() {
            return &iter;
        }
    };

    template<typename PredicatorT>
    auto filter(PredicatorT Predicate) {
        return PredIter<PredicatorT, iterator>(begin(), end(), Predicate);
    }
};

#endif