#ifndef Invoker_h__
#define Invoker_h__


namespace Common {

#ifdef ENABLE_BOOST

typedef boost::shared_ptr<boost::thread> ThreadPtr;
typedef boost::shared_ptr<boost::mutex> MutexPtr;

class Invoker
{
private:
    typedef boost::function<void (void)>    InvokeFunction_t;
    std::queue<InvokeFunction_t>            m_Funcs;
    bool_t                                  m_Created;
protected:
    ThreadPtr                               m_Thread;
    MutexPtr                                m_Mutex;
protected:

    Invoker();
    virtual ~Invoker();

    bool_t                                  NeedInvoke() const;
    void                                    BeginInvoke(InvokeFunction_t f);
    void                                    UpdateInvoker();

public:
    static void                             PerformCrossThreadCall(InvokeFunction_t f, Invoker* invobj, bool_t wait_until_done);

public:
    void                                    CreateInvoker(ThreadPtr t, MutexPtr mutex);
    bool_t                                  IsInvokerCreated() const { return m_Created; }
    ThreadPtr                               Thread() { return m_Thread; }
    MutexPtr                                Mutex() { return m_Mutex; }
};

#endif //ENABLE_BOOST

} //Common

#endif // Invoker_h__
