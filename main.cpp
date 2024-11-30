#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

void display();
void initializeVertices();
void keyDetect(unsigned char key, int x, int y);
void GLAPIENTRY 
MessageCallback(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* useParam);

GLuint VBOid;
GLuint VBOcolor;


bool isNotDisplayed = true;

int main(int argc, char** argv){
	
	glutInit(&argc, argv);
	glutCreateWindow("Rocky Road");
	glutFullScreen();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyDetect);
	GLenum err = glewInit();
	if(err == GLEW_OK){
		glEnable (GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
		printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
		printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
		glutMainLoop();
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	initializeVertices();
	glFlush();
	
}

void initializeVertices(){
	if(isNotDisplayed){
		GLfloat vertices[] = {
		// Outer flame
        0.0f, -0.72f, 0.0f,
        -0.02f, -0.76f, 0.0f,
        0.0f, -0.78f, 0.0f,
        0.02f, -0.76f, 0.0f,
        // Inner flame
        0.0f, -0.72f, 0.0f,
        -0.008f, -0.76f, 0.0f,
        0.0f, -0.77f, 0.0f,
        0.008f, -0.76f, 0.0f,
        // Body
        -0.01f, -0.66f, 0.0f,
        0.01f, -0.66f, 0.0f,
        0.01f, -0.74f, 0.0f,
        -0.01f, -0.74f, 0.0f,
        // Side 1
        -0.014f, -0.67f, 0.0f,
        -0.01f, -0.67f, 0.0f,
        -0.01f, -0.69f, 0.0f,
        -0.014f, -0.69f, 0.0f,
        // Side 2
        0.014f, -0.67f, 0.0f,
        0.01f, -0.67f, 0.0f,
        0.01f, -0.69f, 0.0f,
        0.014f, -0.69f, 0.0f,
		// Rocket triangle (top and fins)
        0.0f, -0.62f, 0.0f,  // Top point
        -0.01f, -0.66f, 0.0f, // Bottom-left
        0.01f, -0.66f, 0.0f,  // Bottom-right
        -0.03f, -0.74f, 0.0f, // Left fin-left
        -0.01f, -0.7f, 0.0f,  // Left fin-top
    	-0.01f, -0.74f, 0.0f, // Left fin-right
   		0.03f, -0.74f, 0.0f,  // Right fin-right
    	0.01f, -0.7f, 0.0f,   // Right fin-top
        0.01f, -0.74f, 0.0f   // Right fin-left
		};
		
		GLfloat colors[] = {
            // Outer flame (Yellow)
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            // Inner flame (Orange)
            1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f,
            // Body (Lighter Orange)
            1.0f, 0.7f, 0.0f, 1.0f, 0.7f, 0.0f, 1.0f, 0.7f, 0.0f, 1.0f, 0.7f, 0.0f,
            // Side 1 (Red)
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            // Side 2 (Red)
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            // Rocket triangle (Red)
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Top triangle
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Left fin
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f  // Right fin
        };
		
		glGenBuffers(1, &VBOid);
		glBindBuffer(GL_ARRAY_BUFFER, VBOid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glGenBuffers(1, &VBOcolor);
		glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glColorPointer(3, GL_FLOAT, 0, 0);
		
		isNotDisplayed = false;
		
	}
	
	glDrawArrays(GL_QUADS, 0, 4);
	
	glDrawArrays(GL_QUADS, 4, 4);
	
	glDrawArrays(GL_QUADS, 8, 4);
	
	glDrawArrays(GL_QUADS, 12, 4);
	
	glDrawArrays(GL_QUADS, 16, 4);
	
	glDrawArrays(GL_TRIANGLES, 20, 3);
	glDrawArrays(GL_TRIANGLES, 23, 3);
	glDrawArrays(GL_TRIANGLES, 26, 3);
}

void keyDetect(unsigned char key, int x, int y){
	cout << key << " " << x << y << endl;
	
	
	switch(key){
		case 27:
			//Esc key pressed
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glDeleteBuffers(1, &VBOid);
			glDeleteBuffers(1, &VBOcolor);
			exit(0);
			break;
		
		case 'd':
        case 'D': 
				break;
        
        case 'a':
        case 'A': 
				break;
				
		case 's':
        case 'S': 
				break;
		case 'w':
        case 'W': 
				break;
	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glutPostRedisplay();
}

void GLAPIENTRY MessageCallback(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message,
								const void* userParam){
	fprintf(stderr, "GL CALLBACK: %s type =0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), 
		type, severity, message);
}
