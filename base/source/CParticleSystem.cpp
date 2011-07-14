/*
 *  CParticleSystem.cpp
 *  Simula um sistema simples de partículas.
 *
 * 	Criado por Alexandre Ramos Coelho, julho 2011.
 *
 */

#include "CParticleSystem.h"
#include "TextureManager.h"

using namespace std;

/*****************************************************************************************/
/*
 * @brief		Construtor da classe
 */
CParticleSystem::CParticleSystem() {

	// TODO: adicionar código aqui  
	m_nCurrentParticle = 1;
	m_fLimits = 0.8;
	m_fX = 0;
	m_fY = 0;

	m_bApplyRadius = true;
}

/*****************************************************************************************/
/*
 * @brief		Destrutor da classe
 */
CParticleSystem::~CParticleSystem() {
	//glDeleteTextures(1, &texture);
}

/*****************************************************************************************/
/*
 * @brief		Método draw
 */
void CParticleSystem::draw () {

	double dDiffTime = SDL_GetTicks() - m_dLastUpdate;
	float fColor;

	//if(dDiffTime > 1.5) { // Controla a velocidade de atualização das partículas
		moveParticles(m_nCurrentParticle);

		if(m_nCurrentParticle != MAX_PARTICLES)
			m_nCurrentParticle++;
	//}
	{
		glDisable(GL_TEXTURE_2D); // Necessario quando se deseja desenhar SEM texturas
		glPushMatrix();
		{

			for(int nIdx = 0; nIdx < MAX_PARTICLES; nIdx++) {

				glPointSize(1 * m_stParticles[nIdx].fScale);
				glBegin(GL_POINTS);

				// Cria uma nova cor entre preto e cinza
				fColor = rand() % 10 + 1;
				glColor3f(fColor * .01, fColor *.01, fColor * .01);

				// Posiciona o ponto
				glVertex2f(m_stParticles[nIdx].fPosX, m_stParticles[nIdx].fPosY);

				glEnd();
			}
		}
		glPopMatrix();
		glColor3f(1,1,1);
	}


	m_dLastUpdate = SDL_GetTicks();

}

/*****************************************************************************************/
/*
 * @brief		Move o sistema de partículas, uma parcela de cada vez
 * @param 	nAmountOfParticles	Número de partículas do sistema a serem movidas
 * @return	void
 */
void CParticleSystem::moveParticles(int nAmountOfParticles) {

	float fMyX, fMyY;
	float fDir;

	srand(time(NULL));

	for(int nIdx = 0; nIdx < nAmountOfParticles; nIdx++) {

		fDir = PARTICLE_DIR;

		m_stParticles[nIdx].fPosY += m_stParticles[nIdx].fAccel - m_stParticles[nIdx].fDecel;
		m_stParticles[nIdx].fDecel += PARTICLE_DECEL_STEP;

		m_stParticles[nIdx].fPosX += m_stParticles[nIdx].fMovX;
		m_stParticles[nIdx].fPosY += m_stParticles[nIdx].fMovY;

		m_stParticles[nIdx].fDir += fDir;

		m_stParticles[nIdx].fScale += .05;	

		if(m_stParticles[nIdx].fPosY < (m_fY-m_fRadius)) {

			m_stParticles[nIdx].fPosX = m_fX;
			m_stParticles[nIdx].fPosY = m_fY;
			m_stParticles[nIdx].fDir = 0;
			m_stParticles[nIdx].fAccel = PARTICLE_ACCEL;
			m_stParticles[nIdx].fDecel = PARTICLE_DECEL_STEP;
			m_stParticles[nIdx].fScale = 1.0;
		}

		/*
			 fMyX = rand()%3 + 1;

			 if(fMyX==1 && m_fPosX[nIdx] <= m_fLimits) {

			 int nMyTemp = rand()%100 + 1;
			 int nTemp = rand()%5 + 1;
			 m_fPosX[nIdx] += nTemp * .001;
			 m_fPosY[nIdx] += nMyTemp * .0004;
			 }

			 if(fMyX == 2) {

			 m_fPosX[nIdx] += .00;
			 m_fPosY[nIdx] += .01;
			 }

			 if(fMyX == 3 && m_fPosX[nIdx] >= m_fLimits) {

			 int nMyTemp = rand()%100 + 1;
			 int nTemp = rand()%5 + 1;
			 m_fPosX[nIdx] -= nTemp * .001;
			 m_fPosY[nIdx] += nMyTemp * .0004;
			 }

			 if(m_fPosY[nIdx] >= m_fLimits) {
			 m_fPosX[nIdx] = 0;
			 m_fPosY[nIdx] = 0;
			 }
		 */	
		//	printf("Part. %03d em %3.2f, %3.2f - M %3.3f A %3.3f\n",
		//				nIdx, m_fPosX[nIdx], m_fPosY[nIdx], fMov, fAccel);

		//	 debug
		//printf("[%3d] Mov x %3.2f, y %3.2f, A %3.2f\n",
		//		nIdx, m_stParticles[0].fMovX, m_stParticles[0].fMovY,
		//		m_stParticles[0].fAccel);
	}


}

