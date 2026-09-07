// cl: /DNDEBUG /MD /GX
#include <string.h>

extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *, int);

class ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    void Set_Priority(int priority);

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned long m_threadId;
    void *m_handle;
    int m_priority;
};

ThreadClass::ThreadClass(const char *name)
{
    m_handle = 0;
    m_priority = 0;
    m_threadId = 0;
    if (name)
        strcpy(m_name, name);
    else
        memcpy(m_name, "No name", 8);
}

void ThreadClass::Set_Priority(int priority)
{
    m_priority = priority;
    if (m_handle)
        SetThreadPriority(m_handle, m_priority);
}
