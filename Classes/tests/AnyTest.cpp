/* 
 * File:   AnyTest.cpp
 * Author: void
 *
 * Created on August 21, 2012, 12:29 AM
 */

#include <cstdlib>
#include <Any.h>
#include <functional>
#include <map>

static std::map<int, Common::Any> m_AnyMap;

int main(int argc, char** argv)
{
    
    std::cout << "%TEST_STARTED% T1 (AnyTest)" << std::endl;

    std::cout << "Test AnyTest STARTED\n";
    //types 
    int i = 10;
    float f = 12.03f;
    double d = 15.33;
    void* pv = &d;
    char c = 127;
    const char *str = "HelloAny\0";
    std::string strs = "HelloAnyStr";
    
    m_AnyMap[0] = i;
    m_AnyMap[1] = f;
    m_AnyMap[2] = d;
    m_AnyMap[3] = pv;
    m_AnyMap[4] = c;
    m_AnyMap[5] = str;
    m_AnyMap[6] = strs;

    try
    {
        int _i      =   Common::any_cast<int>(m_AnyMap[0]);
        float _f    =   Common::any_cast<float>(m_AnyMap[1]);
        double _d   =   Common::any_cast<double>(m_AnyMap[2]);
        void* _pv   =   Common::any_cast<void*>(m_AnyMap[3]);
        char _c     =   Common::any_cast<char>(m_AnyMap[4]);
        const char* _str = Common::any_cast<const char*>(m_AnyMap[5]);
        std::string _strs = Common::any_cast<std::string>(m_AnyMap[6]);
    }
    catch(Common::bad_any_cast& e)
    {
        std::cout << "Test AnyTest FAILED. Explanation:" <<e.what() << std::endl;
    }

    std::cout << "Test AnyTest FINISHED OK\n";

    return (EXIT_SUCCESS);
}

