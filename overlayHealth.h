
//{{BLOCK(overlayHealth)

//======================================================================
//
//	overlayHealth, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 3 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 96 + 2048 = 2656
//
//	Time-stamp: 2022-12-09, 11:46:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_OVERLAYHEALTH_H
#define GRIT_OVERLAYHEALTH_H

#define overlayHealthTilesLen 96
extern const unsigned short overlayHealthTiles[48];

#define overlayHealthMapLen 2048
extern const unsigned short overlayHealthMap[1024];

#define overlayHealthPalLen 512
extern const unsigned short overlayHealthPal[256];

#endif // GRIT_OVERLAYHEALTH_H

//}}BLOCK(overlayHealth)
