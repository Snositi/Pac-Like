#pragma once

#include <Vector2.h>
#include <Matrix3.h>
#include <vector>

class Sprite;

class Actor
{
public:
    Actor();

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    Actor(float x, float y, float collisionRadius, float maxSpeed, char icon);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
    /// <param name="color">The color of the actor when drawn</param>
    Actor(float x, float y, float collisionRadius, float maxSpeed, int color);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
    /// <param name="sprite">That sprite that will be drawn in this actors drawGraph function.</param>
    Actor(float x, float y, float collisionRadius, float maxSpeed, Sprite* sprite);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
    /// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
    /// <param name="sprite">That path for the sprite that will be drawn in this actors drawGraph function.</param>
    Actor(float x, float y, float collisionRadius, float maxSpeed, const char* spriteFilePath);

    /// <summary>
    /// </summary>
    /// <returns>If the actors start function has been called.</returns>
    bool getStarted() { return m_started; }

    /// <summary>
    /// </summary>
    /// <returns>A pointer to the actor that has been set as this actors parent.</returns>
    Actor* getParent() { return m_parent; }

    /// <summary>
    /// </summary>
    /// <returns>The current orientation of this actors z axis.</returns>
    MathLibrary::Vector2 getForward();
    /// <summary>
    /// Rotates the object until its forward matches the value given normalized.
    /// </summary>
    /// <param name="value"></param>
    void setForward(MathLibrary::Vector2 value);
    
    
    /// <returns>A vector representing the position of the object in the world without considering its parent.</returns>
    MathLibrary::Vector2 getWorldPosition();
    /// <summary>
    /// Sets the world position of the actor.
    /// </summary>
    /// <param name="value">The new world coordinates to place the actor.</param>
    void setWorldPostion(MathLibrary::Vector2 value);

    /// <returns>The position of the actor relative to its parent transform.</returns>
    MathLibrary::Vector2 getLocalPosition();
    /// <summary>
    /// Sets the position of the actor relative to its parent transform.
    /// </summary>
    /// <param name="value">The new local coordinates to place the actor.</param>
    void setLocalPosition(MathLibrary::Vector2 value);

    /// <returns>A vector representing the speed and direction the actor is moving in.</returns>
    MathLibrary::Vector2 getVelocity() { return m_velocity; }
    /// <summary>
    /// Instantly changes the velocity to the new value given.
    /// </summary>
    /// <param name="value">The new velocity of the actor.</param>
    void setVelocity(MathLibrary::Vector2 value) { m_velocity = value; }

    /// <returns>The force applied to the velocity every update.</returns>
    MathLibrary::Vector2 getAcceleration() { return m_acceleration; }
    /// <summary>
    /// Instantly changes the force added every frame to the value given.
    /// </summary>
    /// <param name="value">The new acceleration value.</param>
    void setAcceleration(MathLibrary::Vector2 value) { m_acceleration = value; }

    /// <returns>The maximum magnitude of the actor's velocity.</returns>
    float getMaxSpeed() { return m_maxSpeed; }
    /// <summary>
    /// Changes the maximum magnitude of the actor's velocity.
    /// </summary>
    /// <param name="value">The new maximum speed.</param>
    void setMaxSpeed(float value) { m_maxSpeed = value; }

    /// <returns>The actor's display color.</returns>
    int getColor() { return m_color; }
    /// <summary>
    /// Change the display color of the actor.
    /// </summary>
    /// <param name="value">The hex value of the color in 0xRRGGBBAA format.</param>
    void setColor(int value) { m_color = value; }

    /// <returns>Whether collisions will be checked from this actor to others.</returns>
    bool getStatic() { return m_static; }
    /// <summary>
    /// Change whether collisions will be checked from this actor to others.
    /// </summary>
    /// <param name="value">Whether to check collisions.</param>
    void setStatic(bool value) { m_static = value; }

    /// <summary>
    /// Called during the first update after an actor is added to a scene.
    /// </summary>
    virtual void start();

