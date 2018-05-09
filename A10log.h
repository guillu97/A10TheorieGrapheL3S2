

#ifndef A10THEORIEGRAPHEL3S2_A10LOG_H
#define A10THEORIEGRAPHEL3S2_A10LOG_H


#include <fstream>

class Log{
    public:
        Log();
        static std::ofstream log_file();
        static void write_to_log( const std::string &text );
};

#endif //A10THEORIEGRAPHEL3S2_A10LOG_H


