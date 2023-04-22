// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(
    ParticleEmitterDescriptor descriptor,
    int num
)
:   m_descriptor(descriptor)
,   m_position(engine::Vector2::zero())
,   m_currentFrameTime(0)
,   m_lastParticleCreationTime(0)
{
    {
        auto *pool = new engine::ObjectPool<ParticleEmitterItem>(num, [&](void) {
            auto *sprite = descriptor.creatorFunction();
            ParticleEmitterItem *item = new ParticleEmitterItem(sprite);
            return item;
        });
        m_allParticles = std::unique_ptr<engine::ObjectPool<ParticleEmitterItem>>(std::move(pool));
    }
}

void ParticleEmitter::SetPosition(engine::Vector2 value)
{
    m_position = value;
}

void ParticleEmitter::FrameUpdate(Uint64 totalTime)
{
    // Check for particles that need to be killed off
    std::vector<ParticleEmitterItem*>::iterator it = m_aliveParticles.begin();
    while (it != m_aliveParticles.end()) {
        auto *item = (*it);
        if (item->GetAge(totalTime) > m_descriptor.lifetime) {
            KillParticle(item);
            m_allParticles->PutBack(item);
            it = m_aliveParticles.erase(it);
        } else {
            ++it;
        }
    }

    // Generate a particle if needed
    if (m_lastParticleCreationTime + m_descriptor.timeInterval <= totalTime) {
        GenerateParticle();
        m_lastParticleCreationTime = totalTime;
    }

    // Update current time so updating particles can work with it
    m_currentFrameTime = totalTime;

    // Update all living particles
    for (auto it = m_aliveParticles.begin(); it != m_aliveParticles.end(); it++) {
        UpdateParticle(*it);
    }

    //printf("ParticleEmitter:: particle.coutn=%d\n", (int)m_aliveParticles.size());
}

void ParticleEmitter::GenerateParticle()
{
    auto *particle = m_allParticles->Dequeue();
    if (particle == nullptr) { return; };

    particle->m_creationTime = m_currentFrameTime;
    particle->m_sprite->SetPosition(m_position);
    particle->m_sprite->SetAlpha(1.0f);
    m_aliveParticles.emplace_back(particle);
}

void ParticleEmitter::KillParticle(ParticleEmitterItem* particle)
{
    auto *sprite = particle->m_sprite;
    if (sprite == nullptr) { return; };

    sprite->SetAlpha(0.0f);
}

void ParticleEmitter::UpdateParticle(ParticleEmitterItem* item)
{
    double timeSpent = double(item->GetAge(m_currentFrameTime));
    float percentage = float(timeSpent / double(m_descriptor.lifetime));
    m_descriptor.updateFunction(item->m_sprite, percentage);
}
