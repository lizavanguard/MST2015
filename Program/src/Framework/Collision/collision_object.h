//==============================================================================
//
// CollisionObject
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CollisionObject {
public:
  // ctor
  CollisionObject(float size) : size_(size), is_collided_(false) {
  }

  // dtor
  virtual ~CollisionObject() {}

  // React collision
  // Õ“Ë‚µ‚½•ûŒü‚Æ‚»‚Ì—Í‚©‚çÕ“Ë‰“š‚ğs‚¤
  virtual void ReactCollision(const D3DXVECTOR3& power) = 0;

  // get
  float GetSize(void) const { return size_; }
  bool IsCollided(void) const { return is_collided_; }

protected:
  float size_;
  bool is_collided_;
};
