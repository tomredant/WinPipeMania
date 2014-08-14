#include "Log.h"

#include <ctime>
#include <stdio.h>

TLogLevel Log::reportingLevel = logDEBUG;

TLogLevel Log::getReportingLevel()
{
    return reportingLevel;
}

std::string Log::toString (TLogLevel level)
{
    std::string s("UNKNOWN");

    switch (level) {
        case logERROR:
            s = "ERROR";
            break;
        case logWARNING:
            s = "WARNING";
            break;
        case logINFO:
            s = "INFO";
            break;
        case logDEBUG:
            s = "DEBUG";
            break;
    }

    return s;
}

std::string Log::nowTime ()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
    std::string str(buffer);

    return str;
}

std::ostringstream& Log::Get (TLogLevel level)
{
   os << "- " << nowTime();
   os << " " << toString(level) << ": ";

#if 0 // Activate to show filename:linenumber
   os << __FILE__ << ":" << __LINE__ << ": ";
#endif

   return os;
}

Log::Log ()
{
    // Change to filter out log messages
    reportingLevel = logDEBUG;
}

Log::~Log ()
{
#if 1 // Set to 1 to output logs on stderr and 0 to send logs to file
    FILE* pStream = stderr;
#else
    FILE* pStream = fopen("pipemania.log", "a");
#endif
    os << std::endl;
    fprintf(pStream, "%s", os.str().c_str());
    fflush(pStream);
}
