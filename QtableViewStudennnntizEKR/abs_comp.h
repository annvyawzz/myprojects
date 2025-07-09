#ifndef ABS_COMP_H
#define ABS_COMP_H

#include <iostream>
#include <fstream>
#include <memory>
#include <functional>

using namespace std;

template <typename T>
class ABS_COMP
{
public:
    virtual ~ABS_COMP() = default;

    virtual void GetData(istream& in) = 0;
    virtual void PutData(ostream& out) const = 0;
    virtual unique_ptr<ABS_COMP<T>> Merge(const ABS_COMP<T>* arr1, const ABS_COMP<T>* arr2) const = 0;
    virtual void Sort(function<bool(const T&, const T&)> compare = nullptr) = 0;
    virtual unique_ptr<ABS_COMP<T>> Intersection(const ABS_COMP<T>* arr1, const ABS_COMP<T>* arr2) const = 0;

    virtual size_t Size() const = 0;
    virtual void Clear() = 0;
};

#endif // ABS_COMP_H
