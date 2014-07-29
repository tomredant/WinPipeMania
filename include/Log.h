#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <sstream>

#define LOG(lvl) if (lvl <= Log::getReportingLevel()) Log().Get(lvl)

enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG};

class Log
{
    public:
        Log();
        virtual ~Log();
        std::ostringstream& Get(TLogLevel level = logINFO);
        static TLogLevel getReportingLevel();
    private:
        static TLogLevel reportingLevel;
        std::ostringstream os;
        std::string toString (TLogLevel level);
        std::string nowTime ();
};

#endif // LOG_H_INCLUDED
