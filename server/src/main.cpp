#include "IAddress.h"
#include "Acceptor.h"
#include "event.h"

int main()
{
    Event event("172.17.28.149", 20000);

    event.loop();

    return 0;
}

