#include <streambuf>

// a generic version
template <typename char_type,
          typename traits = std::char_traits<char_type>>
class basic_teebuf : public std::basic_streambuf<char_type, traits>
{
  public:
    using int_type = typename traits::int_type;
    basic_teebuf(std::basic_streambuf<char_type, traits> *sb1,
                 std::basic_streambuf<char_type, traits> *sb2) : sb1_(sb1),
                                                                 sb2_(sb2) {}

  private:
    virtual int sync()
    {
        int const r1 = sb1_->pubsync();
        int const r2 = sb2_->pubsync();
        return r1 == 0 && r2 == 0 ? 0 : -1;
    }

    virtual int_type overflow(int_type c)
    {
        int_type const eof = traits::eof();
        if (traits::eq_int_type(c, eof))
        {
            return traits::not_eof(c);
        }
        else
        {
            char_type const ch = traits::to_char_type(c);
            int_type const r1 = sb1_->sputc(ch);
            int_type const r2 = sb2_->sputc(ch);
            return traits::eq_int_type(r1, eof) ||
                           traits::eq_int_type(r2, eof)
                       ? eof
                       : c;
        }
    }

  private:
    std::basic_streambuf<char_type, traits> *sb1_;
    std::basic_streambuf<char_type, traits> *sb2_;
};

using teebuf = basic_teebuf<char>;