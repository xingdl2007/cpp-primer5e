#include "flights.h"
#include <cassert>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::error_code ec = FlightsErrc::NoFlightsFound;
    assert(ec);
    assert(ec == FlightsErrc::NoFlightsFound);
    assert(ec != FlightsErrc::InvertedDates);
    std::cout << ec << " -> " << ec.message() << std::endl;
    return 0;
}
