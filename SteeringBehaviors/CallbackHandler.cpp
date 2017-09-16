#include "CallbackHandler.h"

GameWorld* CallbackHandler::m_pGameWorld = NULL;
GLFWwindow* CallbackHandler::m_pWindow = NULL;

CallbackHandler* CallbackHandler::Instance(GameWorld *world, GLFWwindow* window)
{
    static CallbackHandler instance;
    m_pGameWorld = world;
    m_pWindow = window;
    return &instance;
}

void CallbackHandler::HandleKeyPresses(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    m_pGameWorld->HandleKeyPresses(m_pWindow, key, scancode, action, mods);
}

