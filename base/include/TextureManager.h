/*
 *  TextureManager.h
 *  manages textures to avoid loading the same image twice
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL_opengl.h>
#include <map>
#include <string>


class TextureManager
{
    private:

        static TextureManager m_TextureManager;
        std::map<std::string, GLuint> imgs;
        std::string defaultImageDir;            // base dir to load images from

    public:

        virtual ~TextureManager();
        GLuint findTexture(const char* nomeArq);
        void setDefaultImageDir(char* dir);
        void releaseTexture(char* nomeArq);
        static TextureManager * getInstance ()
        {
            return & m_TextureManager;
        }

    protected:
    
        TextureManager ();
};

#endif
