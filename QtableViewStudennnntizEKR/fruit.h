#ifndef FRUIT_H
#define FRUIT_H

#include "abs_comp.h"
#include <cstring>
using namespace std;

struct S1
{
    char Section[10];
    char Name[20];

    bool operator==(const S1& other) const
    {
        return strcmp(Section, other.Section) == 0 && strcmp(Name, other.Name) == 0;
    }
};

istream& operator>>(istream& in, S1& item);
ostream& operator<<(ostream& out, const S1& item);

class Fruit : public ABS_COMP<S1>
{
private:
    S1* data;
    size_t count;

public:
    Fruit();
    Fruit(const Fruit& other);
    ~Fruit();

    void GetData(istream& in) override;
    void PutData(ostream& out) const override;
    unique_ptr<ABS_COMP<S1>> Merge(const ABS_COMP<S1>* arr1, const ABS_COMP<S1>* arr2) const override;
    void Sort(function<bool(const S1&, const S1&)> compare = nullptr) override;

    size_t Size() const override { return count; }
    void Clear() override;

    Fruit& operator=(const Fruit& other);
    const S1& GetItem(size_t index) const {
        if (index < count) return data[index];
        throw std::out_of_range("Index out of range");
    }

    unique_ptr<ABS_COMP<S1>> Intersection(const ABS_COMP<S1>* arr1, const ABS_COMP<S1>* arr2) const;


};

#endif // FRUIT_H
