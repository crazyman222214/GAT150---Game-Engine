#pragma once
#include "Transform.h"
#include "Model.h"

#include <string>

class Renderer;
class Scene;
class Input;

class Actor
{
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}
	Actor(const Transform& transform, Model* model) : m_transform{ transform }, m_model{model} {}

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float damping) { m_lifespan = m_lifespan; }

	const Transform& GetTransform() { return m_transform; }

	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }


	virtual void OnCollision(Actor* actor) = 0;
	float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }

	void UpdateTransformToMouse(Input& input, Vector2 previousPosition);

	friend class Scene;


protected:
	std::string m_tag;
	bool m_destroyed = false;
	float m_lifespan = 0.0f;

	Transform m_transform;
	Vector2 m_velocity{ 0, 0 };
	float m_damping = 0.0f;

	Model* m_model{ nullptr };
	Scene* m_scene{nullptr};
};