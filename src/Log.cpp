#include "Log.h"

#include <ctime>
#include <stdio.h>

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
    time_t now = time(0);
    tm* localtm = localtime(&now);
    std::string s(asctime(localtm));
    return s;
}


std::ostringstream& Log::Get (TLogLevel level)
{
   os << "- " << nowTime();
   os << " " << toString(level) << ": ";
   os << std::string(level > logDEBUG ? 0 : level - logDEBUG, '\t');
 //  messageLevel = level;
   return os;
}

Log::Log ()
{
    //
}

Log::~Log ()
{
//   if (messageLevel >= Log::ReportingLevel())
   {
      os << std::endl;
      fprintf(stderr, "%s", os.str().c_str());
      fflush(stderr);
   }
}
