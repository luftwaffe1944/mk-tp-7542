#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <cstdio>
#include "MessageError.h"
inline std::string nowTime();

#define LOG_LEVEL_DEBUG "DEBUG"
#define LOG_LEVEL_ERROR "ERROR"
#define LOG_LEVEL_WARNING "WARNING"
#define WHITE_SPACE " "

enum TLogLevel {
	logERROR, logWARNING, logDEBUG
};

template<typename T>
class Log {
public:
	Log();
	virtual ~Log();
	std::ostringstream& get(TLogLevel level = logDEBUG);
	static TLogLevel& reportingLevel();
	static void logMsgError(MessageError msgError);
	static std::string toString(TLogLevel level);
	static TLogLevel fromString(const std::string& level);
protected:
	std::ostringstream os;
private:
	Log(const Log&);
	Log& operator =(const Log&);
};

template<typename T>
Log<T>::Log() {
}

template<typename T>
std::ostringstream& Log<T>::get(TLogLevel level) {
	os << "- " << nowTime();
	os << " " << toString(level) << ": ";
	return os;
}

template<typename T>
Log<T>::~Log() {
	os << std::endl;
	T::output(os.str());
}

template<typename T>
TLogLevel& Log<T>::reportingLevel() {
	static TLogLevel reportingLevel = logDEBUG;
	return reportingLevel;
}

template<typename T>
std::string Log<T>::toString(TLogLevel level) {
	static const char* const buffer[] = { LOG_LEVEL_ERROR, LOG_LEVEL_WARNING,
	LOG_LEVEL_DEBUG };
	return buffer[level];
}

template<typename T>
TLogLevel Log<T>::fromString(const std::string& level) {
	if (level == LOG_LEVEL_DEBUG)
		return logDEBUG;
	if (level == LOG_LEVEL_WARNING)
		return logWARNING;
	if (level == LOG_LEVEL_ERROR)
		return logERROR;
	Log<T>().get(logWARNING) << "Unknown logging level '" << level
			<< "'. Using WARNING level as default.";
	return logWARNING;
}

class Output2FILE {
public:
	static FILE*& stream();
	static void output(const std::string& msg);
};

inline FILE*& Output2FILE::stream() {
	static FILE* pStream = fopen("log/mortal_kombat.log", "a");
	return pStream;
}

inline void Output2FILE::output(const std::string& msg) {
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

class FILELOG_DECLSPEC FILELog: public Log<Output2FILE> {
};
//typedef Log<Output2FILE> FILELog;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logDEBUG
#endif

#define FILE_LOG(level) \
    if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > FILELog::reportingLevel() || !Output2FILE::stream()) ; \
    else FILELog().get(level)

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string nowTime()
{
	const int MAX_LEN = 200;
	char buffer[MAX_LEN];
	if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0,
					"HH':'mm':'ss", buffer, MAX_LEN) == 0)
	return "Error in NowTime()";

	char result[100] = {0};
	static DWORD first = GetTickCount();
	std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
	return result;
}

#else

#include <sys/time.h>

inline std::string nowTime() {
	char buffer[11];
	time_t t;
	time(&t);
	tm r = { 0 };
	strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
	struct timeval tv;
	gettimeofday(&tv, 0);
	char result[100] = { 0 };
	std::sprintf(result, "%s.%03ld", buffer, (long) tv.tv_usec / 1000);
	return result;
}

#endif //WIN32

template<typename T>
void Log<T>::logMsgError(MessageError msgError) {

	TLogLevel logLevel = fromString(msgError.getLogLevel());
	switch (logLevel) {
	case logDEBUG:
		FILE_LOG(logDEBUG) << msgError.getHeadMsg() << WHITE_SPACE
				<< msgError.getDetailMsg();
		break;
	case logERROR:
		FILE_LOG(logERROR) << msgError.getHeadMsg() << WHITE_SPACE
				<< msgError.getDetailMsg();
		break;
	case logWARNING:
		FILE_LOG(logWARNING) << msgError.getHeadMsg() << WHITE_SPACE
				<< msgError.getDetailMsg();
		break;

	}

}

#endif //__LOG_H__
