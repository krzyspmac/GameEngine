# Animation

A very basic animation set is provided. Each sprite provides the `animator` object that provides a set of properties that can be animated using the provede functions. \see engine::PropertyManupulator.

Each animation is done in blocks provede by the global animator. Through it some animatable attributes of a sprite can be animated along a chosen animation curve and over a specific period of time.

```
auto animator = Globals::animator();
auto curve = Globals::curveFactory()->Create(LINEAR);

animator->Animate(1, 5, curve, [&](auto *animator){
    // Animation block. Will get called first to set up the animation
    m_textSprite->animator()->SetPosition(animator, {150, 500});
}, [&](void){
    // Completion Handler, if needed
});
```
