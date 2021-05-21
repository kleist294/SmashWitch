#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

void Camera_Init();
void Camera_Update();
void Camera_SetMatrixToDevice();


const D3DXVECTOR3* Camera_GetFrontVector(void);
const D3DXVECTOR3* Camera_GetRightVector(void);
const D3DXVECTOR3* Camera_GetUpVector(void);

const D3DXVECTOR3* Camera_GetPosition(void);
const D3DXVECTOR3* Camera_GetAt(void);

const D3DXMATRIX& Camera_GetViewMatrix();

#endif