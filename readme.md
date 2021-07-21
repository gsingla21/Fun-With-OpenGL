Open Graphics Library (OpenGL) is a cross-language (language independent), cross-platform (platform-independent) API for rendering 2D and 3D Vector Graphics(use of polygons to represent image). OpenGL API is designed mostly in hardware.

 **Design** : This API is defined as a set of functions which may be called by the client program. Although functions are similar to those of C language but it is language
independent.

 **Development** : It is an evolving API and Khronos Group regularly releases its new version having some extended feature compare to previous one. GPU vendors
may also provide some additional functionality in the form of extension.

 **Associated Libraries** : The earliest version is released with a companion library called OpenGL utility library. But since OpenGL is quite a complex process. So in order to make it easier other library such as OpenGL Utility Toolkit is added which is later superseded by free glut. Later included library were GLEE, GLEW, and
gliding.

 **Implementation** : Mesa 3D is an open source implementation of OpenGL. It can do pure software rendering and it may also use hardware acceleration on BSD, Linux, and other platforms by taking advantage of Direct Rendering Infrastructure.

Install OpenGL on Ubuntu
For installing OpenGL on Ubuntu, just execute the following command (like installing any other thing) in terminal :
**sudo apt-get install freeglut3-dev**

For working on Ubuntu operating system:
**gcc filename.c -lGL -lGLU -lglut**
where filename.c is the name of the file with which this program is saved.
