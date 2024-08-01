#include "Particle.h"

void Particle::Update(float dt)
{
	if (m_lifespan != 0) m_lifespan -= dt;
	if (m_lifespan <= 0) isActive = false;
	m_position += (m_velocity * dt);
}

void Particle::Draw(Renderer& renderer)
{
	if (m_lifespan > 0) renderer.DrawRect(m_position.x, m_position.y, 4.0f, 4.0f);
}

void Particle::Initalize(const Data& data)
{
	isActive = true;
	m_position = data.position;
	m_velocity = data.velocity;
	m_lifespan = data.lifespan;
	r = data.r;
	g = data.g;
	b = data.b;
	a = data.a;
}
