//
//  Scene1ArtistZone.h
//  ConductrEnter
//
//  Created by Miquel Àngel Soler on 25/6/15.
//
//

#ifndef ConductrEnter_Scene1ArtistZone_h
#define ConductrEnter_Scene1ArtistZone_h

class Scene1ArtistZone
{
public:

    Scene1ArtistZone(float originX, float originY, float width, float height);

    void draw();

    int artistIndex;
    float originX;
    float originY;
    float width;
    float height;
};

#endif
