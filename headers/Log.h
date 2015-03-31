#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <cstdio>

inline std::string nowTime();

enum TLogLevel {logERROR, logWARNING, logDEBUG};

template <typename T>
class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& get(TLogLevel level = logDEBUG);
public:
    static TLogLevel& reportingLevel();
    static std::string toString(TLogLevel level);
    static TLogLevel fromString(const std::string& level);
protected:
    std::ostringstream os;
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log()
{
}

template <typename T>
std::ostringstream& Log<T>::get(TLogLevel level)
{
    os << "- " << nowTime();
    os << " " << toString(level) << ": ";
    return os;
}

template <typename T>
Log<T>::~Log()
{
    os << std::endl;
    T::Output(os.str());
}

template <typename T>
TLogLevel& Log<T>::reportingLevel()
{
    static TLogLevel reportingLevel = logDEBUG;
    return reportingLevel;
}

template <typename T>
std::string Log<T>::toString(TLogLevel level)
{
	static const char* const buffer[] = {"ERROR", "WARNING", "DEBUG"};
    return buffer[level];
}

template <typename T>
TLogLevel Log<T>::fromString(const std::string& level)
{
    if (level == "DEBUG")
        return logDEBUG;
    if (level == "WARNING")
        return logWARNING;
    if (level == "ERROR")
        return logERROR;
    Log<T>().Get(logWARNING) << "Unknown logging level '" << level << "'. Using WARNING level as default.";
    return logWARNING;
}

class Output2FILE
{
public:
    static FILE*& stream();
    static void output(const std::string& msg);
};

inline FILE*& Output2FILE::stream()
{
    static FILE* pStream = fopen("mortal_kombat.log", "a");
    return pStream;
}

inline void Output2FILE::output(const std::string& msg)
{
    FILE* pStream = stream();
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   if defined (BUILDING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllexport)
#   elif defined (USING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllimport)
#   else
#       define FILELOG_DECLSPEC
#   endif // BUILDING_DBSIMPLE_DLL
#else
#   define FILELOG_DECLSPEC
#endif // _WIN32

class FILELOG_DECLSPEC FILELog : public Log<Output2FILE> {};
//typedef Log<Output2FILE> FILELog;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logDEBUG
#endif

#define FILE_LOG(level) \
    if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
    else FILELog().Get(level)

#include <sys/time.h>

inline std::string nowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
    return result;
}

#endif //__LOG_H__
