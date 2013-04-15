//
//  ISNSOperation.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 4/15/13.
//
//

#ifndef ISNSOperation_h
#define ISNSOperation_h

#include "HSNSCommon.h"

class ISNSOperation
{
private:
    
protected:
    
    E_SNS_OPERATION_ID m_id;
    E_SNS_OPERATION_STATUS m_status;
    
    std::set<ISNSOperation*> m_synchronousOperationsQueue;
    std::queue<ISNSOperation*> m_asynchronousOperationsQueue;
    
public:
    
    ISNSOperation(E_SNS_OPERATION_ID _id);
    ~ISNSOperation(void);
    
    E_SNS_OPERATION_ID Get_Id(void)
    {
        return m_id;
    };
    
    E_SNS_OPERATION_STATUS Get_Status(void)
    {
        return m_status;
    };
    
    void AppendSynchronousOperation(ISNSOperation* _operation);
    void AppendAsynchronousOperation(ISNSOperation* _operation);
    
    void Update(void);
    void Start(void);
    void Cancel(void);
};

#endif 
