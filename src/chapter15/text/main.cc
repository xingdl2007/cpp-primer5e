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

using std::string;

#include <fstream>

using std::ifstream;

#include <iostream>

using std::cin; using std::cout; using std::cerr;
using std::endl;

#include <cstdlib>  // for EXIT_FAILURE

#include <stack>
#include <sstream>

#include "query.h"
#include "make_plural.h"

using namespace std;

void runQueries(ifstream &infile) {
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile);  // store the file and build the query map
    stack<Query> result;
    string line;
    // iterate with the user: prompt for a word to find and print result
    cout << "enter word to look for, or q to quit: ";
    while (getline(cin, line)) {
        stringstream stream(line);
        if (line == "") { // skip blank line, not robust, just for convenience
            cout << "enter word to look for, or q to quit: ";
            continue;
        }
        if (line == "q") break;
        string s;
        while (stream >> s) {
            // stop if we hit end-of-file on the input or if a 'q' is entered
            if (s == "&" || s == "|" || s == "~") {
                // run the query and print the results
                if (s == "&") {
                    auto r = result.top();
                    result.pop();
                    auto l = result.top();
                    result.pop();
                    result.push(l & r);
                } else if (s == "|") {
                    auto r = result.top();
                    result.pop();
                    auto l = result.top();
                    result.pop();
                    result.push(l | r);
                } else {
                    auto l = result.top();
                    result.pop();
                    result.push(~l);
                }
            } else {
                result.push(Query(s));
            }
        }
        cout << result.top().eval(tq);
        result.pop();
        cout << "enter word to look for, or q to quit: ";
    }
}

// program takes single argument specifying the file to query
int main(int argc, char **argv) {
    // open the file from which user will query words
    ifstream infile;

    // open returns void, so we use the comma operator XREF(commaOp)
    // to check the state of infile after the open
    if (argc < 2 || !(infile.open(argv[1]), infile)) {
        cerr << "No input file!" << endl;
        return EXIT_FAILURE;
    }
    runQueries(infile);

    return 0;
}
