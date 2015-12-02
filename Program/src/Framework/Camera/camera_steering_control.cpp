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
      speed.x += sinf(rotation_.y);
      speed.z += cosf(rotation_.y);
    }
    if (keyboard.IsPress(DIK_S)) {
      speed.x += sinf(rotation_.y + D3DX_PI);
      speed.z += cosf(rotation_.y + D3DX_PI);
    }
    if (keyboard.IsPress(DIK_D)) {
      speed.x += sinf(rotation_.y + D3DX_PI * 0.5f);
      speed.z += cosf(rotation_.y + D3DX_PI * 0.5f);
    }
    if (keyboard.IsPress(DIK_A)) {
      speed.x += sinf(rotation_.y - D3DX_PI * 0.5f);
      speed.z += cosf(rotation_.y - D3DX_PI * 0.5f);
    }
    if (keyboard.IsPress(DIK_I)) {
      speed.y += 1.0f;
    }
    if (keyboard.IsPress(DIK_K)) {
      speed.y -= 1.0f;
    }
    speed *= kMovingSpeed;

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
CameraSteeringControl::CameraSteeringControl()
    : p_steering_(nullptr)
    , p_dummy_(nullptr) {
  p_dummy_ = new ControlableObject();
  p_steering_ = new CameraSteeringHoming(*p_dummy_);
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringControl::~CameraSteeringControl() {
  SafeDelete(p_steering_);
  ObjectBase::Destroy(p_dummy_);
}

//------------------------------------------------
// Execute
//------------------------------------------------
void CameraSteeringControl::Execute(Camera& camera, const float elapsed_time) {
  p_dummy_->UpdateAll(elapsed_time);
  p_steering_->Execute(camera, elapsed_time);
}
