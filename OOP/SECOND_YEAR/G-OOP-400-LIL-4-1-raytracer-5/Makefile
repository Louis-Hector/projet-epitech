##
## EPITECH PROJECT, 2026
## OOP
## File description:
## Makefile
##

CC      =   g++

NAME    =   raytracer

SRC     =   src/main.cpp \
            src/Core/Camera.cpp \
            src/Core/Ray.cpp \
            src/Core/Color.cpp \
            src/Core/Image.cpp \
            src/Core/Intersection.cpp \
            src/Core/AABB.cpp \
            src/Core/BVHNode.cpp \
            src/Core/PpmWriter.cpp \
            src/Core/Scene.cpp \
            src/Core/Renderer.cpp \
            src/Core/Sfml.cpp \
            src/Core/TileRenderJob.cpp \
            src/Math/MathUtils.cpp \
            src/Math/Point3D.cpp \
            src/Math/Vector3D.cpp \
            src/Parsing/Parsing.cpp \
            src/Lights/DirectionalLight.cpp \
            src/Lights/PointLight.cpp \
            src/Lights/SpotLight.cpp \
            src/Materials/Lambertian.cpp \
            src/Materials/Dielectric.cpp \
            src/Materials/Emissive.cpp \
            src/Materials/Metal.cpp \
            src/Materials/Mirror.cpp \
            src/Materials/Transparent.cpp \
            src/Primitives/Cylinder.cpp \
            src/Primitives/LimitedCylinder.cpp \
            src/Primitives/Triangle.cpp \
            src/Primitives/Pyramid.cpp \
            src/Primitives/Plane.cpp \
            src/Primitives/Sphere.cpp \
            src/Primitives/Torus.cpp \
            src/Primitives/Fractal.cpp \
            src/Primitives/Cone.cpp \
            src/Primitives/LimitedCone.cpp \
            src/Primitives/Mobius.cpp \
            src/Primitives/Tanglecube.cpp \
            src/obj/Obj.cpp \
            src/Factory/Factory.cpp \
            src/Factory/MaterialFactory.cpp \
            src/Builder/Builder.cpp

OBJ     =   $(SRC:.cpp=.o)

CFLAGS  =   -Wall -Wextra -Werror -fPIC -I src/Parsing/ -I src/Materials -I src/Core -I src/Primitives -I src/Lights -I src/Math -I src/Factory -I src/Builder -I src/obj

LIBFLAGS = -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LIBFLAGS) $(LDFLAGS)
			@echo "Compilation done"

%.o:		%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJ)
			@echo "Cleaning done"

fclean:		clean
			@rm -f $(NAME)
			@echo "Full cleaning done."

re:			fclean all
