
/* Link the libraries code-wise. */
#ifdef _MSC_VER
#	pragma comment(lib, "OpenGL32.lib")
#	pragma comment(lib, "GLu32.lib")

#	pragma comment(lib, "SDL.lib")
#	pragma comment(lib, "SDLmain.lib")
#	pragma comment(lib, "SDL_image.lib")
#define STB_IMAGE_IMPLEMENTATION
#endif //_MSC_VER

#include <string>
#include <cmath>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include <stdlib.h>
#include <GL/glut.h>
//add head file
#include <vector>
using std::vector;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define PI 3.141592653589793
#define RAD (PI/180)

//unsigned Textures[3];
unsigned Textures[10];
unsigned BoxList(0);					//Added!

										/* These will define the player's position and view angle. */
double X(0.0), Y(0.0), Z(0.0);
double ViewAngleHor(0.0), ViewAngleVer(0.0);

bool open = false;

/*
* DegreeToRadian
*	Converts a specified amount of degrees to radians.
*/
inline double DegreeToRadian(double degrees)
{
	return (degrees / 180.f * PI);
}

/*
* GrabTexObjFromFile
*	This function will use SDL to load the specified image, create an OpenGL
*	texture object from it and return the texture object number.
*/
GLuint GrabTexObjFromFile(const std::string& fileName)
{
	/* Use SDL_image to load the PNG image. */
	SDL_Surface *Image = IMG_Load(fileName.c_str());

	/* Image doesn't exist or failed loading? Return 0. */
	if (!Image)
		return 0;

	unsigned Object(0);

	/* Generate one texture (we're creating only one). */
	glGenTextures(1, &Object);

	/* Set that texture as current. */
	glBindTexture(GL_TEXTURE_2D, Object);

	/* You can use these values to specify mipmaps if you want to, such as 'GL_LINEAR_MIPMAP_LINEAR'. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* We're setting textures to be repeated here. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //NEW!
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //NEW!

																  /* Create the actual texture object. */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image->w, Image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Image->pixels);

	/* Free the surface, we are finished with it. */
	SDL_FreeSurface(Image);

	return Object;
}

