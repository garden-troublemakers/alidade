#ifndef _CONSTS_HPP_
#define _CONSTS_HPP_

#define CAMERA_GHOST 	0
#define CAMERA_PLAYER 	1
#define VOLUME_SOUND 	0
#define VOLUME_MUSIC	1
#define VOLUME_FX		2
#define LEVEL_TEST		0
#define LEVEL_TUTO		1
#define LEVEL_HARD		2
#define CHARACTER_ALTAIR	0
#define LEVEL_PLAYING	0
#define LEVEL_FINISHED  1
#define LEVEL_FAILED 	2

#include <cstdlib>
static inline float frand() {
    return float(rand()) / RAND_MAX;
}

#endif // _CONSTS_HPP_
