#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <iostream>

int main()
{
    std::stringstream oss;
    boost::property_tree::ptree tree;

    auto child = tree.add_child(boost::property_tree::ptree::path_type("summary.biz.metrics"),
                                boost::property_tree::ptree());
    child.put("name", "Shenzhen");
    child.put("message", "Hi~");

    auto out = tree.get_child_optional("summary");
    if (out)
    {
        boost::property_tree::write_json(oss, *out);
    }
    else
    {
        boost::property_tree::write_json(oss, tree);
    }
    std::cout << oss.str() << std::endl;
}