#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

enum class MessageType {
    FILE_MAPPING
};

struct MappingMessage {
    static const MessageType mType = MessageType::FILE_MAPPING;
    unsigned char fileAddr;
    int fileSize;
};

#endif // MESSAGE_H
