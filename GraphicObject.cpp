#include "GraphicObject.h"
GraphicObject::GraphicObject()
{
	this->material = nullptr;
	this->mesh = nullptr;
	this->SetPosition({ 0.0,0.0,0.0 });
	this->SetColor({ 0.0,0.0,0.0 });
	this->SetAngle(0.0);
	this->recalculateMatrix();
};
GraphicObject::GraphicObject(glm::vec3 pos, glm::vec3 color, float angle)
{
	this->material = nullptr;
	this->mesh = nullptr;
	this->SetPosition(pos);
	this->SetColor(color);
	this->SetAngle(angle);
	this->recalculateMatrix();
}
GraphicObject::GraphicObject(glm::vec3 pos, glm::vec3 color, float angle, std::shared_ptr<Material> mat)
{
	this->SetMaterial(mat);
	this->mesh = nullptr;
	this->SetPosition(pos);
	this->SetColor(color);
	this->SetAngle(angle);
	this->recalculateMatrix();
}

void GraphicObject::recalculateMatrix()
{

	GLfloat* matrix = this->modelMatrix;
	float angle = glm::radians(this->GetAngle());
	///X axis
	//matrix[0] =  1.0; matrix[4] = 0.0;			  matrix[8]  = 0.0;
	//matrix[1] =  0.0; matrix[5] = cos(angle*rad); matrix[9]  = -sin(angle * rad);
	//matrix[2] =  0.0; matrix[6] = sin(angle*rad); matrix[10] = cos(angle * rad);
	//matrix[3] =  0.0; matrix[7] = 0.0;			  matrix[11] = 0.0;
	///Z axis
	/*
	matrix[0] = cos(angle * rad); matrix[4] = -sin(angle * rad); matrix[8]  = 0.0;
	matrix[1] = sin(angle * rad); matrix[5] = cos(angle * rad);  matrix[9]  = 0.0;
	matrix[2] = 0.0;			  matrix[6] = 0.0;			     matrix[10] = 1.0;
	matrix[3] = 0.0;			  matrix[7] = 0.0;			     matrix[11] = 0.0;
	*/
	///Y axis
	matrix[0] = cos(angle);        matrix[4] = 0.0; matrix[8] = sin(angle);
	matrix[1] = 0.0;			   matrix[5] = 1.0; matrix[9] = 0.0;
	matrix[2] = -sin(angle);	   matrix[6] = 0.0; matrix[10] = cos(angle);
	matrix[3] = 0.0;			   matrix[7] = 0.0; matrix[11] = 0.0;

	matrix[12] = this->position[0];
	matrix[13] = this->position[1];
	matrix[14] = this->position[2];

	matrix[15] = 1;
}
void GraphicObject::draw()
{
	glColor3f(this->color.r, this->color.g, this->color.b);

	if (this->material != nullptr)
		this->material->Apply();

	glPushMatrix();
	glMultMatrixf(this->modelMatrix);
	if (this->mesh != nullptr)
		this->mesh->Draw();
	else
		glutSolidTeapot(1.0);
	glPopMatrix();
}
void GraphicObject::SetPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
	this->recalculateMatrix();
}
glm::vec3 GraphicObject::GetPosition()
{
	return this->position;
}
void GraphicObject::SetColor(glm::vec3 newColor)
{
	this->color = newColor;
}
glm::vec3 GraphicObject::GetColor()
{
	return this->color;
}
void GraphicObject::SetAngle(float newAngle)
{
	this->angle = newAngle;
	this->recalculateMatrix();
}
float GraphicObject::GetAngle()
{
	return this->angle;
}
void GraphicObject::SetMaterial(std::shared_ptr<Material> mat)
{
	this->material = mat;
	return;
}
void GraphicObject::SetMesh(std::shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
	return;
}
