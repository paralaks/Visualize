#ifndef MarchingCubesSceneConstantsH
#define MarchingCubesSceneConstantsH

const unsigned char MAX_OBJECT_NUMBER            = 20;
const unsigned char MAX_CLIPPING_VOLUME_NUMBER   = 20;
const unsigned char MAX_TEXTURED_SURFACE_NUMBER  = 4 * MAX_CLIPPING_VOLUME_NUMBER;

const unsigned char OBJECT_QUALITY_HIGH          = 0;
const unsigned char OBJECT_QUALITY_LOW           = 1;

const unsigned char STATE_NORMAL               = 10;
const unsigned char STATE_CLIPPING_VOLUME      = 11;
const unsigned char STATE_TEXTURED_SURFACE     = 12;

const unsigned long MAXIMUM_TRIANGLE_COUNT_PER_OBJECT= 1400000;

#endif