#include "stdafx.h"

#include "CCamera.h"


CCamera::CCamera( CameraType cameraType ): m_eCameraType(cameraType)
{
	m_Look = D3DXVECTOR3(0, 0, 1);
	m_Right = D3DXVECTOR3(1, 0, 0);
	m_Up = D3DXVECTOR3(0, 1, 0);
}

CCamera::~CCamera()
{

}

void CCamera::strafe( float units )
{
	switch (m_eCameraType)
	{
	case ECT_LANDOBJECT:
		m_Pos += D3DXVECTOR3(m_Right.x, 0, m_Right.z) * units;
		break;
	case ECT_AIRCRAFT:
		m_Pos += m_Right * units;
		break;
	}
}

void CCamera::fly( float units )
{
	switch (m_eCameraType)
	{
	case ECT_LANDOBJECT:
		m_Pos.y += units;
		break;
	case ECT_AIRCRAFT:
		m_Pos += m_Up * units;
		break;
	}
}

void CCamera::walk( float units )
{
	switch (m_eCameraType)
	{
	case ECT_LANDOBJECT:
		m_Pos += D3DXVECTOR3(m_Look.x, 0, m_Look.z) * units;
		break;
	case ECT_AIRCRAFT:
		m_Pos += m_Look * units;
		break;
	}
}

void CCamera::pitch( float angle )
{
	D3DXMATRIX tMat;
	D3DXMatrixRotationAxis(&tMat, &m_Right, angle);
	D3DXVec3TransformCoord(&m_Up, &m_Up, &tMat);
	D3DXVec3TransformCoord(&m_Look, &m_Look, &tMat);
}

void CCamera::yaw( float angle )
{
	D3DXMATRIX tMat;
	switch (m_eCameraType)
	{
	case ECT_LANDOBJECT:
		{
			D3DXMatrixRotationY(&tMat, angle);
			break;
		}	
	case ECT_AIRCRAFT:
		{
			D3DXMatrixRotationAxis(&tMat, &m_Up, angle);
			break;
		}
	}
	D3DXVec3TransformCoord(&m_Right, &m_Right, &tMat);
	D3DXVec3TransformCoord(&m_Look, &m_Look, &tMat);
}

void CCamera::roll( float angle )
{
	if (m_eCameraType == ECT_AIRCRAFT)
	{
		D3DXMATRIX tMat;
		D3DXMatrixRotationAxis(&tMat, &m_Look, angle);
		D3DXVec3TransformCoord(&m_Up, &m_Up, &tMat);
		D3DXVec3TransformCoord(&m_Right, &m_Right, &tMat);
	}
}

CMatrix CCamera::GetView()
{
	D3DXVec3Normalize(&m_Look, &m_Look);

	D3DXVec3Cross(&m_Up, &m_Look, &m_Right);
	D3DXVec3Normalize(&m_Up, &m_Up);

	D3DXVec3Cross(&m_Right, &m_Up, &m_Look);
	D3DXVec3Normalize(&m_Right, &m_Right);

	float x = -D3DXVec3Dot(&m_Right, &m_Pos);
	float y = -D3DXVec3Dot(&m_Up, &m_Pos);
	float z = -D3DXVec3Dot(&m_Look, &m_Pos);

	m_view[0][0] = m_Right.x;
	m_view[0][1] = m_Up.x;
	m_view[0][2] = m_Look.x;
	m_view[0][3] = 0;

	m_view[1][0] = m_Right.y;
	m_view[1][1] = m_Up.y;
	m_view[1][2] = m_Look.y;
	m_view[1][3] = 0;

	m_view[2][0] = m_Right.z;
	m_view[2][1] = m_Up.z;
	m_view[2][2] = m_Look.z;
	m_view[2][3] = 0;

	m_view[3][0] = x;
	m_view[3][1] = y;
	m_view[3][2] = z;
	m_view[3][3] = 1;

	return m_view;
}

void CCamera::SetCameraType( CameraType cameraType )
{
	m_eCameraType = cameraType;
}

D3DXVECTOR3* CCamera::GetPosition()
{
	return &m_Pos;
}

void CCamera::SetPosition( D3DXVECTOR3* pos )
{
	m_Pos = *pos;
}

D3DXVECTOR3* CCamera::GetRight()
{
	return &m_Right;
}

D3DXVECTOR3* CCamera::GetUp()
{
	return &m_Up;
}

D3DXVECTOR3* CCamera::GetLook()
{
	return &m_Look;
}

void CCamera::SetProject(float fFov, float fAspect, float fNear, float fFar)
{
	float fctg = atanf(fFov / 2);
	float h = 1.0f / fctg;
	float w = h / fAspect;
	float q = fFar / ( fFar - fNear );
	memset ( &m_proj, 0, sizeof(CMatrix));
	m_proj.C[0][0] = w;
	m_proj.C[1][1] = h;
	m_proj.C[2][2] = q;
	m_proj.C[2][3] = 1.0f;
	m_proj.C[3][2] = -q * fNear;
}

CMatrix CCamera::GetProject()
{
	return m_proj;
}

void CCamera::Reset(D3DXVECTOR3 pos, D3DXVECTOR3 look, D3DXVECTOR3 right, D3DXVECTOR3 up)
{
	m_Pos = pos;
	m_Look = look;
	m_Right = right;
	m_Up = up;
}
