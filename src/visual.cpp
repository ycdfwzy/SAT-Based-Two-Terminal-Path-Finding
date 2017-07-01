#include "visual.h"
#include "grids.h"
#include "checker.h"
#include <pshpack2.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

void Visual::Paint(checker& G){
	for (int i = 0; i < 1000; ++ i){
		for (int j = 0; j < 1000; ++ j){
			pRGB[i][j].r = 0;
			pRGB[i][j].g = 0;
			pRGB[i][j].b = 0;
		}
	}
	int lr = 1000/G.m_grids.getrow();
	int lc= 1000/G.m_grids.getcol();
	
	int len = G.m_grids.terminal.size()+1;
	
	for (int i = 1; i <= G.m_grids.getrow(); ++i){
		for (int j = 1; j <= G.m_grids.getcol(); ++j){
			if (G.MAP[i][j] == 0)
			for (int k1 = (i-1)*lr+1; k1 < i*lr; ++k1)
				for (int k2 = (j-1)*lc+1; k2 < j*lc; ++k2){
					pRGB[k1][k2].r = 255;
					pRGB[k1][k2].g = 255;
					pRGB[k1][k2].b = 255;
				}
			else if (G.MAP[i][j] > 0)
			for (int k1 = (i-1)*lr+1; k1 < i*lr; ++k1)
				for (int k2 = (j-1)*lc+1; k2 < j*lc; ++k2){
					pRGB[k1][k2].r = 255*G.MAP[i][j]/len * (G.MAP[i][j]%3==0);
					pRGB[k1][k2].g = 255*G.MAP[i][j]/len * (G.MAP[i][j]%3==1);
					pRGB[k1][k2].b = 255*G.MAP[i][j]/len * (G.MAP[i][j]%3==2);
				}
		}
	}
	
	generateBmp( (BYTE*)pRGB, 1000, 1000, "show.bmp" );
}

void Visual::generateBmp(BYTE* pData, int width, int height, char* filename){
	int size = width*height*3;
	
	BMPFILEHEADER_T bfh;
	bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size  // data size
		+ sizeof( BMPFILEHEADER_T ) // first section size
		+ sizeof( BMPINFOHEADER_T ) // second section size
		;
	bfh.bfReserved1 = 0; // reserved

	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size;
	
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;      
	FILE * fp = fopen( filename,"wb" );
	if( !fp ) return;
	fwrite( &bfh, 1, sizeof(BMPFILEHEADER_T), fp );
	fwrite( &bih, 1, sizeof(BMPINFOHEADER_T), fp );
	fwrite( pData, 1, size, fp );
	fclose( fp );
}
