#include "flights.h"
#include <system_error>

namespace
{ // anonymous namespace

struct FlightsErrCategory : std::error_category
{
    const char *name() const noexcept override;
    std::string message(int ev) const override;
};

const char *FlightsErrCategory::name() const noexcept
{
    return "flights";
}

std::string FlightsErrCategory::message(int ev) const
{
    switch (static_cast<FlightsErrc>(ev))
    {
    case FlightsErrc::NonexistentLocations:
        return "nonexistent airport name in request";

    case FlightsErrc::DatesInThePast:
        return "request for a date from the past";

    case FlightsErrc::InvertedDates:
        return "requested flight return date before departure date";

    case FlightsErrc::NoFlightsFound:
        return "no filight combination found";

    case FlightsErrc::ProtocolViolation:
        return "received malformed request";

    case FlightsErrc::ConnectionError:
        return "could not connect to server";

    case FlightsErrc::ResourceError:
        return "insufficient resources";

    case FlightsErrc::Timeout:
        return "processing timed out";

    default:
        return "(unrecognized error)";
    }
}

const FlightsErrCategory theFlightsErrCategory{};

} // anonymous namespace

std::error_code make_error_code(FlightsErrc e)
{
    return {static_cast<int>(e), theFlightsErrCategory};
}