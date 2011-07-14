/*
 *  TextureManager.cpp
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "TextureManager.h"
#include <iostream>

using namespace std;

TextureManager TextureManager::m_TextureManager;

TextureManager::TextureManager()
{
    defaultImageDir = "data";
}

TextureManager::~TextureManager()
{
    //dtor
    //cout << "~TextureManager: " << imgs.size() << endl;
    map<string,GLuint>::iterator it = imgs.begin();
    while(it != imgs.end())
    {
        GLuint tex = (*it).second;
        cout << tex << endl;
        glDeleteTextures(1, &tex);
        it++;
    }
}

GLuint TextureManager::findTexture(const char* nomeArq)
{
    GLuint tex;
    if(imgs.find(nomeArq) == imgs.end()) {
        cout << "New texture: " << nomeArq << endl;
        // New texture, generate texture id
        glGenTextures(1, &tex);
        imgs[nomeArq] = tex;
        return -1;
    }
    // Return texture id
    cout << "Existing texture: " << imgs[nomeArq] << endl;
    return imgs[nomeArq];
}

void TextureManager::setDefaultImageDir(char* dir)
{
    defaultImageDir = dir;
}

void TextureManager::releaseTexture(char* nomeArq)
{
    if(imgs.find(nomeArq) != imgs.end())
    {
        GLuint tex = imgs[nomeArq];
        imgs.erase(nomeArq);
        glDeleteTextures(1, &tex);
    }
}
