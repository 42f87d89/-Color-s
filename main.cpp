#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <GL/glfw.h>

#define RADCON (3.1415/180)
 
void Init(void);
void Shut_Down(int return_code);
void Main_Loop(void);
void Draw_Square(float red, float green, float blue);
void Draw(void);
 
float rotate_x = 0,
	  rotate_y = 0,
	  XPOS = 0,
	  YPOS = 0,
	  ZPOS = 0;

const float rotations_per_tick = .2;
 
int main(){
	Init();
	Main_Loop();
	Shut_Down(0);
}
 
void Init(void){
	const int window_width = 1280,
			  window_height = 900;
 
	if(glfwInit() != GL_TRUE) Shut_Down(1);
	
	// 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
	if(glfwOpenWindow(window_width, window_height, 5, 6, 5,
					   0, 0, 0, GLFW_WINDOW) != GL_TRUE) Shut_Down(1);
	
	glfwSetWindowTitle("The GLFW Window");
 
	glEnable(GL_DEPTH_TEST);
	
	// set the projection matrix to a normal frustum with a max depth of 50
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float aspect_ratio = ((float)window_height) / window_width;
	glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
	
	glMatrixMode(GL_MODELVIEW);
}
 
void Shut_Down(int return_code){
	glfwTerminate();
	exit(return_code);
}

void Main_Loop(void){
  // the time of the previous frame
	double old_time = glfwGetTime();

	while(1){
		std::cout << rotate_x << "  " << rotate_y << "\n";
		
    // calculate time elapsed, and the amount by which stuff rotates
		double current_time = glfwGetTime(),
			   delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		old_time = current_time;
		
    // escape to quit, arrow keys to rotate view
		if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) break;
		
		if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
			rotate_y += delta_rotate*1.4;
		}
		
		if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
			rotate_y -= delta_rotate*1.4;
		}
		
		if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
			if(rotate_x > -90) rotate_x -= delta_rotate;
		}
		
		if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
			if(rotate_x < 90) rotate_x += delta_rotate;
		}

		if(rotate_y < -180) rotate_y += 360; // Limits the angle, but I'm not sure of the impact
		if(rotate_y > 180) rotate_y -= 360;
		
		//Movement relative to the camera
		if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS){
			XPOS += cos(RADCON*rotate_y+1.571)*0.1f;
			YPOS += sin(RADCON*rotate_x)*0.1;
			ZPOS += sin(RADCON*rotate_y+1.571)*0.1f;
		}
		
		if (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS){
			XPOS += cos(RADCON*rotate_y-1.571)*0.1f;
			ZPOS += sin(RADCON*rotate_y-1.571)*0.1f;
		}
		
 
		// clear the buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// draw the figure
		Draw();
		
		// swap back and front buffers
		glfwSwapBuffers();
	}
}
 
void Draw_Box(int H, int W, int D){
	// Draws a square with a gradient color at coordinates 0, 10
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3i(-W/2, -H/2, -D/2);
		glVertex3i(W/2, -H/2, -D/2);
		glVertex3i(W/2, H/2, -D/2);
		glVertex3i(-W/2, H/2, -D/2);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3i(-W/2, -H/2, D/2);
		glVertex3i(W/2, -H/2, D/2);
		glVertex3i(W/2, H/2, D/2);
		glVertex3i(-W/2, H/2, D/2);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3i(-W/2, -H/2, -D/2);
		glVertex3i(-W/2, -H/2, D/2);
		glVertex3i(-W/2, H/2, D/2);
		glVertex3i(-W/2, H/2, -D/2);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3i(W/2, -H/2, -D/2);
		glVertex3i(W/2, -H/2, D/2);
		glVertex3i(W/2, H/2, D/2);
		glVertex3i(W/2, H/2, -D/2);
    
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3i(-W/2, -H/2, -D/2);
		glVertex3i(-W/2, -H/2, D/2);
		glVertex3i(W/2, -H/2, D/2);
		glVertex3i(W/2, -H/2, -D/2);
	}
	glEnd();
}

void Draw(void){
	// reset view matrix
	glLoadIdentity();

	glRotatef(rotate_x, 1, 0, 0);
	glRotatef(rotate_y, 0, 1, 0);
	glTranslatef(XPOS, YPOS, ZPOS);
	
	Draw_Box(3,10,10);
}
