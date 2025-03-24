#ifndef SLLCODE_H
#define SLLCODE_H

#include <string>

const std::string insertFrontCode = {
    "Node myNode = new Node(value)\n"
    "myNode.next = head\n"
    "head = myNode"
};

const std::string insertMiddleCode = {
    "Node cur = head\n"
    "for(k = 0; k+1 < index; ++k)\n"
    "	cur = cur.next\n"
    "Node myNode = new Node(value)\n"
    "myNode.next = cur.next\n"
    "cur.next = myNode"
};

const std::string removeFrontCode = {
    "Node myNode = head\n"
    "head = head.next\n"
    "delete myNode"
};

const std::string removeMiddleCode = {
    "Node cur = head\n"
    "for(k = 0; k+1 < index; ++k)\n"
    "	cur = cur.next\n"
    "Node myNode = cur.next\n"
    "cur.next = myNode.next\n"
    "delete myNode"
};

const std::string updateCode = {
    "Node cur = head\n"
    "for(k = 0; k < index; ++k)\n"
    "	cur = cur.next\n"
    "cur.data = value"
};

const std::string searchCode = {
    "if empty, return NOT_FOUND\n"
    "Node cur = head\n"
    "int index = 0\n"
    "while (cur.data != value)\n"
    "   index++, cur = cur.next\n"
    "   if cur == null,\n"
    "       return NOT_FOUND\n"
    "return index"
};

#endif