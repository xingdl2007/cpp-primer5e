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
 * reproduced. Any commercial use of this code requires the explicit written
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

#include <iostream>
#include <memory>

using std::cin; using std::cout; using std::endl;
using std::shared_ptr; using std::unique_ptr;

struct connection {
    int conn;
};

connection connect() {
    return {100};
}

void disconnect(connection conn) {
    cout << conn.conn << endl;
}

void end_connection(connection *p) {
    disconnect(*p);
}

int main() {
    connection c = connect();
    // function version
    shared_ptr<connection> ptr(&c, end_connection);

    // lambda version
    //shared_ptr<connection> ptr(&c, [](connection *p) { disconnect(*p); });

    // use unique_ptr
    connection cc = connect();
    unique_ptr<connection, decltype(end_connection) *> uptr(&cc, end_connection);

    //lambda version
    //unique_ptr<connection, void (*)(connection *)> uptr(&cc, [](connection *p) { disconnect(*p); });
    return 0;
}