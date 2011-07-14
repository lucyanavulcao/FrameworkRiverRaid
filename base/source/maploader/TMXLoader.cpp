#include "TMXLoader.h"
#include <iomanip>
#include <cmath>

using namespace std;

TMXLoader::TMXLoader()
{
    img_tileset = new CMultiImage();
}

TMXLoader::~TMXLoader()
{
    //dtor
}

void TMXLoader::cleanup()
{
    //Free the image
    delete img_tileset;
}

bool 	TMXLoader::VisitEnter  (const TiXmlDocument  &doc)
{
    return true; //TODO: for performance, we may not want to return true for each of these callbacks for the visitor pattern.
}

bool 	TMXLoader::VisitExit (const TiXmlDocument &doc)
{
    return true;
}

bool 	TMXLoader::VisitEnter (const TiXmlElement &elem, const TiXmlAttribute *attrib)
{
    cout << ">>>" << elem.Value() << endl;
    if (string("map") == elem.Value()) {
        elem.Attribute("width", &m_NumMapColumns);
        elem.Attribute("height", &m_NumMapRows);

        //elem.Attribute("tileheight");
        //elem.Attribute("tilewidth");

        //TODO: get width and height, and tilewidth and tileheight
        //m_layer_width =

    }
    else if (string("tileset") == elem.Value()) {

        // Need a new class called Tileset

        elem.Attribute("tilewidth", & m_TileWidth);
        elem.Attribute("tileheight", &m_TileHeight);
        elem.Attribute("spacing", &m_TileSpacing);
        elem.Attribute("margin", &m_TilesetMargin);

        //TODO: get spacing and margin
    }
    else if (string("image") == elem.Value()) {
        //string attrib = attrib.ValueStr();
        string attrib = elem.Attribute("source");
        attrib = "data/maps/"+attrib;

        int img_width, img_height;
        elem.Attribute("width", &img_width);
        elem.Attribute("height", &img_height);

        m_TilesetRows = img_height / (m_TileHeight+m_TileSpacing);
        m_TilesetCols = img_width  / (m_TileWidth +m_TileSpacing);

        cout << "tileset: " << m_TilesetRows << " x " << m_TilesetCols << endl;
        cout << "spacing: " << m_TileSpacing << endl;
        img_tileset->loadMultiImage((char*)attrib.c_str(), m_TileWidth, m_TileHeight, m_TileSpacing,
            m_TileSpacing, m_TilesetMargin,m_TilesetMargin, m_TilesetCols, m_TilesetRows, m_TilesetCols*m_TilesetRows);
    }
    else if (string("layer") == elem.Value()) {
        // We don't need to use layer width and height yet.
        //elem.Attribute("name");
        //elem.Attribute("width");
        //elem.Attribute("height");
    }
    else if (string("data") == elem.Value()) {
        const char* text = elem.GetText();
        decode_and_store_map_data( text );
    }

    return true;
}

 bool 	TMXLoader::VisitExit (const TiXmlElement &elem)
{
    return true;
}

 bool 	TMXLoader::Visit (const TiXmlDeclaration &dec)
{
    return true;
}

 bool 	TMXLoader::Visit (const TiXmlText &text)
{
    return true;
}

 bool 	TMXLoader::Visit (const TiXmlComment &comment)
{
    return true;
}

 bool 	TMXLoader::Visit (const TiXmlUnknown &unknown)
{
    return true;
}

bool TMXLoader::loadMap(char* mapName)
{
    TiXmlDocument doc(mapName);

    if ( ! doc.LoadFile() ) {
		return false;
	}

    //TiXmlElement* elem = doc.RootElement();

    doc.Accept(this);

    return true;
}

void TMXLoader::decode_and_store_map_data( string encoded_data )
{
    vector< int > layerDataRow( getNumMapColumns() );
    int m_LayerRow = 0;
    int m_LayerCol = 0;

    vector<int> unencoded_data = base64_decode(encoded_data);

    for (int i = 0; i < getNumMapRows(); i++)
    {
        m_LayerData.push_back( layerDataRow );
    }

    for (int i = 0; i < unencoded_data.size(); i += 4)
    {
        // Get the grid ID

        int a = unencoded_data[i];
        int b = unencoded_data[i + 1];
        int c = unencoded_data[i + 2];
        int d = unencoded_data[i + 3];

        int gid = a | b << 8 | c << 16 | d << 24;

        m_LayerData[m_LayerRow][m_LayerCol] = gid;

        if ((i + 4) % ( getNumMapColumns() * 4) == 0) {
            m_LayerRow++;
            m_LayerCol = 0;
        }
        else {
            m_LayerCol++;
        }
    }

    // DEBUG: output map to console
    for (int row = 0; row < m_NumMapRows; row++)
    {
        for (int col = 0; col < m_NumMapColumns; col++)
        {
           cout << setw(4) << m_LayerData[row][col];
        }
        cout << endl;
    }
}

void TMXLoader::draw()
{
    //cout << "TMXLoader::draw " << getNumMapRows() << " x " << getNumMapColumns() << endl;
    for (int row = 0; row < getNumMapRows(); row++)
    {
        for (int col = 0; col < getNumMapColumns(); col++)
        {
            int gid = m_LayerData[row][col];

            if (gid == 0)
                continue;

            //cout << "\nGID is " << gid;

            int tileset_col;
            int tileset_row;

            gid--; // convert to something we can use with the 0 based system.

            tileset_col = gid % m_TilesetCols;
            tileset_row = gid / m_TilesetCols;

            int tileNum = tileset_row*m_TilesetCols + tileset_col;

            img_tileset->setPosition(col * getTileWidth(), row * getTileHeight());
            img_tileset->drawFrame(tileNum);
            /*
            srcrect.x = getTilesetMargin() + (getTileSpacing() + 32) * tileset_col;
            srcrect.y = getTilesetMargin() + (getTileSpacing() + 32) * tileset_row;
            srcrect.w = getTileWidth();
            srcrect.h = getTileHeight();

            dstrect.x = col * getTileWidth();
            dstrect.y = row * getTileHeight();
            dstrect.w = getTileWidth();
            dstrect.h = getTileHeight();

//            SDL_BlitSurface(img_tileset, &srcrect, img_map, &dstrect);
*/
        }
    }
}

void TMXLoader::getCenter(int col, int row, float& x, float& y)
{
    x = col * m_TileWidth;// + m_TileWidth/2;
    y = row * m_TileHeight;// + m_TileHeight/2;
}

int TMXLoader::getCell(int col, int row)
{
    int gid = m_LayerData[row][col];

    if (gid == 0)
        return -1;

    int tileset_col;
    int tileset_row;

    gid--; // convert to something we can use with the 0 based system.

    tileset_col = gid % m_TilesetCols;
    tileset_row = gid / m_TilesetCols;

    return tileset_row*m_TilesetCols + tileset_col;
}

int TMXLoader::getCellFromWorld(float x, float y)
{
    int col, row;
    convertWorldToCell(x,y,col,row);
    return getCell(col, row);
}

void TMXLoader::convertWorldToCell(float x, float y, int&col, int& row)
{
    col = floor(x / m_TileWidth);
    row = floor(y / m_TileHeight);
}

/*
SDL_Surface* TMXLoader::getMapImage()
{
    return img_map;
}
*/
