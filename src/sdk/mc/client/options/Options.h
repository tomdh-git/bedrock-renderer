#pragma once
// The registry ClientInstance::getOptions() returns. IOptionsReader::get(OptionID)
// is vtable idx 1 with (this, out*, key) shape: live 1.26.51 GDK 6764 wrapper
// at idx1 forwards to an inner that does cmp edx,0x335 + mov rax,[rcx+rax*8+0x10].
// Game callers do lea rdx,[rsp+xx]; mov r8d,key; call idx1.
#include "sdk/mc/client/options/Option.h"
#include "sdk/mc/client/options/OptionID.h"

struct Options {
    Option* getOption(OptionID id); // vtable[1]
    void loadFile(const char* path); // vtable[18]: parse + apply an options file
    bool isFirstPerson();            // perspective option (id 3) == 0
};
