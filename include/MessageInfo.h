//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_MESSAGEINFO_H
#define ITIVITI_DEV_MESSAGEINFO_H

struct MessageInfo {
    MessageInfo(uint64_t id): id(id) {};
    uint64_t id;
    uint64_t start;
};

#endif //ITIVITI_DEV_MESSAGEINFO_H
