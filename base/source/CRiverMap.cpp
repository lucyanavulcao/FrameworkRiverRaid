/*
 *  CRiverMap.cpp
 *
 *  Criado por Alexandre Ramos Coelho, 07/11
 *
 * 	Classe para criar um mapa de tiles que possa ser 'rolado' na vertical
 * 	e na horizontal
 */

#include <fstream>
#include <iomanip>

#include "CRiverMap.h"

using namespace std;

/*****************************************************************************************/
/*
 * @brief		Construtor da classe. Inicializa as vari·veis membro
 * @param		void
 * @return	void
 */
CRiverMap::CRiverMap() {

	m_nScrollOffsetY = 0;
	m_nScrollOffsetX = 0;
	m_nStartPosX = 0;
	m_nStartPosY = 0;
}

/*****************************************************************************************/
/*
 * @brief		Carrega o mapa de tiles ‡ partir de um arquivo. Cria uma matriz com o Ìndice
 * 					de cada tile
 * @param		nomeArq	Arquivo de texto com o mapa de tiles
 * @return	true se o arquivo foi aberto corretamente, false caso contr·rio
 */
bool CRiverMap::loadMap(const char nomeArq[]) {

	char aux[40];
	int ind;

	ifstream arq;
	arq.open(nomeArq, ios::in);

	if ( !arq.is_open() ) {
		return false;
	} else {
		arq >> aux >> widthTileMap;
		arq >> aux >> heightTileMap;
		for(int lin=0; lin<heightTileMap; lin++) {
			for (int col=0; col<widthTileMap; col++) {
				arq >> ind;
				map.push_back(ind-1); // este -1 est√° aqui pois as sprites do TMX iniciam em 1
			}
		}
		arq.close();
	}
	return true;


}

/*****************************************************************************************/
/*
 * @brief		Carrega as imagens correspondentes ao mapa de tiles
 * @param		nomeArq	Arquivo de texto com o mapa de tiles
 * @param		w	...
 * @return	true se o arquivo foi carregado, false caso contr·rio
 */
bool CRiverMap::loadTileMap(const char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                            int column, int row, int total) {
	if(!loadMultiImage(nomeArq,w,h,hSpace,vSpace,xIni,yIni,column,row,total))
		return false;
	return true;
}

/*****************************************************************************************/
/*
 * @brief		MÈtodo que desenha um mapa de tiles na tela
 * @param
 * @return
 */
void CRiverMap::draw() {

	//cout << "CRiverMap::draw - Desenhado o map de tiles..."<< flush;
	//cout << "Largura: "<< getWidth() << " Altura: " << getHeight() << endl;
	int cont = 0;
	int x = getStartPosX();
	int y = getStartPosY();
	cont = 0;

	// Faz o scroll vertical
	y += m_nScrollOffsetY;

	for(int lin=0; lin<heightTileMap; lin++) {
		for (int col=0; col<widthTileMap; col++) {
			setPosition(x,y);
			drawFrame(map[cont]);
			cont++;
			x += getWidth();
		}
		x = 0; // FIXME: isso aqui est· correto? Devo zerar?
		y += getHeight();
	}
	//cout << "FIM." << endl;
		
}

// **********************************************************
//
//
// **********************************************************
void CRiverMap::printMap() {

	cout << "PrintMap..." << endl;
	int cont =0;
	cout << "Print Map"<< endl;
	for(int lin=0; lin<heightTileMap; lin++) {
		cout << "Linha " << lin << ": ";
		for (int col=0; col<widthTileMap; col++) {
			cout << setw (4) << map[cont];
			cont ++;
		}
		cout << endl;
	}
	cout << "Print Map: END;"<< endl;
}

int CRiverMap::getTileNumber(int col, int lin) // x, y
{
	return map[lin*widthTileMap+col] + 1; // // este +1 est√° aqui pois as sprites do TMX iniciam em 1
}

/*************************************************************************/
/*
 * @brief	Retorna a string com uma linha completa do mapa
 * @param
 * @return
 */
std::vector<int> CRiverMap::getTileLine(int nLine) {
	std::vector<int> vLinhaMapa;
	int nStartPos = nLine * widthTileMap;

	for(int nCol = 0; nCol < widthTileMap; nCol++) {
		
		vLinhaMapa.push_back(map[nStartPos + nCol]);
	}

	return vLinhaMapa;
}

/*************************************************************************/
/*
 * @brief		Copia uma nova linha de tiles para a linha especificada do mapa
 * @param		vLine		Vetor com os novos tiles
 * @param		nLine		Linha do mapa onde ser„o inseridos os novos tiles
 * @return	true se ok, false se a linhas n„o tem o mesmo tamanho
 */
bool CRiverMap::putTileLine(std::vector<int> vLine, int nLine) {

	int nStartPos = nLine * widthTileMap;

	if(vLine.size() != widthTileMap) // Linhas tem tamanhos diferentes
		return false;

	for(int nCol = 0; nCol < widthTileMap; nCol++) {

		map[nStartPos+nCol] = vLine[nCol];
	}

	return true;
}

/*************************************************************************/
/*
 * @brief		Seta o valor do offset vertical do mapa de tiles. ⁄til para 
 * 					scroll vertical
 * @param		nOffset	Valor do offset em pixels
 * @return	void
 */
void CRiverMap::setOffsetY(int nOffset) {
	m_nScrollOffsetY = nOffset;
}

/*************************************************************************/
/*
 * @brief		Seta o valor do offset horizontal do mapa de tiles. ⁄til para 
 * 					scroll lateral
 * @param		nOffset	Valor do offset em pixels
 * @return	void
 */
void CRiverMap::setOffsetX(int nOffset) {
	m_nScrollOffsetX = nOffset;
}

/*************************************************************************/
/*
 * @brief		ObtÈm o valor de offset vertical atual
 * @param		void
 * @return	valor do offset vertical
 */
int CRiverMap::getOffsetY() {
	return m_nScrollOffsetY;
}

/*************************************************************************/
/*
 * @brief		ObtÈm o valor de offset horizontal atual
 * @param		void
 * @return	valor do offset horizontal
 */
int CRiverMap::getOffsetX() {
	return m_nScrollOffsetX;
}

/*************************************************************************/
/*
 * @brief		Seta a posiÁ„o horizontal inicial de desenho do mapa
 * @param		nPos	PosiÁ„o X inicial
 * @return	void
 */
void CRiverMap::setStartPosX(int nPos) {

	m_nStartPosX = nPos;
}

/*************************************************************************/
/*
 * @brief		Seta a posiÁ„o vertical inicial de desenho do mapa
 * @param		nPos	PosiÁ„o Y inicial
 * @return	void
 */
void CRiverMap::setStartPosY(int nPos) {

	m_nStartPosY = nPos;
}

/*************************************************************************/
/*
 * @brief		Troca os tiles de um mapa por valores randomicos
 * @param		nMaxRandom	Valor m·ximo a ser randomizado (i.e. maior Ìndice 
 * 					de tile)
 * @return	void
 */
void CRiverMap::scrambleMap(int nMaxRandom) {

	for(int nIdx = 0; nIdx < widthTileMap*heightTileMap; nIdx++)
		map[nIdx] = rand() % (nMaxRandom-1) + 1; 

}

/*************************************************************************/
void CRiverMap::mapSliceScramble(int nNum) {

	map[0] += nNum;
}

