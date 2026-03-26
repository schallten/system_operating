// used to provide functions to get OS details , like name , version etc.
#ifndef SYSTEM_DETAILS_H
#define SYSTEM_DETAILS_H

#include <string>

class SystemDetails {
public:
    static std::string getOSName() {
        return "MyOS"; // Placeholder name for the OS
    }
    static std::string getOSVersion() {
        return "1.0.0"; // Placeholder version for the OS
    }
};



#endif