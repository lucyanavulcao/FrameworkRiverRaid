#ifndef _TIXMLPARSINGDATA_H
#define _TIXMLPARSINGDATA_H


#include "tinyxml.h"

class TiXmlParsingData {
  friend class TiXmlDocument;

  public:
    void Stamp(const char * now, TiXmlEncoding encoding);

    inline const TiXmlCursor & Cursor() { return cursor; };


  private:
    // Only used by the document!
    inline TiXmlParsingData(const char * start, int _tabsize, int row, int col) {
    		assert( start );
    		stamp = start;
    		tabsize = _tabsize;
    		cursor.row = row;
    		cursor.col = col;
    	};

    TiXmlCursor cursor;

    const char * stamp;

    int tabsize;

};
#endif
