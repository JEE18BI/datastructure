#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct product {
    int id;
    std::string name;
    double price;
    int num;
    int storeid;
    int rate;
    int numOFrate;

    product() = default;
    product(int PId, std::string PName, double PPrice, int PNum, int Sid, int Rate, int NumOFrate)
        : id(PId), name(PName), price(PPrice), num(PNum), storeid(Sid), rate(Rate), numOFrate(NumOFrate) {}
};

#endif // PRODUCT_H
