#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"
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

public:
  boxObject(float massOfBox, float pos[3], float sizeOfBox[3],
            Color boxColor = RED) {
    this->size = (btVector3){pos[0], pos[1], pos[2]};
    this->mass = massOfBox;
    objectColor = boxColor;
    btCollisionShape *boxCollShape = new btBoxShape(size / 2.0);
    collitionShapes.push_back(boxCollShape);
    btDefaultMotionState *boxMotionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1)), btTransform());
    motionStates.push_back(boxMotionState);
    btRigidBody::btRigidBodyConstructionInfo(this->mass, boxMotionState,
                                             boxCollShape);
  }
  void render() {

    rlPushMatrix();
    rlMultMatrixf(modelMat);
    DrawCubeV({0.0f, 0.0f, 0.0f}, {size.x(), size.y(), size.z()}, objectColor);
    DrawCubeWiresV({0.0f, 0.0f, 0.0f}, {size.x(), size.y(), size.z()}, BLACK);
    rlPopMatrix();
  }
  ~boxObject() {}
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
};

inline btRigidBody *GenerateGroundPlane() {
  btCollisionShape *shape = new btStaticPlaneShape(btVector3(0, 1, 1), 1);
  collitionShapes.push_back(shape);
  btDefaultMotionState *groundMotionState = new btDefaultMotionState(
      btTransform(btQuaternion(0, 0, 0, 1)), btTransform::getIdentity());
  motionStates.push_back(groundMotionState);
  btRigidBody::btRigidBodyConstructionInfo floorCI(0, groundMotionState, shape,
                                                   btVector3(0, 0, 0));
  btRigidBody *floor = new btRigidBody(floorCI);

  return floor;
}
