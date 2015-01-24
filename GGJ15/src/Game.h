//
//  Game.h
//  Stephane
//
//  Created by Stephan LB on 24/01/2015.
//
//

#ifndef __Stephane__Game__
#define __Stephane__Game__


#include "Bird.h"
#include "Map.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class Game
{
public:
    static Game& getInstance()
    {
        static Game instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
private:
    Game() {};                   // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Game(Game const&);              // Don't Implement
    void operator=(Game const&); // Don't implement
    
    
};

#endif /* defined(__Stephane__Game__) */
