#pragma once
#define RED glm::vec3(1, 0, 0)
#define PURPLE glm::vec3(1,0,1)
#define GREEN glm::vec3(0, 1, 0)
#define BLUE glm::vec3(0, 0, 1)
#define BLACK glm::vec3(0, 0, 0)
#define BACKGROUND glm::vec4(1.0f, 1.f, 1.0f, 1.00f)

#define PI 3.14159265358
#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))

#define V_NORMAL_SCALE 70
#define F_NORMAL_SCALE 50
#define INIT_SCALE 1000

// camera definitions
// view volume
#define LEFT -10
#define BOTTOM -10
#define RIGHT 10
#define TOP 10
#define NEAR 10
#define FAR 50
#define LEFT_MOVEMENT -100.0f
#define RIGHT_MOVEMENT 100.0f
#define TOP_MOVEMENT 100.0f
#define BOTTOM_MOVEMENT -100.0f
#define NEAR_MOVEMENT -50.0f
#define FAR_MOVEMENT 50.0f