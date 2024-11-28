#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "GraphicObject.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "MazeGenerator.h" // Подключаем генератор лабиринтов

extern std::vector<glm::vec3> teapotColors;

extern std::vector<GraphicObject> DrawQueue;
extern std::vector<std::shared_ptr<Material>> Materials;
extern std::vector<std::shared_ptr<Mesh>> Meshes;

extern Camera MainCamera;
extern Light MainLight;

// Список игровых объектов, расположенных на карте
extern std::shared_ptr<GameObject> mapObjects[21][21];

// Графический объект для плоскости
extern GraphicObject planeGraphicObject;

extern LARGE_INTEGER StartCounter, Frequency;

// Динамический массив для карты лабиринта
extern std::vector<std::vector<int>> generatedPathMap;

void initData();
