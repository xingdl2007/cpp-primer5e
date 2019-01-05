#include <glog/logging.h>

int main(int argc, char const *argv[])
{
    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);

    // ...
    LOG(INFO) << "Found j" << 122 << " cookies";
    return 0;
}
