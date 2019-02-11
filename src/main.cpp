#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "ceiling.h"
#include "firebeam.h"
#include "coin.h"
#include "fireline.h"
#include "fireline_helix.h"
#include "waterballoon.h"
#include "jet.h"
#include "boomerang.h"
#include "dragon.h"
#include "ice_ball.h"
#include "magnet.h"
#include "zero.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"
#include "seven.h"
#include "eight.h"
#include "nine.h"
#include "score_s.h"
#include "lives_l.h"
#include "ring.h"
#include "powerup.h"
#include "gate.h"
#include "powerup_cover.h"
#include<bits/stdc++.h>
#include <unistd.h>

#define NO_OF_COINS 16
#define POWERUP_COUNT 2
#define FIRE_OBSTACLE_COUNT 5
#define BOOMERANG_COUNT 4

using namespace std;
#define f first
#define s second
#define pb push_back
#define mp make_pair

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Platform platform;
Ceiling ceiling;
Coin coin[NO_OF_COINS];
Jet jet[3];
FireBeam firebeam[FIRE_OBSTACLE_COUNT];
FireLine fireline[FIRE_OBSTACLE_COUNT];
FireLine_Helix fireline_helix[FIRE_OBSTACLE_COUNT];
Water_Balloon balloon;
Boomerang boomerang[BOOMERANG_COUNT];
Dragon dragon;
IceBall iceball;
Magnet magnet;
Zero zero[7],zerol[3];
One one[7],onel[3],stage1;
Two two[7],twol[3],stage2;
Three three[7],threel[3],stage3;
Four four[7],fourl[3];
Five five[7],fivel[3];
Six six[7],sixl[3];
Seven seven[7],sevenl[3];
Eight eight[7],eightl[3];
Nine nine[7],ninel[3];
Score_S score_s;
Lives_L lives_l;
Ring ring;
Gate gate;
Powerup powerup[POWERUP_COUNT];
Powerup_Cover power_tri[POWERUP_COUNT];
bool active_magnet=0,create_coin[NO_OF_COINS],create_firebeam[FIRE_OBSTACLE_COUNT],create_fireline[FIRE_OBSTACLE_COUNT],create_balloon=0,flag_balloon=1,create_jet[3],create_boomerang[BOOMERANG_COUNT],create_dragon=1,create_iceball=0,create_magnet=0,create_ring=1,create_powerup[POWERUP_COUNT];
bounding_box_t coins[NO_OF_COINS],ball_1,firebeams[FIRE_OBSTACLE_COUNT][3],balloon_s,iceball1,powerup_s[POWERUP_COUNT],gate1;
pair<float,float> pos;
int level=1;
float speed_level[]={0,0.02,0.025,0.03};

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
// float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye(0,0,1);
    // glm::vec3 eye(ball1.position.x,0,1);
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // glm::vec3 target (ball1.position.x, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;


    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    platform.draw(VP);
    ceiling.draw(VP);
    gate.draw(VP);
    switch(level)
    {
        case 1:stage1.draw(VP);
                break;
        case 2:stage2.draw(VP);
                break;
        case 3:stage3.draw(VP);
                break;
    }
    for(int i=0;i<FIRE_OBSTACLE_COUNT;i++)
    {
        if(create_firebeam[i])
            firebeam[i].draw(VP);
        if(create_fireline[i])
            fireline[i].draw(VP),fireline_helix[i].draw(VP);
    }
    for(int i=0;i<NO_OF_COINS;i++)
        if(create_coin[i])
            coin[i].draw(VP);
    if(create_balloon)
        balloon.draw(VP);
    if(level>1)
        for(int i=0;i<BOOMERANG_COUNT;i++)
            if(create_boomerang[i])
                boomerang[i].draw(VP);
    for(int i=0;i<3;i++)
        if(create_jet[i])
            jet[i].draw(VP);
    if(level==3)
    {   
        if(create_dragon)
            dragon.draw(VP);
        if(create_iceball)
            iceball.draw(VP);
        if(magnet.position.x<=3.3 and !create_magnet and !active_magnet)
        {
            magnet.time=glfwGetTime();
            create_magnet=1;
        }
        if(create_magnet and !active_magnet)
        {
            ball1.speedx+=0.02;
            active_magnet=1;
            magnet.draw(VP);
        }
        else if(create_magnet and active_magnet)
            magnet.draw(VP);
    }
    int rem,n=ball1.score;
    n=min(n,9999999);
    for(int k=0;k<7;k++)
    {
        rem=n%10;
        n/=10;
        switch(rem)
        {
            case 0:zero[k].draw(VP);
                    break;
            case 1:one[k].draw(VP);
                    break;
            case 2:two[k].draw(VP);
                    break;
            case 3:three[k].draw(VP);
                    break;
            case 4:four[k].draw(VP);
                    break;
            case 5:five[k].draw(VP);
                    break;
            case 6:six[k].draw(VP);
                    break;
            case 7:seven[k].draw(VP);
                    break;
            case 8:eight[k].draw(VP);
                    break;
            case 9:nine[k].draw(VP);
                    break;
        }
    }
    score_s.draw(VP);
    n=ball1.lives;
    n=min(n,999);
    for(int k=0;k<3;k++)
    {
        rem=n%10;
        n/=10;
        switch(rem)
        {
            case 0:zerol[k].draw(VP);
                    break;
            case 1:onel[k].draw(VP);
                    break;
            case 2:twol[k].draw(VP);
                    break;
            case 3:threel[k].draw(VP);
                    break;
            case 4:fourl[k].draw(VP);
                    break;
            case 5:fivel[k].draw(VP);
                    break;
            case 6:sixl[k].draw(VP);
                    break;
            case 7:sevenl[k].draw(VP);
                    break;
            case 8:eightl[k].draw(VP);
                    break;
            case 9:ninel[k].draw(VP);
                    break;
        }
    }
    lives_l.draw(VP);
    if(create_ring)
        ring.draw(VP);
    for(int i=0;i<POWERUP_COUNT;i++)
        if(create_powerup[i])
        {
            powerup[i].draw(VP);
            power_tri[i].draw(VP);
        }
}

