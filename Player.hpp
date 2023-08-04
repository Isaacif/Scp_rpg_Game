#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include <raymath.h>

typedef enum Animation
{
    RUNNING = 1, IDLE = 2  
} Animation;

class Player
{
    public:
        Vector3 characterPosition;
        Vector3 moveDirection;
        Vector3 targetPoint;

        Model model;
        ModelAnimation current;
        ModelAnimation *anims;
        float characterSpeed;

        unsigned int animsCount = 0;
        int animFrameCounter = 0, animId = 0;
        bool animPlaying = false;
        bool drawMesh = 1;
        bool drawSkeleton = 0;


        Player(Vector3 Position, float speed);
        
        ModelAnimation setAnimation(Animation animation);
        void loadMesh(const char *fileName);
        void rotateToDirection();
        void moveCharacter();

    private:
        float x_dist, z_dist = 0.0f;
        float yawAngle = 0.0f;
};



#endif