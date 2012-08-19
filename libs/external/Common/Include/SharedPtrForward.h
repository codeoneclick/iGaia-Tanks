/* 
 * File:   SharedPtrForward.h
 * Author: void
 *
 * Created on June 30, 2012, 12:51 AM
 */

#ifndef SHAREDPTRFORWARD_H
#    define	SHAREDPTRFORWARD_H

#define SHARED_PTR_FORWARD(__Class)\
class __Class;\
boost::shared_ptr<__Class> __Class##Ptr;\
boost::shared_ptr<__Class> __Class##ConstPtr;\

#define SHARED_PTR_FORWARD_S(__Class)\
struct __Class;\
boost::shared_ptr<__Class> __Class##Ptr;\
boost::shared_ptr<__Class> __Class##ConstPtr;\

#endif	/* SHAREDPTRFORWARD_H */

