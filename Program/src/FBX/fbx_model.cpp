//=========================================================
// fbx_model.cpp
// author:ryuya nakamura
//=========================================================


//-------------------------------------
// include
//-------------------------------------
#include "fbx_model.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Texture/texture_manager.h"

//-------------------------------------
// warning
//-------------------------------------
#pragma warning(disable:4996)
#pragma warning(disable:4244)


//-------------------------------------
// FbxModel()
//-------------------------------------
FbxModel::FbxModel(LPDIRECT3DDEVICE9	device) :
device_(device),
position_(0.0f, 0.0f, 0.0f),
rotation_(0.0f, 0.0f, 0.0f),
h_toon_sampler_(0),
h_diffuse_sampler_(0),
p_toon_texture_(nullptr)
{
  D3DXMatrixIdentity(&rotation_matrix_);
	mesh_count_ = 0;
	mesh_ = NULL;
	mesh_cursor_ = 0;
	bone_count_ = 0;
	bone_ = NULL;
	bone_cursor_ = 0;
	root_ = NULL;
	cur_time_ = 0;

  anim_play_flg_ = false;  // �A�j���[�V�����Đ����Ă邩�ۂ�
  anim_loop_flg_ = false;
  p_anim_flame_ = nullptr;  // �A�j���[�V�����t���[���o�^�l�@��P�ҋ@�@�O�`�P�O�t���[���@�Q�����@�P�O�`�Q�O
  anim_count_ = 0;  // �A�j���[�V������
  anim_add_count_ = 0.0f;  // �A�j���[�V�����Đ��X�s�[�h
  anim_playing_num_ = 0;

  D3DVERTEXELEMENT9 vertex_element[] = {
      { 0, 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
      { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
      { 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
      { 0, 40, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
      { 0, 52, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
      D3DDECL_END()
  };

  device_->CreateVertexDeclaration(vertex_element, &p_declaration_);

  ID3DXBuffer* p_error = nullptr;
  LPD3DXBUFFER compiled_code;

  if( FAILED(D3DXCompileShaderFromFile("hlsl/no_technique/SkinMeshPS.hlsl", nullptr, nullptr,
    "PS", "ps_3_0", 0,
    &compiled_code, &p_error,
    &p_pixel_shader_constant)) ) {
    MessageBox(nullptr, reinterpret_cast<LPCSTR>( p_error->GetBufferPointer() ),
               "D3DXCompileShaderFromFile", MB_OK);
    SafeRelease(p_error);
  }

  if( FAILED(device_->CreatePixelShader(reinterpret_cast<DWORD*>( compiled_code->GetBufferPointer() ),
    &p_pixel_shader)) ) {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
  }

  SafeRelease(compiled_code);

  // ---------���_�V�F�[�_�[����----------

  if( FAILED(D3DXCompileShaderFromFile("hlsl/no_technique/SkinMeshVS.hlsl", nullptr, nullptr,
    "VS", "vs_3_0", 0,
    &compiled_code, &p_error,
    &p_vertex_shader_constant)) ) {
    MessageBox(nullptr, reinterpret_cast<LPCSTR>( p_error->GetBufferPointer() ),
               "D3DXCompileShaderFromFile", MB_OK);
    SafeRelease(p_error);
  }

  if( FAILED(device_->CreateVertexShader(reinterpret_cast<DWORD*>( compiled_code->GetBufferPointer() ),
    &p_vertex_shader)) ) {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
  }
  SafeRelease(compiled_code);

  h_toon_sampler_ = p_pixel_shader_constant->GetSamplerIndex("ToonSampler");
  h_diffuse_sampler_ = p_pixel_shader_constant->GetSamplerIndex("DiffuseSampler");
  p_toon_texture_ = TextureManager::Instance().Find("General", "toon");
}


//-------------------------------------
// ~FbxModel()
//-------------------------------------
FbxModel::~FbxModel()
{
  for( int i = 0; i < mesh_count_; i++ ) {
    SafeRelease(mesh_[i].vertex_);
    SafeRelease(mesh_[i].index_);
  }
  SafeDeleteArray(mesh_);
  for( int i = 0; i < bone_count_; i++ ) {
    DeleteBone(&bone_[i]);
  }
  SafeDeleteArray(bone_);

  SafeRelease(p_declaration_);

  SafeRelease(p_vertex_shader);
  SafeRelease(p_vertex_shader_constant);
  SafeRelease(p_pixel_shader);
  SafeRelease(p_pixel_shader_constant);

  delete[] p_anim_flame_;
}

void FbxModel::DeleteBone(BONE *bone) {
  if( bone->child_ ) {
    DeleteBone(bone->child_);
  }
  if( bone->sibling_ ) {
    DeleteBone(bone->sibling_);
  }
  SafeDeleteArray(bone->key_);
}


//-------------------------------------
// Update()
//-------------------------------------
void FbxModel::Update()
{
	D3DXMATRIX element;
	float anim_length = 0.0f;

	D3DXMatrixIdentity(&element);

  D3DXMATRIX rot;
  if (D3DXMatrixIsIdentity(&rotation_matrix_)) {
    D3DXMatrixRotationYawPitchRoll(&rot, rotation_.y, rotation_.x, rotation_.z);
  }
  else {
    rot = rotation_matrix_;
  }
  D3DXMatrixMultiply(&element, &element, &rot);

  D3DXMATRIX trans;
  D3DXMatrixTranslation(&trans, position_.x, position_.y, position_.z);
  D3DXMatrixMultiply(&element, &element, &trans);

	UpdateBoneMatrix(&bone_[0], &element);

  // �Đ�
  if( anim_play_flg_ ) {
    cur_time_ += anim_add_count_;
    // �I���t���[�����B
    if( cur_time_ >= p_anim_flame_[anim_playing_num_] ) {
      // ���[�v���邩�ۂ�
      if( anim_loop_flg_ ) {
        if( anim_playing_num_ > 0 ) {
          cur_time_ = p_anim_flame_[anim_playing_num_ - 1];
        } else {
          cur_time_ = 0.0f;
        }
      } else {
        anim_play_flg_ = false;
      }
    }
  }
}


//-------------------------------------
// Draw()
//-------------------------------------
void FbxModel::Draw()
{
	if (mesh_ == NULL)
	{
		return;
	}

	// �ϐ��錾
	D3DXMATRIX scale, rotate, translate;

	int i(0);
	int indexed_matrix_num = 0;

  device_->SetVertexDeclaration(p_declaration_);

	DWORD def_cull = 0;
	device_->GetRenderState(D3DRS_CULLMODE, &def_cull);

	device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

  device_->SetVertexShader(p_vertex_shader);
  device_->SetPixelShader(p_pixel_shader);

  D3DXMATRIX *p_world = new D3DXMATRIX[bone_count_];

	for (i = 0; i < bone_count_; i++)
	{
    p_world[i] = bone_[i].world_matrix_;
	}

  p_vertex_shader_constant->SetMatrixArray(device_, "worldArray", p_world, bone_count_);

  const auto& p_camera = CameraManager::Instance().Find("MAIN_CAMERA");
  D3DXMATRIX viewProj = p_camera.GetViewMatrix() * p_camera.GetProjectionMatrix();
  p_vertex_shader_constant->SetMatrix(device_, "viewProj", &viewProj);

  D3DXVECTOR3 cameraVec = p_camera.CalculateCameraDirection();
  D3DXVECTOR4 camera(cameraVec, 0.0f);

  D3DXMATRIX invWorld, World;
  D3DXMatrixIdentity(&World);

  D3DXMATRIX rot;
  D3DXMatrixRotationYawPitchRoll(&rot, rotation_.y, rotation_.x, rotation_.z);
  D3DXMatrixMultiply(&World, &World, &rot);

  D3DXMATRIX trans;
  D3DXMatrixTranslation(&trans, position_.x, position_.y, position_.z);
  D3DXMatrixMultiply(&World, &World, &trans);

  D3DXMatrixInverse(&invWorld, NULL, &World);
  D3DXVec4Transform(&camera, &camera, &invWorld);
  //D3DXVec4Normalize(&camera, &camera);
  cameraVec.x = camera.x;
  cameraVec.y = camera.y;
  cameraVec.z = camera.z;
  D3DXVec3Normalize(&cameraVec, &cameraVec);
  p_vertex_shader_constant->SetFloatArray(device_, "cameraDir", (float*)&cameraVec, 3);

  D3DXVECTOR3 lightVec(1.0f, -1.0f, 1.0f);
  D3DXVECTOR4 light(lightVec, 0.0f);
  D3DXVec4Transform(&light, &light, &invWorld);
  //D3DXVec4Normalize(&light, &light);
  lightVec.x = light.x;
  lightVec.y = light.y;
  lightVec.z = light.z;
  D3DXVec3Normalize(&lightVec, &lightVec);
  p_vertex_shader_constant->SetFloatArray(device_, "lightVec", (float*)&lightVec, 3);

	D3DMATERIAL9 debug_material;
	for (i = 0; i < mesh_count_; i++)
	{
		if (mesh_[i].index_ == NULL || mesh_[i].vertex_ == NULL)
		{
			continue;
		}
    
    // TODO:
    device_->SetTexture(h_toon_sampler_, p_toon_texture_);
    device_->SetTexture(h_diffuse_sampler_, mesh_[i].texture_);
		debug_material = mesh_[i].material_;
		device_->SetMaterial(&debug_material);
    device_->SetStreamSource(0, mesh_[i].vertex_, 0, sizeof(VERTEX_BLEND3D));
		device_->SetIndices(mesh_[i].index_);
		device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh_[i].vertex_max_, 0, mesh_[i].index_max_ / 3);
	}

  SafeDeleteArray(p_world);
  device_->SetVertexShader(NULL);
  device_->SetPixelShader(NULL);
	//device_->SetMaterial(&def_material);
	device_->SetRenderState(D3DRS_CULLMODE, def_cull);
}


//-------------------------------------
// LoadMesh()
//-------------------------------------
void FbxModel::Load(
const std::string &path)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 device = nullptr;
	FbxManager *manager = nullptr;
	FbxImporter *importer = nullptr;
	FbxScene *scene = nullptr;
	FbxNode *root = nullptr;
	int i(0);

	// �}�l�[�W������
	manager = FbxManager::Create();
	// �C���|�[�^����
	importer = FbxImporter::Create(manager, "");
	// �V�[���I�u�W�F�N�g����
	scene = FbxScene::Create(manager, path.c_str());


	// �t�@�C���ǂݍ���
	importer->Initialize(path.c_str());
	// �V�[���f�[�^�̒��o
	importer->Import(scene);

	// ���[�g�{�[���̒��o
	root = scene->GetRootNode();

	// ���[�g�{�[���̎擾
	FbxNode *root_bone(GetRootBone(root));

	// �{�[���𐔂���
	bone_count_ = 0;
	bone_cursor_ = 0;
	CountUpBone(root_bone);

	// �{�[���z��𐶐�
	bone_ = new BONE[bone_count_];
	for (i = 0; i < bone_count_; i++)
	{
		bone_[i].id_ = i;
		D3DXMatrixIdentity(&bone_[i].bone_matrix_);
		D3DXMatrixIdentity(&bone_[i].offset_matrix_);
		D3DXMatrixIdentity(&bone_[i].transform_matrix_);
		D3DXMatrixIdentity(&bone_[i].world_matrix_);

		bone_[i].child_ = NULL;
		bone_[i].sibling_ = NULL;

		memset(bone_[i].name_, '\0', 128);

		bone_[i].key_max_ = 0;
		bone_[i].key_ = NULL;
	}

	// ���O���擾
	LoadBoneName(root_bone);

	// �{�[���̊K�w�ǂݍ���
	bone_cursor_ = 0;
	LoadBoneHierarchy(root_bone);

	// �A�j���[�V�������擾
	LoadAnimationKeyFrame(root_bone, scene);

	// ���b�V���z�񐶐�
	mesh_count_ = 0;
	mesh_cursor_ = 0;
	CountUpMesh(root);

	// ���b�V���z��𐶐�
	mesh_ = new MESH[mesh_count_];
	for (i = 0; i < mesh_count_; i++)
	{
		mesh_[i].vertex_ = NULL;
		mesh_[i].index_ = NULL;
		mesh_[i].vertex_max_ = 0;
		mesh_[i].index_max_ = 0;
		memset(&mesh_[i].material_, 0, sizeof(D3DMATERIAL9));
		memset(mesh_[i].texture_filename_, '\0', 128);
		mesh_[i].texture_ = NULL;
		memset(mesh_[i].uvset_name_, '\0', 128);
	}

	// ���b�V���ǂݍ���
	mesh_cursor_ = 0;
	LoadMesh(root);


	// �j������
	scene->Destroy();
	scene = nullptr;

	importer->Destroy();
	importer = nullptr;

	manager->Destroy();
	manager = nullptr;
}


//-------------------------------------
// GetRootBone()
//-------------------------------------
FbxNode *FbxModel::GetRootBone(FbxNode *node)
{
	// �e���Ȃ������烊�^�[��
	if (node == NULL)
	{
		return NULL;
	}

	// �ϐ��錾
	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	// ���[�g�{�[���������烊�^�[��
	if (attribute != NULL &&
		attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		return node;
	}

	// �ċA����
	int child_count(node->GetChildCount());
	int i(0);

	for (i = 0; i < child_count; i++)
	{
		FbxNode *checked(NULL);
		FbxNode *child(node->GetChild(i));

		checked = GetRootBone(child);
		if (checked != NULL)
		{
			return checked;
		}
	}

	return NULL;
}


//-------------------------------------
// CountUpBone()
//-------------------------------------
void FbxModel::CountUpBone(FbxNode *node)
{
	// �e���Ȃ������烊�^�[��
	if (node == NULL)
	{
		return;
	}

	// �ϐ��錾
	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	// �{�[���̐������Z
	if (attribute != NULL &&
		attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		bone_count_++;
	}

	// �ċA����
	int child_max(node->GetChildCount());
	int i(0);

	for (i = 0; i < child_max; i++)
	{
		FbxNode *child(node->GetChild(i));
		CountUpBone(child);
	}

}


//-------------------------------------
// LoadBoneName()
//-------------------------------------
void FbxModel::LoadBoneName(FbxNode *node)
{
	// null�`�F�b�N
	if (node == NULL)
	{
		return;
	}

	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	if (attribute == NULL)
	{
		return;
	}

	if (attribute->GetAttributeType() != FbxNodeAttribute::eSkeleton)
	{
		return;
	}

	BONE *dst_bone(&bone_[bone_cursor_]);
	bone_cursor_++;

	// ���O�̓ǂݍ���
	const char *name = node->GetName();
	strcpy(dst_bone->name_, name);

	// �ċA����
	int child_count(node->GetChildCount());
	int i(0);
	for (i = 0; i < child_count; i++)
	{
		FbxNode *child(node->GetChild(i));
		LoadBoneName(child);
	}
}


//-------------------------------------
// LoadBoneHierarchy()
//-------------------------------------
void FbxModel::LoadBoneHierarchy(FbxNode *node)
{
	if (node == NULL)
	{
		return;
	}

	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	if (attribute == NULL)
	{
		return;
	}

	if (attribute->GetAttributeType() != FbxNodeAttribute::eSkeleton)
	{
		return;
	}

	BONE *dst_bone(&bone_[bone_cursor_]);
	bone_cursor_++;

	int child_count(node->GetChildCount());
	int i(0);
	for (i = 0; i < child_count; i++)
	{
		FbxNode *child(node->GetChild(i));

		attribute = child->GetNodeAttribute();

		if (attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			const char *child_name(child->GetName());

			BONE *child_bone(SearchBoneByName((char*)child_name));

			if (dst_bone->child_ == NULL)
			{
				dst_bone->child_ = child_bone;
			}
			else
			{
				BONE *sibling_end(dst_bone->child_);
				while (sibling_end->sibling_ != NULL)
				{
					sibling_end = sibling_end->sibling_;
				}

				sibling_end->sibling_ = child_bone;
			}
		}
	}

	for (i = 0; i < child_count; i++)
	{
		FbxNode *child(node->GetChild(i));
		LoadBoneHierarchy(child);
	}

}


//-------------------------------------
// SearchBoneByName()
//-------------------------------------
FbxModel::BONE *FbxModel::SearchBoneByName(char *name)
{
	if (bone_ == NULL)
	{
		return NULL;
	}
	if (name == NULL)
	{
		return NULL;
	}

	int i(0);

	for (i = 0; i < bone_count_; i++)
	{
		if (strcmp(bone_[i].name_, name) == 0)
		{
			return bone_ + i;
		}
	}

	return NULL;
}


//-------------------------------------
// LoadAnimationKeyFrame()
//-------------------------------------
void FbxModel::LoadAnimationKeyFrame(FbxNode *node, FbxScene *scene)
{
	// �e���Ȃ������烊�^�[��
	if (node == NULL)
	{
		return;
	}

	// �ϐ��錾
	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	// �{�[���̐������Z
	if (attribute != NULL &&
		attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		LoadAnimationKeyFrameFormNode(node, scene);
	}

	// �ċA����
	int child_max(node->GetChildCount());
	int i(0);

	for (i = 0; i < child_max; i++)
	{
		FbxNode *child(node->GetChild(i));
		LoadAnimationKeyFrame(child, scene);
	}

}


//-------------------------------------
// LoadAnimaitonKeyFrameFromNode()
//-------------------------------------
void FbxModel::LoadAnimationKeyFrameFormNode(FbxNode *node, FbxScene *scene)
{
	// �ϐ��錾
	int i(0), j(0);

	// ���O���擾
	const char *bone_name(node->GetName());
	BONE *dst_bone(SearchBoneByName((char *)bone_name));

	// �O�̂��߃`�F�b�N����
	if (dst_bone == NULL) return;

	// �V�[������A�j���[�V�����X�^�b�N�����擾
	int stack_count(scene->GetSrcObjectCount<FbxAnimStack>());

	// �A�j���[�V�����X�^�b�N�擾(0�����g��Ȃ�)
	if (stack_count == 0) return;

	// �A�j���[�V�����X�^�b�N���擾
	FbxAnimStack *stack(scene->GetSrcObject<FbxAnimStack>(0));

	// ���݂̃A�j���[�V�����X�^�b�N��ݒ�
	scene->SetCurrentAnimationStack(stack);

	// �X�^�b�N����A�j���[�V�������C�������擾
	int layer_count(stack->GetMemberCount<FbxAnimLayer>());

	// �X�^�b�N����A�j���[�V�������C�����擾
	if (layer_count == 0) return;
	FbxAnimLayer *layer(stack->GetMember<FbxAnimLayer>(0));

	// �t���[������擾
	uint64_t one_frame(0);
	float time_scale(0.0f);
	FbxTime::EMode time_mode(scene->GetGlobalSettings().GetTimeMode());

	switch (time_mode)
	{
	case FbxTime::EMode::eFrames24:
		time_scale = 60.0f / 24.0f;
		one_frame = 1924423250;
		break;
	case FbxTime::EMode::eFrames30:
		time_scale = 60.0f / 30.0f;
		one_frame = 1539538600;
		break;
	case FbxTime::EMode::eFrames60:
		time_scale = 60.0f / 60.0f;
		one_frame = 769769300;
		break;
	default:
		time_scale = 1.0f;
		break;
	}

	FbxTime time_end(stack->LocalStop);

	FbxAnimCurve *x_curve(NULL), *y_curve(NULL), *z_curve(NULL);
	int x_key_count(0), y_key_count(0), z_key_count(0);

	x_curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
	y_curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
	z_curve = node->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);

	// �L�[�t���[���̐����擾
	if (x_curve != NULL){ x_key_count = x_curve->KeyGetCount(); }
	if (y_curve != NULL){ y_key_count = y_curve->KeyGetCount(); }
	if (z_curve != NULL){ z_key_count = z_curve->KeyGetCount(); }

	// �L�[�t���[���i�[�p�R���e�i��`
	std::set<FbxTime> key_frames;
	std::set<FbxTime>::iterator it;
	key_frames.clear();

	//�L�[�t���[���̎擾�A�������̂͂܂Ƃ߂������߁ASTL���g�p
	for (int i = 0; i < x_key_count; i++)
	{
		FbxTime work = x_curve->KeyGetTime(i);
		key_frames.insert(work);
	}
	for (int i = 0; i < y_key_count; i++)
	{
		FbxTime work = y_curve->KeyGetTime(i);
		key_frames.insert(work);
	}
	for (int i = 0; i < z_key_count; i++)
	{
		FbxTime work = z_curve->KeyGetTime(i);
		key_frames.insert(work);
	}

	// ��translation, scaling�͏Ȃ��A���Ԃ�ꏏ
	dst_bone->key_max_ = key_frames.size();
	dst_bone->key_ = new KEY_FRAME[dst_bone->key_max_];

	for (int i = 0; i < dst_bone->key_max_; i++)
	{
		dst_bone->key_[i].time_ = 0.0f;
		dst_bone->key_[i].translation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		dst_bone->key_[i].rotation_ = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
		dst_bone->key_[i].scaling_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	int sec(0);
	it = key_frames.begin();
	for (i = 0; i < dst_bone->key_max_; i++)
	{
		int work_frame(0);
		FbxTime key_frame(*it);
		int dummy(0);

		// �L�[�̎��Ԃ��擾
		work_frame = key_frame.Get() / one_frame;
		dst_bone->key_[i].time_ = (float)work_frame;

		// �e�L�[�t���[���ł�rotate�s����擾
		FbxMatrix work_mtx = node->EvaluateLocalTransform(key_frame);
		D3DXMATRIX transform;
		for (int j = 0; j < 16; j++)
		{
			transform.m[j / 4][j % 4] = (float)work_mtx.Get(j / 4, j % 4);
		}

		D3DXMATRIX translation, rotation, scaling;

		// �s�񂩂�e�v�f�𔲂��o��
		ExtractTranslationFromMatrix(&translation, &transform);
		ExtractRotationFromMatrix(&rotation, &transform);
		ExtractScalingFromMatrix(&scaling, &transform);

		// translation�i�[
		dst_bone->key_[i].translation_.x = translation._41;
		dst_bone->key_[i].translation_.y = translation._42;
		dst_bone->key_[i].translation_.z = translation._43;

		// rotation�i�[
		D3DXQuaternionRotationMatrix(&dst_bone->key_[i].rotation_, &rotation);

		// scaling�i�[
		dst_bone->key_[i].scaling_.x = scaling._11;
		dst_bone->key_[i].scaling_.y = scaling._22;
		dst_bone->key_[i].scaling_.z = scaling._33;

		it++;
	}

	// �I�t�Z�b�g�̌v�Z
	FbxTime zero_frame = FBXSDK_TIME_ZERO;
	FbxMatrix init_mtx = node->EvaluateGlobalTransform(zero_frame);
	D3DXMATRIX init;
	for (j = 0; j < 16; j++)
	{
		init.m[j / 4][j % 4] = (float)init_mtx.Get(j / 4, j % 4);
	}
	D3DXMatrixInverse(&dst_bone->offset_matrix_, NULL, &init);

	// �R���e�i�N���A
	key_frames.clear();

	// 0�X�^�[�g�ɋ���
	float min_time(0.0f);
	if (dst_bone->key_max_ > 0)
	{
		min_time = dst_bone->key_[0].time_;
	}

	for (i = 0; i < dst_bone->key_max_; i++)
	{
		if (min_time > dst_bone->key_[i].time_)
		{
			min_time = dst_bone->key_[i].time_;
		}
	}

	for (i = 0; i < dst_bone->key_max_; i++)
	{
		dst_bone->key_[i].time_ -= min_time;
	}

}


//-------------------------------------
// CountUpMesh()
//-------------------------------------
void FbxModel::CountUpMesh(FbxNode *node)
{
	// �e���Ȃ������烊�^�[��
	if (node == NULL)
	{
		return;
	}

	// �ϐ��錾
	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	// �{�[���̐������Z
	if (attribute != NULL &&
		attribute->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		int material_count(node->GetMaterialCount());
		mesh_count_ += material_count;
	}

	// �ċA����
	int child_max(node->GetChildCount());
	int i(0);

	for (i = 0; i < child_max; i++)
	{
		FbxNode *child(node->GetChild(i));
		CountUpMesh(child);
	}
}


//-------------------------------------
// LoadMesh()
//-------------------------------------
void FbxModel::LoadMesh(FbxNode *node)
{
	// �e���Ȃ������烊�^�[��
	if (node == NULL)
	{
		return;
	}

	// �ϐ��錾
	FbxNodeAttribute *attribute(node->GetNodeAttribute());

	// �{�[���̐������Z
	if (attribute != NULL &&
		attribute->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		LoadMeshFromNode(node);
	}

	// �ċA����
	int child_max(node->GetChildCount());
	int i(0);

	for (i = 0; i < child_max; i++)
	{
		FbxNode *child(node->GetChild(i));
		LoadMesh(child);
	}
}


//-------------------------------------
// LoadMeshFromNode()
//-------------------------------------
void FbxModel::LoadMeshFromNode(FbxNode *node)
{
	// �ϐ��錾
	int i(0);

	FbxMesh *mesh(node->GetMesh());

	int material_count(node->GetMaterialCount());

	// �}�e���A�����C���擾
	int layer_count(mesh->GetLayerCount());
	FbxLayerElementMaterial *material_layer(NULL);

	for (i = 0; i < layer_count; i++)
	{
		material_layer = mesh->GetLayer(i)->GetMaterials();
		if (material_layer != NULL)
		{
			break;
		}
	}

	// �X�L���̓ǂݍ���
	int skin_count(mesh->GetDeformerCount(FbxDeformer::eSkin));
	int cluster_count(0);
	FbxSkin *skin(NULL);
	if (skin_count > 0)
	{
		skin = (FbxSkin*)mesh->GetDeformer(0, FbxDeformer::eSkin);
	}
	else
	{
		// �X�L�j���O����Ă��Ȃ��̂ŁAweight��index��0�N���A����
	}


	int primitive_count(mesh->GetPolygonCount());

	int *layer_table(new int[primitive_count]);
	memset(layer_table, 0, sizeof(int) * primitive_count);

	for (i = 0; i < primitive_count; i++)
	{
		int material_index = material_layer->GetIndexArray().GetAt(i);
		layer_table[i] = material_index;
	}


	for (i = 0; i < material_count; i++)
	{
		MESH *dst_mesh(&this->mesh_[mesh_cursor_ + i]);

		// �}�e���A���擾
		LoadMaterialFromNode(node, i);

		LoadTextureFromNode(node, i, dst_mesh->uvset_name_);
	}


	// ���b�V���̒��g���擾
	int material_index(0);
	int primitive_index(0);
	for (material_index = 0; material_index < material_count; material_index++)
	{
		std::vector<int> index_array;
		std::vector<VERTEX_BLEND3D> vertex_array;
		std::vector<VERTEX_BLEND3D>::iterator it;

		int mesh_index(mesh_cursor_ + material_index);
		MESH *dst_mesh(&this->mesh_[mesh_index]);

		for (primitive_index = 0; primitive_index < primitive_count; primitive_index++)
		{
			if (layer_table[primitive_index] != material_index)
			{
				continue;
			}

			int primitive_vertex_num(mesh->GetPolygonSize(primitive_index));

			int base(0);
			for (base = 0; base < primitive_vertex_num - 2; base++)
			{
				for (i = 0; i < 3; i++)
				{
          VERTEX_BLEND3D work_vertex = {};

					int point_index(i);
					if (point_index != 0)
					{
						point_index += base;
					}

					int vertex_id = mesh->GetPolygonVertex(primitive_index, point_index);

					FbxVector4 position = mesh->GetControlPointAt(vertex_id);

					if (position[3] != 0.0f)
					{
						work_vertex.position.x = (float)position[0] / (float)position[3];
						work_vertex.position.y = (float)position[1] / (float)position[3];
						work_vertex.position.z = (float)position[2] / (float)position[3];
					}
					else
					{
						work_vertex.position.x = (float)position[0];
						work_vertex.position.y = (float)position[1];
						work_vertex.position.z = (float)position[2];
					}

					FbxVector4 normal;
					mesh->GetPolygonVertexNormal(primitive_index, point_index, normal);
					if (normal[3] != 0.0f)
					{
						work_vertex.normal.x = (float)normal[0] / (float)normal[3];
						work_vertex.normal.y = (float)normal[1] / (float)normal[3];
						work_vertex.normal.z = (float)normal[2] / (float)normal[3];
					}
					else
					{
						work_vertex.normal.x = (float)normal[0];
						work_vertex.normal.y = (float)normal[1];
						work_vertex.normal.z = (float)normal[2];
					}

					FbxVector2 texcoord(0.0, 0.0);
					bool dummy = false;
					mesh->GetPolygonVertexUV(primitive_index, point_index, dst_mesh->uvset_name_, texcoord, dummy);
          work_vertex.texcoord.x = (float)texcoord[0];
          work_vertex.texcoord.y = 1.0f - (float)texcoord[1];

					LoadBoneIndexAndWeight(skin, &work_vertex, vertex_id);

					//work_vertex.diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					it = find(vertex_array.begin(), vertex_array.end(), work_vertex);

					int vertex_index = distance(vertex_array.begin(), it);

					if (it == vertex_array.end())
					{
						vertex_array.push_back(work_vertex);
					}

					index_array.push_back(vertex_index);
				}
			}
		}

		//LPDIRECT3DDEVICE9 device = NULL;

		int size = index_array.size();
		dst_mesh->index_max_ = size;

		if (FAILED(device_->CreateIndexBuffer(
			sizeof(WORD)* size,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&(dst_mesh->index_),
			NULL)))
		{
			dst_mesh->index_ = NULL;
		}

		WORD *work_index(NULL);
		dst_mesh->index_->Lock(0, 0, (void**)&work_index, 0);

		for (i = 0; i < size; i++)
		{
			work_index[i] = index_array[i];
		}

		dst_mesh->index_->Unlock();


		size = vertex_array.size();
		dst_mesh->vertex_max_ = size;
		if (FAILED(device_->CreateVertexBuffer(
      sizeof(VERTEX_BLEND3D)* size,
      D3DCREATE_MIXED_VERTEXPROCESSING,
			0,
			D3DPOOL_MANAGED,
			&dst_mesh->vertex_,
			NULL)))
		{
			dst_mesh->vertex_ = NULL;
		}

    VERTEX_BLEND3D *work_vertex(NULL);
		dst_mesh->vertex_->Lock(0, 0, (void **)&work_vertex, 0);

		for (i = 0; i < size; i++)
		{
			work_vertex[i] = vertex_array[i];
		}

		dst_mesh->vertex_->Unlock();

		index_array.clear();
		vertex_array.clear();
	}

	delete[] layer_table;

	mesh_cursor_ += material_count;

}


//-------------------------------------
// LoadMaterialFromNode()
//-------------------------------------
void FbxModel::LoadMaterialFromNode(FbxNode *node, int material_index)
{
	FbxSurfaceMaterial *material(node->GetMaterial(material_index));

	if (material == NULL)
	{
		return;
	}

	MESH *dst_mesh(&this->mesh_[mesh_cursor_ + material_index]);

	if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		FbxSurfaceLambert *lambert = (FbxSurfaceLambert*)material;

		dst_mesh->material_.Ambient.r = (float)lambert->Ambient.Get()[0];
		dst_mesh->material_.Ambient.g = (float)lambert->Ambient.Get()[1];
		dst_mesh->material_.Ambient.b = (float)lambert->Ambient.Get()[2];
		//dst_mesh->material_.Ambient.a = (float)lambert->Ambient.Get()[3];



		dst_mesh->material_.Diffuse.r = (float)lambert->Diffuse.Get()[0];
		dst_mesh->material_.Diffuse.g = (float)lambert->Diffuse.Get()[1];
		dst_mesh->material_.Diffuse.b = (float)lambert->Diffuse.Get()[2];
		//dst_mesh->material_.Diffuse.a = (float)lambert->Diffuse.Get()[3];



		dst_mesh->material_.Emissive.r = (float)lambert->Emissive.Get()[0];
		dst_mesh->material_.Emissive.g = (float)lambert->Emissive.Get()[1];
		dst_mesh->material_.Emissive.b = (float)lambert->Emissive.Get()[2];
		//dst_mesh->material_.Emissive.a = (float)lambert->Emissive.Get()[3];


		dst_mesh->material_.Ambient.a = (float)lambert->TransparencyFactor.Get();
		dst_mesh->material_.Diffuse.a = (float)lambert->TransparencyFactor.Get();
		dst_mesh->material_.Emissive.a = (float)lambert->TransparencyFactor.Get();
	}
	else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		FbxSurfacePhong *phong = (FbxSurfacePhong*)material;

		dst_mesh->material_.Ambient.r = (float)phong->Ambient.Get()[0];
		dst_mesh->material_.Ambient.g = (float)phong->Ambient.Get()[1];
		dst_mesh->material_.Ambient.b = (float)phong->Ambient.Get()[2];
		//dst_mesh->material_.Ambient.a = (float)phong->Ambient.Get()[3];



		dst_mesh->material_.Diffuse.r = (float)phong->Diffuse.Get()[0];
		dst_mesh->material_.Diffuse.g = (float)phong->Diffuse.Get()[1];
		dst_mesh->material_.Diffuse.b = (float)phong->Diffuse.Get()[2];
		//dst_mesh->material_.Diffuse.a = (float)phong->Diffuse.Get()[3];



		dst_mesh->material_.Emissive.r = (float)phong->Emissive.Get()[0];
		dst_mesh->material_.Emissive.g = (float)phong->Emissive.Get()[1];
		dst_mesh->material_.Emissive.b = (float)phong->Emissive.Get()[2];
		//dst_mesh->material_.Emissive.a = (float)phong->Emissive.Get()[3];


		dst_mesh->material_.Specular.r = (float)phong->Specular.Get()[0];
		dst_mesh->material_.Specular.g = (float)phong->Specular.Get()[1];
		dst_mesh->material_.Specular.b = (float)phong->Specular.Get()[2];
		//dst_mesh->material_.Specular.a = (float)phong->Specular.Get()[3];


		dst_mesh->material_.Ambient.a = (float)phong->TransparencyFactor.Get();
		dst_mesh->material_.Diffuse.a = (float)phong->TransparencyFactor.Get();
		dst_mesh->material_.Emissive.a = (float)phong->TransparencyFactor.Get();
		dst_mesh->material_.Specular.a = (float)phong->TransparencyFactor.Get();

		dst_mesh->material_.Power = (float)phong->Shininess.Get();
	}
}


//-------------------------------------
// LoadTextureFromNode()
//-------------------------------------
void FbxModel::LoadTextureFromNode(FbxNode *node, int material_index, char *dst_uvset)
{
	// �ϐ��錾
	FbxSurfaceMaterial *material(node->GetMaterial(material_index));

	if (material == NULL)
	{
		return;
	}

	MESH *dst_mesh(&this->mesh_[mesh_cursor_ + material_index]);
	FbxProperty diffuse_property(material->FindProperty(FbxSurfaceMaterial::sDiffuse));
	int layered_texture_count(diffuse_property.GetSrcObjectCount<FbxLayeredTexture>());

	if (layered_texture_count == 0)
	{
		int texture_count = diffuse_property.GetSrcObjectCount<FbxFileTexture>();
		int i(0);
    if (texture_count == 0) {
      for (int i = 0; i < mesh_count_; ++i) {
        mesh_[i].texture_ = TextureManager::Instance().Find("Model", "tree");
      }
    }

		for (i = 0; i < texture_count; i++)
		{
			FbxFileTexture *texture = diffuse_property.GetSrcObject<FbxFileTexture>(i);

			if (texture == NULL)
			{
        continue;
			}

      // �e�N�X�`������
      const char *texture_filename = texture->GetRelativeFileName();
      char texture_pass[20] = {0};
      int pass_num(16);
      for( ; texture_filename[pass_num] != NULL; ++pass_num ) {
        texture_pass[pass_num - 16] = texture_filename[pass_num];
      }
      
      strcpy(dst_mesh->texture_filename_, texture_pass);

			strcpy(dst_uvset, texture->UVSet.Get().Buffer());
      dst_mesh->texture_ = TextureManager::Instance().Find("Model", texture_pass);

			break;
		}
	}

	return;
}


//-------------------------------------
// LoadBoneIndexAndWeight()
//-------------------------------------
void FbxModel::LoadBoneIndexAndWeight(FbxSkin *skin, VERTEX_BLEND3D *dst_vertex, int vertex_id)
{
	if (skin == NULL)
	{
		return;
	}

	int cluster_count(skin->GetClusterCount());
	int inful_bone_index = 0;
	int i(0), j(0);

	for (i = 0; i < cluster_count; i++)
	{
		FbxCluster *cluster(skin->GetCluster(i));

		int inful_count(cluster->GetControlPointIndicesCount());
		for (j = 0; j < inful_count; j++)
		{
			if (vertex_id == cluster->GetControlPointIndices()[j])
			{
				break;
			}
		}

		if (j == inful_count)
		{
			continue;
		}

		char *bone_name = (char*)cluster->GetLink()->GetName();

		BONE *work_bone = SearchBoneByName(bone_name);
    // 32�r�b�g�Ɏl��
    dst_vertex->matrix_index[inful_bone_index] = work_bone->id_;
    //dst_vertex->matrix_index |= work_bone->id_ << (8 * inful_bone_index);

		if (inful_bone_index != 3)
		{
			dst_vertex->weight[inful_bone_index] = (float)cluster->GetControlPointWeights()[j];
		}

		inful_bone_index++;

		if (inful_bone_index == 4)
		{
			break;
		}
	}
}


//-------------------------------------
// ExatractTranslationFromMatrix()
//-------------------------------------
void FbxModel::ExtractTranslationFromMatrix(D3DXMATRIX *out, D3DXMATRIX *src)
{
	D3DXMATRIX work;
	D3DXMatrixIdentity(&work);
	work._41 = src->_41;
	work._42 = src->_42;
	work._43 = src->_43;
	*out = work;
}


//-------------------------------------
// ExtractRotationFromMatrix()
//-------------------------------------
void FbxModel::ExtractRotationFromMatrix(D3DXMATRIX *out, D3DXMATRIX *src)
{
	D3DXMATRIX work;
	D3DXVECTOR3 e;
	work = *src;

	work._41 = 0.0f;
	work._42 = 0.0f;
	work._43 = 0.0f;

	e.x = work._11;
	e.y = work._21;
	e.z = work._31;
	D3DXVec3Normalize(&e, &e);
	work._11 = e.x;
	work._21 = e.y;
	work._31 = e.z;

	e.x = work._12;
	e.y = work._22;
	e.z = work._32;
	D3DXVec3Normalize(&e, &e);
	work._12 = e.x;
	work._22 = e.y;
	work._32 = e.z;

	e.x = work._13;
	e.y = work._23;
	e.z = work._33;
	D3DXVec3Normalize(&e, &e);
	work._13 = e.x;
	work._23 = e.y;
	work._33 = e.z;

	*out = work;
}


//-------------------------------------
// ExtractScalingEromMatrix()
//-------------------------------------
void FbxModel::ExtractScalingFromMatrix(D3DXMATRIX *out, D3DXMATRIX *src)
{
	D3DXMATRIX work;
	D3DXVECTOR3 e;
	D3DXVECTOR3 scale;

	work = *src;

	e.x = work._11;
	e.y = work._12;
	e.z = work._13;
	scale.x = D3DXVec3Length(&e);


	e.x = work._21;
	e.y = work._22;
	e.z = work._23;
	scale.y = D3DXVec3Length(&e);


	e.x = work._31;
	e.y = work._32;
	e.z = work._33;
	scale.z = D3DXVec3Length(&e);

	D3DXMatrixIdentity(&work);
	work._11 = scale.x;
	work._22 = scale.y;
	work._33 = scale.z;

	*out = work;
}


//-------------------------------------
// UpdateBoneMatrix()
//-------------------------------------
void FbxModel::UpdateBoneMatrix(BONE *subject, D3DXMATRIX *parent)
{
	KEY_FRAME *prev(NULL), *next(NULL);
	int i(0);
	float t(0.0f);
	float length(0.0f);
	D3DXMATRIX trs_mtx, scl_mtx, rot_mtx;
	float time(cur_time_);
	int key_max(subject->key_max_);

	for (i = 0; i < key_max - 1; i++)
	{
		if (subject->key_[i].time_ <= cur_time_ && cur_time_ <= subject->key_[i + 1].time_)
		{
			prev = &subject->key_[i];
			next = &subject->key_[i + 1];
			length = next->time_ - prev->time_;

			if (length < 0.0001f)
			{
				length = 0.0f;
				t = 0.0f;
			}
			else
			{
				t = (cur_time_ - prev->time_) / length;
			}
			break;
		}
	}

	if (i == key_max - 1)
	{
		length = subject->key_[key_max - 1].time_ - subject->key_[key_max - 2].time_;
		prev = &subject->key_[key_max - 2];
		next = &subject->key_[key_max - 1];
		t = 1.0f;
	}

	// scaling�̐ݒ�
	D3DXMatrixIdentity(&scl_mtx);
	scl_mtx._11 = t * (next->scaling_.x) + (1.0f - t) * (prev->scaling_.x);
	scl_mtx._22 = t * (next->scaling_.y) + (1.0f - t) * (prev->scaling_.y);
	scl_mtx._33 = t * (next->scaling_.z) + (1.0f - t) * (prev->scaling_.z);
	
	// rotation�̐ݒ�
	D3DXMatrixIdentity(&rot_mtx);
	D3DXQUATERNION quat;
	D3DXQuaternionSlerp(&quat, &prev->rotation_, &next->rotation_, t);
	D3DXMatrixRotationQuaternion(&rot_mtx, &quat);


	// translation�̐ݒ�
	D3DXMatrixIdentity(&trs_mtx);
	trs_mtx._41 = (1.0f - t) * (prev->translation_.x) + t * (next->translation_.x);
	trs_mtx._42 = (1.0f - t) * (prev->translation_.y) + t * (next->translation_.y);
	trs_mtx._43 = (1.0f - t) * (prev->translation_.z) + t * (next->translation_.z);

	D3DXMatrixIdentity(&subject->bone_matrix_);
	D3DXMatrixMultiply(&subject->bone_matrix_, &subject->bone_matrix_, &scl_mtx);
	D3DXMatrixMultiply(&subject->bone_matrix_, &subject->bone_matrix_, &rot_mtx);
	D3DXMatrixMultiply(&subject->bone_matrix_, &subject->bone_matrix_, &trs_mtx);

	// ���ɓn���s��̌v�Z
	D3DXMatrixMultiply(&subject->transform_matrix_, &subject->bone_matrix_, parent);

	// ���[���h�̍X�V
	D3DXMatrixMultiply(&subject->world_matrix_, &subject->offset_matrix_, &subject->transform_matrix_);

	if (subject->child_ != NULL)
	{
		UpdateBoneMatrix(subject->child_, &subject->transform_matrix_);
	}
	if (subject->sibling_ != NULL)
	{
		UpdateBoneMatrix(subject->sibling_, parent);
	}
}


//-------------------------------------
// end of file
//-------------------------------------
