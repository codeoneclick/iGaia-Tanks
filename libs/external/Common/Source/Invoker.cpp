#include "pch.h"
#include "Invoker.h"

namespace Common {

#ifdef ENABLE_BOOST

static boost::condition_variable CondVar;

Invoker::Invoker() : m_Created(FALSE)
{

}

Invoker::~Invoker()
{
    
}

bool_t Invoker::NeedInvoke() const
{
    APP_API_ASSERT(m_Created);
    return boost::this_thread::get_id() != m_Thread->get_id();
}

void Invoker::BeginInvoke( InvokeFunction_t f )
{
    APP_API_ASSERT(m_Created);
    boost::mutex::scoped_try_lock lock(*m_Mutex);

    m_Funcs.push(f);
}

//Must be called from secondary thread context
void Invoker::UpdateInvoker()
{
    APP_API_ASSERT(m_Created);

    boost::mutex::scoped_try_lock lock(*m_Mutex);

    while(!m_Funcs.empty())
    {
		m_Funcs.front()();
        CondVar.notify_one();
		m_Funcs.pop();
    }
}

void Invoker::CreateInvoker(ThreadPtr t, MutexPtr mutex)
{
    APP_API_ASSERT(t);
    APP_API_ASSERT(mutex);

    m_Thread = t;
    m_Mutex = mutex;
    m_Created = TRUE;
}

void Invoker::PerformCrossThreadCall( InvokeFunction_t f, Invoker* invobj, bool_t wait_until_done )
{
    APP_API_ASSERT(invobj->IsInvokerCreated());

    if (!wait_until_done)
    {
        invobj->BeginInvoke(f);
    }
    else
    {
        boost::mutex::scoped_lock lock(*invobj->m_Mutex);
        invobj->m_Funcs.push(f);
        CondVar.wait(lock);
    }
}

#endif //ENABLE_BOOST

} //Common