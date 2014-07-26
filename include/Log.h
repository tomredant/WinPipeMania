#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <sstream>

enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG};

class Log
{
    public:
        Log();
        virtual ~Log();
        std::ostringstream& Get(TLogLevel level = logINFO);
    private:
        std::ostringstream os;
        std::string toString (TLogLevel level);
        std::string nowTime ();
};

#endif // LOG_H_INCLUDED
