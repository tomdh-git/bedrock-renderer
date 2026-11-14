#include "sdk/mc/client/options/Option.h"
#include "sdk/SigManager.h"

void Option::push() {
    reinterpret_cast<void (*)(Option*)>(SIG("Option::push"))(this);
}
