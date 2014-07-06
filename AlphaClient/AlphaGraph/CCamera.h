#pragma once
#include "d3d9.h"
#include "d3dx9.h"

class CCamera
{
public:
	enum CameraType{ ECT_LANDOBJECT, ECT_AIRCRAFT };
	CCamera(CameraType cameraType);
	~CCamera();

	void strafe(float units);		//left / right
	void fly(float units);			//up / down
	void walk(float units);			//forward / backward

	void pitch(float angle);		// rotate on right vector
	void yaw(float angle);			// rotate on up vector
	void roll(float angle);			// rotate on look vector

	void getViewMatrix(D3DXMATRIX* vOut);
	void SetCameraType(CameraType cameraType);
	D3DXVECTOR3* GetPosition();
	void SetPosition(D3DXVECTOR3* pos);
	
	D3DXVECTOR3* GetRight();
	D3DXVECTOR3* GetUp();
	D3DXVECTOR3* GetLook();

private:
	CameraType m_eCameraType;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	D3DXVECTOR3 m_Look;
	D3DXVECTOR3 m_Pos;
};