void tick_input(GLFWwindow *window) {
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if(!ball1.immune)
    {
        int left  = glfwGetKey(window, GLFW_KEY_LEFT);
        int right = glfwGetKey(window, GLFW_KEY_RIGHT);
        int up = glfwGetKey(window, GLFW_KEY_UP);
        int down = glfwGetKey(window, GLFW_KEY_DOWN);
        if(left)
        {
            ball1.position.x-=0.1;
            ball1.position.x=min(3.5f,max(-3.3f,ball1.position.x));
        }
        if(right)
        {
           ball1.position.x+=0.1;
           ball1.position.x=min(3.5f,max(-3.3f,ball1.position.x));
        }
        if(up)
        {
            ball1.move_up();
            for(int i=0;i<3;i++)
            {
                create_jet[i]=1;
                if(i==1)
                    jet[i].position.x=ball1.position.x,jet[i].position.y=ball1.position.y;
                else if(i==0)
                    jet[i].position.x=ball1.position.x-0.12,jet[i].position.y=ball1.position.y;
                else
                    jet[i].position.x=ball1.position.x+0.12,jet[i].position.y=ball1.position.y;
            }
        }
        else
            for(int i=0;i<3;i++)
                create_jet[i]=0;
        if(down && ball1.position.y>-3.5)
        {
            for(int i=0;i<3;i++)
                create_jet[i]=0;
            ball1.down=1;
            ball1.position.y-=0.1;
            ball1.position.y=max(ball1.position.y,-2.3f);
        }
    }
    ball_1.x=ball1.position.x;
    ball_1.y=ball1.position.y;
    if(space && !create_balloon)
    {
        create_balloon=1;
        flag_balloon=0;
        balloon.time=glfwGetTime();
    }
}

