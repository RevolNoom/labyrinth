#pragma once
#include "BaseObject.h"

class Sprite2D : public BaseObject
{
protected:
	GLint		m_iWidth;
	GLint		m_iHeight;
	GLuint		m_vboId;

public:
	Sprite2D() : BaseObject(), m_iWidth(0), m_iHeight(0), m_vboId(0) {}
	Sprite2D(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Sprite2D(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	Sprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	// Rev's mod:
	// Obviously, a Sprite2D only use 
	// Sprite2D.nfg model and TextureShader
	// So, remove them from constructor
	Sprite2D(std::shared_ptr<Texture> texture);
	
	~Sprite2D();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

	virtual void		Set2DPosition(GLint x, GLint y);
	virtual void		Set2DPosition(Vector2 position);
	virtual void		SetSize(GLint width, GLint height);

};

