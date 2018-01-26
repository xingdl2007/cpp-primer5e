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
#include <iostream>

using namespace std;

namespace lecture {
    class Base {
    public:
        int pub_mem = 100;
    protected:
        int prot_mem;
    private:
        int priv_mem;
    };

    struct Pub_Derv : public Base {
        int f() { return prot_mem; }

        void memfcn(Base &b) { b = *this; }
    };

    struct Prot_Derv : protected Base {
        int f() { return prot_mem; }

        void memfcn(Base &b) { b = *this; }
    };

    struct Priv_Derv : private Base {
        int f() { return prot_mem; }

        void memfcn(Base &b) { b = *this; }
    };

    struct Derived_from_Public : public Pub_Derv {
        int use_base() { return prot_mem; }

        void memfcn(Base &b) { b = *this; }
    };

    struct Derived_from_Protedted : public Prot_Derv {
        int use_base() { return prot_mem; }

        void memfcn(Base &b) { b = *this; }

    };

    struct Derived_from_Private : public Priv_Derv {
        int use_base() { return f(); }

        // void memfcn(Base &b) { b = *this; }
    };
}

class base {
public:
    string name() { return basename; }

    virtual void print(ostream &os) { os << basename; }

    void print() { cout << "hhh"; }

private:
    string basename;
};

class derived : public base {
public:
    using base::print;

    void print(ostream &os) override {
        base::print(os);
        os << " + derived " << i << endl;
    }

private:
    int i;
};

int main() {
    derived d;
    d.print();
    d.print(cout);

    base *b = &d;
    b->print();
    b->print(cout);

    lecture::Pub_Derv pub;
    cout << pub.pub_mem << endl;

    //lecture::Pub_Derv d1;
    //lecture::Priv_Derv d2;
    //lecture::Prot_Derv d3;
    //lecture::Derived_from_Public dd1;
    //lecture::Derived_from_Private dd2;
    //lecture::Derived_from_Protedted dd3;

    //lecture::Base *p = &d1;    // d1 has type Pub_Derv: legal
    //p = &d2;        // d2 has type Priv_Derv: legal
    //p = &d3;        // d3 has type Prot_Derv
    //p = &dd1;        // dd1 has type Derived_from_Public: legal
    //p = &dd2;        // dd2 has type Derived_from_Private
    //p = &dd3;        // dd3 has type Derived_from_Protected

    return 0;
}
