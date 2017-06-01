// ParticleToy.cpp : Defines the entry point for the console application.
//

#include "Particle.h"

#include "forces/SpringForce.h"
//#include "forces/StaticForce.h"
#include "constraints/RodConstraint.h"
#include "constraints/DotConstraint.h"
#include "constraints/LineConstraint.h"
#include "constraints/CircularWireConstraint.h"
#include "forces/GravityForce.h"
#include "forces/WallForce.h"

#include <iostream>

#include "solvers/EulerianSolver.h"
#include "solvers/ForwardEulerianSolver.h"
#include "solvers/MidPointSolver.h"

#include "forces/DampeningForce.h"
#include "solvers/Runge4Solver.h"
#include "SceneBuilder.h"


#include <GL/glut.h>

/* macros */

/* global variables */
static int N;
static float dt, d;
static int dsim;
static int dump_frames;
static int frame_number;

static int win_id;
static int win_x, win_y;
static int mouse_down[3];
static int mouse_release[3];
static int mouse_shiftclick[3];
static int omx, omy, mx, my;
static int hmx, hmy;
static int sceneMenu;
static int solverMenu;
static int mainMenu;
static Solver* solver;
static ParticleSystem* particleSystem;

/*
----------------------------------------------------------------------
free/clear/allocate simulation data
----------------------------------------------------------------------
*/

static void free_data(void) {
    particleSystem->particles.clear();
    particleSystem->particles.clear();
    particleSystem->particles.clear();

    delete(solver);
    delete(particleSystem);
    glutDestroyMenu(sceneMenu);
}

static void clear_data(void) {
    int size = particleSystem->particles.size();

    for (int i = 0; i < size; i++) {
        particleSystem->particles[i]->reset();
    }
}


static void init_system(void) {

    particleSystem = new ParticleSystem();
    solver = new ForwardEulerianSolver();

}



/*
----------------------------------------------------------------------
OpenGL specific drawing routines
----------------------------------------------------------------------
*/

