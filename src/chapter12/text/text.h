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

#ifndef _TEXT_H_
#define _TEXT_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <memory>

class TextQuery;

class QueryResult {
public:
    QueryResult(std::shared_ptr<TextQuery> text_, std::string query_)
            : text(text_), query(query_) {}

    void print(std::ostream &out);

private:
    std::weak_ptr<TextQuery> text;
    std::string query;
};

class TextQuery {
    typedef std::vector<std::string>::size_type size_type;

    friend class QueryResult;

public:
    explicit TextQuery(std::ifstream &in);

private:
    std::map<std::string, std::set<size_type>> dict;
    std::vector<std::string> contents;
};

void truncate(std::string &s) {
    auto ret1 = std::find_if_not(s.begin(), s.end(),
                                 [](char c) {
                                     return !std::isalnum(c);
                                 });
    s.erase(s.begin(), ret1);
    auto ret2 = std::find_if(s.begin(), s.end(),
                             [](char c) {
                                 return !std::isalnum(c);
                             });
    s.erase(ret2, s.end());
}

TextQuery::TextQuery(std::ifstream &in) {
    std::string line;
    size_type line_num = 0;
    while (std::getline(in, line)) {
        contents.push_back(line);
        line_num = contents.size() - 1;
        std::istringstream words(line);
        std::string word;
        while (words >> word) {
            truncate(word);
            dict[word].insert(line_num);
        }
    }
}

void QueryResult::print(std::ostream &out) {
    auto src = text.lock();
    if (src) {
        auto ret = src->dict.find(query);
        if (ret != src->dict.end()) {
            for (auto no:ret->second) {
                out << "(line: " << no << ")-> " << src->contents[no] << "\n";
            }
        } else {
            out << "Oops..: " << std::quoted(query) << " not find\n" << std::ends;
        }
    } else {
        out << "Oops..\n" << std::ends;
    }
}

#endif