
//{{BLOCK(general_BGD)

//======================================================================
//
//	general_BGD, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 555 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 17760 + 2048 = 20320
//
//	Time-stamp: 2022-11-10, 18:53:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GENERAL_BGD_H
#define GRIT_GENERAL_BGD_H

#define general_BGDTilesLen 17760
extern const unsigned short general_BGDTiles[8880];

#define general_BGDMapLen 2048
extern const unsigned short general_BGDMap[1024];

#define general_BGDPalLen 512
extern const unsigned short general_BGDPal[256];

#endif // GRIT_GENERAL_BGD_H

//}}BLOCK(general_BGD)
