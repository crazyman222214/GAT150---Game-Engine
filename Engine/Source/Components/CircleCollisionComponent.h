#pragma once
#include "CollisionComponent.h"

class CircleCollisionComponent : public CollisionComponent {
public:
	CLASS_DECLARATION(CircleCollisionComponent)

	void Initialize() override;
	void Update(float dt) override;
	bool CheckCollision(const CollisionComponent* collision) override;

public:
	float radius = 0.0f;

	// Inherited via CollisionComponent
	std::unique_ptr<Object> Clone() override;
};