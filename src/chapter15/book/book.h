/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 *
 * "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
 *
 *
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 *
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address:
 *
 * 	Pearson Education, Inc.
 * 	Rights and Permissions Department
 * 	One Lake Street
 * 	Upper Saddle River, NJ  07458
 * 	Fax: (201) 236-3290
*/

#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
#include <iostream>

class Quote {
public:
    // constructors
    Quote() = default;

    Quote(const std::string &s, double sales_price) :
            bookNo(s), price(sales_price) {}

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const {
        return n * price;
    }

    virtual ~Quote() = default;

    virtual void debug() const {
        std::cout << "Quote: <bookNO: " << bookNo
                  << "> <price: " << price << "> " << std::endl;
    }

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Disc_Quote : public Quote {
public:
    Disc_Quote() = default;

    Disc_Quote(const std::string &s, double p, std::size_t min, double dis)
            : Quote(s, p), quantity(min), discount(dis) {}

    double net_price(std::size_t n) const =0;

    virtual void debug() const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_Quote : public Disc_Quote {
public:
    Bulk_Quote() = default;

    Bulk_Quote(const std::string &s, double p, std::size_t min, double dis)
            : Disc_Quote(s, p, min, dis) {}

    double net_price(std::size_t n) const override {
        if (n >= quantity) {
            return price * (1 - discount) * n;
        }
        return price * n;
    }

    virtual void debug() const {
        std::cout << "Bulk Quote: <bookNO: " << isbn()
                  << "> <price: " << price << "> "
                  << "<min_qty: " << quantity
                  << "> <discount: " << discount << ">"
                  << std::endl;
    }
};

class Limited_Quote : public Disc_Quote {
public:
    Limited_Quote() = default;

    Limited_Quote(const std::string &s, double p, std::size_t max, double dis)
            : Disc_Quote(s, p, max, dis) {}

    double net_price(std::size_t n) const override {
        if (n > quantity) {
            return n * price;
        }
        return n * (1 - discount) * price;
    }

    ~Limited_Quote() = default;

    virtual void debug() const {
        std::cout << "Limited Quote: <bookNO: " << isbn()
                  << "> <price: " << price << "> "
                  << "<max_qty: " << quantity
                  << "> <discount: " << discount << ">"
                  << std::endl;
    }
};

#endif
