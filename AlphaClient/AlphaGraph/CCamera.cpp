#include "stdafx.h"

#include "CCamera.h"


CCamera::CCamera( CameraType cameraType ): m_eCameraType(cameraType)
{

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
	D3DXVec3TransformCoord(&m_Look, &m_Pos, &tMat);
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
	D3DXVec3TransformCoord(&m_Look, &m_Pos, &tMat);
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

void CCamera::GetViewMatrix(D3DXMATRIX* vOut)
{
	D3DXVec3Normalize(&m_Look, &m_Look);

	D3DXVec3Cross(&m_Up, &m_Look, &m_Right);
	D3DXVec3Normalize(&m_Up, &m_Up);

	D3DXVec3Cross(&m_Right, &m_Up, &m_Look);
	D3DXVec3Normalize(&m_Right, &m_Right);

	float x = -D3DXVec3Dot(&m_Right, &m_Pos);
	float y = -D3DXVec3Dot(&m_Up, &m_Pos);
	float z = -D3DXVec3Dot(&m_Look, &m_Pos);

	(*vOut)(0, 0) = m_Right.x;
	(*vOut)(0, 1) = m_Up.x;
	(*vOut)(0, 2) = m_Look.x;
	(*vOut)(0, 3) = 0;

	(*vOut)(1, 0) = m_Right.y;
	(*vOut)(1, 1) = m_Up.y;
	(*vOut)(1, 2) = m_Look.y;
	(*vOut)(1, 3) = 0;

	(*vOut)(2, 0) = m_Right.z;
	(*vOut)(2, 1) = m_Up.z;
	(*vOut)(2, 2) = m_Look.z;
	(*vOut)(2, 3) = 0;

	(*vOut)(3, 0) = x;
	(*vOut)(3, 1) = y;
	(*vOut)(3, 2) = z;
	(*vOut)(3, 3) = 1;
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
