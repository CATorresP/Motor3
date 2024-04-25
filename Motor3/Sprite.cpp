#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>


Sprite::Sprite() : vboID(0)
{

}

Sprite::~Sprite()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::init(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	// Revisamos que exista una identificación de un buffer asignado
	if (this->vboID == 0) {
		// Creamos un buffer // reservamos un espacio en el GPU
		glGenBuffers(1, &vboID);
	}
	Vertex vertexData[6];
	// Asignamos valores a cada vertice triangulo inferior izquierda y superior derecha
	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);

	for (size_t i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 0, 255);
	}

	vertexData[1].setColor(0, 255, 0, 255);
	vertexData[4].setColor( 0,0, 255, 255);

	// Enlazamos nuestro buffer al contexto definiendo el tipo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// Asignamos valores en la gpu enviandole el tipo de buffer enlazado actualmente y el tamaño en bytes, finalmente el tipo de asignación que es estatico para pocos cambios
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Desenlazamos el buffer del contexto
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// habilitamos
		
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)offsetof(Vertex, position)
	);
	glVertexAttribPointer(
		1,
		4,
		GL_UNSIGNED_BYTE,
		GL_FALSE,
		sizeof(Vertex),
		(void*)offsetof(Vertex, color)
	);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::setPosition()
{

}
