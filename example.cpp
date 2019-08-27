#include "clog.h"

int main(int argc, char * argv[])
{
    clog::set_log_level("debug");

    LogDebug << "Debug" << clog::endl;

    clog::set_log_level("info");
    LogDebug << "Debug" << clog::endl; //will not be print.

    LogInfo << "Info" << clog::endl;

    LogError << "Error" << clog::endl;

    clog::set_log_file("clog.log");

    LogInfo << "Info" << clog::endl;

    return 0;
}