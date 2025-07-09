#include "fruit.h"
#include <algorithm>
using namespace std;


istream& operator>>(istream& in, S1& item)
{
    in >> item.Name >> item.Section ;
    return in;
}

ostream& operator<<(ostream& out, const S1& item)
{
    out << item.Name << " " << item.Section;
    return out;
}

Fruit::Fruit() : data(nullptr), count(0) {}

Fruit::Fruit(const Fruit& other) : count(other.count)
{
    data = new S1[count];
    for (size_t i = 0; i < count; ++i)
    {
        strcpy(data[i].Name, other.data[i].Name);
        strcpy(data[i].Section, other.data[i].Section);

    }
}

Fruit::~Fruit()
{
    delete[] data;
}

void Fruit::GetData(istream& in)
{
    Clear();
    S1 temp;
    while (in >> temp)
    {
        S1* newData = new S1[count + 1];
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

void Fruit::PutData(ostream& out) const
{
    for (size_t i = 0; i < count; ++i)
    {
        out << data[i] << "\n";
    }
}

unique_ptr<ABS_COMP<S1>> Fruit::Merge(const ABS_COMP<S1>* arr1, const ABS_COMP<S1>* arr2) const
 {
    auto result = make_unique<Fruit>();

    const Fruit* f1 = dynamic_cast<const Fruit*>(arr1);
    const Fruit* f2 = dynamic_cast<const Fruit*>(arr2);

    if (!f1 || !f2) return result;

    for (size_t i = 0; i < f1->count; ++i)
    {
        S1* newData = new S1[result->count + 1];
        for (size_t j = 0; j < result->count; ++j)
        {
            newData[j] = result->data[j];
        }
        newData[result->count] = f1->data[i];
        delete[] result->data;
        result->data = newData;
        ++result->count;
    }

    for (size_t i = 0; i < f2->count; ++i)
    {
        bool found = false;
        for (size_t j = 0; j < result->count; ++j)
        {
            if (result->data[j] == f2->data[i])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            S1* newData = new S1[result->count + 1];
            for (size_t j = 0; j < result->count; ++j)
            {
                newData[j] = result->data[j];
            }
            newData[result->count] = f2->data[i];
            delete[] result->data;
            result->data = newData;
            ++result->count;
        }
    }

    return result;
}

void Fruit::Sort(function<bool(const S1&, const S1&)> compare)
{
    if (compare)
    {
        sort(data, data + count, compare);
    } else
    {
        sort(data, data + count, [](const S1& a, const S1& b)
             {
            int sec = strcmp(a.Section, b.Section);
            if (sec != 0) return sec < 0;
            return strcmp(a.Name, b.Name) < 0;
        });
    }
}

void Fruit::Clear()
{
    delete[] data;
    data = nullptr;
    count = 0;
}

Fruit& Fruit::operator=(const Fruit& other)
{
    if (this != &other)
    {
        delete[] data;
        count = other.count;
        data = new S1[count];
        for (size_t i = 0; i < count; ++i)
        {
            strcpy(data[i].Name, other.data[i].Name);
            strcpy(data[i].Section, other.data[i].Section);
        }
    }
    return *this;
}


unique_ptr<ABS_COMP<S1>> Fruit::Intersection(const ABS_COMP<S1>* arr1, const ABS_COMP<S1>* arr2) const
{
    auto result = make_unique<Fruit>();

    const Fruit* f1 = dynamic_cast<const Fruit*>(arr1);
    const Fruit* f2 = dynamic_cast<const Fruit*>(arr2);

    if (!f1 || !f2) return result;

    for (size_t i = 0; i < f1->Size(); ++i)
    {
        for (size_t j = 0; j < f2->Size(); ++j)
        {
            if (f1->GetItem(i) == f2->GetItem(j))
            {
                S1* newData = new S1[result->Size() + 1];
                for (size_t k = 0; k < result->Size(); ++k)
                {
                    newData[k] = result->GetItem(k);
                }
                newData[result->Size()] = f1->GetItem(i);
                delete[] result->data;
                result->data = newData;
                ++result->count;
                break;
            }
        }
    }

    return result;
}
