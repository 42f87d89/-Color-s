#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <GL/glfw.h>
#include <vector>

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

class body{
	public:
		body(){}
		virtual void draw(){}
};
std::vector<body*> bodies;
class box:public body{
	private:
		int H, W ,D;
	public:
		box(int a, int b, int c){H=a;W=b;D=c;}
		void draw(){
			glPolygonOffset(1,1);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_QUADS);
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				glVertex3i(-W/2, -H/2, -D/2);
				glVertex3i(W/2, -H/2, -D/2);
				glVertex3i(W/2, H/2, -D/2);
				glVertex3i(-W/2, H/2, -D/2);

				glVertex3i(-W/2, -H/2, D/2);
				glVertex3i(W/2, -H/2, D/2);
				glVertex3i(W/2, H/2, D/2);
				glVertex3i(-W/2, H/2, D/2);

				glVertex3i(-W/2, -H/2, -D/2);
				glVertex3i(-W/2, -H/2, D/2);
				glVertex3i(-W/2, H/2, D/2);
				glVertex3i(-W/2, H/2, -D/2);

				glVertex3i(W/2, -H/2, -D/2);
				glVertex3i(W/2, -H/2, D/2);
				glVertex3i(W/2, H/2, D/2);
				glVertex3i(W/2, H/2, -D/2);
    
				glVertex3i(-W/2, -H/2, -D/2);
				glVertex3i(-W/2, -H/2, D/2);
				glVertex3i(W/2, -H/2, D/2);
				glVertex3i(W/2, -H/2, -D/2);
			}
			glEnd();

			glPolygonOffset(-1,-1);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBegin(GL_QUADS);
			{
				glColor3f(0, 0, 0);
				glVertex3i(-W/2, -H/2, -D/2);
				glVertex3i(W/2, -H/2, -D/2);
				glVertex3i(W/2, H/2, -D/2);
				glVertex3i(-W/2, H/2, -D/2);

				glVertex3i(-W/2, -H/2, D/2);
				glVertex3i(W/2, -H/2, D/2);
				glVertex3i(W/2, H/2, D/2);
				glVertex3i(-W/2, H/2, D/2);

				glVertex3i(-W/2, -H/2, -D/2);
				glVertex3i(-W/2, -H/2, D/2);
				glVertex3i(-W/2, H/2, D/2);
				glVertex3i(-W/2, H/2, -D/2);

				glVertex3i(W/2, -H/2, -D/2);
				glVertex3i(W/2, -H/2, D/2);
				glVertex3i(W/2, H/2, D/2);
				glVertex3i(W/2, H/2, -D/2);
    
				glVertex3i(-W/2, -H/2, -D/2);
				glVertex3i(-W/2, -H/2, D/2);
				glVertex3i(W/2, -H/2, D/2);
				glVertex3i(W/2, -H/2, -D/2);
			}
			glEnd();
		}
};

class Color:public body{
	private:
		float x, y, z,
			  xVel, yVel, zVel,
			  xzGr;
		int age = 0;
	public:
		Color(int a, int b, int c){x=a;y=b;z=c;}
		
		void update(){
			age++;
			
			if 
			
			
			int count = 1;  //  This counter is for increasing the probability of movent as it increases
			if (rand()%5 == 0)  //   1 in 10 chance of changing what the dot is doing
			{
				if(rand()%count==0)  //  1 in count chance of making the dot move with a random velocity
				{
					xVel = rand() % 2;  //  makes the dots move with an axis velocity of max 2
					zVel = rand() % 2;  //
					if (rand()%2 == 1){xVel = -xVel;}  //  1 in 2 chance of making the dot turn around in the x direction
					if (rand()%2 == 1){zVel = -zVel;}  //  1 in 2 chance of making the dot turn around in the y direction
				}else{count = 1;zVel=0;xVel=0;}  //  Makes the dot stay still and resets the count
			}else{count++;}  //  Increments the count
			
			if(1){
				x += xVel*0.1;
			}
			if(1){
				z += zVel*0.1;
			}
			xzGr = zVel/xVel;
		}
		
		void draw(){
			update();
			
			glPolygonOffset(1,1);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLE_FAN);
			{
				glColor3f(0.0f, 0.8f, 0.0f);
				glVertex3f(x, y, z);
				glVertex3f(x-0.5, y, z-1);
				glVertex3f(x, y+0.5, z-1);
				glVertex3f(x+0.5, y, z-1);
			}
			glEnd();
			
