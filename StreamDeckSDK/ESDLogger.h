#pragma once

#include <string>

class ESDConnectionManager;

#ifdef _MSC_VER
#define ESDLOGGER_FORMAT_STRING(x) _Printf_format_string_ const char* x
#define ESDLOGGER_FORMAT_FUNCTION(fmt_idx, first_idx)
#else
#define ESDLOGGER_FORMAT_STRING(x) const char* x
#define ESDLOGGER_FORMAT_FUNCTION(fmt_idx, first_idx) \
  // __attribute__((format(printf(fmt_idx, first_idx))))
#endif

class ESDLogger {
 public:
  static ESDLogger* Get();

  void SetWin32DebugPrefix(const std::string& mPrefix);
  void SetConnectionManager(ESDConnectionManager* conn);
  void LogMessage(const char* context, ESDLOGGER_FORMAT_STRING(format), ...)
    ESDLOGGER_FORMAT_FUNCTION(2, 3);

 private:
  ESDLogger();

  std::string mPrefix;
  ESDConnectionManager* mConnectionManager = nullptr;

  void LogToStreamDeckSoftware(const std::string& message);
  void LogToSystem(const std::string& message);
};

#define ESDLog(...) ESDLogger::Get()->LogMessage(__FILE__, __VA_ARGS__)
#ifndef NDEBUG
#define ESDDebug(...) ESDLog(__VA_ARGS__)
#else
#define ESDDebug(...) while (0)
#endif
