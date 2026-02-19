#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

typedef struct Message {
    int src;
    int sink;
    int size;
    int period;
    int tl;

    std::string to_string() {
        return "[" + std::to_string(src) + "," +
                      std::to_string(sink) + "," +
                      std::to_string(size) + "," +
                      std::to_string(period) + "," +
                      std::to_string(tl) + "]";
    }
} Message;

#endif // MESSAGE_HPP