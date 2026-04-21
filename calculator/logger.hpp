#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <ios>
#include <string>


class Logger
{
private:
    std::ofstream logFile;
public:
    Logger(const std::string& filename) { logFile.open(filename, std::ios::app); }
    ~Logger() { logFile.close(); }
    void log(const std::string &msg)
    {
        logFile << msg << std::endl;
        logFile.flush();
    }
};

#endif // LOGGER_H_
