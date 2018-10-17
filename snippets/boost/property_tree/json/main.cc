#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <set>
#include <vector>

void generate() {
  boost::property_tree::ptree tree;
  boost::property_tree::ptree child;

  std::set<std::pair<std::string, std::string>> track = {
      {"Hello", "World"}, {"World", "Beijing"}, {"Beijing", "Shenzhen"}};
  int counter = 120;

  for (auto &t : track) {
    boost::property_tree::ptree leaf;
    leaf.add("from", t.first);
    leaf.add("to", t.second);
    child.push_back(std::make_pair("", leaf));
  }

  tree.add_child("edges", child);
  tree.add("counter", counter);

  boost::property_tree::write_json("generate.json", tree);
}

int main() {
  std::set<std::string> tracks;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json("input.json", pt);
  boost::property_tree::write_json("output.json", pt);

  // generate from source data
  generate();
}