			glPolygonOffset(-1,-1);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBegin(GL_TRIANGLE_FAN);
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex3f(x, y, z);
				glVertex3f(x-0.5, y, z-1);
				glVertex3f(x, y+0.5, z-1);
				glVertex3f(x+0.5, y, z-1);
			}
			glEnd();
		}
};

void Init(void){
	const int window_width = 1280,
			  window_height = 900;
 
	if(glfwInit() != GL_TRUE) Shut_Down(1);
	
	// 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
	if(glfwOpenWindow(window_width, window_height, 8, 8, 8,
					  8, 8, 8, GLFW_WINDOW) != GL_TRUE) Shut_Down(1);
	
	glfwSetWindowTitle("Tesdf");
	//glfwSetKeyCallback( keyhandler );
	glEnable(GL_DEPTH_TEST);
	
	glfwDisable( GLFW_MOUSE_CURSOR );
	
	// set the projection matrix to a normal frustum with a max depth of 50
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float aspect_ratio = ((float)window_height) / window_width;
	glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 200);
	
	glMatrixMode(GL_MODELVIEW);
}
 
void Shut_Down(int return_code){
	glfwTerminate();
	exit(return_code);
}



void Main_Loop(void){
  // the time of the previous frame
	double old_time = glfwGetTime();
	int m_x = 0;int m_y = 0;
	bool mouserelease = 0;

	while(1){
		std::cout << XPOS << "  " << ZPOS << "\n";
		
    // calculate time elapsed, and the amount by which stuff rotates
		double current_time = glfwGetTime();
			   //delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		old_time = current_time;
		
    // escape to quit, arrow keys to rotate view
		if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) break;
		
		if(glfwGetKey('P') == GLFW_PRESS){
			if(mouserelease){
				glfwEnable( GLFW_MOUSE_CURSOR );
			}
			else{
				glfwDisable( GLFW_MOUSE_CURSOR );
			}
			mouserelease = !mouserelease;
		}
		
		glfwGetMousePos(&m_x,&m_y);
		
		if(!mouserelease) glfwSetMousePos(1280/2, 900/2);
		
		rotate_y -= (m_x-1280/2)*0.1;
		if(1) rotate_x += (m_y-900/2)*0.1;
		
		if(rotate_y < -180) rotate_y += 360; // Limits the angle, but I'm not sure of the impact
		if(rotate_y > 180) rotate_y -= 360;
		
		//Movement relative to the camera
		if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS){	
			YPOS -= 0.1;
		}
		
		if (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS){
			YPOS += 0.1;
		}
		
		if (glfwGetKey('W') == GLFW_PRESS){
			ZPOS += sin(RADCON*rotate_y+1.571)*0.1f;
			XPOS += cos(RADCON*rotate_y+1.571)*0.1f;
		}
		
		if (glfwGetKey('S') == GLFW_PRESS){
			ZPOS -= sin(RADCON*rotate_y+1.571)*0.1f;
			XPOS -= cos(RADCON*rotate_y+1.571)*0.1f;
		}
		
		if (glfwGetKey('A') == GLFW_PRESS){
			ZPOS -= sin(RADCON*rotate_y)*0.1f;
			XPOS -= cos(RADCON*rotate_y)*0.1f;
		}
		
		if (glfwGetKey('D') == GLFW_PRESS){
			ZPOS += sin(RADCON*rotate_y)*0.1f;
			XPOS += cos(RADCON*rotate_y)*0.1f;
		}
		
		if (rand()%(bodies.size()*5)==1){
			bodies.push_back(new Color((rand()%300)/10-15,(rand()%30)/10,(rand()%300)/10-15));
		}
		
		
		// clear the buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// draw the figure
		Draw();
		
		// swap back and front buffers
		glfwSwapBuffers();
	}
}

void Draw(void){
	// reset view matrix
	glLoadIdentity();
	
	glRotatef(rotate_x, 1, 0, 0);
	glRotatef(rotate_y, 0, 1, 0);
	glTranslatef(XPOS, YPOS, ZPOS);
	
	for(uint i=0; i<bodies.size();i++){bodies[i]->draw();}
}

int main(){
	bodies.push_back(new box(3,30,30));
	bodies.push_back(new Color(0,0,0));
	Init();
	Main_Loop();
	Shut_Down(0);
}
