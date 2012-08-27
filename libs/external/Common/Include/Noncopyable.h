/* 
 * File:   Noncopyable.h
 * Author: void
 *
 * Created on August 20, 2012, 11:17 PM
 */

#ifndef NONCOPYABLE_H
#    define	NONCOPYABLE_H

namespace Common
{
    class Noncopyable
    {
    public:
        Noncopyable() = default;
        Noncopyable(Noncopyable const &) = delete;
        Noncopyable & operator=(Noncopyable const &) = delete;
    } ;
}

#endif	/* NONCOPYABLE_H */

