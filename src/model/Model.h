/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "network/Network.h"
#include "log/Logger.h"


/*
 * Model class
 *
 * Provides access to all model components.
 */

class Model
{
private:
    static Network  m_network;
    static Logger   m_logger;

public:
    static Network& network() { return m_network; }
    static Logger& logger() { return m_logger; }
};
