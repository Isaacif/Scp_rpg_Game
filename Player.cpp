#include "Player.hpp"

Player::Player(Vector3 Position, float speed)
{
    TraceLog(LOG_INFO, "All loaded");
    characterPosition = Position, characterSpeed = speed;
    moveDirection = characterPosition, targetPoint = Position;
}

ModelAnimation Player::setAnimation(Animation animation)
{
    current = this->anims[animation];
    return current;
}

void Player::loadMesh(const char *fileName)
{   
    model = LoadModel(fileName); 
    anims = LoadModelAnimations(fileName, &animsCount);
}

void Player::rotateToDirection()
{
    yawAngle = atan2f(moveDirection.x, moveDirection.z);
    model.transform = MatrixRotateY(yawAngle);
}

void Player::moveCharacter()
{
    x_dist = std::abs(characterPosition.x - targetPoint.x);
    z_dist = std::abs(characterPosition.z - targetPoint.z);

    if(!(x_dist < 0.05 && z_dist < 0.05))
    {
        characterPosition = Vector3Add(characterPosition, Vector3Scale(moveDirection, characterSpeed));
        moveDirection = Vector3Normalize(Vector3Subtract(targetPoint, characterPosition));

        model.transform = MatrixRotateY(yawAngle);

        TraceLog(LOG_INFO, "Target Position: %.2f, %.2f, %.2f", targetPoint.x, targetPoint.y, targetPoint.z);
        TraceLog(LOG_INFO, "Atual: %.2f, %.2f, %.2f", characterPosition.x, characterPosition.y, characterPosition.z);
        TraceLog(LOG_INFO, "Diference: %.2f, %.2f, %.2f", x_dist, targetPoint.y, z_dist);
    }
    else
    {
        characterPosition = targetPoint;
        this->setAnimation(IDLE);
    }
}