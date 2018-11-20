#include <streambuf>
#include <iostream>
#include <fstream>

class teebuf : public std::streambuf
{
  public:
    // Construct a streambuf which tees output to both input streambufs
    teebuf(std::streambuf *sb1, std::streambuf *sb2)
        : sb1_(sb1), sb2_(sb2) {}

  protected:
    // This tee buffer has no buffer. So every character "overflows"
    // and can be put directly into the teed buffers.
    virtual int overflow(int c)
    {
        if (c == EOF)
        {
            return !EOF;
        }
        else
        {
            int const r1 = sb1_->sputc(c);
            int const r2 = sb2_->sputc(c);
            return r1 == EOF || r2 == EOF ? EOF : c;
        }
    }

    // Sync both teed buffers.
    virtual int sync()
    {
        int const r1 = sb1_->pubsync();
        int const r2 = sb2_->pubsync();
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }

  private:
    std::streambuf *sb1_;
    std::streambuf *sb2_;
};

class teestream : public std::ostream
{
  public:
    teestream(std::ostream &o1, std::ostream &o2);

  private:
    teebuf tbuf;
};

teestream::teestream(std::ostream &o1, std::ostream &o2)
    : std::ostream(&tbuf), tbuf(o1.rdbuf(), o2.rdbuf())
{
}

int main()
{
    std::ofstream log("hello-world.log");
    teestream tee(std::cout, log);
    tee << "Hello, world!\n";
    tee << "eof: " << EOF << "\n";
    tee << "!eof: " << !EOF << "\n";
    return 0;
}