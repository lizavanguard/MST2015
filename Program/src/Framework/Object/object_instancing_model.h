//==============================================================================
//
// ObjectInstancingModel
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"
#include "Framework/Model/model_manager.h"

#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectInstancingModel : public ObjectBase {
  using InstanceDataContainerType = std::vector<D3DXMATRIX>;

public:
  // ctor
  ObjectInstancingModel(const char* p_filename, unsigned int num_instances);

  // dtor
  virtual ~ObjectInstancingModel();

  // Update instance-data
  void UpdateInstanceData(unsigned int index, const D3DXVECTOR3& position, const D3DXVECTOR3& rotation);

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  // property
  XModelData* p_xmodel_data_;
  LPD3DXEFFECT p_shader_;

  LPDIRECT3DVERTEXDECLARATION9 p_declaration_;				// デクラレーション
  LPDIRECT3DVERTEXBUFFER9 p_instancing_vertex_buffer_;
  LPDIRECT3DPIXELSHADER9 p_pixel_shader;
  LPD3DXCONSTANTTABLE p_pixel_shader_constant;		// 定数レジスタのテーブル
  LPDIRECT3DVERTEXSHADER9 p_vertex_shader;
  LPD3DXCONSTANTTABLE p_vertex_shader_constant;		// 定数レジスタのテーブル
  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
  LPDIRECT3DINDEXBUFFER9 p_index_buffer_;
  unsigned int num_vertices_;
  unsigned int num_faces_;
  unsigned int num_instancing_;
  InstanceDataContainerType instancing_matrices_;
};

using ObjectInstancingModelFactory = liza::generic::Factory<ObjectInstancingModel>;