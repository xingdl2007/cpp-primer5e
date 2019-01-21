#include <iostream>
#include <array>
#include <string>
#include "addspace.hpp"

template <typename... T>
auto foldSum(T... s)
{
    return (... + s);
}

struct Node
{
    int value;
    Node *left;
    Node *right;
    Node(int i = 0) : value(i), left(nullptr), right(nullptr) {}
};

// pointer to member
auto left = &Node::left;
auto right = &Node::right;

template <typename T, typename... TP>
Node *traverse(T np, TP... paths)
{
    return (np->*...->*paths); // np ->* paths1 ->* paths2 ...
}

// template <typename... Types>
// void print(Types const &... args)
// {
//     (std::cout << ... << args) << '\n';
// }

int main(int argc, char const *argv[])
{
    {
        std::string s{"world"};
        print(1.2, "hello", s);
    }

    {
        std::cout << "Sum [0,10]: " << foldSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << '\n';
        // init binary tree structure:
        Node *root = new Node{0};
        root->left = new Node{1};
        root->left->right = new Node{2};
        root->left->left = new Node{3};
        root->left->left->right = new Node{4};

        // interesting
        Node *node = traverse(root, left, left, right);
        std::cout << node->value << std::endl;
    }
    return 0;
}
