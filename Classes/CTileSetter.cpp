//
//  CTileSetter.cpp
//  iGaia
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTileSetter.h"

CTileSetter::STileTexCoords** CTileSetter::m_pTilesTable = NULL;
const int CTileSetter::k_TILES_TYPE_COUNT = 16;
const int CTileSetter::k_TILESETS_TYPE_COUNT = 16;
const float CTileSetter::k_TILE_TEXTURE_OFFSET = 0.0001f;

CTileSetter::CTileSetter()
{
    if(m_pTilesTable == NULL)
    {
        m_pTilesTable = new CTileSetter::STileTexCoords*[k_TILESETS_TYPE_COUNT * 2];
        for(unsigned int i = 0; i < k_TILESETS_TYPE_COUNT * 2; ++i)
        {
            m_pTilesTable[i] = new CTileSetter::STileTexCoords[k_TILES_TYPE_COUNT];
        }
        CreateTileTable();
    }
}

CTileSetter::~CTileSetter()
{

}

void CTileSetter::CreateTileTable()
{
	float fTexCoordOffsetL = 0.0f;
	float fTexCoordOffsetR = 0.0f;
	float fTexCoordOffsetU = 0.0f;
	float fTexCoordOffsetD = 0.0f;

	unsigned int iTilesetTypeIndex = 0;
	for( unsigned int i = 0; i < k_TILESETS_TYPE_COUNT; ++i)
	{
		fTexCoordOffsetU = 1.0f / k_TILESETS_TYPE_COUNT * i + k_TILE_TEXTURE_OFFSET;
		fTexCoordOffsetD = 1.0f / k_TILESETS_TYPE_COUNT * ( i + 1 ) - k_TILE_TEXTURE_OFFSET;
		
		for( unsigned int j = 0; j < k_TILES_TYPE_COUNT; j++)
		{
			fTexCoordOffsetL = 1.0f / k_TILES_TYPE_COUNT * j + k_TILE_TEXTURE_OFFSET;
			fTexCoordOffsetR = 1.0f / k_TILES_TYPE_COUNT * ( j + 1 ) - k_TILE_TEXTURE_OFFSET;

			m_pTilesTable[iTilesetTypeIndex][j].m_vTexCoord[0] =  glm::vec2(fTexCoordOffsetR,fTexCoordOffsetD);
			m_pTilesTable[iTilesetTypeIndex][j].m_vTexCoord[1] =  glm::vec2(fTexCoordOffsetR,fTexCoordOffsetU);
			m_pTilesTable[iTilesetTypeIndex][j].m_vTexCoord[2] =  glm::vec2(fTexCoordOffsetL,fTexCoordOffsetU);
			m_pTilesTable[iTilesetTypeIndex][j].m_vTexCoord[3] =  glm::vec2(fTexCoordOffsetL,fTexCoordOffsetD);
		}
		iTilesetTypeIndex++;
		unsigned int iTileIndex = 0;
		for( int j = (k_TILES_TYPE_COUNT - 1); j >= 0; j--)
		{
			fTexCoordOffsetR = 1.0f / k_TILES_TYPE_COUNT * j + k_TILE_TEXTURE_OFFSET;
			fTexCoordOffsetL = 1.0f / k_TILES_TYPE_COUNT * ( j + 1 ) - k_TILE_TEXTURE_OFFSET;
			
			if( j == 5  || j == 10 )
			{
				float fTexCoordTemp = fTexCoordOffsetR;
				fTexCoordOffsetR = fTexCoordOffsetL;
				fTexCoordOffsetL = fTexCoordTemp;
			}

			m_pTilesTable[iTilesetTypeIndex][iTileIndex].m_vTexCoord[0] = glm::vec2(fTexCoordOffsetR,fTexCoordOffsetD);
			m_pTilesTable[iTilesetTypeIndex][iTileIndex].m_vTexCoord[1] = glm::vec2(fTexCoordOffsetR,fTexCoordOffsetU);
			m_pTilesTable[iTilesetTypeIndex][iTileIndex].m_vTexCoord[2] = glm::vec2(fTexCoordOffsetL,fTexCoordOffsetU);
			m_pTilesTable[iTilesetTypeIndex][iTileIndex].m_vTexCoord[3] = glm::vec2(fTexCoordOffsetL,fTexCoordOffsetD);
			iTileIndex++;
		}
		iTilesetTypeIndex++;
	}
}

void CTileSetter::Load_SourceData(const std::string& _sName, int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;
    m_pSource = new unsigned char[m_iWidth * m_iHeight]; 
    memset(m_pSource, 0x0, sizeof(unsigned char) * m_iWidth * m_iHeight);
}

