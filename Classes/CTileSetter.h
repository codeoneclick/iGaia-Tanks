//
//  CTileSetter.h
//  iGaia
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CTileSetter_h
#define iGaia_CTileSetter_h
#include <glm/glm.hpp>
#include "stdlib.h"
#include <vector>

class CTileSetter
{
public:
    enum E_TILE_LEVEL { LEVEL_01 = 0, LEVEL_02, LEVEL_03, LEVEL_04, LEVEL_05, LEVEL_MAX };
    enum E_TILE_NODE  { T_C_02 = 0, T_LD, T_RD, T_LU, T_RU, T_L, T_D, T_DIAG_01, T_DIAG_02, T_U, T_R, T_RD_EXT, T_LD_EXT, T_RU_EXT, T_LU_EXT, T_C_01 };
    
    struct STileIndex
    {
        int m_iTileIndex;
        int m_iTexCoordIndex;
    };
    
    struct STileTableValue
    {
        char m_iTileType;
        char m_iTilesetType;
    };
    
    struct STileTexCoords
    {
        glm::vec2 m_vTexCoord[4];
    };
    
protected:
    void CreateTileTable(void);
    void CreateTileMap(void);
    
    static const int k_TILES_TYPE_COUNT;
    static const int k_TILESETS_TYPE_COUNT;
    static const float k_TILE_TEXTURE_OFFSET;
    
    static STileTexCoords** m_pTilesTable;
    STileTexCoords* m_pData;
    unsigned char* m_pSource;
    STileTableValue* m_pTempData;
    int m_iWidth;
    int m_iHeight;
    std::vector<STileIndex> m_lEditCacheData;
    
    void Set_Tile(int _iX, int _iY, E_TILE_LEVEL _eLevel);
    void Set_Tile(int _iX, int _iY, E_TILE_LEVEL _eLevel, E_TILE_NODE _eNode);
    void Set_Tileset(int _iX, int _iY, E_TILE_LEVEL _eLevel);

public :
	CTileSetter(void);
	~CTileSetter(void);
    void Set_SourceData(unsigned char* _pSource, int _iWidth, int _iHeight) { m_pSource = _pSource; m_iWidth = _iWidth; m_iHeight = _iHeight; }
    void Load_SourceData(const std::string& _sName, int _iWidth, int _iHeight);
    void Create_TexCoordData(void);
    STileTexCoords* Get_TexCoordData(void) { return m_pData; }
    void Edit(int _iX, int _iY, E_TILE_LEVEL _eLevel);
    std::vector<STileIndex> Get_EditCacheData(void) { return m_lEditCacheData; }
};

#endif