void tick_elements() {
    ball1.tick(create_ring);
    gate.tick();
    gate.position.x=max(gate.position.x,3.0f);
    gate1.x=gate.position.x,gate1.y=gate.position.y;
    if(detect_collision(ball_1,gate1))
    {
        level++;
        return;
    }
    if(create_ring and detect_collision_ring(ball_1,ring.position.x,ring.position.y,ring.radius) and !ball1.immune)
    {
        ball1.position.x=pos.f,ball1.position.y=pos.s;
        ball1.immune=1;
        ball1.speedx+=0.001;
    }
    for(int i=0;i<NO_OF_COINS;i++)
    {
        coin[i].tick();
        coins[i].x=coin[i].position.x;
        coins[i].y=coin[i].position.y;
        if(create_coin[i] and detect_collision(ball_1,coins[i]))
        {
            create_coin[i]=0;
            ball1.score+=coin[i].score;
        }
    }
    if(create_balloon)
        balloon.tick();
    for(int i=0;i<FIRE_OBSTACLE_COUNT;i++)
    {
        if(create_firebeam[i])
        {
            firebeam[i].tick();
            for(int j=0;j<3;j++)
                firebeams[i][j].y=firebeam[i].position.y;
            firebeams[i][0].x=firebeam[i].position.x-0.5;
            firebeams[i][1].x=firebeam[i].position.x;
            firebeams[i][2].x=firebeam[i].position.x+0.5;
        }
        if(create_fireline[i])
        {
            fireline[i].tick();
            fireline_helix[i].tick();
        }
        if(create_balloon and create_firebeam[i] and (detect_collision(balloon_s,firebeams[i][0]) || detect_collision_balloon(balloon_s,firebeams[i][1].x-0.4,firebeams[i][1].x+0.4,firebeams[i][1].y-0.01,firebeams[i][1].y+0.01,90*((3.14159265359)/180),firebeams[i][1].x,firebeams[i][1].y,0) || detect_collision(balloon_s,firebeams[i][2])))
            create_firebeam[i]=0,create_balloon=0,flag_balloon=1;
        if(create_balloon and create_fireline[i] and detect_collision_balloon(balloon_s,fireline[i].minx+fireline[i].position.x,fireline[i].maxx+fireline[i].position.x,fireline[i].miny+fireline[i].position.y,fireline[i].maxy+fireline[i].position.y,fireline[i].theta,fireline[i].position.x,fireline[i].position.y,1))
            create_fireline[i]=0,create_balloon=0,flag_balloon=1;
        if(create_firebeam[i] and (detect_collision(ball_1,firebeams[i][0]) || detect_collision(ball_1,firebeams[i][1]) || detect_collision(ball_1,firebeams[i][2])))
        {
            if(!ball1.immune)
            {
                ball1.lives--;
                ball1.position.x=3.5,ball1.position.y=2;       
            }
        }
        if(create_fireline[i] and (detect_collision_fireline(ball_1,fireline[i].minx+fireline[i].position.x,fireline[i].maxx+fireline[i].position.x,fireline[i].miny+fireline[i].position.y,fireline[i].maxy+fireline[i].position.y,fireline[i].theta,fireline[i].position.x,fireline[i].position.y)))
        {
            if(!ball1.immune)
            {
                ball1.lives--;
                ball1.position.x=3.5,ball1.position.y=2;            
            }
        }
    }
    for(int i=0;i<3;i++)
    {
        jet[i].position.x=ball1.position.x;
        jet[i].position.y=ball1.position.y;
        if(create_jet[i])
            jet[i].tick();
    }
    if(level>1)
    {
        for(int i=0;i<BOOMERANG_COUNT;i++)
        {
            boomerang[i].tick(create_boomerang[i]);
            if(create_boomerang[i] and detect_collision_boomerang(ball_1,boomerang[i].position.x,boomerang[i].position.y))
            {
                if(!ball1.immune)
                {
                    ball1.lives--;
                    ball1.position.x=3.5,ball1.position.y=2;
                }
            }
        }
    }
    if((balloon.position.y>3.046f || balloon.position.y<-2.3f || balloon.position.x>3.5f)  && create_balloon)
    {
        create_balloon=0;
        flag_balloon=1;
    }
    if(flag_balloon)
    {
        balloon.position.x=ball1.position.x;
        balloon.position.y=ball1.position.y;
        balloon.y1=balloon.position.y;
        balloon_s.x=balloon.position.x;
        balloon_s.y=balloon.position.y;
    }
    else if(create_balloon)
    {
        balloon_s.x=balloon.position.x;
        balloon_s.y=balloon.position.y;
    }
    balloon_s.x=balloon.position.x,balloon_s.y=balloon.position.y;
    if(level==3)
    {
        if(create_dragon)
        {
            dragon.position.y=ball1.position.y;
            dragon.tick();
            dragon.position.x=max(2.8f,dragon.position.x);
        }
        if(!create_iceball)
            iceball.position.x=dragon.position.x,iceball.position.y=dragon.position.y;
        if(create_iceball)
        {
            iceball.tick();
            if(iceball.position.x<-3.4)
                create_iceball=0;
        }
        iceball1.x=iceball.position.x,iceball1.y=iceball.position.y;
        if(create_iceball and detect_collision(iceball1,ball_1))
        {
            if(!ball1.immune)
            {
                ball1.lives--;
                ball1.position.x=-1,ball1.position.y=-3.3;
                create_iceball=0;            
            }
        }
        magnet.tick(!create_magnet);
        if(glfwGetTime()-dragon.time > 13)
            create_dragon=0;
        if(glfwGetTime()-magnet.time > 7 and create_magnet)
        {
            create_magnet=0;
            ball1.speedx-=0.02;
        }
    }
    for(int i=0;i<POWERUP_COUNT;i++)
    {
        if(create_powerup[i])
        {
            powerup[i].tick();
            power_tri[i].position.x=powerup[i].position.x-0.1;
            power_tri[i].position.y=powerup[i].position.y;
            powerup_s[i].x=powerup[i].position.x;
            powerup_s[i].y=powerup[i].position.y;
        }
        if(create_powerup[i] and (detect_collision(ball_1,powerup_s[i]) or detect_collision_power_tri(ball_1,power_tri[i].position.x,power_tri[i].position.y)))
        {
            if(powerup[i].base=="SCORE")
                ball1.score+=powerup[i].val;
            else
                ball1.lives+=powerup[i].val;
            create_powerup[i]=0;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // srand(time(0));
    ball1 = Ball(-3.4, -2.3, COLOR_RED);
    ball_1.x=-3,ball_1.y=-2.3,ball_1.width=0.4,ball_1.height=0.4;
    platform = Platform(-4,-3.5075,COLOR_BLACK);
    ceiling = Ceiling(0,1,COLOR_GREEN);
    balloon=Water_Balloon(ball1.position.x,ball1.position.y,COLOR_AQUA);
    ring=Ring(0,0,COLOR_BLOOD_RED);
    ring.radius=0.6;
    gate=Gate(40,0,COLOR_BROWN);
    gate1.x=gate.position.x,gate1.y=gate.position.y;
    gate1.height=5.546,gate1.width=2;
    gate.speedx=speed_level[level];
    if(level==3)
    {
        dragon=Dragon(10,ball1.position.y,COLOR_PINK_RED);
        dragon.speedx=speed_level[level];
        iceball=IceBall(dragon.position.x,dragon.position.y,COLOR_ICE);
        magnet=Magnet(12.9,2,COLOR_BLOOD_RED);
        magnet.speedx=speed_level[level];
        create_magnet=active_magnet=0;
        dragon.time=glfwGetTime();
        dragon.iceball_time=glfwGetTime();
        iceball1.x=iceball.position.x,iceball1.y=iceball.position.y;
        iceball1.width=iceball1.height=0.1;
        create_dragon=1,create_iceball=0;
    }
    int j=0;
    for(float i=-1.6;i>=-3.4;i-=0.3)
    {
        zero[j]=Zero(i,3.5,COLOR_LIGHT_PINK);
        one[j]=One(i,3.5,COLOR_LIGHT_PINK);
        two[j]=Two(i,3.5,COLOR_LIGHT_PINK);
        three[j]=Three(i,3.5,COLOR_LIGHT_PINK);
        four[j]=Four(i,3.5,COLOR_LIGHT_PINK);
        five[j]=Five(i,3.5,COLOR_LIGHT_PINK);
        six[j]=Six(i,3.5,COLOR_LIGHT_PINK);
        seven[j]=Seven(i,3.5,COLOR_LIGHT_PINK);
        eight[j]=Eight(i,3.5,COLOR_LIGHT_PINK);
        nine[j]=Nine(i,3.5,COLOR_LIGHT_PINK);
        j++;
    }
    stage1=One(1.5,3.5,COLOR_LIGHT_PINK);
    stage2=Two(1.5,3.5,COLOR_LIGHT_PINK);
    stage3=Three(1.5,3.5,COLOR_LIGHT_PINK);
    j=0;
    for(float i=3;i>=2.1;i-=0.3)
    {
        zerol[j]=Zero(i,3.5,COLOR_LIGHT_PINK);
        onel[j]=One(i,3.5,COLOR_LIGHT_PINK);
        twol[j]=Two(i,3.5,COLOR_LIGHT_PINK);
        threel[j]=Three(i,3.5,COLOR_LIGHT_PINK);
        fourl[j]=Four(i,3.5,COLOR_LIGHT_PINK);
        fivel[j]=Five(i,3.5,COLOR_LIGHT_PINK);
        sixl[j]=Six(i,3.5,COLOR_LIGHT_PINK);
        sevenl[j]=Seven(i,3.5,COLOR_LIGHT_PINK);
        eightl[j]=Eight(i,3.5,COLOR_LIGHT_PINK);
        ninel[j]=Nine(i,3.5,COLOR_LIGHT_PINK);
        j++;
    }
    score_s=Score_S(-3.8,3.5,COLOR_BLOOD_RED);
    lives_l=Lives_L(2,3.5,COLOR_BLOOD_RED);
    if(level>1)
    {
        for(int i=0;i<BOOMERANG_COUNT;i++)
        {
            boomerang[i]=Boomerang(3.5+i*12,3,COLOR_MAGENTA);
            create_boomerang[i]=0;
        }
    }
    for(int i=0;i<FIRE_OBSTACLE_COUNT;i++)
    {
        int firebeam_x=i*5+8;
        float firebeam_y=-1.2 + (rand()%2);
        int dir;
        if(rand()%100<=50)
            dir=0;
        else
            dir=1;
        firebeam[i] = FireBeam(firebeam_x,firebeam_y,COLOR_ORANGE,dir);
        firebeam[i].speedx=speed_level[level];
        firebeams[i][0].x=firebeam_x-0.5,firebeams[i][0].y=firebeam_y,firebeams[i][0].width=0.2,firebeams[i][0].height=0.2;
        firebeams[i][1].x=firebeam_x,firebeams[i][1].y=firebeam_y,firebeams[i][1].width=0.8,firebeams[i][1].height=0.02;
        firebeams[i][2].x=firebeam_x+0.5,firebeams[i][2].y=firebeam_y,firebeams[i][2].width=0.2,firebeams[i][2].height=0.2;
        create_firebeam[i]=1,create_fireline[i]=1;
        float angle=(15+(rand()%(75-15+1)))*((3.14159265359)/180);
        int fireline_x=i*5+4;
        float fireline_y=-1.3 + (rand()%(2));
        fireline[i] = FireLine(fireline_x,fireline_y,COLOR_ORANGE,angle);
        fireline_helix[i]=FireLine_Helix(fireline_x,fireline_y,COLOR_BLUE,angle);
        fireline[i].speedx=speed_level[level];
        fireline_helix[i].speedx=speed_level[level];
    }
    for(int i=0;i<NO_OF_COINS;i++)
    {
        if(rand()%2==1)
            coin[i] = Coin(2*i+1,(-2+rand()%(2+2+1)),COLOR_YELLOW,50);
        else
            coin[i] = Coin(2*i+1,(-2+rand()%(2+2+1)),COLOR_LIGHT_GREEN,100);
        coin[i].speedx=speed_level[level];
        coins[i].x=i*10,coins[i].y=0,coins[i].width=0.15,coins[i].height=0.15;
        create_coin[i]=1;
    }
    for(int i=0;i<POWERUP_COUNT;i++)
    {
        int x=i*9+3;
        if(!i)
            powerup[i] = Powerup(x,0,COLOR_PINK_RED,i%2,"SCORE",500);
        else if(i%2)
            powerup[i] = Powerup(x,0,COLOR_PINK_RED,i%2,"LIFE",1);
        power_tri[i] = Powerup_Cover(x-0.1,0,COLOR_BLUE);
        create_powerup[i]=1;
        powerup_s[i].x=powerup[i].position.x,powerup_s[i].y=powerup[i].position.y;
        powerup_s[i].width=powerup_s[i].height=0.01;
    }
    for(int i=0;i<3;i++)
        if(i==1)
            jet[i]=Jet(ball1.position.x,ball1.position.y,COLOR_PURPLE),create_jet[i]=0;
        else if(i==0)
            jet[i]=Jet(ball1.position.x-0.12,ball1.position.y,COLOR_PURPLE),create_jet[i]=0;
        else
            jet[i]=Jet(ball1.position.x+0.12,ball1.position.y,COLOR_PURPLE),create_jet[i]=0;            
    balloon_s.width=0.1,balloon_s.height=0.1;
    create_balloon=0,flag_balloon=1;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window) and ball1.lives>0 and level==1) {
        // Process timers
        // cout<<ball1.lives<<endl;
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            reset_screen(width/height);
        }
        if(level>1)
        {
            for(int i=0;i<BOOMERANG_COUNT;i++)
            {
                if(boomerang[i].position.x<4 and boomerang[i].position.x>-4)
                    create_boomerang[i]=1;
                if(boomerang[i].position.x<-4 || boomerang[i].position.y<-2.29)
                    create_boomerang[i]=0;
            }
        }
        if(level>2)
            if(dragon.shoot)
                create_iceball=1;
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window) and ball1.lives>0 and level==2) {
        // Process timers
        // cout<<ball1.lives<<endl;
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            reset_screen(width/height);
        }
        if(level>1)
        {
            for(int i=0;i<BOOMERANG_COUNT;i++)
            {
                if(boomerang[i].position.x<4 and boomerang[i].position.x>-4)
                    create_boomerang[i]=1;
                if(boomerang[i].position.x<-4 || boomerang[i].position.y<-2.29)
                    create_boomerang[i]=0;
            }
        }
        if(level>2)
            if(dragon.shoot)
                create_iceball=1;
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window) and ball1.lives>0 and level==3) {
        // Process timers
        // cout<<ball1.lives<<endl;
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            reset_screen(width/height);
        }
        if(level>1)
        {
            for(int i=0;i<BOOMERANG_COUNT;i++)
            {
                if(boomerang[i].position.x<4 and boomerang[i].position.x>-4)
                    create_boomerang[i]=1;
                if(boomerang[i].position.x<-4 || boomerang[i].position.y<-2.29)
                    create_boomerang[i]=0;
            }
        }
        if(level>2)
            if(dragon.shoot)
                create_iceball=1;
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}
float area(pair<float,float> a,pair<float,float> b,pair<float,float> c)
{
    return abs(0.5*(a.f*(b.s-c.s)+b.f*(c.s-a.s)+c.f*(a.s-b.s)));
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision_fireline(bounding_box_t a,float minx,float maxx,float miny,float maxy,float angle,float x1,float y1)
{
    float m=tan(angle);
    float c=y1-m*x1;
        for(float i=a.x-(a.width/2);i<=a.x+(a.width/2);i+=0.1)
            for(float j=a.y-(a.height/2);j<=a.y+(a.height/2);j+=0.1)
                if((minx<= i && i<=maxx) && (miny<= j && j<=maxy))
                    if(((m*i-j+c)*(m*i-j+c))/(1+m*m)<=0.01*0.01)
                        return 1;
    return 0;
}

bool detect_collision_balloon(bounding_box_t a,float minx,float maxx,float miny,float maxy,float angle,float x1,float y1,int stage)
{
    if(stage==0)
    {
        for(float i=a.x-a.width;i<=a.x+a.width;i+=0.01)
            for(float j=a.y-a.height;j<=a.y+a.height;j+=0.01)
                if((minx<= i && i<=maxx) && (miny<= j && j<=maxy))
                    if((i-x1)*(i-x1)<=0.02*0.02)
                        return 1;
        return 0;
    }
    else
    {
        float m=tan(angle);
        float c=y1-m*x1;
        for(float i=a.x-a.width;i<=a.x+a.width;i+=0.01)
            for(float j=a.y-a.height;j<=a.y+a.height;j+=0.01)
                if((minx<= i && i<=maxx) && (miny<= j && j<=maxy))
                    if(((m*i-j+c)*(m*i-j+c))/(1+m*m)<=0.02*0.02)
                        return 1;
        return 0;
    }
}

bool detect_collision_boomerang(bounding_box_t a,float x,float y)
{
    float coor[]={
        0.2f+x,0.2f+y,0.0f,
        0.0f+x,0.0f+y,0.0f,
        0.0f+x,-0.2f+y,0.0f,
        0.0f+x,0.0f+y,0.0f,
        0.0f+x,-0.2f+y,0.0f,
        -0.2f+x,0.2f+y,0.0f
    };
    pair<float,float> a1,a2,a3,b1,b2,b3;
    a1.f=coor[0],a1.s=coor[1];
    a2.f=coor[3],a2.s=coor[4];
    a3.f=coor[6],a3.s=coor[7];
    b1.f=coor[9],b1.s=coor[10];
    b2.f=coor[12],b2.s=coor[13];
    b3.f=coor[15],b3.s=coor[16];
    for(float i=a.x-(a.width/2);i<=a.x+(a.width/2);i+=0.1)
            for(float j=a.y-(a.height/2);j<=a.y+(a.height/2);j+=0.1)
                if((area(a1,a2,a3)==area(a1,a2,mp(i,j))+area(a1,a3,mp(i,j))+area(a3,a2,mp(i,j))) or (area(b1,b2,b3)==area(b1,b2,mp(i,j))+area(b1,b3,mp(i,j))+area(b3,b2,mp(i,j))) )
                       return 1;
    return 0;
}

bool detect_collision_ring(bounding_box_t a,float x,float y,float r)
{
    if((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)>=(r-0.01)*(r-0.01) and (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)<=r*r and a.y>=y)
        return 1;
    for(float i=a.x-(a.width/2);i<=a.x+(a.width/2);i+=0.1)
        for(float j=a.y-(a.height/2);j<=a.y+(a.height/2);j+=0.1)
            if((x-i)*(x-i)+(y-j)*(y-j)>=(r-0.01)*(r-0.01) and (x-i)*(x-i)+(y-j)*(y-j)<=r*r and j>=y)
            {
                pos.f=i,pos.s=j;
                return 1;
            } 
   return 0;
}

bool detect_collision_power_tri(bounding_box_t a,float x,float y)
{
    float coor[]={
        0.0f+x,0.1f+y,0.0f,
        0.0f+x,-0.1f+y,0.0f,
        -0.1f+x,0.0f+y,0.0f,

        0.2f+x,0.1f+y,0.0f,
        0.2f+x,-0.1f+y,0.0f,
        0.3f+x,0.0f+y,0.0f
    };
    pair<float,float> a1,a2,a3,b1,b2,b3;
    a1.f=coor[0],a1.s=coor[1];
    a2.f=coor[3],a2.s=coor[4];
    a3.f=coor[6],a3.s=coor[7];
    b1.f=coor[9],b1.s=coor[10];
    b2.f=coor[12],b2.s=coor[13];
    b3.f=coor[15],b3.s=coor[16];
    for(float i=a.x-(a.width/2);i<=a.x+(a.width/2);i+=0.1)
            for(float j=a.y-(a.height/2);j<=a.y+(a.height/2);j+=0.1)
                if((area(a1,a2,a3)==area(a1,a2,mp(i,j))+area(a1,a3,mp(i,j))+area(a3,a2,mp(i,j))) or (area(b1,b2,b3)==area(b1,b2,mp(i,j))+area(b1,b3,mp(i,j))+area(b3,b2,mp(i,j))) )
                       return 1;
    return 0;
}

void reset_screen(float value) {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left*value, right*value, bottom, top, 0.1f, 500.0f);
}
