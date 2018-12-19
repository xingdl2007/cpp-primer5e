#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void generate()
{
  boost::property_tree::ptree tree;
  boost::property_tree::ptree child;

  std::set<std::pair<std::string, std::string>> track = {
      {"Hello", "World"}, {"World", "Beijing"}, {"Beijing", "Shenzhen"}};
  int counter = 120;

  for (auto &t : track)
  {
    boost::property_tree::ptree leaf;
    leaf.add("from", t.first);
    leaf.add("to", t.second);
    child.push_back(std::make_pair("", leaf));
  }

  tree.add_child("edges", child);
  tree.add("counter", counter);

  boost::property_tree::write_json("generate.json", tree);
}

int main()
{
  std::set<std::string> tracks;
  boost::property_tree::ptree pt;
  std::cout << sizeof(pt) << std::endl;
  boost::property_tree::read_json("input.json", pt);
  std::cout << sizeof(pt) << std::endl;
  std::cout << pt.data() << std::endl; // nothing
  boost::property_tree::write_json("output.json", pt);

  // same key-value pair
  boost::property_tree::ptree fish, fish_pt1, fish_pt2;
  fish_pt1.put_value("blue");
  fish_pt2.put_value("yellow");
  std::cout << fish_pt1.data() << std::endl;
  std::cout << fish_pt2.data() << std::endl;
  fish.push_back(std::make_pair("fish", fish_pt1));
  fish.push_back(std::make_pair("fish", fish_pt2));
  boost::property_tree::write_json("fish.json", fish);

  // root node has no data
  boost::property_tree::ptree root;
  root.put("height", 0);
  std::cout << root.data() << std::endl; // nothing

  // list of string
  std::vector<std::string> vfruit{"orange", "appel", "pear"};
  boost::property_tree::ptree fruits_node;
  for (auto &f : vfruit)
  {
    boost::property_tree::ptree node;
    node.put_value(f);
    std::cout << "node: " << node.data() << std::endl;
    fruits_node.push_back(std::make_pair("", node));
  }
  root.add_child("fruit", fruits_node);

  // list of int
  boost::property_tree::ptree age_node;
  std::vector<int> vage{33, 23, 45};
  for (auto &f : vage)
  {
    boost::property_tree::ptree node;
    node.put("", f);
    std::cout << "node: " << node.data() << std::endl;
    age_node.push_back(std::make_pair("", node));
  }
  root.add_child("age", age_node);

  boost::property_tree::ptree empty;
  root.add_child("empty", empty);
  boost::property_tree::write_json("root.json", root);

  // single: illformated ptree, so can't write to json file
  // boost::property_tree::ptree single;
  // single.put_value(1);
  // boost::property_tree::write_json("single.json", single);

  // generate from source data
  generate();

  // interesting tree structure, key and value separately stored
  {
    cout << endl;
    namespace pt = boost::property_tree;
    pt::ptree tree;
    tree.push_back(pt::ptree::value_type("pi", pt::ptree("3.1415926")));
    tree.data() = "Goooooogle";
    cout << tree.data() << endl;
    auto it = tree.find("pi");
    cout << it->first << endl;
    cout << it->second.data() << endl;
  }
}
