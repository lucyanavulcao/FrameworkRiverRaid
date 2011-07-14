/*
 *  CMultiImage.h
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CMULTIIMAGE_H
#define CMULTIIMAGE_H

#include <vector>
#include "CImage.h"
#include "TexRect.h"

class CMultiImage : public CImage
{
    public:
        CMultiImage();
        virtual ~CMultiImage();
        bool loadMultiImage(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                int column, int row, int total);
        virtual void drawFrame(int frame);
        void setMirror(bool mirror);
        int isMirror() { return mirror; }
    protected:
        bool mirror;                // true = mirror frames (x)
        int totalFrames;            // total frames
        std::vector<TexRect> uvs;   // texcoords for each frame
};

#endif // CMULTIIMAGE_H
