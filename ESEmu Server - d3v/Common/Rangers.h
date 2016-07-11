#pragma once

#define INT_RANGE(x) { if (x > 2147483646) || (x < - 2147483646) \ printf("[/!\] Int32 Overflow (%d).\n", x); \ x = 0; }
#define LONG_RANGE(x) { if (x > 2147483646) || (x < - 2147483646) \ printf("[/!\] Long32 Overflow (%ld).\n", x); \ x = 0; }
#define LONG_LONG_RANGE(x) { if (x > 9223372036854775806) || (x < - 9223372036854775806) \ printf("[/!\] Long64 Overflow (%ld).\n", x); \ x = 0; }
#define SHORT_INT_RANGE(x) { if (x > 32766) || (x < - 32766) \ printf("[/!\] Short16 Overflow (%d).\n", x); \ x = 0; }
//#define FLOAT_RANGE(x) { if (x > 2147483646) || (x < - 2147483646) \ printf("[/!\] Float32 Overflow (%f).\n", x); \ x = 0; }
//#define DOUBLE_RANGE(x) { if (x > 9223372036854775806) || (x < - 9223372036854775806) \ printf("[/!\] Double64 Overflow (%ld).\n", x); \ x = 0; }
#define CHAR_RANGE(x) { if (x > 254) || (x < - 254) \ printf("[/!\] Char Overflow (%c).\n", x); \ x = 0; }