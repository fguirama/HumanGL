#include "humanGL.h"
#include "class/BodyPart.hpp"
#include <GL/glew.h>

void drawBodyPart(BodyPart* part, MatrixStack &stack) {
	if (!part)
		return;

	// 1. Sauvegarde matrice parent
	stack.push();

	// 2. Appliquer transformations locales
	Matrix4 model = Matrix4::identity();

	model.translate(part->localPosition);
	model.rotateX(part->localRotation.x);
	model.rotateY(part->localRotation.y);
	model.rotateZ(part->localRotation.z);
	model.scale(part->localScale);
	stack.top() *= model;

	// Appliquer au stack
	stack.top() = stack.top() * model;

	// 3. Envoyer au shader
	glUniformMatrix4fv(
		glGetUniformLocation(shaderProgram, "uModel"),
		1,
		GL_FALSE,
		stack.top().data()
	);

	// 4. Draw du cube (1 seul draw call obligatoire)
	drawCube();

	// 5. Dessiner les enfants (hiérarchie)
	for (auto& child : part->getChildren()) {
		drawBodyPart(child.get(), stack);
	}

	// =========================
	// 6. Restaurer matrice parent
	// =========================
	stack.pop();
}
