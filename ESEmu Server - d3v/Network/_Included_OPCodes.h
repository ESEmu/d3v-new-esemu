#pragma once
#ifndef _INC_OPCODES_H_
#define _INC_OPCODES_H_


// Server -> Client
#include "Login Server\Server\AK_AUTH.h"
#include "Login Server\Server\AK_DATE.h"
#include "Login Server\Server\AK_KEEPALIVE.h"
#include "Login Server\Server\AK_CHANNELLIST_ACK.h"
#include "Login Server\Server\AK_CHANNELLIST.h"
#include "Login Server\Server\AK_LOGIN_CLOSE.h"

// Client -> Server
#include "Login Server\Client\REQ_AUTH.h"
#include "Login Server\Client\REQ_DATE.h"
#include "Login Server\Client\REQ_KEEPALIVE.h"
#include "Login Server\Client\REQ_CHANNELLIST.h"
#include "Login Server\Client\REQ_SERVERLIST.h"
#include "Login Server\Client\REQ_LOGIN_CLOSE.h"

//-------------- GAME CORE

#include "Game Server\Client\REQ_CHECKVERSION.h"
#include "Game Server\Server\AK_CHECKVERSION.h"
#include "Game Server\Server\AK_CHECKVERSION_ACK1.h"
#include "Game Server\Server\AK_CHECKVERSION_ACK2.h"
#include "Game Server\Server\AK_CHECKVERSION_ACK3.h"

#include "Game Server\Client\REQ_SESSIONCHECK.h"
#include "Game Server\Server\AK_SESSIONCHECK.h"
#include "Game Server\Server\AK_SESSIONCHECK_ACK1.h"
#include "Game Server\Server\AK_SESSIONCHECK_ACK2.h"

#include "Game Server\Client\REQ_SESSIONCHECK2.h"
#include "Game Server\Server\AK_SESSIONCHECK2.h"

#include "Game Server\Client\REQ_SESSIONCHECK3.h"
#include "Game Server\Server\AK_SESSIONCHECK3.h"

#include "Game Server\Client\REQ_DATECHECK.h"
#include "Game Server\Server\AK_DATECHECK.h"

#include "Game Server\Client\REQ_CURRENTIP.h"
#include "Game Server\Server\AK_CURRENTIP.h"

#include "Game Server\Client\REQ_CHARDATA.h"
#include "Game Server\Server\AK_CHARDATA.h"
#include "Game Server\Server\AK_CHARDATA_ACK1.h"
#include "Game Server\Server\AK_CHARDATA_ACK2.h"

#include "Game Server\Client\REQ_CHECKCHARNAME.h"
#include "Game Server\Server\AK_CHECKCHARNAME.h"

#include "Game Server\Client\REQ_CHARCREATE.h"
#include "Game Server\Server\AK_CHARCREATE.h"

#include "Game Server\Client\REQ_AUTHTOKEN.h"
#include "Game Server\Server\AK_AUTHTOKEN.h"

#include "Game Server\Client\REQ_CHECKPINCODE.h"
#include "Game Server\Server\AK_PINCODE_REQ.h"
#include "Game Server\Server\AK_PINCODE_ACK.h"

#include "Game Server\Client\REQ_CHECKVALIDSERVER.h"
#include "Game Server\Server\AK_CHECKVALIDSERVER.h"

#endif INC_OPCODES_H_
