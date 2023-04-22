// Copyright (c) 2023 Krzysztof Pawłowski
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

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp

#include "game_include.hpp"
#include "interfaces.h"

/** Describes the configurations and workings of the particle emitter.
 */
typedef struct ParticleEmitterDescriptor {
    /** The time interval which controls how often would the particles be emitted.
        In milliseconds. \see(TimeI)
     */
    Uint64 timeInterval;

    /** The lifetime of a single particle.

        When the lifetime expires the particle is
        brought back to the `available` pool of particles.
     */
    Uint64 lifetime;

    /** The vector which will control the living particles.

        All particles considered `alive` will have their position modified,
        in a linear fashion, by this vector.
     */
    engine::Vector2 emmiterVector;

    /** The creator function.
     */
    std::function<engine::SpriteRepresentationI*(void)> creatorFunction;

    /** The update function.

        Every time a frame is being updated each living particle will fire an update
        function. There additional processing can occur.

        sprite - The sprite to be processed
        completionPercentage - The percentage of the completion of the lifetime
     */
    std::function<void(engine::SpriteRepresentationI* sprite, float completionPercentage)> updateFunction;
} ParticleEmitterDescriptor;

/** Describes the particle item, kept by the emitter
 */
typedef struct ParticleEmitterItem {
    engine::SpriteRepresentationI *m_sprite;
    Uint64 m_creationTime;

    ParticleEmitterItem(engine::SpriteRepresentationI* sprite)
    :   m_sprite(sprite)
    ,   m_creationTime(0)
    { }

    Uint64 GetAge(Uint64 now) { return now - m_creationTime; };
} ParticleEmitterItem;

class ParticleEmitter {
    ParticleEmitterDescriptor m_descriptor;
    engine::Vector2 m_position;
    Uint64 m_currentFrameTime;
    Uint64 m_lastParticleCreationTime;

    std::unique_ptr<engine::ObjectPool<ParticleEmitterItem>> m_allParticles;
    std::vector<ParticleEmitterItem*> m_aliveParticles;
public:
    /** Construct the particle emitter.

        Provide the descriptor and the number of total particles to be created.
     */
    ParticleEmitter(
        ParticleEmitterDescriptor,
        int
    );

    /** Update the emitter's position. */
    void SetPosition(engine::Vector2);

    /** Frame update */
    void FrameUpdate(Uint64 totalTime);

private:
    /** Generate a particle */
    void GenerateParticle();

    /** Kill a particle */
    void KillParticle(ParticleEmitterItem*);

    /** Update the particle. */
    void UpdateParticle(ParticleEmitterItem*);
};

#endif /* ParticleEmitter_hpp */
