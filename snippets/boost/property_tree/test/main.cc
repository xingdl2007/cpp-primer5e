#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>

namespace pt = boost::property_tree;

int main()
{
    pt::ptree tree, child;
    child.put("name", "test");
    tree.add_child("child", child);

    for (auto const &c : tree)
    {
        std::cout << c.second.get<std::string>("name") << std::endl;
    }
}