#pragma once
#include "d3d9.h"
#include "d3dx9.h"

class CCamera
{
public:
	enum CameraType{ ECT_LANDOBJECT, ECT_AIRCRAFT };
	CCamera(CameraType cameraType);
	~CCamera();

	void Reset(D3DXVECTOR3 pos, D3DXVECTOR3 look, D3DXVECTOR3 right, D3DXVECTOR3 up);

	void strafe(float units);		//left / right
	void fly(float units);			//up / down
	void walk(float units);			//forward / backward

	void pitch(float angle);		// rotate on right vector
	void yaw(float angle);			// rotate on up vector
	void roll(float angle);			// rotate on look vector

	CMatrix GetView();
	void SetCameraType(CameraType cameraType);
	D3DXVECTOR3* GetPosition();
	void SetPosition(D3DXVECTOR3* pos);
	
	D3DXVECTOR3* GetRight();
	D3DXVECTOR3* GetUp();
	D3DXVECTOR3* GetLook();

	CMatrix GetProject();
	void SetProject(float fFov, float fAspect, float fNear, float fFar);
private:
	CameraType m_eCameraType;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	D3DXVECTOR3 m_Look;
	D3DXVECTOR3 m_Pos;
	CMatrix m_proj;
	CMatrix m_view;
};