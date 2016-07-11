#pragma once

//            _____                    _____                    _____                    _____                    _____
//           /\    \                  /\    \                  /\    \                  /\    \                  /\    \
//          /::\    \                /::\    \                /::\    \                /::\____\                /::\____\
//         /::::\    \              /::::\    \              /::::\    \              /::::|   |               /:::/    /
//        /::::::\    \            /::::::\    \            /::::::\    \            /:::::|   |              /:::/    /
//       /:::/\:::\    \          /:::/\:::\    \          /:::/\:::\    \          /::::::|   |             /:::/    /
//      /:::/__\:::\    \        /:::/__\:::\    \        /:::/__\:::\    \        /:::/|::|   |            /:::/    /
//     /::::\   \:::\    \       \:::\   \:::\    \      /::::\   \:::\    \      /:::/ |::|   |           /:::/    /
//    /::::::\   \:::\    \    ___\:::\   \:::\    \    /::::::\   \:::\    \    /:::/  |::|___|______    /:::/    /      _____
//   /:::/\:::\   \:::\    \  /\   \:::\   \:::\    \  /:::/\:::\   \:::\    \  /:::/   |::::::::\    \  /:::/____/      /\    \
//  /:::/__\:::\   \:::\____\/::\   \:::\   \:::\____\/:::/__\:::\   \:::\____\/:::/    |:::::::::\____\|:::|    /      /::\____\
//  \:::\   \:::\   \::/    /\:::\   \:::\   \::/    /\:::\   \:::\   \::/    /\::/    / ~~~~~/:::/    /|:::|____\     /:::/    /
//   \:::\   \:::\   \/____/  \:::\   \:::\   \/____/  \:::\   \:::\   \/____/  \/____/      /:::/    /  \:::\    \   /:::/    /
//    \:::\   \:::\    \       \:::\   \:::\    \       \:::\   \:::\    \                  /:::/    /    \:::\    \ /:::/    /
//     \:::\   \:::\____\       \:::\   \:::\____\       \:::\   \:::\____\                /:::/    /      \:::\    /:::/    /
//      \:::\   \::/    /        \:::\  /:::/    /        \:::\   \::/    /               /:::/    /        \:::\__/:::/    /
//       \:::\   \/____/          \:::\/:::/    /          \:::\   \/____/               /:::/    /          \::::::::/    /
//        \:::\    \               \::::::/    /            \:::\    \                  /:::/    /            \::::::/    /
//         \:::\____\               \::::/    /              \:::\____\                /:::/    /              \::::/    /
//          \::/    /                \::/    /                \::/    /                \::/    /                \::/____/
//           \/____/                  \/____/                  \/____/                  \/____/                  ~~
//

/*
	TODO:
	  - Set migration serial as dynamic.
	  - Check all Queryes for ASQLi::FilterQuery.
	  - Improve ASQLi::FilterQuery.
	  - Add new security measures.
	  - Hash passwords in the database and encrypt them.
	  - Code Hack logs.
	  - Code logging system.
	  - Code unknown packets dumper.
*/

/*
	Console credits.
*/
#define CREDITS_BANNER "[ ESEmu Project SERVER ]\nMade by d3vil401 (http://d3vsite.org/) & Sonny\nd3v Version 2.12 [FIRE]\n\n"

/*
	Compiling configuration.
*/
#define BOOST_NETWORK
#define USING_WORKERS

/*
	This enables some Development functions like:
		- Thread Manager & Priority Engine (which works, but not tested and code is not compiling for header collision).
		- LUASystem
*/
#define IS_DEVELOPMENT

/*
	Global things.
*/
#ifdef _DEBUG
#define DUMP(Buffer, Size)						{ \
													  for (auto i = 0; i < Size; i++) \
													    printf("0x%02X ", Buffer[i]); \
													  printf("\n\n"); \
												}
#define PDUMP(Buffer, Size)						{ \
													  for (auto i = 0; i < Size; i++) \
													    printf("%02X ", Buffer[i]); \
													  printf("\n\n"); \
																								}
#else
#define DUMP(Buffer, Size)
#endif