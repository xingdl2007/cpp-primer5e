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

Message::Message(const Message &m) {
    contents = m.contents;
    folders = m.folders;
    add_to_folders(m);
}

Message::Message(Message &&m) : contents(std::move(m.contents)) {
    move_folers(&m);
}

Message::~Message() {
    remove_from_folders();
}

Message &Message::operator=(const Message &m) {
    if (this != &m) {
        remove_from_folders();
        contents = m.contents;
        folders = m.folders;
        add_to_folders(m);
    }
    return *this;
}

Message &Message::operator=(Message &&rhs) {
    if (this != &rhs) {
        remove_from_folders();
        contents = std::move(rhs.contents);
        move_folers(&rhs);
    }
    return *this;
}

void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    f.rmMsg(this);
}

void Message::add_to_folders(const Message &m) {
    for (auto *f:m.folders) {
        f->addMsg(this);
    }
}

void Message::remove_from_folders() {
    for (auto *f:folders) {
        f->rmMsg(this);
    }
}

void Message::move_folers(Message *m) {
    folders = std::move(m->folders);
    for (auto f:folders) {
        f->rmMsg(m);
        f->addMsg(this);
    }
    m->folders.clear();
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    for (auto *f:lhs.folders) {
        f->rmMsg(&lhs);
    }
    for (auto *f:rhs.folders) {
        f->rmMsg(&rhs);
    }
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    for (auto *f:lhs.folders) {
        f->addMsg(&lhs);
    }
    for (auto *f:rhs.folders) {
        f->addMsg(&rhs);
    }
}
