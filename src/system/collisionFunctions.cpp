#include "collisionFunctions.h"


#include  "cmath"
// Collision by Jeffrey Thompson https://www.jeffreythompson.org/collision-detection/circle-circle.php
bool isCircleCircleColliding(Circle circle1, Circle circle2)
{
    const float distanceY = circle1.y - circle2.y;
    const float distanceX = circle1.x - circle2.x;
    const float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

    return distance < circle1.radius + circle2.radius;
}

// Collision by Jeffrey Thompson https://www.jeffreythompson.org/collision-detection/circle-rect.php
bool isCircleRectColliding(Circle circle, Rectangle rectangle)
{
    // temporary variables to set edges for testing
    float testX = circle.x;
    float testY = circle.y;

    // which edge is closest?
    if (circle.x < rectangle.x) testX = rectangle.x; // test left edge
    else if (circle.x > rectangle.x + rectangle.width) testX = rectangle.x + rectangle.width; // right edge
    if (circle.y < rectangle.y) testY = rectangle.y; // top edge
    else if (circle.y > rectangle.y + rectangle.height) testY = rectangle.y + rectangle.height; // bottom edge

    // get distance from closest edges
    float distX = circle.x - testX;
    float distY = circle.y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the radius, collision!
    if (distance <= circle.radius)
    {
        return true;
    }
    return false;
}

bool isPointRecColliding(Vector2 mouse, Rectangle rec) //Check if works
{
    float rightEdge = rec.x + rec.width;
    float leftEdge = rec.x;
    float upEdge = rec.y;
    float downEdge = rec.y + rec.height;

    if (mouse.x <= rightEdge && mouse.x >= leftEdge && mouse.y >= upEdge && mouse.y <= downEdge)
    {
        return true;
    }
    return false;
}

bool isRecRecColliding(Rectangle rec, Rectangle rec2)
{
    float rec1RightEdge = rec.x + rec.width;
    float rec1LeftEdge = rec.x;
    float rec1UpEdge = rec.y;
    float rec1DownEdge = rec.y + rec.height;

    float rec2RightEdge = rec2.x + rec2.width;
    float rec2LeftEdge = rec2.x;
    float rec2UpEdge = rec2.y;
    float rec2DownEdge = rec2.y + rec2.height;

    if (rec1RightEdge >= rec2LeftEdge && // r1 right edge past r2 left
        rec1LeftEdge <= rec2RightEdge && // r1 left edge past r2 right
        rec1DownEdge >= rec2UpEdge && // r1 top edge past r2 bottom
        rec1UpEdge <= rec2DownEdge)
    {
        // r1 bottom edge past r2 top
        return true;
    }
    return false;
}
