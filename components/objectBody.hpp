#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btQuaternion.h"
#include "LinearMath/btTransform.h"
#include <btBulletDynamicsCommon.h>
#include <vector>
extern std::vector<btCollisionShape *> collitionShapes;
extern std::vector<btDefaultMotionState *> motionStates;
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
