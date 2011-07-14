/*
 *  CImage.cpp
 *  Handle image loading.
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "CImage.h"
#include "TextureManager.h"

using namespace std;

CImage::CImage() {
	xOffset = 0;
	yOffset = 0;
	xTexOffset = 0; // Mexer aqui dá um shift na imagem com os sprites
	yTexOffset = 0;
	scale = 1;
	rotation = 0;
	x = 0;
	y = 0;
}

bool CImage::loadImage(const char nomeArq[]) {
	SDL_Surface* surf = IMG_Load(nomeArq);
	if (!surf) {
		cout << "Error loading " << nomeArq << endl;
		return false;
	}

	// power of two ?
	if(surf->w & (surf->w-1) != 0) {
		cout << "Warning: " << nomeArq << " width isn't a power of 2!" << endl;
	}

	if(surf->h & (surf->h-1) != 0) {
		cout << "Warning: " << nomeArq << " height isn't a power of 2!" << endl;
	}

	// get the number of channels in the SDL surface
	GLint nOfColors = surf->format->BytesPerPixel;
	GLenum texture_format;

	if (nOfColors == 4) {   // contains an alpha channel
		cout << nomeArq << " has alpha" << endl;
		if (surf->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nOfColors == 3) {   // no alpha channel
		cout << nomeArq << " has no alpha" << endl;
		if (surf->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		cout << "Warning: " << nomeArq << " is not truecolor..  this will probably break" << endl;
		// this error should not go unhandled
	}

	width  = surf->w;
	height = surf->h;

	//
	printf("Carregando imagem %s: [%d,%d]\n", nomeArq, width, height);

	texture = TextureManager::getInstance()->findTexture(nomeArq);

	if(texture == -1) {
		// 2nd time, now we get the texture id
		texture = TextureManager::getInstance()->findTexture(nomeArq);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Set the texture's repeating properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Edit the texture object's image data using the information SDL_Surface gives us

		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surf->w, surf->h, 0,
		              texture_format, GL_UNSIGNED_BYTE, surf->pixels );
	}

	// Finally, free the SDL surface
	SDL_FreeSurface(surf);

	xOffset = width/2;
	yOffset = height/2;

	return true;
}

/** @brief setPosition
  *
  * @todo: document this function
  */
void CImage::setPosition(float x, float y) {
	setX(x);
	setY(y);
}

/** @brief setY
  *
  * @todo: document this function
  */
void CImage::setY(float y) {
	this->y = y;
}

/** @brief setX
  *
  * @todo: document this function
  */
void CImage::setX(float x) {
	this->x = x;
}

/** @brief setRotation
  *
  * @todo: document this function
  */
void CImage::setRotation(float r) {
	this->rotation = r;
}

/** @brief setScale
  *
  * @todo: document this function
  */
void CImage::setScale(float s) {
	this->scale = s;
}

// Funcao que desenha a imagem toda e sera sobrescrita nas subclasses.
void CImage::draw () {
	float u1 = xTexOffset;
	float v1 = yTexOffset;
	float u2 = xTexOffset+1;
	float v2 = yTexOffset+1;

	if(!glIsEnabled(GL_TEXTURE_2D))
		glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texture );

	glPushMatrix();
	{
		glTranslatef(xOffset,yOffset,0);
		glTranslatef(x,y,0);
		glRotatef(rotation, 0, 0, 1);
		glScalef(scale, scale, 1);
		glTranslatef(-xOffset,-yOffset,0);

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

	}
	glPopMatrix();
}

void CImage::setXOffset(float xo) {
	xOffset = xo;
}

void CImage::setYOffset(float yo) {
	yOffset = yo;
}

void CImage::setXTexOffset(float xo) {
	xTexOffset = xo;
}

void CImage::setYTexOffset(float yo) {
	yTexOffset = yo;
}

// Destrutor para limpar a area ocupada pelo bitmap.
// (agora isso Ã© feito por TextureManager)
CImage::~CImage() {
	//glDeleteTextures(1, &texture);
}
