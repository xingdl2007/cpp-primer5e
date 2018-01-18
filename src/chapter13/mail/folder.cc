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

#include "message.h"

void Folder::add_to_messages(const Folder &f) {
    for (auto *m:f.messages) {
        m->folders.insert(this);
    }
}

void Folder::remove_from_messages() {
    for (auto *m:messages) {
        m->folders.erase(this);
    }
}

// copy ctor
Folder::Folder(const Folder &f) {
    add_to_messages(f);
    messages = f.messages;
}

Folder::~Folder() {
    remove_from_messages();
}

// copy-assignment operator
Folder &Folder::operator=(const Folder &f) {
    if (this != &f) {
        remove_from_messages();
        add_to_messages(f);
        messages = f.messages;
    }
    return *this;
}

void swap(Folder &lhs, Folder &rhs) {
    using std::swap;

    lhs.remove_from_messages();
    rhs.remove_from_messages();

    swap(lhs.messages, rhs.messages);

    lhs.add_to_messages(lhs);
    rhs.add_to_messages(rhs);
}