void CTileSetter::Create_TexCoordData(void)
{
    m_lEditCacheData.clear();
    m_pData = new CTileSetter::STileTexCoords[m_iWidth * m_iHeight];
    memset(m_pData, 0x0, sizeof(CTileSetter::STileTexCoords) * m_iWidth * m_iHeight);
    m_pTempData = new CTileSetter::STileTableValue[m_iWidth * m_iHeight];
    memset(m_pTempData, 0xF, sizeof(CTileSetter::STileTableValue) * m_iWidth * m_iHeight);
    for(int i = 0; i < m_iWidth; ++i)
    {
		for(int j = 0; j < m_iHeight; ++j)
		{
            if( i == 0 || j == 0 || i == (m_iWidth - 1) || j == (m_iHeight - 1))
            {
                Set_Tile(i, j, LEVEL_03);
            }
            else
            {
                Set_Tile(i, j, LEVEL_01);
            }
        }
    }
    CreateTileMap();
}

void CTileSetter::Edit(int _iX, int _iY, CTileSetter::E_TILE_LEVEL _eLevel)
{
    m_lEditCacheData.clear();
    
    for(int i = 0; i < 2; ++i)
    {
        Set_Tile(_iX, _iY, _eLevel);
    }
    CreateTileMap();
}

void CTileSetter::Set_Tile(int _iX, int _iY, CTileSetter::E_TILE_LEVEL _eLevel)
{
    m_pSource[_iX + _iY * m_iHeight] = _eLevel;
	Set_Tileset(_iX, _iY, _eLevel);
	for(char indexLevel_01 = 1; indexLevel_01 < LEVEL_MAX; indexLevel_01++)
	{
		_iX--;
		_iY--;
		for(char indexLevel_02 = 0; indexLevel_02 < indexLevel_01 * 2; indexLevel_02++)
		{
			if(_iX >= 0 && _iX < m_iWidth && _iY >= 0 && _iY < m_iHeight)
			{
				char iCurrentLevel = static_cast<unsigned char>(m_pSource[_iX + _iY * m_iHeight]);
				if(iCurrentLevel > _eLevel)
				{
					char iIncLevel = indexLevel_01 + _eLevel;
					if(iCurrentLevel > iIncLevel && iIncLevel < LEVEL_MAX)
						m_pSource[_iX + _iY * m_iHeight] = iIncLevel;
				}
				if(iCurrentLevel < _eLevel)
				{
					char iDecLevel = _eLevel - indexLevel_01;
					if(iCurrentLevel < iDecLevel && iDecLevel >-1 )
						m_pSource[_iX + _iY * m_iHeight] = iDecLevel;
				}
				Set_Tileset(_iX, _iY, static_cast<CTileSetter::E_TILE_LEVEL>(iCurrentLevel));		
			}_iX++;
		}
		for(char indexLevel_02 = 0; indexLevel_02 < indexLevel_01 * 2; indexLevel_02++)
		{
			if(_iX >= 0 && _iX < m_iWidth && _iY >= 0 && _iY < m_iHeight)
			{
				char iCurrentLevel = m_pSource[_iX + _iY * m_iHeight];
				if(iCurrentLevel > _eLevel)
				{
					char iIncLevel = indexLevel_01 + _eLevel;
					if( iCurrentLevel > iIncLevel && iIncLevel < LEVEL_MAX)
						m_pSource[_iX + _iY * m_iHeight] = iIncLevel;
				}
				if(iCurrentLevel < _eLevel)
				{
					char iDecLevel = _eLevel - indexLevel_01;
					if( iCurrentLevel < iDecLevel && iDecLevel > -1)
						m_pSource[_iX + _iY * m_iHeight] = iDecLevel;
				}
				Set_Tileset(_iX, _iY, static_cast<CTileSetter::E_TILE_LEVEL>(iCurrentLevel));
			}_iY++;
		}
		for(char indexLevel_02 = 0; indexLevel_02 < indexLevel_01 * 2; indexLevel_02++)
		{
			if(_iX >= 0 && _iX < m_iWidth && _iY >= 0 && _iY < m_iHeight)
			{
				char iCurrentLevel = m_pSource[_iX + _iY * m_iHeight];
				if(iCurrentLevel > _eLevel)
				{
					char iIncLevel = indexLevel_01 + _eLevel;
					if( iCurrentLevel > iIncLevel && iIncLevel < LEVEL_MAX)
						m_pSource[_iX + _iY * m_iHeight] = iIncLevel;
				}
				if(iCurrentLevel < _eLevel)
				{
					char iDecLevel = _eLevel - indexLevel_01;
					if( iCurrentLevel < iDecLevel && iDecLevel > -1)
						m_pSource[_iX + _iY * m_iHeight] = iDecLevel;
				}
				Set_Tileset(_iX, _iY, static_cast<CTileSetter::E_TILE_LEVEL>(iCurrentLevel));  
			}_iX--;
		}
        for(char indexLevel_02 = 0; indexLevel_02 < indexLevel_01 * 2; indexLevel_02++)
		{
			if(_iX >= 0 && _iX < m_iWidth && _iY >= 0 && _iY < m_iHeight)
			{
				char iCurrentLevel = m_pSource[_iX + _iY * m_iHeight];
				if(iCurrentLevel > _eLevel)
				{
					char iIncLevel = indexLevel_01 + _eLevel;
					if( iCurrentLevel > iIncLevel && iIncLevel < LEVEL_MAX)
						m_pSource[_iX + _iY * m_iHeight] = iIncLevel;
				}
				if(iCurrentLevel < _eLevel)
				{
					char iDecLevel = _eLevel - indexLevel_01;
					if( iCurrentLevel < iDecLevel && iDecLevel > -1)
						m_pSource[_iX + _iY * m_iHeight] = iDecLevel;
				}
				Set_Tileset(_iX, _iY, static_cast<CTileSetter::E_TILE_LEVEL>(iCurrentLevel));
			}_iY--;
		}
	}
}

