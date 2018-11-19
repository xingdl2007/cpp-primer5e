#include <fstream>
#include <iostream>

class redirecter
{
  public:
    redirecter(std::ostream &dst, std::ostream &src) : src_(src), sbuf_(src.rdbuf())
    {
        src_.rdbuf(dst.rdbuf());
    }
    ~redirecter()
    {
        // restore
        src_.rdbuf(sbuf_);
    }

  private:
    std::ostream &src_;
    std::streambuf *const sbuf_;
};

void hello_world()
{
    std::cout << "Hello World!\n";
}

// Note that redirect will be destroyed before log, thus restoring std::cout's original buffer.
// This detail is crucial, since destroying the file closes it and destroys its stream buffer,
// so we must not allow std::cout to continue using this buffer.
// See main2.cc.
int main()
{
    std::ofstream log("hello-world.log");
    {
        redirecter redirect(log, std::cout);
        hello_world();
    }
    hello_world();
    return 0;
}