/*
*	CompileLists
*		Compiles the display lists used by our application.
*/
void CompileLists()
{
	/* Let's generate a display list for a box. */
	BoxList = glGenLists(1);
	glNewList(BoxList, GL_COMPILE);

	/*
	* Render everything as you usually would, without texture binding. We're rendering the box from the
	* '3D Objects' tutorial here.
	*/
	GLfloat boxColor[] = { 0.1,0.1,0.1,1 };
	GLfloat boxdiffColor[] = { 1,1,1,1 };
	GLfloat boxspecColor[] = { 2,2,2,1 };
	GLfloat shin[] = { 32.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, boxColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, boxdiffColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, boxspecColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glBegin(GL_QUADS);
	///* Front */
	//glTexCoord2d(0, 0); glVertex3d(400, 125, 0.4);
	//glTexCoord2d(1, 0); glVertex3d(750, 125, 0.4);
	//glTexCoord2d(1, 1); glVertex3d(750, 475, 0.4);
	//glTexCoord2d(0, 1); glVertex3d(400, 475, 0.4);

	///* Left side */
	//glTexCoord2d(0, 0); glVertex3d(400, 125, -0.4);
	//glTexCoord2d(1, 0); glVertex3d(400, 125, 0.4);
	//glTexCoord2d(1, 1); glVertex3d(400, 475, 0.4);
	//glTexCoord2d(0, 1); glVertex3d(400, 475, -0.4);

	///* Back */
	//glTexCoord2d(0, 0); glVertex3d(750, 125, -0.4);
	//glTexCoord2d(1, 0); glVertex3d(400, 125, -0.4);
	//glTexCoord2d(1, 1); glVertex3d(400, 475, -0.4);
	//glTexCoord2d(0, 1); glVertex3d(750, 475, -0.4);

	///* Right side */
	//glTexCoord2d(0, 0); glVertex3d(750, 125, 0.4);
	//glTexCoord2d(1, 0); glVertex3d(750, 125, -0.4);
	//glTexCoord2d(1, 1); glVertex3d(750, 475, -0.4);
	//glTexCoord2d(0, 1); glVertex3d(750, 475, 0.4);

	///* Top */
	//glTexCoord2d(0, 0); glVertex3d(400, 125, -0.4);
	//glTexCoord2d(1, 0); glVertex3d(750, 125, -0.4);
	//glTexCoord2d(1, 1); glVertex3d(750, 125, 0.4);
	//glTexCoord2d(0, 1); glVertex3d(400, 125, 0.4);

	///* Bottom */
	//glTexCoord2d(0, 0); glVertex3d(400, 475, -0.4);
	//glTexCoord2d(1, 0); glVertex3d(750, 475, -0.4);
	//glTexCoord2d(1, 1); glVertex3d(750, 475, 0.4);
	//glTexCoord2d(0, 1); glVertex3d(400, 475, 0.4);

	/*yjx 20180409 16:03*/
	//后面
	//glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3d(1500, 100, 0);//右上
							 //glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3d(2000, 100, 0);//左上
							 //glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3d(2000, 475, 0);//左下
							 //glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3d(1500, 475, 0);//右下
							 //前面
							 //glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3d(2000, 100, -0.8);//右上
								//glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3d(1500, 100, -0.8);//左上
								//glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3d(1500, 475, -0.8);//左下
								//glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3d(2000, 475, -0.8);//右下
								//左面
								//glColor3f(0.0f, 0.0f, 1.0f);	
	glTexCoord2f(0, 0);
	glVertex3d(1500, 100, -0.8);//右上
								//glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3d(1500, 100, 0);//左上
							 //glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 1);
	glVertex3d(1500, 475, 0);//左下
							 //glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 1);
	glVertex3d(1500, 475, -0.8);//右下

								//右面
								//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3d(2000, 100, 0);//右上
							 //glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3d(2000, 100, -0.8);//左上
								//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 1);
	glVertex3d(2000, 475, -0.8);//左下
								//glColor3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 1);
	glVertex3d(2000, 475, 0);//右下
							 //下面
							 //glColor3ub(128, 128, 128);
	glTexCoord2f(0, 0);
	glVertex3d(2000, 475, -0.8);//右上
								//glColor3ub(128, 128, 128);
	glTexCoord2f(1, 0);
	glVertex3d(1500, 475, -0.8);//左上
								//glColor3ub(128, 128, 128);
	glTexCoord2f(1, 1);
	glVertex3d(1500, 475, 0);//左下
							 //glColor3ub(128, 128, 128);
	glTexCoord2f(0, 1);
	glVertex3d(2000, 475, 0);//右下

							 //上面		
							 //glColor3ub(151, 200, 151);
	glTexCoord2f(0, 0);
	glVertex3d(2000, 100, -0.8);//右上
								//glColor3ub(151, 200, 151);
	glTexCoord2f(1, 0);
	glVertex3d(1500, 100, -0.8);//左上
								//glColor3ub(151, 200, 151);
	glTexCoord2f(1, 1);
	glVertex3d(1500, 100, 0);//左下
							 //glColor3ub(151, 200, 151);
	glTexCoord2f(0, 1);
	glVertex3d(2000, 100, 0);//右下
							 /*yjx 20180409 16:03 添加结束*/
	glEnd();
	glEndList();
}

enum { SKY_LEFT = 3, SKY_BACK = 4, SKY_RIGHT = 5, SKY_FRONT = 6, SKY_TOP = 7, SKY_BOTTOM = 8 };
void drawSkybox(float size)
{
	glRotated(ViewAngleVer, 1, 0, 0);
	glRotated(ViewAngleHor, 0, 1, 0);
	glTranslated(-X, -Y, -Z);

	bool b1 = glIsEnabled(GL_TEXTURE_2D);     //new, we left the textures turned on, if it was turned on
	glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);       //turn off depth texting
	glEnable(GL_TEXTURE_2D);        //and turn on texturing
	glBindTexture(GL_TEXTURE_2D, Textures[SKY_FRONT]);  //use the texture we want
	glBegin(GL_QUADS);      //and draw a face
							//back face
	glTexCoord2f(0, 0);      //use the correct texture coordinate
	glVertex3f(size / 2, size / 2, size / 2);       //and a vertex
	glTexCoord2f(1, 0);      //and repeat it...
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Textures[SKY_LEFT]);
	glBegin(GL_QUADS);
	//left face
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Textures[SKY_BACK]);
	glBegin(GL_QUADS);
	//front face
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Textures[SKY_RIGHT]);
	glBegin(GL_QUADS);
	//right face
	glTexCoord2f(0, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Textures[SKY_TOP]);
	glBegin(GL_QUADS);                      //top face
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Textures[SKY_BOTTOM]);
	glBegin(GL_QUADS);
	//bottom face
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	
	glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
	glEnable(GL_DEPTH_TEST);

	if (!b1)
		glDisable(GL_TEXTURE_2D);
}
/*yjx 20180409 16:19*/
float angle = 0;
/*yjx 20180409 16:19 添加结束*/
/*
* DrawRoom
*	This will render the entire scene (in other words, draw the room).
*/
void DrawRoom()
{
	/* You also could do this at front by using the SDL surface's values or in an array. */
	static float WallTexWidth(0.f);
	static float WallTexHeight(0.f);

	static float FloorTexWidth(0.f);
	static float FloorTexHeight(0.f);

	static bool Once(false);

	/* Perform this check only once. */
	if (!Once)
	{
		/* Bind the wall texture. */
		glBindTexture(GL_TEXTURE_2D, Textures[0]);

		/* Retrieve the width and height of the current texture (can also be done up front with SDL and saved somewhere). */
		glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &WallTexWidth);
		glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &WallTexHeight);

		/* Bind the floor texture. */
		glBindTexture(GL_TEXTURE_2D, Textures[1]);

		/* Retrieve the width and height of the current texture (can also be done up front with SDL and saved somewhere). */
		glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &FloorTexWidth);
		glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &FloorTexHeight);

		Once = true;
	}

	glPushMatrix();

	/* Move the world and rotate the view. */
	glRotated(ViewAngleVer, 1, 0, 0);
	glRotated(ViewAngleHor, 0, 1, 0);

	glTranslated(-X, -Y, -Z);

	/* Set the coordinate system. */
	glOrtho(0, 800, 600, 0, -1, 1);

	/* Draw walls. */
	GLfloat ambientColor[] = { 0.1,0.1,0.1,1.0 };
	GLfloat diffColor[] = { 1,1,1,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_BACK, GL_DIFFUSE, diffColor);

	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_QUADS);
	/* Wall in front of you when the app starts. */
	glTexCoord2f(0, 0);
	glVertex3d(-200, 0, 4.0);   //vertex point bottom left

	glTexCoord2f(1200.f / WallTexWidth, 0);
	glVertex3d(1000, 0, 4.0);				//bottom right

	glTexCoord2f(1200.f / WallTexWidth, 400.f / WallTexHeight);
	glVertex3d(1000, 500, 4.0);

	glTexCoord2f(0, 400.f / WallTexHeight);
	glVertex3d(-200, 500, 4.0);



	/* Wall left of you. */
	glTexCoord2f(0, 0);
	glVertex3d(-200, 0, -4.0);

	glTexCoord2f(1200.f / WallTexWidth, 0);
	glVertex3d(-200, 0, 4.0);

	glTexCoord2f(1200.f / WallTexWidth, 400.f / WallTexHeight);
	glVertex3d(-200, 500, 4.0);

	glTexCoord2f(0, 400.f / WallTexHeight);
	glVertex3d(-200, 500, -4.0);

	/* Wall right of you. */
	glTexCoord2f(0, 0);
	glVertex3d(1000, 0, 4.0);

	glTexCoord2f(1200.f / WallTexWidth, 0);
	glVertex3d(1000, 0, -4.0);

	glTexCoord2f(1200.f / WallTexWidth, 400.f / WallTexHeight);
	glVertex3d(1000, 500, -4.0);

	glTexCoord2f(0, 400.f / WallTexHeight);
	glVertex3d(1000, 500, 4.0);

	/* Wall behind you (you won't be able to see this just yet, but you will later). */
	glTexCoord2f(0, 0);
	glVertex3d(1000, 0, -4.0);
	glTexCoord2f(400.f / WallTexWidth, 0);
	glVertex3d(600, 0, -4.0);
	glTexCoord2f(400.f / WallTexWidth, 400.f / WallTexHeight);
	glVertex3d(600, 500, -4.0);
	glTexCoord2f(0, 400.f / WallTexHeight);
	glVertex3d(1000, 500, -4.0);									//bottom right

	glTexCoord2f(0, 0);
	glVertex3d(200, 0, -4.0);
	glTexCoord2f(400.f / WallTexWidth, 0);
	glVertex3d(-200, 0, -4.0);
	glTexCoord2f(400.f / WallTexWidth, 400.f / WallTexHeight);
	glVertex3d(-200, 500, -4.0);
	glTexCoord2f(0, 400.f / WallTexHeight);
	glVertex3d(200, 500, -4.0);

	

	//glTexCoord2f(1200.f / WallTexWidth, 0);
	//glVertex3d(-200, 0,-4.0);

	//glTexCoord2f(1200.f / WallTexWidth, 400.f / WallTexHeight);
	//glVertex3d(-200, 500,-4.0);									//bottom left

	//glTexCoord2f(0, 400.f / WallTexHeight);	
	//glVertex3d(1000, 500,-4.0);									//bottom right



	//glTexCoord2f(400.f / WallTexWidth, 0);
	//glVertex3d(600, 0, -4.0);

	//glTexCoord2f(0, 0);
	//glVertex3d(200, 0, -4.0);

	//glTexCoord2f(0, 400.f / WallTexHeight);
	//glVertex3d(200, 500, -4.0);

	//glTexCoord2f(400.f / WallTexWidth, 400.f / 3*WallTexHeight);
	//glVertex3d(600, 500, -4.0);


	glEnd();
	
	//door on wall while close
	if (!open) {
	glBindTexture(GL_TEXTURE_2D, Textures[9]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3d(600, 0, -4.0);
		glTexCoord2f(1, 0);
		glVertex3d(200, 0, -4.0);
		glTexCoord2f(1, 1);
		glVertex3d(200, 500, -4.0);
		glTexCoord2f(0,1);
		glVertex3d(600, 500, -4.0);
		glEnd();
	}
	else {
	//door on wall while open
		glBindTexture(GL_TEXTURE_2D, Textures[9]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3d(600, 0, -4.0);
		glTexCoord2f(1, 0);
		glVertex3d(600, 0, -5.0);
		glTexCoord2f(1, 1);
		glVertex3d(600, 500, -5.0);
		glTexCoord2f(0, 1);
		glVertex3d(600, 500, -4.0);
		glEnd();
	}
	
	//
	
	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(1000, 500, 0.0);
	glTexCoord2f(2400.f / WallTexWidth, 0);
	glVertex3d(-200, 500, 0.0);
	glTexCoord2f(2400.f / WallTexWidth, 2400.f / WallTexHeight);
	glVertex3d(-200, 6000, 0.0);
	glTexCoord2f(0, 2400.f / WallTexHeight);
	glVertex3d(1000, 6000, 0.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(400, 500, -2.0);
	glTexCoord2f(2400.f / WallTexWidth, 0);
	glVertex3d(400, 500, 2.0);
	glTexCoord2f(2400.f / WallTexWidth, 2400.f / WallTexHeight);
	glVertex3d(400, 6000, 2.0);
	glTexCoord2f(0, 2400.f / WallTexHeight);
	glVertex3d(400, 6000, -2.0);
	glEnd();
	
	

	/* Draw the floor and the ceiling, this is done separatly because glBindTexture isn't allowed inside glBegin. */
	glBindTexture(GL_TEXTURE_2D, Textures[1]);
	//GLfloat materialColor1[] = { 0.1,0.1,0.1,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffColor);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(-200, 500, 4.0);

	glTexCoord2f(1200.f / FloorTexWidth, 0);
	glVertex3d(1000, 500, 4.0);

	glTexCoord2f(1200.f / FloorTexWidth, (8.f / 2.f * 600.f) / FloorTexHeight);
	glVertex3d(1000, 500, -4.0);

	glTexCoord2f(0, (8.f / 2.f * 600.f) / FloorTexHeight);
	glVertex3d(-200, 500, -4.0);

	/* Ceiling. */
	glTexCoord2f(0, 0);
	glVertex3d(-200, 0, 4.0);

	glTexCoord2f(1200.f / FloorTexWidth, 0);
	glVertex3d(1000, 0, 4.0);

	glTexCoord2f(1200.f / FloorTexWidth, (8.f / 2.f * 600.f) / FloorTexHeight);
	glVertex3d(1000, 0, -4.0);

	glTexCoord2f(0, (8.f / 2.f * 600.f) / FloorTexHeight);
	glVertex3d(-200, 0, -4.0);

	glEnd();
	/*light source 1 in room*/
	//{
	//	glEnable(GL_LIGHTING);
	//	GLfloat room_light_position[] = { 0.0, 150.0 , 0.0,1.0f };
	//	GLfloat room_light_ambient[] = { 1.0f,1.0f,1.0f,1.0f };
	//	GLfloat room_light_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	//	GLfloat room_light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	//	glLightfv(GL_LIGHT1, GL_POSITION, room_light_position);
	//	glLightfv(GL_LIGHT1, GL_AMBIENT, room_light_ambient);
	//	glLightfv(GL_LIGHT1, GL_DIFFUSE, room_light_diffuse);
	//	glLightfv(GL_LIGHT1, GL_SPECULAR, room_light_specular);
	//	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);
	//	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, -90.0);
	//	//GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//	GLfloat sun_mat_shininess = 30.0f;
	//	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	//	//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);

	//	glEnable(GL_DEPTH_TEST);
	//}
	/* Now we're going to render some boxes using display lists. */
	glPushMatrix();
	/* Let's make it a bit smaller... */
	glScaled(0.5, 0.4, 0.5);

	/* Can't bind textures while generating a display list, but we can give it texture coordinates and bind it now. */

	glBindTexture(GL_TEXTURE_2D, Textures[2]);

	/*
	* Because display lists have preset coordinates, we'll need to translate it to move it around. Note that we're
	* moving the small version of the cube around, not the big version (because we scaled *before* translating).
	*/

	/*yjx 20180409 16:09*/
	//glTranslated(-700, 750, 6);
	glTranslated(600, 800, 4);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslated(-1750, -287.5, 0.4);
	/*yjx 20180409 16:09 添加结束*/
	/*
	* Let's draw a whole lot of boxes. Note that because we're not pushing and popping matrices, translations
	* and changes will 'accumulate' and add to the previous translation.
	*/
	//for(short i(0); i < 12; ++i)
	//{
	//	glTranslated(350, 0, 0);

	//	/* These make sure that every once in a while, a new row is started. */
	//	if(i == 5)		glTranslated(-1575, -350, 0);
	//	if(i == 9)		glTranslated(-1225, -350, 0);

	//	/*
	//	 * glCallList is all that is really needed to execute the display list. Remember to try the 'K' button
	//	 * to turn on wireframe mode, with these extra polygons, it looks pretty neat!
	//	 */
	glCallList(BoxList);
	//}

	glPopMatrix();

	glPopMatrix();
	glFlush();
	angle += 0.1;
}

void DrawSun() {

	//glColor3f(255,0,0);
	glRotated(ViewAngleVer, 1, 0, 0);
	glRotated(ViewAngleHor, 0, 1, 0);
	glTranslated(-X, -Y + 5.0, -Z + 20.0);
	GLfloat materialColor1[] = { 1,0,0,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialColor1);
	glutSolidSphere(1, 20, 16);
	{
		glEnable(GL_LIGHTING);
		GLfloat sun_light_position[] = { -X, -Y + 5.0 , -Z + 20.0,1.0f };
		GLfloat sun_light_ambient[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
		GLfloat sun_light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, -90.0);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);

	}
}
void DrawLight1() {
	/*light source 1 in room*/
	glRotated(ViewAngleVer, 1, 0, 0);
	glRotated(ViewAngleHor, 0, 1, 0);
	glTranslated(-X, -Y + 0.8, -Z - 1);
	glEnable(GL_LIGHTING);
	//GLfloat room_light_position[] = { 0.0, 150.0 , -10.0,1.0f };
	GLfloat room_light_position[] = { 0.0, 300.0 , -10.0 ,1.0f };
	GLfloat room_light_ambient[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat room_light_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat room_light_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, room_light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, room_light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, room_light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, room_light_specular);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, -90.0);
	//GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_mat_shininess = 30.0f;
	//glMaterialf(GL_FRONT, GL_AMBIENT, sun_mat_shininess);
	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);

	glEnable(GL_DEPTH_TEST);

	glutSolidSphere(0.05, 20, 16);
}

