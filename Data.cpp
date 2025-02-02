#include "Data.h"
#include "MazeGenerator.h"

std::vector<glm::vec3> teapotColors;

std::vector<GraphicObject> DrawQueue;
Camera MainCamera;
Light MainLight;

std::vector<std::shared_ptr<Material>> Materials;
std::vector<std::shared_ptr<Mesh>> Meshes;
LARGE_INTEGER StartCounter, Frequency;

const int mazeWidth = 10; // Ширина лабиринта
const int mazeHeight = 10; // Высота лабиринта

std::vector<std::vector<int>> pathMap;
std::shared_ptr<GameObject> mapObjects[21][21];
GraphicObject planeGraphicObject;

void initData()
{
    QueryPerformanceCounter(&StartCounter);
    QueryPerformanceFrequency(&Frequency);

    teapotColors = { {1.0,1.0,1.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{1.0,1.0,0.0}, {1.0,0.0,1.0} };

    MainCamera.SetPosition({ 10, 15, 17.5 });

    Materials.emplace_back(std::make_shared<Material>(R"(assets\materials\mat1.txt)"));//White
    Materials.emplace_back(std::make_shared<Material>(R"(assets\materials\mat2.txt)"));//Blue Shiny
    Materials.emplace_back(std::make_shared<Material>(R"(assets\materials\mat3.txt)"));//Orange Shiny
    Materials.emplace_back(std::make_shared<Material>(R"(assets\materials\mat4.txt)"));//Green Ambient

    Meshes.emplace_back(std::make_shared<Mesh>(R"(assets\models\ChamferBox.obj)"));//Movable
    Meshes.emplace_back(std::make_shared<Mesh>(R"(assets\models\Box.obj)"));//Walls
    Meshes.emplace_back(std::make_shared<Mesh>(R"(assets\models\Sphere.obj)")); //Entity
    Meshes.emplace_back(std::make_shared<Mesh>(R"(assets\models\SimplePlane.obj)"));//Floor
    // Meshes.emplace_back(std::make_shared<Mesh>(R"(assets\models\Krafton.obj)")); 

    planeGraphicObject.SetMesh(Meshes[3]);
    planeGraphicObject.SetMaterial(Materials[0]);
    planeGraphicObject.SetPosition({ 0,-0.501,0 });

    GraphicObject chambox, graybox, darkbox;
    chambox.SetMesh(Meshes[0]);
    chambox.SetMaterial(Materials[2]);

    graybox.SetMesh(Meshes[1]);
    graybox.SetMaterial(Materials[1]);

    darkbox.SetMesh(Meshes[1]);
    darkbox.SetMaterial(Materials[3]);

    // Генерация лабиринта
    pathMap = MazeGenerator::generate(mazeWidth, mazeHeight);
    // Устанавливаем границы
    for (int i = 0; i < 21; ++i) {
        pathMap[0][i] = 3;
        pathMap[21 - 1][i] = 3;
        pathMap[i][0] = 3;
        pathMap[i][21 - 1] = 3;
    }
    

    // Обработка сгенерированного лабиринта
    for (int i = 0; i < pathMap.size(); i++) {
        for (int j = 0; j < pathMap[i].size(); j++) {
            if (pathMap[i][j]) {
                mapObjects[i][j] = std::make_shared<GameObject>();
                mapObjects[i][j]->SetPosition(i - 10, j - 10);
                switch (pathMap[i][j]) {
                default: break;
                case 1:
                    mapObjects[i][j]->SetGraphicObject(chambox); break;
                case 2:
                    mapObjects[i][j]->SetGraphicObject(graybox); break;
                case 3:
                    mapObjects[i][j]->SetGraphicObject(darkbox); break;
                }
            }
        }
    }
}
