/*
 *  CTiro.cpp
 *
 *  Created by Isabel Manssour and Márcio Pinho on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CTIRO_H
#define CTIRO_H

class CTiro {
    public:
        CTiro(float x1=0, float y1=0);
        void setX(float x1) { x = x1; }
        void setY(float y1) { y = y1; }
        float getX() { return x; }
        float getY() { return y; }
    private:
        float x;
        float y;
};

#endif // CTIRO_H
