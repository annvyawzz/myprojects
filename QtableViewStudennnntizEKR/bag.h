#ifndef BAG_H
#define BAG_H

#include "abs_comp.h"
#include <cstring>
using namespace std;

struct S2
{
    char Name[20];
    int Num;
    char Section[10];


    bool operator==(const S2& other) const
    {
        return Num == other.Num && strcmp(Section, other.Section) == 0 && strcmp(Name, other.Name) == 0;
    }
};

istream& operator>>(istream& in, S2& item);
ostream& operator<<(ostream& out, const S2& item);

class Bag : public ABS_COMP<S2>
{
private:
    S2* data;
    size_t count;

public:
    Bag();
    Bag(const Bag& other);
    ~Bag();

    void GetData(istream& in) override;
    void PutData(ostream& out) const override;
    unique_ptr<ABS_COMP<S2>> Merge(const ABS_COMP<S2>* arr1, const ABS_COMP<S2>* arr2) const override;
    void Sort(function<bool(const S2&, const S2&)> compare = nullptr) override;

    size_t Size() const override { return count; }
    void Clear() override;

    Bag& operator=(const Bag& other);
    const S2& GetItem(size_t index) const {
        if (index < count) return data[index];
        throw std::out_of_range("Index out of range");
    }

    unique_ptr<ABS_COMP<S2>> Intersection(const ABS_COMP<S2>* arr1, const ABS_COMP<S2>* arr2) const;
};

#endif // BAG_H
