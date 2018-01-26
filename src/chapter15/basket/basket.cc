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

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "basket.h"

using namespace std;

double print_total(ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

double Basket::total_receipt(ostream &os) const {
    double sum = 0.0;
    for (auto it = items.begin();
         it != items.end();
         it = items.upper_bound(*it)) {
        sum += print_total(os, **it, items.count(*it));
    }
    os << "Total Sale: " << sum << endl;
    return sum;
}

int main() {
    {
        vector<shared_ptr<Quote>> basket;
        basket.push_back(make_shared<Quote>("0-201-82470-1", 50));

        // slice down
        basket.push_back(make_shared<Bulk_Quote>("0-201-548480-8", 50, 10, .25));
        cout << basket.back()->net_price(15) << endl;
    }

    // new Basket
    {
        cout << "\nnew Basket: " << endl;
        Basket basket;
        auto q = Quote("0-201-482470-3", 20);
        auto b = Bulk_Quote("0-201-548480-7", 23.8, 10, .5);

        for (int i = 0; i < 1; i++) {
            // shared_ptr
            basket.add_item(make_shared<Quote>("0-201-482470-1", 50));
            basket.add_item(make_shared<Bulk_Quote>("0-201-548480-8", 50, 10, .25));
            cout << endl;

            // l-value: const Quote&
            basket.add_item(q);
            basket.add_item(b);

            // r-value: Quote&&
            basket.add_item(Quote("0-201-482470-2", 50));
            basket.add_item(Bulk_Quote("0-201-548480-9", 29.55, 10, .25));
            cout << endl;

        }
        basket.total_receipt(cout);
    }

    return 0;
}
