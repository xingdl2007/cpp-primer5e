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

#ifndef _BASKET_H_
#define _BASKET_H_

#include <string>
#include <memory>
#include <iostream>
#include <set>

#include "book.h"

class Basket {
public:
    void add_item(const std::shared_ptr<Quote> &sale) {
        items.insert(sale);
        std::cout << "void add_item(const std::shared_ptr<Quote> &sale) " << std::endl;
    }

    // overloaded add_item
    // copy Quote
    void add_item(const Quote &sale) {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
        std::cout << "void add_item(const Quote &sale) " << std::endl;
    }

    // move Quote
    void add_item(Quote &&sale) {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
        std::cout << "void add_item(Quote &&sale) " << std::endl;
    }

    double total_receipt(std::ostream &) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }

    // in-class initialization must use {} or =
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

#endif
