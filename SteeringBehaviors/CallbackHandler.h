#ifndef CALLBACKHANDLER_H
#define CALLBACKHANDLER_H

#include "LOpenGL.h"
#include "GameWorld.h"

class CallbackHandler
{
private:
    CallbackHandler() {}
    CallbackHandler(const CallbackHandler&);
    CallbackHandler& operator=(const CallbackHandler&);

private:
    static GameWorld* m_pGameWorld;

public:
    ~CallbackHandler() {}
    static CallbackHandler* Instance(GameWorld* world);
};

#endif // CALLBACKHANDLER_H
