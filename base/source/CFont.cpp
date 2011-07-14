/*
 *  CFont.h
 *  Font management class
 *
 *  Created by Alberto Dietrich on 04/11.
 *  Modified by Marcelo Cohen on 04/11.
 *  Modified by Isabel Manssour on 05/11.
 *
 */

#include "CFont.h"

CFont::CFont()
{
    //ctor
    strcpy(textForDrawing," ");
    selectedType = CFONT_BOTTOM | CFONT_LEFT;
}

CFont::~CFont()
{
    //dtor
}


/** @brief loadFont
  *
  * @todo: document this function
  */
bool CFont::loadFont(const char nomeArq[], int imgWidth, int imgHeight)
{

	charHeight = imgHeight / 16;
	charWidth = imgWidth / 16;
	return CMultiImage::loadMultiImage (nomeArq, charWidth, charHeight, 0, 0, 0, 0, 16, 16, 256);

}

void CFont::draw()
{
    draw(textForDrawing, selectedType);
}

/** @brief draw
  *
  * @todo: document this function
  */
void CFont::draw(float x, float y, const char text[], int type)
{
    float oldX = getX();
    float oldY = getY();
    setX(x);
    setY(y);
    draw(text, type);
    setX(oldX);
    setY(oldY);
}

/** @brief draw
  *
  * @todo: document this function
  */
void CFont::draw(const char text[], int type)
{

	int i = 0;

	while (text[i] != '\0') i++;

	int xTrans = 0;

	// Verifica se o bit de desenhar
	// pela direita esta ligado
	if (type & CFONT_RIGHT)
	{

		xTrans -= (charWidth * i);

	}
	// Se no verifica se desenha
	// pelo meio
	else if (type & CFONT_HCENTER)
	{

		xTrans -= ((charWidth * i) / 2);

	}
	// Se no, desenha normal
	// pela esquerda sem transladar

	int yTrans = 0;

	// Verifica se o bit de desenhar
	// por cima esta ligado
	if (type & CFONT_TOP)
	{

		yTrans -= charHeight;

	}
	// Se no verifica se desenha
	// pelo meio
	else if (type & CFONT_VCENTER)
	{

		yTrans -= (charHeight / 2);

	}
	// Se no, desenha normal
	// por baixo sem transladar

//	glColor3f (1.0f, 1.0f, 1.0f);

    /*
	if(glIsEnabled(GL_TEXTURE_2D))
       glDisable(GL_TEXTURE_2D);

	glBegin (GL_QUADS);
	glVertex2f (x - 2, y - 2);
	glVertex2f (x + 2, y - 2);
	glVertex2f (x + 2, y + 2);
	glVertex2f (x - 2, y + 2);
	glEnd ();
    */

	glColor3f (1.0f, 1.0f, 1.0f);
	glPushMatrix ();
	glTranslatef (xTrans, yTrans, 0.0f);
    //glRotatef(rotation,0,0,1);
    //glScalef(scale,scale,1);
	i = 0;

	float firstX = getX ();
    float currentX = firstX;
    float deltaX = charWidth;

	while (text[i] != '\0')
	{
		setX (currentX);
		drawFrame (text[i]);
        currentX += deltaX;
		i++;
	}

	setX (firstX);
	glPopMatrix ();
}

void CFont::setType(int type)
{
        selectedType = type;
}

void CFont::setText(const char text[])
{
    strcpy(textForDrawing,text);
}