void CTileSetter::Set_Tileset(int _iX, int _iY, CTileSetter::E_TILE_LEVEL _eLevel)
{
    char tile_00 = m_pSource[_iX       + (_iY - 1 ) * m_iHeight];
	char tile_01 = m_pSource[(_iX + 1) + ( _iY - 1 ) * m_iHeight];
	char tile_02 = m_pSource[(_iX + 1) + _iY * m_iHeight];
	char tile_03 = m_pSource[(_iX + 1) + (_iY + 1) * m_iHeight];
	char tile_04 = m_pSource[_iX       + (_iY + 1) * m_iHeight];
	char tile_05 = m_pSource[(_iX - 1) + (_iY + 1) * m_iHeight];
	char tile_06 = m_pSource[(_iX - 1) + _iY * m_iHeight];
	char tile_07 = m_pSource[(_iX - 1) + (_iY - 1) * m_iHeight];
    
	if(tile_00!=_eLevel&&tile_01!=_eLevel&&tile_02!=_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_RD);
	if(tile_02!=_eLevel&&tile_03!=_eLevel&&tile_04!=_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY    ,_eLevel,T_RU);
	if(tile_04!=_eLevel&&tile_05!=_eLevel&&tile_06!=_eLevel)if(tile_04<_eLevel)Set_Tile(_iX - 1,_iY    ,_eLevel,T_LU);
	if(tile_06!=_eLevel&&tile_07!=_eLevel&&tile_00!=_eLevel)if(tile_06<_eLevel)Set_Tile(_iX - 1,_iY - 1,_eLevel,T_LD);
	//------------------------------------2
	if(tile_00!=_eLevel&&tile_01!=_eLevel&&tile_02==_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_D);
	if(tile_02==_eLevel&&tile_03!=_eLevel&&tile_04!=_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY,    _eLevel,T_U);
	if(tile_04!=_eLevel&&tile_05!=_eLevel&&tile_06==_eLevel)if(tile_04<_eLevel)Set_Tile(_iX-1,  _iY,    _eLevel,T_U);
	if(tile_06==_eLevel&&tile_07!=_eLevel&&tile_00!=_eLevel)if(tile_06<_eLevel)Set_Tile(_iX-1,  _iY - 1,_eLevel,T_D);
	//------------------------------------3
	if(tile_00==_eLevel&&tile_01!=_eLevel&&tile_02!=_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_R);
	if(tile_02!=_eLevel&&tile_03!=_eLevel&&tile_04==_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY,    _eLevel,T_R);
	if(tile_04==_eLevel&&tile_05!=_eLevel&&tile_06!=_eLevel)if(tile_04<_eLevel)Set_Tile(_iX-1,  _iY,    _eLevel,T_L);
	if(tile_06!=_eLevel&&tile_07!=_eLevel&&tile_00==_eLevel)if(tile_06<_eLevel)Set_Tile(_iX-1,  _iY - 1,_eLevel,T_L);
	//------------------------------------4
	if(tile_00!=_eLevel&&tile_01==_eLevel&&tile_02!=_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_DIAG_01);
	if(tile_02!=_eLevel&&tile_03==_eLevel&&tile_04!=_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY,    _eLevel,T_DIAG_02);
	if(tile_04!=_eLevel&&tile_05==_eLevel&&tile_06!=_eLevel)if(tile_04<_eLevel)Set_Tile(_iX-1,  _iY,    _eLevel,T_DIAG_01);
	if(tile_06!=_eLevel&&tile_07==_eLevel&&tile_00!=_eLevel)if(tile_06<_eLevel)Set_Tile(_iX-1,  _iY - 1,_eLevel,T_DIAG_02);
	//------------------------------------5
	if(tile_00!=_eLevel&&tile_01==_eLevel&&tile_02==_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_LD_EXT);
	if(tile_02!=_eLevel&&tile_03==_eLevel&&tile_04==_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY,    _eLevel,T_RD_EXT);
	if(tile_04!=_eLevel&&tile_05==_eLevel&&tile_06==_eLevel)if(tile_04<_eLevel)Set_Tile(_iX-1,  _iY,    _eLevel,T_RU_EXT);
	if(tile_06!=_eLevel&&tile_07==_eLevel&&tile_00==_eLevel)if(tile_06<_eLevel)Set_Tile(_iX-1,  _iY - 1,_eLevel,T_LU_EXT);
	//------------------------------------6
	if(tile_00==_eLevel&&tile_01==_eLevel&&tile_02!=_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_RU_EXT);
	if(tile_02==_eLevel&&tile_03==_eLevel&&tile_04!=_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY,    _eLevel,T_LU_EXT);
	if(tile_04==_eLevel&&tile_05==_eLevel&&tile_06!=_eLevel)if(tile_04<_eLevel)Set_Tile(_iX-1,  _iY,    _eLevel,T_LD_EXT);
	if(tile_06==_eLevel&&tile_07==_eLevel&&tile_00!=_eLevel)if(tile_06<_eLevel)Set_Tile(_iX-1,  _iY - 1,_eLevel,T_RD_EXT);
	//------------------------------------7
	if(tile_00==_eLevel&&tile_01!=_eLevel&&tile_02==_eLevel)if(tile_00<_eLevel)Set_Tile(_iX,    _iY - 1,_eLevel,T_RD_EXT);
	if(tile_02==_eLevel&&tile_03!=_eLevel&&tile_04==_eLevel)if(tile_02<_eLevel)Set_Tile(_iX,    _iY,    _eLevel,T_RU_EXT);
	if(tile_04==_eLevel&&tile_05!=_eLevel&&tile_06==_eLevel)if(tile_04<_eLevel)Set_Tile(_iX-1,  _iY,    _eLevel,T_LU_EXT);
	if(tile_06==_eLevel&&tile_07!=_eLevel&&tile_00==_eLevel)if(tile_06<_eLevel)Set_Tile(_iX-1,  _iY - 1,_eLevel,T_LD_EXT);
	//------------------------------------
    
	if(tile_00==_eLevel&&tile_01==_eLevel&&tile_02==_eLevel)Set_Tile(_iX,     _iY - 1,_eLevel,T_C_02);
	if(tile_02==_eLevel&&tile_03==_eLevel&&tile_04==_eLevel)Set_Tile(_iX,     _iY,    _eLevel,T_C_02);
	if(tile_04==_eLevel&&tile_05==_eLevel&&tile_06==_eLevel)Set_Tile(_iX - 1, _iY,    _eLevel,T_C_02);
	if(tile_06==_eLevel&&tile_07==_eLevel&&tile_00==_eLevel)Set_Tile(_iX - 1, _iY - 1,_eLevel,T_C_02);
}

