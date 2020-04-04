#pragma once
using namespace std;

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>

const INT WINSIZEX = 1280;
const INT WINSIZEY = 720;
static INT Width = 20;
static INT Height = 10;
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix = D3DXMATRIX;

#define g_Device DXUTGetD3D9Device()
#define DeltaTime DXUTGetElapsedTime()

#include "CSingleton.h"
#include "CGraphicsManager.h"
#include "CCameraManager.h"
#include "CInputManager.h"
#include "CTexture.h"
#include "CNode.h"
#include "CAStarMap.h"
#include "CAStar.h"