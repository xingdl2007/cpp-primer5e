#include <assert.h>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <exception>
#include <iostream>
#include <set>
#include <string>

namespace pt = boost::property_tree;

struct debug_settings {
  std::string m_file;
  int m_level;
  std::set<std::string> m_modules;
  void load(const std::string &filename);
  void save(const std::string &filename);
};

void debug_settings::load(const std::string &filename) {
  pt::ptree tree;
  pt::read_xml(filename, tree);
  assert(!tree.empty());

  m_file = tree.get<std::string>("debug.filename");
  m_level = tree.get("debug.level", 0);

  // interesting
  pt::ptree t1 = tree.get_child("debug.filename");
  pt::ptree t2 = tree.get_child("debug.level");
  assert(t1.empty());
  assert(t2.empty());

  // first level: only "debug" node
  for (pt::ptree::value_type &v : tree) {
    std::cout << v.first << std::endl;
  }

  // second level: all debug node's children
  for (pt::ptree::value_type &v : tree.get_child("debug")) {
    std::cout << "\t" << v.first << std::endl;
  }

  // third level: all children of debug.modules
  for (pt::ptree::value_type &v : tree.get_child("debug.modules")) {
    std::cout << "\t\t" << v.first << std::endl;
    m_modules.insert(v.second.data());
  }
  auto range = tree.equal_range("debug");
  assert(range.first != range.second);
}

void debug_settings::save(const std::string &filename) {
  pt::ptree tree;

  // add will not override existed node
  for (const std::string &name : m_modules)
    tree.add("debug.modules.module", name);

  // put will override existed node
  tree.put("debug.filename", m_file);
  tree.put("debug.level", m_level);

  pt::write_xml(filename, tree);
}

/**
 * A property tree with std::string for key and data, and default
 * comparison.

   typedef basic_ptree<std::string, std::string> ptree;

 */

// basically property tree is a standard container with type of pair<string,
// ptree>
// ptree itself

void tutorial() {
  pt::ptree pt;
  pt.push_back(pt::ptree::value_type("pi", pt::ptree("3.14159")));
  pt.push_back(pt::ptree::value_type("hello", pt::ptree("world")));

  std::cout << "print out pt itself's data: " << pt.data() << std::endl;

  // ok
  pt::ptree::const_iterator it = pt.to_iterator(pt.find("pi"));
  std::cout << it->first << std::endl; // output: pi
  double pi = boost::lexical_cast<double>(it->second.data());
  std::cout << pi << std::endl;

  // interesting
  pt::ptree::const_iterator it2 = pt.to_iterator(pt.find("hello"));
  std::cout << it2->first << " " << it2->second.data() << std::endl;
}

void tutorial2() {
  pt::ptree pt;
  pt.put("pi", 3.14159); // create a new node, associated with a key of "pi"
  double pi = pt.get<double>("pi");

  std::cout << "tutorial2 pt: " << pt.data() << std::endl;
  std::cout << pi << std::endl;
}

void tutorial3() {
  pt::ptree pt;
  float v = pt.get<float>("a.path.to.float.value");
  (void)v; // suppress compiler warning
}

void tutorial4() {
  pt::ptree pt;
  float v = pt.get("a.path.to.float.value", -1.f);
  std::cout << "tutorial4: " << v << std::endl;
}

void tutorial5() {
  pt::ptree pt;
  boost::optional<float> v = pt.get_optional<float>("a.path.to.float.value");
  if (v) {
    std::cout << "tutorial5: success" << std::endl;
  } else {
    std::cout << "tutorial5: failed" << std::endl;
  }
}

void tutorial6() {
  pt::ptree pt;
  pt.put_value(3.14f);
  std::cout << "tutorial6: " << pt.data() << std::endl;
  std::cout << pt.get_value(1.f) << std::endl;
}

int main() {
  try {
    debug_settings ds;
    ds.load("debug_settings.xml");
    ds.save("debug_settings_out.xml");
    std::cout << "Success\n";
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
  }

  tutorial();
  tutorial2();
  try {
    tutorial3();
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
  }
  tutorial4();
  tutorial5();
  tutorial6();
  return 0;
}
