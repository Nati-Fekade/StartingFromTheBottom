
//{{BLOCK(foreground)

//======================================================================
//
//	foreground, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 37 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1184 + 2048 = 3744
//
//	Time-stamp: 2022-12-09, 11:42:04
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FOREGROUND_H
#define GRIT_FOREGROUND_H

#define foregroundTilesLen 1184
extern const unsigned short foregroundTiles[592];

#define foregroundMapLen 2048
extern const unsigned short foregroundMap[1024];

#define foregroundPalLen 512
extern const unsigned short foregroundPal[256];

#endif // GRIT_FOREGROUND_H

//}}BLOCK(foreground)
