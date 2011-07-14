#ifndef TMXLOADER_H
#define TMXLOADER_H

#include "../CMultiImage.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "base64.h"
#include "tinyxml.h"

using namespace std;

class TMXLoader : public TiXmlVisitor
{
    public:
        TMXLoader();
        virtual ~TMXLoader();

        void cleanup();

        virtual bool 	VisitEnter  (const TiXmlDocument  &);
        virtual bool 	VisitExit (const TiXmlDocument &);
        virtual bool 	VisitEnter (const TiXmlElement &, const TiXmlAttribute *);
        virtual bool 	VisitExit (const TiXmlElement &);
        virtual bool 	Visit (const TiXmlDeclaration &);
        virtual bool 	Visit (const TiXmlText &);
        virtual bool 	Visit (const TiXmlComment &);
        virtual bool 	Visit (const TiXmlUnknown &);

        bool loadMap(char* mapName);

        CMultiImage* getTilesetImage() { return img_tileset; }
        //SDL_Surface* getMapImage();

        int getTileWidth() { return m_TileWidth; }
        int getTileHeight() { return m_TileWidth; }
        int getTileSpacing() { return m_TileSpacing; }
        int getTilesetMargin() { return m_TilesetMargin; }
        int getNumMapColumns() { return m_NumMapColumns; }
        int getNumMapRows() { return m_NumMapRows; }

        void draw();
    
        // Return center of cell in world units
        void getCenter(int col, int row, float& x, float& y);
        // Return specific cell
        int getCell(int col, int row);
        int getCellFromWorld(float x, float y);
        // Convert from world to cell coords
        void convertWorldToCell(float x, float y, int&col, int& row);

    protected:

    private:
        int m_TileWidth;
        int m_TileHeight;
        int m_TileSpacing;
        int m_TilesetMargin;
        int m_NumMapColumns;
        int m_NumMapRows;

        int m_TilesetRows;
        int m_TilesetCols;

        CMultiImage* img_tileset;

        vector< vector< int > > m_LayerData;

        void decode_and_store_map_data( string encoded_data );
        //TiXmlDocument *doc;

};

#endif // TMXLOADER_H