void CTileSetter::Set_Tile(int _iX, int _iY, E_TILE_LEVEL _eLevel, E_TILE_NODE _eNode)
{
    int iIndex = _iX + _iY * m_iHeight;
    if(iIndex < 0)
    {
        return;
    }
    if(m_pTempData[iIndex].m_iTileType != _eNode || m_pTempData[iIndex].m_iTilesetType != _eLevel)
    {
        STileIndex tIndex;
        tIndex.m_iTileIndex = _iY + _iX * m_iWidth;
        tIndex.m_iTexCoordIndex = iIndex;
        m_lEditCacheData.push_back(tIndex);
    }
    
    m_pTempData[iIndex].m_iTileType = _eNode;
	m_pTempData[iIndex].m_iTilesetType = _eLevel;
}

void CTileSetter::CreateTileMap()
{
    for(int i = 0; i < m_lEditCacheData.size(); ++i)
    {
		int iIndex = m_lEditCacheData[i].m_iTexCoordIndex;
        for(int k = 0; k < 4; ++k)
        {
            char iTilesetIndex = m_pTempData[iIndex].m_iTilesetType;
            char iTileNodeIndex = m_pTempData[iIndex].m_iTileType;
            m_pData[iIndex].m_vTexCoord[k] = m_pTilesTable[iTilesetIndex][iTileNodeIndex].m_vTexCoord[k];
        }
    }
}

