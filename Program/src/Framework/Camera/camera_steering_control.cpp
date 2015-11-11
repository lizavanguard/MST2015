//==============================================================================
//
// CameraSteeringControl
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera_steering_control.h"
#include "camera_steering_homing.h"
#include "camera.h"

#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Object/object_base.h"

//==============================================================================
// class implementation
//==============================================================================
class ControlableObject : public ObjectBase {
public:
  ControlableObject() {}
  virtual ~ControlableObject() {}

private:
  virtual void _Update(float) {
    static const float kMovingSpeed = 0.5f;
    static const float kRotationSpeed = 0.1f;

    auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
    D3DXVECTOR3 speed(0.0f, 0.0f, 0.0f);
    if (keyboard.IsPress(DIK_W)) {
      speed.z += kMovingSpeed;
    }
    if (keyboard.IsPress(DIK_S)) {
      speed.z -= kMovingSpeed;
    }
    if (keyboard.IsPress(DIK_D)) {
      speed.x += kMovingSpeed;
    }
    if (keyboard.IsPress(DIK_A)) {
      speed.x -= kMovingSpeed;
    }
    if (keyboard.IsPress(DIK_I)) {
      speed.y += kMovingSpeed;
    }
    if (keyboard.IsPress(DIK_K)) {
      speed.y -= kMovingSpeed;
    }
    position_ += speed;

    float rotation = 0.0f;
    if (keyboard.IsPress(DIK_E)) {
      rotation += kRotationSpeed;
    }
    if (keyboard.IsPress(DIK_Q)) {
      rotation -= kRotationSpeed;
    }
    rotation_.y += rotation;
  }

  virtual void _Draw(void) {}
};

//------------------------------------------------
// ctor
//------------------------------------------------
CameraSteeringControl::CameraSteeringControl(Camera& camera, ObjectBase& target)
    : CameraSteering(camera, target)
    , p_steering_(nullptr)
    , p_dummy_(nullptr) {
  p_dummy_ = new ControlableObject();
  p_steering_ = new CameraSteeringHoming(camera, *p_dummy_);
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringControl::~CameraSteeringControl() {
  SafeDelete(p_steering_);
  ObjectBase::Destroy(p_dummy_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void CameraSteeringControl::Update(const float elapsed_time) {
  p_dummy_->UpdateAll(elapsed_time);
  p_steering_->Update(elapsed_time);
}
