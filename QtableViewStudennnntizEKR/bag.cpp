#include "bag.h"
#include <algorithm>
using namespace std;

istream& operator>>(istream& in, S2& item)
{
    in >> item.Name >> item.Num >> item.Section ;
    return in;
}

ostream& operator<<(ostream& out, const S2& item)
{
    out << item.Num << " " << item.Section << " " << item.Name;
    return out;
}

Bag::Bag() : data(nullptr), count(0) {}

Bag::Bag(const Bag& other) : count(other.count)
{
    data = new S2[count];
    for (size_t i = 0; i < count; ++i)
    {
        data[i] = other.data[i];
    }
}

Bag::~Bag()
{
    delete[] data;
}

void Bag::GetData(istream& in)
{
    Clear();
    S2 temp;
    while (in >> temp)
    {
        S2* newData = new S2[count + 1];
        for (size_t i = 0; i < count; ++i)
        {
            newData[i] = data[i];
        }
        newData[count] = temp;
        delete[] data;
        data = newData;
        ++count;
    }
}

void Bag::PutData(std::ostream& out) const
{
    for (size_t i = 0; i < count; ++i)
    {
        out << data[i] << "\n";

    }
}

unique_ptr<ABS_COMP<S2>> Bag::Merge(const ABS_COMP<S2>* arr1, const ABS_COMP<S2>* arr2) const
{
    auto result = make_unique<Bag>();

    const Bag* b1 = dynamic_cast<const Bag*>(arr1);
    const Bag* b2 = dynamic_cast<const Bag*>(arr2);

    if (!b1 || !b2) return result;

    for (size_t i = 0; i < b1->count; ++i)
    {
        S2* newData = new S2[result->count + 1];
        for (size_t j = 0; j < result->count; ++j)
        {
            newData[j] = result->data[j];
        }
        newData[result->count] = b1->data[i];
        delete[] result->data;
        result->data = newData;
        ++result->count;
    }

    for (size_t i = 0; i < b2->count; ++i)
    {
        bool found = false;
        for (size_t j = 0; j < result->count; ++j)
        {
            if (result->data[j] == b2->data[i])
            {
                found = true;
                break;
            }
        }
        if (!found) {
            S2* newData = new S2[result->count + 1];
            for (size_t j = 0; j < result->count; ++j)
            {
                newData[j] = result->data[j];
            }
            newData[result->count] = b2->data[i];
            delete[] result->data;
            result->data = newData;
            ++result->count;
        }
    }

    return result;
}

void Bag::Sort(function<bool(const S2&, const S2&)> compare)
{
    if (compare)
    {
        sort(data, data + count, compare);
    } else
    {
        sort(data, data + count, [](const S2& a, const S2& b)
                  {
            if (a.Num != b.Num) return a.Num < b.Num;
            int sec = strcmp(a.Section, b.Section);
            if (sec != 0) return sec < 0;
            return strcmp(a.Name, b.Name) < 0;
        });
    }
}

void Bag::Clear()
{
    delete[] data;
    data = nullptr;
    count = 0;
}

Bag& Bag::operator=(const Bag& other)
{
    if (this != &other)
    {
        delete[] data;
        count = other.count;
        data = new S2[count];
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}


unique_ptr<ABS_COMP<S2>> Bag::Intersection(const ABS_COMP<S2>* arr1, const ABS_COMP<S2>* arr2) const
{
    auto result = make_unique<Bag>();

    const Bag* b1 = dynamic_cast<const Bag*>(arr1);
    const Bag* b2 = dynamic_cast<const Bag*>(arr2);

    if (!b1 || !b2) return result;

    for (size_t i = 0; i < b1->Size(); ++i)
    {
        for (size_t j = 0; j < b2->Size(); ++j)
        {
            if (b1->GetItem(i) == b2->GetItem(j))
            {
                S2* newData = new S2[result->Size() + 1];
                for (size_t k = 0; k < result->Size(); ++k)
                {
                    newData[k] = result->GetItem(k);
                }
                newData[result->Size()] = b1->GetItem(i);
                delete[] result->data;
                result->data = newData;
                ++result->count;
                break;
            }
        }
    }

    return result;
}
