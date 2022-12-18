
//{{BLOCK(transition)

//======================================================================
//
//	transition, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 510 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 16320 + 2048 = 18880
//
//	Time-stamp: 2022-12-04, 23:54:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TRANSITION_H
#define GRIT_TRANSITION_H

#define transitionTilesLen 16320
extern const unsigned short transitionTiles[8160];

#define transitionMapLen 2048
extern const unsigned short transitionMap[1024];

#define transitionPalLen 512
extern const unsigned short transitionPal[256];

#endif // GRIT_TRANSITION_H

//}}BLOCK(transition)
