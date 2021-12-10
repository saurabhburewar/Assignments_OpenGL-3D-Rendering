#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

void init (void) {

    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_position[] = {0, 100, 0, 1};
    GLfloat light_ambient[] = {0, 0, 0, 1.0};
    glClearColor( 0, 0, 0, 0 );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60, 1, 0, 100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 10, 0, 0, 0, 1);
    // gluLookAt(0, -200, 100, 0, 0, 10, 0, 0, 1);
}

void display (void) {
    string line;
    vector<int> counts;
    vector<vector<float>> vertices;
    vector<vector<int>> faces;
    ifstream file ("Models/cat01.off");
    if (file.is_open()) {
        getline(file, line);
        if (line == "OFF") {
            getline(file, line);
            stringstream lineStream(line);
            int value;
            while (lineStream >> value) {
                counts.push_back(value);
            }

            for (int i = 0; i < counts[0]; i++) {
                vector<float> vertex;
                getline(file, line);
                stringstream lineStream(line);
                float value;
                while (lineStream >> value) {
                    vertex.push_back(value);
                }
                vertices.push_back(vertex);
            }
            
            for (int i = 0; i < counts[1]; i++) {
                vector<int> face;
                getline(file, line);
                stringstream lineStream(line);
                int value;
                while (lineStream >> value) {
                    face.push_back(value);
                }
                faces.push_back(face);
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file";
    }

    glBegin(GL_POINTS);
    // Position of light source
    glVertex3f(0, -100, 0);
    glEnd();

        // Translate object by (0, 200, -100)

    for (int i = 0; i < vertices.size(); i++) {
        float m[4][4] = {{1,0,0,0}, {0,1,0, 200}, {0,0,1,-100}, {0,0,0,1}};
        float v[] = {vertices[i][0], vertices[i][1], vertices[i][2], 1};
        float vy[4];

        for (int j = 0; j < 4; j++) {
            vy[j] = 0;
        }
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                vy[j] += (m[j][k] * v[k]);
            }
        }
        vertices[i][0] = vy[0]/vy[3];
        vertices[i][1] = vy[1]/vy[3];
        vertices[i][2] = vy[2]/vy[3];
    }


    for (int i = 0; i < faces.size(); i++) {
        if (faces[i][0] == 3) {
            int ind1 = faces[i][1];
            int ind2 = faces[i][2];
            int ind3 = faces[i][3];
            glBegin(GL_TRIANGLES);

            glVertex3f( vertices[ind1][0], vertices[ind1][1], vertices[ind1][2] );
            glVertex3f( vertices[ind2][0], vertices[ind2][1], vertices[ind2][2] );
            glVertex3f( vertices[ind3][0], vertices[ind3][1], vertices[ind3][2] );
            glEnd();
        }
    }

    // Finding normals

    for (int i = 0; i < faces.size(); i++) {
        if (faces[i][0] == 3) {
            int ind1 = faces[i][1];
            int ind2 = faces[i][2];
            int ind3 = faces[i][3];

            
            
            vector<float> v1= {vertices[ind1][0],vertices[ind1][1],vertices[ind1][2]};
            vector<float> v2= {vertices[ind2][0],vertices[ind2][1],vertices[ind2][2]}; 
            vector<float> v3= {vertices[ind3][0],vertices[ind3][1],vertices[ind3][2]};

            vector<float> u={vertices[ind1][0]-vertices[ind2][0], vertices[ind1][1]-vertices[ind2][1], vertices[ind1][2]-vertices[ind2][2]};
            vector<float> v={vertices[ind2][0]-vertices[ind3][0], vertices[ind2][1]-vertices[ind3][1], vertices[ind2][2]-vertices[ind3][2]};

            vector<float> cp={v[1]*u[2]-v[2]*u[1], v[2]*u[0]-v[0]*u[2], v[0]*u[1]-v[1]*u[0]};

            // oriented Normal

            if(cp[2]<0)
            {
                cp[0]*=-1;
                cp[1]*=-1;
                cp[2]*=-1;
            }
            // printf("cp: %f %f %f\n", cp[0],cp[1],cp[2]);
        }
    }

    float x_min=10000,x_max=0,y_min=10000,y_max=0,z_min=10000,z_max=0;
    for (int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i][0]<x_min)
                x_min=vertices[i][0];
            if(vertices[i][0]>x_max)
                x_max=vertices[i][0];
            if(vertices[i][1]<y_min)
                y_min=vertices[i][1];
            if(vertices[i][1]>y_max)
                y_max=vertices[i][1];
            if(vertices[i][2]<z_min)
                z_min=vertices[i][2];
            if(vertices[i][2]>z_max)
                z_max=vertices[i][0];
        }

        // near frustrum

        printf("Near frustrum limit in plane perpendicular to y axis= (%f,%f), (%f,%f), (%f,%f), (%f,%f) at %f in y-axis position\n",x_min,z_min,x_min,z_max,x_max,z_min,x_max,z_max,y_min);
        printf("Far frustrum limit in plane perpendicular to y axis= (%f,%f), (%f,%f), (%f,%f), (%f,%f) at %f in y-axis position\n",x_min,z_min,x_min,z_max,x_max,z_min,x_max,z_max,y_max);
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
    glEnable(GL_CULL_FACE);
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 10, 30 );
    glutCreateWindow("Model");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}