/*****************************************************************************************/
/*
 * @brief		Configura a posição inicial do emissor de partículas
 * @param		nPosX		Posição X do emissor
 * @param		nPosY		Posição Y do emissor
 * @return	void
 */
void CParticleSystem::setStartPos(float fPosX, float fPosY) {

	srand(time(NULL));
	m_fX = fPosX;
	m_fY = fPosY;
	m_fRadius = 50;

	m_dTimeStarted = SDL_GetTicks();

	// Reseta todas as partículas para a nova posição inicial
	for(int nIdx = 0; nIdx < MAX_PARTICLES; nIdx++) {

		m_stParticles[nIdx].fPosX = m_fX;
		m_stParticles[nIdx].fPosY = m_fY;

		m_stParticles[nIdx].fMovX = PARTICLE_MOV;
		m_stParticles[nIdx].fMovY = PARTICLE_MOV;
		m_stParticles[nIdx].fScale = 1;
		m_stParticles[nIdx].fDir = 0;
		m_stParticles[nIdx].fAccel = PARTICLE_ACCEL;
		m_stParticles[nIdx].fDecel = PARTICLE_DECEL_STEP;
	}

}

/*****************************************************************************************/
/*
 * @brief		Move todas as partículas do sistema em um determinado offset. Útil para scroll
 * @param		nNewX		Offset para a nova posição X na tela
 * @param		nNewY		Offset para a nova posição Y
 * @return	void
 */
void CParticleSystem::moveParticleSystem(float fOffsetX, float fOffsetY) {

	m_fX += fOffsetX;
	m_fY += fOffsetY;

	for(int nIdx = 0; nIdx < MAX_PARTICLES; nIdx++) {
		m_stParticles[nIdx].fPosX += fOffsetX;
		m_stParticles[nIdx].fPosY += fOffsetY;
	}

}

/*****************************************************************************************/
/*
 * @brief		Move somente a origem do sistema de partículas
 * @param		fNewX		Offset para a nova posição X na tela
 * @param		fNewY		Offset para a nova posição Y na tela
 * @return	void
 */
void CParticleSystem::moveOriginParticleSystem(float fNewX, float fNewY) {

	m_fX = fNewX;
	m_fY = fNewY;
}


/*****************************************************************************************/
/*void CParticleSystem::moveParticleSystem(float fOffsetX, float fOffsetY) {

	for(int nIdx = 0; nIdx < MAX_PARTICLES; nIdx++) {
		m_stParticles[nIdx].fPosX += fOffsetX;
		m_stParticles[nIdx].fPosY = fOffsetY;
	}
}
*/

/*****************************************************************************************/
/*
 * @brief		Retorna a posição X atual do sistema de partículas
 * @param		void
 * @return	a posição X do sistema de partículas
 */
float CParticleSystem::getX(void) {
	return m_fX;
}

/*****************************************************************************************/
/*
 * @brief		Retorna a posição Y atual do sistema de partículas
 * @param		void
 * @return	a posição Y do sistema de partículas
 */
float CParticleSystem::getY(void) {
	return m_fY;
}
