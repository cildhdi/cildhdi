#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cassert>

/*
if you have defined DEBUG before including this head file, the each output will begin with
[loglevel, time]
or
[loglevel, time, filepath, line]
*/
#ifdef DEBUG
#define DEBUG_INFO ", File:" << __FILE__ << ", Line:" << __LINE__
#else
#define DEBUG_INFO ""
#endif // DEBUG

#define SWITCH_BRANCH(level)    \
    case cl::LogLevel::level:   \
        info << std::left << std::setw(11) << #level << ", "; \
        break;

#define LOG(logger) logger << "\n"                       \
                           << [&]() -> std::string {\
                                std::ostringstream info;\
			                    info << "[";\
                                std::time_t now = std::time(nullptr);\
                                switch (logger.get_loglevel())                                      \
                                {\
                                    SWITCH_BRANCH(Debug);\
                                    SWITCH_BRANCH(Information);\
                                    SWITCH_BRANCH(Warning);\
                                    SWITCH_BRANCH(Error);\
                                    SWITCH_BRANCH(Unkonwn);\
                                }\
                                info << std::put_time(std::localtime(&now), "%c");\
                                return info.str(); }() \
                                           << DEBUG_INFO << "]\n\t"

namespace cl
{

enum LogLevel
{
    Debug,
    Information,
    Warning,
    Error,
    Unkonwn
};

class Logger
{
  public:
    //return false if output had been added, output must be avaliable until ~Logger() or it's removed.
    bool add_output(std::ostream &output);
    bool remove_output(std::ostream &output);
    void set_loglevel(const LogLevel &loglevel);
    LogLevel get_loglevel() const;

  public:
    template <typename T>
    Logger &operator<<(const T &msg)
    {
        for (auto &output : _outputs)
        {
            (*output) << msg;
        }
        return *this;
    }

  private:
    std::vector<std::ostream *> _outputs;
    LogLevel _current_level = LogLevel::Unkonwn;
};

} // namespace cl