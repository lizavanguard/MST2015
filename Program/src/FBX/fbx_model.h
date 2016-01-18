//=========================================================
// fbx_model.h
// author:ryuya nakamura
//=========================================================

//-------------------------------------
// include guard
//-------------------------------------
#pragma once
#ifndef __FbxModel_H__
#define __FbxModel_H__

//-------------------------------------
// link
//-------------------------------------
//#pragma comment(lib, "libfbxsdk")
#pragma comment(lib, "libfbxsdk-mt")

//-------------------------------------
// class
//-------------------------------------
class FbxModel
{
public:
  FbxModel(LPDIRECT3DDEVICE9	device);
	virtual ~FbxModel();
	void Update();
	void Draw();
	void Load(const std::string &path);

  // アニメーションの使い方
  // ①初期化後、SetAnimationCountでアニメーション数登録
  // ②SetAnimationFlameでアニメーションフレーム登録していく
  // ③SetAnimationSpeedで再生速度登録
  // ④AnimationLoop～でループ設定
  // ⑤AnimationPlayで再生
  // ループでない場合、GetAnimationでアニメーション再生終了判定が行える

  void AnimationPlay() { anim_play_flg_ = true; }
  void AnimationStop() { anim_play_flg_ = false; }
  bool GetAnimation() { return anim_play_flg_; }
  void AnimationLoopOn() { anim_loop_flg_ = true; }
  void AnimationLoopOff() { anim_loop_flg_ = false; }

  void SetAnimation(int anim_num) {
    anim_playing_num_ = anim_num;
    if( anim_playing_num_ > 0 ) {
      cur_time_ = p_anim_flame_[anim_playing_num_ - 1];
    } else {
      cur_time_ = 1.0f;
    }
  }

  void SetAnimationSpeed(float speed) { anim_add_count_ = speed; }
  void SetAnimationFlame(int index, float flame) { p_anim_flame_[index] = flame; }
  void SetAnimationCount(int count) {
    anim_count_ = count;
    if( p_anim_flame_ == nullptr ) {
      p_anim_flame_ = new float[anim_count_];
    } else {
      delete[] p_anim_flame_;
      p_anim_flame_ = new float[anim_count_];
    }
  }

  void SetPosition(const D3DXVECTOR3& position) { position_ = position; }
  void SetRotation(const D3DXVECTOR3& rotation) { rotation_ = rotation; }
  void SetRotationMatrix(const D3DXMATRIX& rotation_matrix) { rotation_matrix_ = rotation_matrix; }
  void SetScale(const D3DXVECTOR3& scale) { scale_ = scale; }
private:
  struct VERTEX_BLEND3D {
    D3DXVECTOR3 position;
    float weight[3];
    float matrix_index[4];
    D3DXVECTOR3 normal;
    D3DXVECTOR2 texcoord;

    bool operator == ( const VERTEX_BLEND3D &rhs ) const {
      return memcmp(this, &rhs, sizeof(VERTEX_BLEND3D)) == 0;
    }
  };

	struct MESH
	{
		LPDIRECT3DVERTEXBUFFER9 vertex_;
		LPDIRECT3DINDEXBUFFER9 index_;
		int vertex_max_;
		int index_max_;
		D3DMATERIAL9 material_;
		char texture_filename_[128];
		LPDIRECT3DTEXTURE9 texture_;
		char uvset_name_[128];
	};

	struct KEY_FRAME
	{
		float time_;
		D3DXVECTOR3 translation_;
		D3DXQUATERNION rotation_;
		D3DXVECTOR3 scaling_;
	};

	struct BONE
	{
		int id_;
		D3DXMATRIX bone_matrix_;
		D3DXMATRIX offset_matrix_;
		D3DXMATRIX transform_matrix_;
		D3DXMATRIX world_matrix_;
		BONE *child_;
		BONE *sibling_;
		char name_[128];
		int key_max_;
		KEY_FRAME *key_;
		BONE(){
			child_ = nullptr;
			sibling_ = nullptr;
			memset(name_, 0, 128);
			id_ = -1;
		}
	};

	FbxNode *GetRootBone(FbxNode *node);
	void CountUpBone(FbxNode *node);
	void LoadBoneName(FbxNode *node);
	void LoadBoneHierarchy(FbxNode *node);
	FbxModel::BONE *SearchBoneByName(char *name);
	void LoadAnimationKeyFrame(FbxNode *node, FbxScene *scene);
	void LoadAnimationKeyFrameFormNode(FbxNode *node, FbxScene *scene);
	void CountUpMesh(FbxNode *node);
	void LoadMesh(FbxNode *node);
	void LoadMeshFromNode(FbxNode *node);
	void LoadMaterialFromNode(FbxNode *node, int material_index);
	void LoadTextureFromNode(FbxNode *node, int material_index, char *dst_uvset);
  void LoadBoneIndexAndWeight(FbxSkin *skin, VERTEX_BLEND3D *dst_vertex, int vertex_id);
	void ExtractTranslationFromMatrix(D3DXMATRIX *out, D3DXMATRIX *src);
	void ExtractRotationFromMatrix(D3DXMATRIX *out, D3DXMATRIX *src);
	void ExtractScalingFromMatrix(D3DXMATRIX *out, D3DXMATRIX *src);
	void UpdateBoneMatrix(BONE *subject, D3DXMATRIX *parent);
  void DeleteBone(BONE *bone);

  LPDIRECT3DDEVICE9	device_;
	int mesh_count_;
	MESH *mesh_;
	int mesh_cursor_;
	int bone_count_;
	BONE *bone_;
	BONE *root_;
	float cur_time_;  // アニメーションカウント
	int bone_cursor_;
  bool anim_play_flg_;  // アニメーション再生してるか否か
  bool anim_loop_flg_;
  float *p_anim_flame_;  // アニメーションフレーム登録値　例１待機　０～１０フレーム　２歩き　１０～２０
  int anim_count_;  // アニメーション数
  float anim_add_count_;  // アニメーション再生スピード
  int anim_playing_num_;  // 再生中のアニメーション番号
  D3DXVECTOR3 position_;
  D3DXVECTOR3 rotation_;
  D3DXVECTOR3 scale_;

  LPDIRECT3DVERTEXDECLARATION9	p_declaration_;
  LPDIRECT3DPIXELSHADER9 p_pixel_shader;
  LPD3DXCONSTANTTABLE p_pixel_shader_constant;		// 定数レジスタのテーブル
  LPDIRECT3DVERTEXSHADER9 p_vertex_shader;
  LPD3DXCONSTANTTABLE p_vertex_shader_constant;		// 定数レジスタのテーブル

  unsigned int h_toon_sampler_;
  unsigned int h_diffuse_sampler_;
  LPDIRECT3DTEXTURE9 p_toon_texture_;
  D3DXMATRIX rotation_matrix_;
};


#endif //__FbxModel_H__


//-------------------------------------
// end of file
//-------------------------------------
