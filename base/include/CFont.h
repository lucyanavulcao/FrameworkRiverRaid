/*
 *  CFont.h
 *  Font management class
 *
 *  Created by Alberto Dietrich on 04/11.
 *  Modified by Marcelo Cohen on 04/11.
 *  Modified by Isabem Manssour on 05/11.
 *
 */

#ifndef CFONT_H
#define CFONT_H

#include "CMultiImage.h"
#include <cstring>

class CFont : public CMultiImage
{
	private:

		int charHeight, charWidth;
		char textForDrawing[100];
		int selectedType;

    public:
        CFont();
        virtual ~CFont();
        bool loadFont(const char nomeArq[], int imgwidth, int imgHeight);
        void draw();
        void draw(const char text[], int type=CFONT_BOTTOM | CFONT_LEFT);
        void draw(float x, float y, const char text[], int type=CFONT_BOTTOM | CFONT_LEFT);
        void setType(int type=CFONT_BOTTOM | CFONT_LEFT);
        void setText(const char text[]);
        enum CFONT_ALIGN
        {
            CFONT_TOP = 1,
            CFONT_BOTTOM = 2,
            CFONT_LEFT = 4,
            CFONT_RIGHT = 8,
            CFONT_VCENTER = 16,
            CFONT_HCENTER = 32
        };

};

#endif // CFONT_H