    /// <summary>
    /// Sets this actor as the given actors parent so that their matrices are concatenated for following updates.
    /// </summary>
    /// <param name="child">The new child of the actor.</param>
    void addChild(Actor* child);

    /// <summary>
    /// Finds an actor at the given index and sets that actor's parent to be nullptr. Does not delete the child.
    /// </summary>
    /// <param name="index">The index in the children arrray to remove.</param>
    void removeChild(int index);

    /// <summary>
    /// Sets the given actor's parent to be nullptr. Does not delete the child.
    /// </summary>
    /// <param name="child">The child to look for in the array to remove.</param>
    void removeChild(Actor* child);

    /// <returns>The amount of children attached to this actor.</returns>
    int getChildCount() { return (int)m_children.size(); }

    /// <returns>A container of the children attached to this actor.</returns>
    std::vector<Actor*> getChildren() { return m_children; }

    /// <summary>
    /// Changes the scale of the object to be the values given.
    /// </summary>
    /// <param name="scale">The scale of the object on the x and y axis.</param>
    void setScale(MathLibrary::Vector2 scale);

    /// <summary>
    /// Increases the scale of the actor by the given value.
    /// </summary>
    /// <param name="scale">The amount to scale the object on the x and y axis.</param>
    void scale(MathLibrary::Vector2 scale);

    /// <summary>
    /// Set the rotation angle to be the given value in radians
    /// </summary>
    /// <param name="radians">The angle to se the transform's rotation to</param>
    void setRotation(float radians);

    /// <summary>
    /// Increases the angle of rotation by the given amount.
    /// </summary>
    /// <param name="radians">The amount of radians to increase the rotation by</param>
    void rotate(float radians);

    /// <summary>
    /// Rotates the actor to face the given position
    /// </summary>
    /// <param name="position">The position the actor should be facing</param>
    void lookAt(MathLibrary::Vector2 position);

    /// <summary>
    /// Checks if the collision circle of the given actor is overlapping with this actor.
    /// </summary>
    /// <param name="other">The actor to check collision against.</param>
    /// <returns>Returns true if the distance between the two actors is less than their combined radii.</returns>
    bool checkCollision(Actor* other);

    int getShouldTransition() { return m_shouldTransition.x; }
    void setShouldTransition(int value) { m_shouldTransition.x = value; }
    int getDesiredTransitions() { return m_shouldTransition.y; }
    void setDesiredTransitions(int value) { m_shouldTransition.y = value; }

    /// <summary>
    /// Called when a collision between this actor and another occurs. 
    /// </summary>
    /// <param name="other">The actor this actor collided with.</param>
    virtual void onCollision(Actor* other);

    virtual void update(float deltaTime);
    virtual void draw();
    virtual void debug();
    virtual void end();

protected:
    /// <summary>
    /// Updates the actors forward vector to be
    /// the last direction it moved in
    /// </summary>
    void updateFacing();
private:
    /// <summary>
    /// Updates the global transform to be the combination of the paernt and local
    /// transforms. Updates the transforms for all children of this actor
    /// </summary>
    void updateGlobalTransform();

private:
    MathLibrary::Matrix3* m_globalTransform;
    MathLibrary::Matrix3* m_localTransform;
    MathLibrary::Matrix3* m_rotation;
    MathLibrary::Matrix3* m_translation;
    MathLibrary::Matrix3* m_scale;
    MathLibrary::Vector2 m_velocity;
    MathLibrary::Vector2 m_acceleration;
    float m_maxSpeed;
    float m_collisionRadius;
    char m_icon;
    int m_color;

    //{bool shouldTransition?,int transtionByHowMuch?}
    MathLibrary::Vector2 m_shouldTransition = {0,0};
    bool m_started = false;
    bool m_static = false;
    Actor* m_parent = nullptr;
    Sprite* m_sprite = nullptr;

    std::vector<Actor*> m_children;
};

