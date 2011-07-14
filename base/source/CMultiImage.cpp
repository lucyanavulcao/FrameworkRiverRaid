/*
 *  CMultiImage.cpp
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include "CMultiImage.h"

using namespace std;

/** @brief CMultiImage
 *
 * @todo: document this function
 */
CMultiImage::CMultiImage()
{

}


/** @brief ~CMultiImage
  *
  * @todo: document this function
  */
CMultiImage::~CMultiImage()
{

}

/** @brief loadMultiImage
  *
  * @todo: document this function
  */
bool CMultiImage::loadMultiImage(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni, int column, int row, int total)
{
    if(!loadImage(nomeArq))
        return false;

    // Verifica se os valores de espaço entre os frames são corretos
	if ( (hSpace<0 || vSpace<0) || (hSpace>width || vSpace>height) )
		return false;

	if ( xIni<0 || yIni<0 )
		return false;

	if ( column<1 || row<1 )
		return false;

    totalFrames = total;

	if (totalFrames < 1)
		return false;

/**/
	int xAux;
	int yAux = yIni;

	for (int i=0; i<row; i++)
	{
	    xAux = xIni;
		for (int j=0; j<column && uvs.size()<totalFrames; j++)
		{
			// Cria um "sub-bitmap" do pai, nas coordenadas especificadas com o tamanho especificado.
			float u1 = (float)xAux/width;
			float v1 = (float)yAux/height;
			float u2 = (float)(xAux+w)/width;
			float v2 = (float)(yAux+h)/height;
			TexRect rect = { u1, v1, u2, v2 };
			//cout << "Rect: " << rect.u1 << "," << rect.v1
            //    << " - " << rect.u2 << "," << rect.v2 << endl;
			uvs.push_back(rect);
			xAux += w + hSpace;
			//xAux--;
		}
		xAux = xIni;
		yAux += h + vSpace;
		//yAux--;
	}
/**/
	width = w;
	height = h;

    xOffset = w/2;
    yOffset = h/2;

    //cout << "CMultiImage::load: " << xOffset << " " << yOffset << endl;
    cout << "CMultiImage::load: total frames = " << totalFrames << endl;

    mirror = false;
    return true;
}

/** @brief draw
  *
  * @todo: document this function
  */
void CMultiImage::drawFrame(int frame)
{
    TexRect& t = uvs[frame];
	float u1 = t.u1 + xTexOffset;
    float v1 = t.v1 + yTexOffset;
    float u2 = t.u2 + xTexOffset;
    float v2 = t.v2 + yTexOffset;

    if(!glIsEnabled(GL_TEXTURE_2D))
       glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture );

    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0);
    glTranslatef(x,y,0);
    glRotatef(rotation, 0, 0, 1);
    float s = scale;
    if(mirror)
        s = -scale;
    glScalef(s, scale, 1);
    glTranslatef(-xOffset, -yOffset, 0);
    glBegin( GL_QUADS );

    //Bottom-left vertex (corner)
    glTexCoord2f( u1, v1 );
    glVertex3f( 0, 0, 0.0f );

    //Bottom-right vertex (corner)
    glTexCoord2f( u2, v1 );
    glVertex3f( width, 0, 0.f );

    //Top-right vertex (corner)
    glTexCoord2f( u2, v2 );
    glVertex3f( width, height, 0.f );

    //Top-left vertex (corner)
    glTexCoord2f( u1, v2 );
    glVertex3f( 0, height, 0.f );
    glEnd();
    glPopMatrix();
}

// Sets the mirroring of frames
// true - horizontally flips frames
void CMultiImage::setMirror(bool mirror)
{
	this->mirror = mirror;
}