static void pre_display(void) {
    glViewport(0, 0, win_x, win_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void post_display(void) {
    // Write frames if necessary.
    if (dump_frames) {
        const int FRAME_INTERVAL = 4;
        if ((frame_number % FRAME_INTERVAL) == 0) {
            const int w = glutGet(GLUT_WINDOW_WIDTH);
            const int h = glutGet(GLUT_WINDOW_HEIGHT);
            unsigned char *buffer = (unsigned char *) malloc(w * h * 4 * sizeof(unsigned char));
            if (!buffer)
                exit(-1);
            // glRasterPos2i(0, 0);
            glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            static char filename[80];
            sprintf(filename, "snapshots/img%.5i.png", frame_number / FRAME_INTERVAL);
            printf("Dumped %s.\n", filename);
//			saveImageRGBA(filename, buffer, w, h);

            free(buffer);
        }
    }
    frame_number++;

    glutSwapBuffers();
}

static void draw_particles(void) {
    particleSystem->drawParticles();

}

static void draw_forces(void) {
    particleSystem->drawForces();
}

static void draw_constraints(void) {
    particleSystem->drawConstraints();
}

/*
----------------------------------------------------------------------
relates mouse movements to particle toy construction
----------------------------------------------------------------------
*/

static void get_from_UI() {
    int i, j;
    // int size, flag;
    int hi, hj;
    // float x, y;
    if (!mouse_down[0] && !mouse_down[2] && !mouse_release[0]
        && !mouse_shiftclick[0] && !mouse_shiftclick[2])
        return;

    i = (int) ((mx / (float) win_x) * N);
    j = (int) (((win_y - my) / (float) win_y) * N);

    if (i < 1 || i > N || j < 1 || j > N) return;

    if (mouse_down[0]) {

    }

    if (mouse_down[2]) {
    }

    hi = (int) ((hmx / (float) win_x) * N);
    hj = (int) (((win_y - hmy) / (float) win_y) * N);

    if (mouse_release[0]) {
    }

    omx = mx;
    omy = my;
}

static void remap_GUI() {
    int i, size = particleSystem->particles.size();
    for (i = 0; i < size; i++) {
        particleSystem->particles[i]->m_Position[0] = particleSystem->particles[i]->m_ConstructPos[0];
        particleSystem->particles[i]->m_Position[1] = particleSystem->particles[i]->m_ConstructPos[1];
    }
}

/*
----------------------------------------------------------------------
GLUT callback routines
----------------------------------------------------------------------
*/

static void key_func(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
        case 'C':
            clear_data();
            break;

        case 'd':
        case 'D':
            dump_frames = !dump_frames;
            break;

        case 'q':
        case 'Q':
            free_data();
            exit(0);

        case ' ':
            dsim = !dsim;
            break;
        default:
            break;
    }
}

/**
 *
 * @param p1
 * @param p2
 * @return the squared distance between two particles.
 */
static float distanceSq(Particle* p1, Particle* p2){
    Vec2f distVec = p1->m_Position - p2->m_Position;
    return distVec * distVec;
}
/**
 *
 * @param particle
 * @return the closest particle to the given particle.
 */
static Particle* closestParticle(Particle* particle){
    int pSize = particleSystem->particles.size();
    Particle * closest = nullptr;
    float cDist = 0;
    for(int i = 0; i < pSize; i++){
        if(i==0) {
            closest = particleSystem->particles[0];
            cDist = distanceSq(closest, particle);
        }
        else{
            float nxtDist = distanceSq(particleSystem->particles[i],particle);
            if(cDist > nxtDist){
                closest = particleSystem->particles[i];
                cDist = nxtDist;
            }
        }
    }

    return closest;
}

bool inRange(Particle* p1, Particle* p2) {
    float x = p1->m_Position[0] - p2->m_Position[0];
    float y = p1->m_Position[1] - p2->m_Position[1];
    float range = 0.05f;

    return (x >= 0 ? x : -1 * x) < range && (y >= 0 ? y : -1 * y) < range;
}

static void mouse_func(int button, int state, int x, int y) {
    omx = mx = x;
    omx = my = y;

    if (!mouse_down[0]==1) {
        hmx = x;
        hmy = y;
    }
    if (mouse_down[button]) mouse_release[button] = state == GLUT_UP;
    if (mouse_down[button]) mouse_shiftclick[button] = glutGetModifiers() == GLUT_ACTIVE_SHIFT;
    mouse_down[button] = state == GLUT_DOWN;

    //create particle
    if (mouse_down[0]==1) {
        float loc_x = (float) ((float) mx / (float) win_x * 2.0 - 1.0);
        float loc_y = 0 - (float) ((float) my / (float) win_y * 2.0 - 1.0);

        Vec2f place(loc_x, loc_y);
        Particle *mousePoint = new Particle(place);
        Particle *closestPart = closestParticle(mousePoint);

        if ( closestPart != nullptr && !inRange(closestPart, mousePoint)) {
            particleSystem->forces.push_back(
                    new SpringForce(mousePoint, closestPart, sqrt(distanceSq(mousePoint, closestPart)), 0.1, 0.01)
            );
        }

        particleSystem->particles.push_back(mousePoint);
        particleSystem->forces.push_back(new DampeningForce(mousePoint));
        printf("create new particle at: %f, %f\n", mousePoint->m_ConstructPos[0], mousePoint->m_ConstructPos[1]);
    }
}

static void motion_func(int x, int y) {
    mx = x;
    my = y;
}

static void reshape_func(int width, int height) {
    glutSetWindow(win_id);
    glutReshapeWindow(width, height);

    win_x = width;
    win_y = height;
}

static void idle_func(void) {
    if (dsim){
        solver->simulation_step(particleSystem, dt);

        // This is not in motion_func because a held particle would stop moving when the mouse stops moving, even though
        // the mouse button is still pressed
        if (mouse_down[0]) {
            float loc_x = (float) ((float) mx / (float) win_x * 2.0 - 1.0);
            float loc_y = 0 - (float) ((float) my / (float) win_y * 2.0 - 1.0);
            particleSystem->particles.back()->m_Position = Vec2f(loc_x, loc_y);
        }
    } else {
        get_from_UI();
        remap_GUI();
    }

    glutSetWindow(win_id);
    glutPostRedisplay();
}

static void display_func(void) {
    pre_display();

    draw_forces();
    draw_constraints();
    draw_particles();

    post_display();
}


/*
----------------------------------------------------------------------
open_glut_window --- open a glut compatible window and set callbacks
----------------------------------------------------------------------
*/
// process events in scene submenu
void processSceneMenuEvents(int option) {
    delete(particleSystem);

    switch (option) {
        case 0:
            particleSystem = createEmptyScene();
            printf("Created empty scene\n");
            break;
        case 1:
            particleSystem = createCurtainScene();
            printf("Created Curtain scene\n");
            break;
        case 2:
        default:
            printf("Created circular wire scene\n");
            particleSystem = createCircularWireScene();
            break;
    }
}

// Process events in solver submenu
void processSolverMenuEvents(int option) {
    delete(solver);

    switch(option) {
        case 0:
            printf("ForwardEuler solver selected\n");
            solver = new ForwardEulerianSolver();
            break;
        case 1:
            printf("Mid-Point solver selected\n");
            //solver = new MidPointSolver();
            break;
        case 2:
        default:
            printf("Runge-Kutta 4th order solver selected\n");
            //solver = new Runge4Solver();
    }
}

// Creates the entire menu, including submenus
static void createMenu() {
    sceneMenu = glutCreateMenu(processSceneMenuEvents);
    glutAddMenuEntry("Empty scene", 0);
    glutAddMenuEntry("Circular wire", 1);

    solverMenu = glutCreateMenu(processSolverMenuEvents);
    glutAddMenuEntry("Forward euler", 0);
    glutAddMenuEntry("Mid-point", 1);
    glutAddMenuEntry("Runge-kutta 4", 2);

    mainMenu = glutCreateMenu(0);
    glutAddSubMenu("Scenes", sceneMenu);
    glutAddSubMenu("Solvers", solverMenu);

    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

static void open_glut_window(void) {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(win_x, win_y);
    win_id = glutCreateWindow("Particletoys!");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    createMenu();

    pre_display();

    glutKeyboardFunc(key_func);
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutReshapeFunc(reshape_func);
    glutIdleFunc(idle_func);
    glutDisplayFunc(display_func);
}

void Console()
{
    AllocConsole();
    FILE *pFileCon = NULL;
    pFileCon = freopen("CONOUT$", "w", stdout);

    COORD coordInfo;
    coordInfo.X = 100;
    coordInfo.Y = 9000;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),ENABLE_QUICK_EDIT_MODE| ENABLE_EXTENDED_FLAGS);
}

/*
----------------------------------------------------------------------
main --- main routine
----------------------------------------------------------------------
*/

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    Console();

    if (argc == 1) {
        N = 64;
        dt = 0.001f; //(max 2.03f runge4)
        d = 5.f;
    } else {
        N = atoi(argv[1]);
        dt = (float) atof(argv[2]);
        d = (float) atof(argv[3]);
    }

    printf("\n\nHow to use this application:\n\n");
    printf("\t Toggle construction/simulation display with the spacebar key\n");
    printf("\t Dump frames by pressing the 'd' key\n");
    printf("\t Quit by pressing the 'q' key\n");

    dsim = 0;
    dump_frames = 0;
    frame_number = 0;

    init_system();

    win_x = 512;
    win_y = 512;
    open_glut_window();

    glutMainLoop();

    exit(0);
}