int main(int argc, char **argv)
{
	/* Initialize SDL and set up a window. */
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption("OpenGL - Display Lists", 0);
	SDL_WM_GrabInput(SDL_GRAB_ON);

	SDL_ShowCursor(SDL_DISABLE);

	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

	/* Basic OpenGL initialization, handled in 'The Screen'. */
	glShadeModel(GL_SMOOTH);
	glClearColor(255, 255, 255, 1);



	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(80.0, 800.0 / 600.0, 0.1, 100.0);

	/* We now switch to the modelview matrix. */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/* Enable 2D texturing. */
	glEnable(GL_TEXTURE_2D);

	/* Set up alpha blending. */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4d(1, 1, 1, 1);

	Textures[0] = GrabTexObjFromFile("Data/Wall.png");
	Textures[1] = GrabTexObjFromFile("Data/Floor.png");
	Textures[2] = GrabTexObjFromFile("Data/Box.png");			//Added!

	Textures[SKY_LEFT] = GrabTexObjFromFile("Data/left.png");
	Textures[SKY_BACK] = GrabTexObjFromFile("Data/back.png");
	Textures[SKY_RIGHT] = GrabTexObjFromFile("Data/right.png");
	Textures[SKY_FRONT] = GrabTexObjFromFile("Data/front.png");
	Textures[SKY_TOP] = GrabTexObjFromFile("Data/top.png");
	Textures[SKY_BOTTOM] = GrabTexObjFromFile("Data/bottom.png");

	Textures[9] = GrabTexObjFromFile("Data/door.png");



	//Replaced this with a loop that immediately checks the entire array.
	//sizeof(Textures) is the size of the entire array in bytes (unsigned int = 4 bytes)
	//so sizeof(Textures) would give 3 * 4 = 12 bytes, divide this by 4 bytes and you
	//have 3.

	//	for(unsigned i(0); i < sizeof(Textures) / sizeof(unsigned); ++i)
	//	{
	//		if(Textures[i] == 0)
	//		{
	//#ifdef _WIN32
	//		MessageBoxA(0, "Something went seriously wrong!", "Fatal Error!", MB_OK | MB_ICONERROR);
	//#endif //_WIN32
	//
	//		return 1;
	//		}
	//	}


	//initskybox();
	/* Compile the display lists. */
	CompileLists();


	SDL_Event event;

	int RelX(0), RelY(0);
	int MovementDelay(SDL_GetTicks());

	bool Wireframe(false);
	bool light_status(false);
	bool door_status(false);

	bool Keys[9] =
	{
		false, /* Up arrow down? */
		false, /* Down arrow down? */
		false, /* Left arrow down? */
		false,  /* Right arrow down? */
		false,
		false,
		/*yjx 20180409 16:10*/
		false, //zoom-in
		false, //zoom-out
			   /*yjx 20180409 16:10 添加结束*/
		false
	};

	/* Application loop. */
	for (;;)
	{
		/* Handle events with SDL. */
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break;

			/* Mouse events? */
			else if (event.type == SDL_MOUSEMOTION)
			{
				/* Get the relative mouse movement of the mouse (based on CurMouseCoord - PrevMouseCoord). */
				SDL_GetRelativeMouseState(&RelX, &RelY);

				ViewAngleHor += RelX / 4;
				ViewAngleVer += RelY / 4;

				/* Prevent the horizontal angle from going over 360 degrees or below 0 degrees. */
				if (ViewAngleHor >= 360.0)		ViewAngleHor = 0.0;
				else if (ViewAngleHor < 0.0)		ViewAngleHor = 360.0;

				/* Prevent the vertical view from moving too far (comment this out to get a funny effect). */
				if (ViewAngleVer > 60.0)			ViewAngleVer = 60.0; /* 60 degrees is when you're looking down. */
				else if (ViewAngleVer < -60.0)	ViewAngleVer = -60.0; /* This is when you're looking up. */

																	  /* This delay might seem strange, but it helps smoothing out the mouse if you're experiencing jittering. */
				SDL_Delay(5);
			}

			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					break;

				if (event.key.keysym.sym == SDLK_k)
					glPolygonMode(GL_FRONT_AND_BACK, ((Wireframe = !Wireframe) ? GL_LINE : GL_FILL));

				if (event.key.keysym.sym == SDLK_l)
					(light_status = !light_status) ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

				if (event.key.keysym.sym == SDLK_o)
					(door_status = !door_status) ? open=true : open=false;

				if (event.key.keysym.sym == SDLK_UP)			Keys[0] = true;
				if (event.key.keysym.sym == SDLK_DOWN)		Keys[1] = true;
				if (event.key.keysym.sym == SDLK_LEFT)		Keys[2] = true;
				if (event.key.keysym.sym == SDLK_RIGHT)		Keys[3] = true;
				if (event.key.keysym.sym == SDLK_w)		Keys[4] = true;
				if (event.key.keysym.sym == SDLK_s)		Keys[5] = true;
				/*yjx 20180409 16:12*/
				if (event.key.keysym.sym == SDLK_q)			Keys[6] = true;	//zoom-in
				if (event.key.keysym.sym == SDLK_e)			Keys[7] = true; //zoom-out
																			/*yjx 20180409 16:12 添加结束*/
			}

			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_UP)			Keys[0] = false;
				if (event.key.keysym.sym == SDLK_DOWN)		Keys[1] = false;
				if (event.key.keysym.sym == SDLK_LEFT)		Keys[2] = false;
				if (event.key.keysym.sym == SDLK_RIGHT)		Keys[3] = false;
				if (event.key.keysym.sym == SDLK_w)		Keys[4] = false;
				if (event.key.keysym.sym == SDLK_s)		Keys[5] = false;
				/*yjx 20180409 16:13*/
				if (event.key.keysym.sym == SDLK_q)			Keys[6] = false;	//zoom-in
				if (event.key.keysym.sym == SDLK_e)			Keys[7] = false; //zoom-out
																			 /*yjx 20180409 16:13 添加结束*/
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		drawSkybox(50);
		glPopMatrix();

		glPushMatrix();
		DrawRoom();
		glPopMatrix();

		glPushMatrix();
		DrawLight1();
		glPopMatrix();

		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		DrawSun();
		glPopMatrix();
		glPopAttrib();


		/* move if the keys are pressed, this is explained in the tutorial. */
		if (Keys[0])
		{
			X -= cos(DegreeToRadian(ViewAngleHor + 90.0)) * 0.05;
			Z -= sin(DegreeToRadian(ViewAngleHor + 90.0)) * 0.05;
		}

		if (Keys[1])
		{
			X += cos(DegreeToRadian(ViewAngleHor + 90.0)) * 0.05;
			Z += sin(DegreeToRadian(ViewAngleHor + 90.0)) * 0.05;
		}

		if (Keys[2])
		{
			X += cos(DegreeToRadian(ViewAngleHor + 180.0)) * 0.05;
			Z += sin(DegreeToRadian(ViewAngleHor + 180.0)) * 0.05;
		}

		if (Keys[3])
		{
			X -= cos(DegreeToRadian(ViewAngleHor + 180.0)) * 0.05;
			Z -= sin(DegreeToRadian(ViewAngleHor + 180.0)) * 0.05;
		}

		if (Keys[4])
		{
			Y += 0.01;

		}

		if (Keys[5])
		{
			Y -= 0.01;

		}
		/*yjx 20180409 16:15*/
		if (Keys[6])	//zoom-in
		{
			glScalef(1.1f, 1.1f, 1.0f);
		}

		if (Keys[7])		//zoom-out
		{
			glScalef(0.9f, 0.9f, 1.0f);
		}
		/*yjx 20180409 16:15 添加结束*/


		/* Swap the display buffers. */
		SDL_GL_SwapBuffers();
	}

	/* Delete the created textures. */
	//glDeleteTextures(3, Textures);		//Changed to 3.
	glDeleteTextures(10, Textures);
	glDeleteLists(BoxList, 1);

	/* Clean up. */
	SDL_Quit();
	return 0;
}