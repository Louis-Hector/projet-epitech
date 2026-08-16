# Raytracer

**Raytracer** is a project from the module ***G4 - Object-Oriented Programming***. RayTracer aims to create a program capable of generating an image from a file describing the scene.

---

## Content

- [Summary](#summary)
- [Installation](#installation)
- [Available scenes](#available-scenes)
- [Project structure](#project-structure)
- [Design Patterns](#design-patterns)
- [Implement it yourself](#implement-it-yourself)
- [Authors](#authors)

---

## Summary

### You will have the possibility to see what was realised in this Raytracer across the different categories:

### Required Features (Must)

- Sphere
- Plane
- Translation
- Directional light
- Flat color
- Add primitives to scene
- Set up lighting
- Set up camera

### Should Features

- Cylinder
- Rotation
- Drop shadows

### Could Features

- Limited cylinder 
- Torus 
- Tanglecube 
- Triangles 
- `.OBJ` file 
- Scale 
- Multiple directional lights 
- Multiple point lights 
- Colored light 
- Transparency 
- Refraction 
- Reflection 
- Supersampling 
- Ambient occlusion

---

## Installation

### 1. Git clone the repositiry on your PC
```bash
git clone git@github.com:EpitechPGE2-2025/G-OOP-400-LIL-4-1-raytracer-5.git
cd G-OOP-400-LIL-4-1-raytracer-5
```

### 2. Compile the project
```bash
make
```
So you obtain the executable raytracer (you can see with the command ls)

### 3. You have two options to start the project:

### 3.0
```bash
./raytracer [--sfml]
```
This will launch all the files .cfg in the folder ***scenes***. All the result will be store in the foler ***scrennshots***.

### 3.1
``` bash
./raytracer your_file.cfg [--sfml]
```
This will launch your file .cfg. The result will be store in the foler ***scrennshots***. (your_file.ppm)

---

## Available scenes

All the scenes you are about to see are available and at your disposal in the scenes folder.

### Primitives (Form: file):

- Sphere: `scenes/demo_sphere.cfg`
- Plane: `scenes/demo_plane.cfg`
- Cylinder: `scenes/demo_cylinder.cfg`
- Limited cylinder: `scenes/demo_limited_cylinder.cfg`
- Torus: `scenes/demo_torus.cfg`
- Tanglecube: `scenes/demo_tanglecube.cfg`
- Triangles: `scenes/demo_triangles.cfg`

### Lights - Shadows

- Directional light: `scenes/demo_directional_light.cfg`
- Set up lighting: `scenes/demo_scene_lighting.cfg`
- Drop shadows: `scenes/demo_drop_shadows.cfg`
- Multiple directional lights: `scenes/demo_multiple_directional_lights.cfg`
- Multiple point lights: `scenes/demo_multiple_point_lights.cfg`
- Colored light: `scenes/demo_colored_light.cfg`

### Transformation

- Translation: `scenes/demo_translation.cfg`
- Rotation: `scenes/demo_rotation.cfg`
- Scale: `scenes/demo_scale.cfg`

### And many Features

- Flat color: `scenes/demo_flat_color.cfg`
- Add primitives to scene: `scenes/demo_scene_primitives.cfg`
- Set up camera: `scenes/demo_scene_camera.cfg`
- `.OBJ` file: `scenes/demo_obj.cfg`
- Transparency: `scenes/demo_transparency.cfg`
- Refraction: `scenes/demo_refraction.cfg`
- Reflection: `scenes/demo_reflection.cfg`
- Supersampling: `scenes/demo_supersampling.cfg`
- Ambient occlusion:
`with AO`: `scenes/ambient_occlusion_demo.cfg`
`without AO`: `scenes/demo_ambient_occlusion_without.cfg`

### Notes

- Some older files in `scenes/` are legacy experiments and do not follow the `demo_*.cfg` naming.
- `fractales.cfg` currently targets an older parser API and should not be used as proof that fractals are implemented in the current branch.

---

## Project structure

```bash
.
├── bonus
│   ├── Makefile
│   ├── README.md
│   └── src
│       ├── Builder
│       │   ├── Builder.cpp
│       │   └── Builder.hpp
│       ├── Core
│       │   ├── RenderConfig.hpp
│       │   ├── RenderContext.hpp
│       │   ├── Renderer.cpp
│       │   ├── Renderer.hpp
│       │   ├── Scene.cpp
│       │   ├── Scene.hpp
│       │   ├── Sfml.cpp
│       │   ├── TileRenderJob.cpp
│       │   └── TileRenderJob.hpp
│       ├── main.cpp
│       └── Parsing
│           └── Parsing.cpp
├── Makefile
├── README.md
├── scenes
│   ├── camping
│   │   ├── materials.mtl
│   │   └── model.obj
│   ├── colored_light_mix.cfg
│   ├── colored_light_warm.cfg
│   ├── cone.cfg
│   ├── cylinder_between_two_spheres.cfg
│   ├── demo_ambient_occlusion.cfg
│   ├── demo_ambient_occlusion_without.cfg
│   ├── demo_colored_light.cfg
│   ├── demo_cylinder.cfg
│   ├── demo_directional_light.cfg
│   ├── demo_drop_shadows.cfg
│   ├── demo_flat_color.cfg
│   ├── demo_limited_cylinder.cfg
│   ├── demo_multiple_directional_lights.cfg
│   ├── demo_multiple_point_lights.cfg
│   ├── demo_obj.cfg
│   ├── demo_plane.cfg
│   ├── demo_reflection.cfg
│   ├── demo_refraction.cfg
│   ├── demo_rotation.cfg
│   ├── demo_scale.cfg
│   ├── demo_scene_camera.cfg
│   ├── demo_scene_lighting.cfg
│   ├── demo_scene_primitives.cfg
│   ├── demo_sphere.cfg
│   ├── demo_supersampling.cfg
│   ├── demo_tanglecube.cfg
│   ├── demo_torus.cfg
│   ├── demo_translation.cfg
│   ├── demo_transparency.cfg
│   ├── demo_triangles.cfg
│   ├── fractal.cfg
│   ├── glurak
│   │   ├── materials.mtl
│   │   ├── materials.mtl.bak
│   │   └── model.obj
│   ├── mobius.cfg
│   ├── obj.cfg
│   ├── pathtracing_lights_showcase.cfg
│   ├── pokeball
│   │   ├── materials.mtl
│   │   └── model.obj
│   ├── Pyramid.cfg
│   ├── reflection_demo.cfg
│   ├── scattering_materials_demo.cfg
│   ├── squirtle
│   │   ├── materials.mtl
│   │   └── model.obj
│   ├── squirtle_spotlight.cfg
│   ├── test.cfg
│   ├── Torus.cfg
│   ├── Triangle.cfg
│   └── tunnel.cfg
├── screenshots
│   ├── cone.ppm
│   ├── cylinder_between_two_spheres.ppm
│   ├── demo_ambient_occlusion.ppm
│   ├── demo_ambient_occlusion_without.ppm
│   ├── demo_colored_light.ppm
│   ├── demo_cylinder.ppm
│   ├── demo_directional_light.ppm
│   ├── demo_drop_shadows.ppm
│   ├── demo_flat_color.ppm
│   ├── demo_limited_cylinder.ppm
│   ├── demo_multiple_directional_lights.ppm
│   ├── demo_multiple_point_lights.ppm
│   ├── demo_obj.ppm
│   ├── demo_plane.ppm
│   ├── demo_reflection.ppm
│   ├── demo_refraction.ppm
│   ├── demo_rotation.ppm
│   ├── demo_scale.ppm
│   ├── demo_scene_camera.ppm
│   ├── demo_scene_lighting.ppm
│   ├── demo_scene_primitives.ppm
│   ├── demo_sphere.ppm
│   ├── demo_supersampling.ppm
│   ├── demo_tanglecube.ppm
│   ├── demo_torus.ppm
│   ├── demo_translation.ppm
│   ├── demo_transparency.ppm
│   ├── demo_triangles.ppm
│   ├── fractal.ppm
│   ├── pathtracing_lights_showcase.ppm
│   ├── reflection_demo.ppm
│   ├── squirtle_spotlight.ppm
│   ├── Torus.ppm
│   ├── Triangle.ppm
│   └── tunnel.ppm
└── src
    ├── Builder
    │   ├── Builder.cpp
    │   └── Builder.hpp
    ├── Core
    │   ├── AABB.cpp
    │   ├── AABB.hpp
    │   ├── BVHNode.cpp
    │   ├── BVHNode.hpp
    │   ├── Camera.cpp
    │   ├── Camera.hpp
    │   ├── Color.cpp
    │   ├── Color.hpp
    │   ├── Image.cpp
    │   ├── Image.hpp
    │   ├── Intersection.cpp
    │   ├── Intersection.hpp
    │   ├── PpmWriter.cpp
    │   ├── PpmWriter.hpp
    │   ├── Ray.cpp
    │   ├── Ray.hpp
    │   ├── RayTracerError.hpp
    │   ├── RenderConfig.hpp
    │   ├── RenderContext.hpp
    │   ├── Renderer.cpp
    │   ├── Renderer.hpp
    │   ├── Scene.cpp
    │   ├── Scene.hpp
    │   ├── Sfml.cpp
    │   ├── Sfml.hpp
    │   ├── TileRenderJob.cpp
    │   └── TileRenderJob.hpp
    ├── Factory
    │   ├── Factory.cpp
    │   ├── Factory.hpp
    │   ├── MaterialFactory.cpp
    │   └── MaterialFactory.hpp
    ├── Lights
    │   ├── DirectionalLight.cpp
    │   ├── DirectionalLight.hpp
    │   ├── ILight.hpp
    │   ├── PointLight.cpp
    │   ├── PointLight.hpp
    │   ├── SpotLight.cpp
    │   └── SpotLight.hpp
    ├── main.cpp
    ├── Materials
    │   ├── Dielectric.cpp
    │   ├── Dielectric.hpp
    │   ├── Emissive.cpp
    │   ├── Emissive.hpp
    │   ├── FlatMaterial.o
    │   ├── IMaterial.hpp
    │   ├── Lambertian.cpp
    │   ├── Lambertian.hpp
    │   ├── Metal.cpp
    │   ├── Metal.hpp
    │   ├── Mirror.cpp
    │   ├── Mirror.hpp
    │   ├── Transparent.cpp
    │   └── Transparent.hpp
    ├── Math
    │   ├── MathConstants.hpp
    │   ├── MathConstants.o
    │   ├── MathUtils.cpp
    │   ├── MathUtils.hpp
    │   ├── Point3D.cpp
    │   ├── Point3D.hpp
    │   ├── Vector3D.cpp
    │   └── Vector3D.hpp
    ├── obj
    │   ├── Obj.cpp
    │   └── Obj.hpp
    ├── Parsing
    │   ├── Parsing.cpp
    │   └── Parsing.hpp
    └── Primitives
        ├── Cone.cpp
        ├── Cone.hpp
        ├── Cylinder.cpp
        ├── Cylinder.hpp
        ├── Fractal.cpp
        ├── Fractal.hpp
        ├── IPrimitive.hpp
        ├── LimitedCone.cpp
        ├── LimitedCone.hpp
        ├── LimitedCylinder.cpp
        ├── LimitedCylinder.hpp
        ├── Mobius.cpp
        ├── Mobius.hpp
        ├── Plane.cpp
        ├── Plane.hpp
        ├── Pyramid.cpp
        ├── Pyramid.hpp
        ├── Sphere.cpp
        ├── Sphere.hpp
        ├── Tanglecube.cpp
        ├── Tanglecube.hpp
        ├── Torus.cpp
        ├── Torus.hpp
        ├── Triangle.cpp
        └── Triangle.hpp

22 directories, 195 files
```
---

## Design Patterns

- **Factory** for creating components such as materials, primitives, or lights (Factory.cpp | Factory.hpp)

- **Builder** for creating an element step by step, such as a scene, by adding the camera, then primitives, etc. (Builder.cpp | Builder.hpp)

---

## Implement it yourself

### HPP

Changing the necessary parameters in the private section of the class, e.g., for Cylinder:

```c++
private:
    Math::Point3D _center;
    Math::Vector3D _rotation;
    double _height;
    double _radius;
    Color _color;
```

### CPP

Next, in the CPP code, we added the `hit` function to calculate the intersection between a ray and our shape.

```c++
bool MA_SHAPE::hit(const RayTracer::Ray &ray, Intersection &intersection) const
{
    ...
}
```

### Factory

After you have your Cpp and hpp, you just have to implement the new element in the factory:

```c++
std::unique_ptr<RayTracer::IPrimitive> Factory::buildCylinder(libconfig::Setting &setting, const RayTracer::IMaterial *material);
{
    ...
}
```

---

## Authors

- [Noam Bouillet](https://github.com/nomaisthere)
- [Louis Hector](https://github.com/MinFlag)
- [Paul Ammeloot](https://github.com/PaulAMMELOOT)
- [Logan Capoen](https://github.com/logan-capoen)