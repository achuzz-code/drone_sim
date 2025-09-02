#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"
#include <array>
#include <btBulletDynamicsCommon.h>
#include <raylib.h>
#include <rlgl.h>
#include <vector>
extern std::vector<btCollisionShape *> collitionShapes;
extern std::vector<btDefaultMotionState *> motionStates;
class boxObject {
private:
  float mass;
  Color objectColor;
  btVector3 size;
  btVector3 positon;
  float modelMat[16];
  btRigidBody *body;

public:
  boxObject(float massOfBox, std::array<float, 3> pos,
            std::array<float, 3> sizeOfBox, Color boxColor = RED) {
    this->size = btVector3(sizeOfBox.at(0), sizeOfBox.at(1), sizeOfBox.at(2));
    this->mass = massOfBox;
    objectColor = boxColor;
    btCollisionShape *boxCollShape = new btBoxShape(size / 2.0);
    collitionShapes.push_back(boxCollShape);
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(pos.at(0), pos.at(1), pos.at(2)));

    btDefaultMotionState *boxMotionState =
        new btDefaultMotionState(startTransform);
    motionStates.push_back(boxMotionState);
    btVector3 inertia(0, 0, 0);
    if (mass != 0.0f) {
      boxCollShape->calculateLocalInertia(mass, inertia);
    }
    btRigidBody::btRigidBodyConstructionInfo boxCI(mass, boxMotionState,
                                                   boxCollShape, inertia);
    body = new btRigidBody(boxCI);
    body->setRestitution(0.8f); // 0 = no bounce, 1 = perfectly elastic
  }
  void render() {
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(modelMat);
    rlPushMatrix();
    rlMultMatrixf(modelMat);
    DrawCubeV({0.0f, 0.0f, 0.0f}, {size.x(), size.y(), size.z()}, objectColor);
    DrawCubeWiresV({0.0f, 0.0f, 0.0f}, {size.x(), size.y(), size.z()}, BLACK);
    rlPopMatrix();
  }
  ~boxObject() {}
  btRigidBody *getBody() { return this->body; }
  void kick() {
    this->body->applyForce(btVector3{0, 100, 0}, btVector3{0, 0, 3});
  }
};

class physicsDomain {
public:
  btDefaultCollisionConfiguration *collisionConfig;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *broadphase;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *world;
  physicsDomain() {
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
                                        collisionConfig);
    world->setGravity(btVector3(0, -9.81f, 0));
  }
  ~physicsDomain() {
    delete collisionConfig;
    delete dispatcher;
    delete broadphase;
    delete world;
    for (auto i : collitionShapes) {
      delete i;
    }
    for (auto i : motionStates) {
      delete i;
    }
  }
  void addObject(btRigidBody *body) { this->world->addRigidBody(body); }
  void stepPhysics() { this->world->stepSimulation(1.0 / 60.0, 5); }
};

inline btRigidBody *GenerateGroundPlane() {
  btCollisionShape *shape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
  collitionShapes.push_back(shape);
  btDefaultMotionState *groundMotionState = new btDefaultMotionState(
      btTransform(btQuaternion(0, 0, 0, 1)), btTransform::getIdentity());
  motionStates.push_back(groundMotionState);
  btRigidBody::btRigidBodyConstructionInfo floorCI(0, groundMotionState, shape,
                                                   btVector3(0, 0, 0));
  btRigidBody *floor = new btRigidBody(floorCI);

  return floor;
}
