#ifndef PRODUCT_H
#define PRODUCT_H

#include "abs_comp.h"
#include <string>

class Product
{
public:
    std::string name;
    double price;
    int quantity;

    Product(const std::string& n = "", double p = 0.0, int q = 0);
    bool operator==(const Product& other) const;
};

class ProductArray : public ABS_COMP<Product>
{
public:
    void GetData(std::istream& in) override;
    void PutData(std::ostream& out) const override;
    std::unique_ptr<ABS_COMP<Product>> Merge(const ABS_COMP<Product>* arr1, const ABS_COMP<Product>* arr2) const override;
    void Sort(std::function<bool(const Product&, const Product&)> compare = nullptr) override;
};

#endif // PRODUCT_H
