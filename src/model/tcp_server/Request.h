/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QByteArray>

/*
 * Request structure
 *
 * Data structure holding a request information.
 */
struct Request {
    unsigned char   system;
    unsigned char   command;
    unsigned int    length;
    QByteArray      data;
};

