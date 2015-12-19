//==============================================================================
//
// ObjectCubeMapping
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_base.h"

#include "Framework/CubeTextureForEnvironmentMapping/CubeTextureForEnvironmentMapping.h"
#include "Framework/Model/model_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CubeTextureForEnvironmentMapping;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectCubeMapping : public ObjectBase {
public:
  // ctor
  ObjectCubeMapping(const char* p_filename, CubeTextureForEnvironmentMapping::ObjectDrawer* p_object_drawer);

  // dtor
  virtual ~ObjectCubeMapping();

  // set
  void OnDrawingCCW(void) { is_drawn_ccw_ = true; }
  void OnDrawingCW(void) { is_drawn_cw_ = true; }
  void OffDrawingCCW(void) { is_drawn_ccw_ = false; }
  void OffDrawingCW(void) { is_drawn_cw_ = false; }

  // Draw
  // BeginScene‚ÆEndScene‚ÌŠÔ‚ÅŒÄ‚Ño‚µ‚Ä
  void UpdateCubeMapping(void) { p_cube_mapping_->Draw(position_); }

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

protected:
  // property
  XModelData* p_xmodel_data_;
  LPD3DXEFFECT p_shader_;
  CubeTextureForEnvironmentMapping* p_cube_mapping_;
  bool is_drawn_ccw_;
  bool is_drawn_cw_;
};
