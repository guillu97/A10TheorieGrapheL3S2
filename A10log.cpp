
#include "A10log.h"



void Log::write_to_log( const std::string &text ){
    std::ofstream log_file(
        "A10log_file.txt", std::ios_base::out | std::ios_base::app );
    log_file << text << std::endl;
}
