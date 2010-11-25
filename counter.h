#ifndef COUNTER_H
#define COUNTER_H

//template class counting instances of defined classes
//base idea is taken from "Counting Objects in C++, by By Scott Meyers, April 01, 1998"
//old article, but idea seems to work weel

template<typename T>
class Counter {
public:
    Counter() { ++count; }
    Counter(const Counter&) { ++count; }
    ~Counter() { --count; }

    static size_t howMany()
    { return count; }

    //setStartingCount and compareCounters are for checking if 'count' had changed since set time
    static void setStartingCount()
    { startingCount = count; }

    static bool compareCounters()
    { return (count == startingCount); }

private:
    static size_t count;
    static size_t startingCount;
};

template<typename T>
size_t
Counter<T>::count = 0;

template<typename T>
size_t
Counter<T>::startingCount = 0;

#endif // COUNTER_H
