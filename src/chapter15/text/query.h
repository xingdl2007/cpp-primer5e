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

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <iostream>

#include "text.h"

class QueryBase {
    friend class Query;

protected:
    using line_no = TextQuery::line_no;

    virtual ~QueryBase() = default;

private:
    virtual QueryResult eval(const TextQuery &) const = 0;

    virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~(const Query &);

    friend Query operator&(const Query &, const Query &);

    friend Query operator|(const Query &, const Query &);

public:
    Query(const std::string &);

    std::string rep() const { return q->rep(); }

    QueryResult eval(const TextQuery &t) const { return q->eval(t); }

private:
    Query(std::shared_ptr<QueryBase> query) : q(query) {}

    std::shared_ptr<QueryBase> q;
};

inline std::ostream &operator<<(std::ostream &os, const Query query) {
    os << query.rep();
    return os;
}

// inheritance hierarchy
class WordQuery : public QueryBase {
    friend Query;

    WordQuery(const std::string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const override {
        return t.query(query_word);
    }

    std::string rep() const override { return query_word; }

    std::string query_word;
};

class NotQuery : public QueryBase {
    friend Query operator~(const Query &q);

    NotQuery(const Query &q) : query(q) {}

    std::string rep() const { return "~(" + query.rep() + ")"; }

    QueryResult eval(const TextQuery &) const override;

    Query query;
};

inline Query operator~(const Query &q) {
    return std::shared_ptr<QueryBase>(new NotQuery(q));
}

class BinaryQuery : public QueryBase {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string p) : lhs(l), rhs(r), op(p) {}

    std::string rep() const override {
        return "(" + lhs.rep() + " "
               + op + " "
               + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string op;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &lhs, const Query &rhs);

    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}

    QueryResult eval(const TextQuery &) const override;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &lhs, const Query &rhs);

    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}

    QueryResult eval(const TextQuery &) const override;
};

inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}


#endif
