/*
 *  CParticleSystem.h
 *
 *  Simula um sistema simples de partículas usando o OPENGL.
 *  Refereências:
 *	http://www.swiftless.com/tutorials/opengl/particles.html
 *	http://snipplr.com/view/54306/opengl-particle-system-smoke-stream/
 *
 * 	Criado por Alexandre Ramos Coelho, julho 2011.
 *
 */

#ifndef CPARTICLE_SYSTEM_H
#define CPARTICLE_SYSTEM_H

#include <iostream>
#include <time.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#define	MAX_PARTICLES				50
#define MIN_PARTICLES				10
#define	PARTICLE_DECEL_STEP	.0025	// Mudar o valor desta variável muda completamente o comportamento das partículas
#define	PARTICLE_ACCEL			((((((8 - 5 + 2) * rand()%11) + 5 - 1 + 1) * rand()%11) + 1) * 0.01)
#define PARTICLE_DIR				((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1)
#define PARTICLE_MOV				(((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005)

class CParticleSystem
{
	protected:
		typedef struct {
			float fPosX;	//! Posição X da partícula
			float fPosY;	//! Posição Y da partícula
			float fMovX;	//! Movimento em X da partícula
			float fMovY;	//! Movimento em Y da partícula
			float fDir;
			float fAccel;
			float fDecel;
			float fScale;
			bool bVisible;
		}stParticles;

		GLuint texture;     // texture id for this image
		int m_nCurrentParticle;
		float m_fLimits;
		float m_fX, m_fY;
		float m_fRadius;
		stParticles m_stParticles[MAX_PARTICLES];

		double m_dTimeStarted; 
		double m_dLastUpdate;
		
	public:
		CParticleSystem();
		virtual ~CParticleSystem();
		virtual void draw();
		void moveParticles(int nAmountOfParticles);
		void setStartPos(float fPosX, float fPosY);

};

#endif  // CPARTICLE_SYSTEM_H
