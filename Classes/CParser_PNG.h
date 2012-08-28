/* 
 * File:   CParser_PNG.h
 * Author: void
 *
 * Created on August 18, 2012, 10:45 PM
 */

#ifndef CPARSER_PNG_H
#    define	CPARSER_PNG_H

#include <glm/glm.hpp>
#include "CTexture.h"
#include "IParser.h"
#include <memory>

class CParser_PNG: public IParser
{
public:
    struct SDescription
    {
        GLenum m_glFormat;
        GLenum m_glType;
        int m_uiBPP;
        glm::vec2 m_vSize;
        unsigned int m_uiMIP;
        char* m_pTextureData;
        char* m_pHeaderData;
        bool m_bCompressed;
        unsigned int m_iNumFaces;
    };

private:

    std::unique_ptr<SDescription> m_pSourceData;

public:
    CParser_PNG();
    CParser_PNG(const CParser_PNG& orig);
    virtual ~CParser_PNG();

    void* Get_SourceData(void);
    void Load(const std::string& _sName);
    void Commit(void);
} ;

#endif	/* CPARSER_PNG_H */

