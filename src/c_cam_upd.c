#include <raylib.h>
#include <math.h>
#include <raymath.h>

void CustomCameraUpdate(Camera3D *cam) {
	float speed = 0.1f;
	float sens = 0.006f;
	
	static float bobTimer = 0.0f;
	float bobSpeed = 9.0f;
	float bobAmount = 0.06f;

	static float pitch = 0.0;
	static float yaw = 0.0;
	Vector2 delta = GetMouseDelta();
	Vector3 CameraDelta;
	yaw -= delta.x * sens;
	pitch -= delta.y * sens;
	if (pitch < -1.5f) {
		pitch = -1.5;
	}
	else if (pitch > 1.5f) {
		pitch = 1.5f;
	}
	CameraDelta.x = sinf(yaw) * cosf(pitch);
	CameraDelta.y = sinf(pitch);
	CameraDelta.z = cosf(yaw) * cosf(pitch);


	//updating camera view
	cam->target.x = cam->position.x + CameraDelta.x;
	cam->target.y = cam->position.y + CameraDelta.y;
	cam->target.z = cam->position.z + CameraDelta.z;


	if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D) ) {
		bobTimer += GetFrameTime() * bobSpeed;
		float offset = sinf(bobTimer) * bobAmount;
		cam->position.y = 2.0f + offset;
	}
	else {
		if (cam->position.y < 2.0f || cam->position.y > 2.0f) {
    		bobTimer += GetFrameTime() * bobSpeed;if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D) ) {
    			bobTimer += GetFrameTime() * bobSpeed;
    			float offset = sinf(bobTimer) * bobAmount;
    			cam->position.y = 2.0f + offset;
    		}
    		else {
				cam->position.y = Lerp(cam->position.y, 2.0f, 0.1f);
    		}
		}
		else {
			bobTimer = 0;
		}
	}

	
	Vector3 walkForward = {
	    .x = sinf(yaw), 
	    .y = 0.0f, 
	    .z = cosf(yaw)
	};
	Vector3 walkRight = {
	    .x = sinf(yaw - 1.57f),
	    .y = 0.0f,
	    .z = cosf(yaw - 1.57f)
	};

	if ( IsKeyDown(KEY_LEFT_SHIFT) ) {
		speed = 0.3f;
		bobSpeed = 12;
	}
	else {
		speed = Lerp(speed,	0.1f,0.05f);
		bobSpeed = Lerp(bobSpeed, 9, 0.5f);
	}

	if (IsKeyDown(KEY_W)) {
	    cam->position.x += walkForward.x * speed;
	    cam->position.z += walkForward.z * speed;
	}
	if (IsKeyDown(KEY_S)) {
	    cam->position.x -= walkForward.x * speed;
	    cam->position.z -= walkForward.z * speed;
	}
	if (IsKeyDown(KEY_D)) {
	    cam->position.x += walkRight.x * speed;
	    cam->position.z += walkRight.z * speed;
	}
	if (IsKeyDown(KEY_A)) {
	    cam->position.x -= walkRight.x * speed;
	    cam->position.z -= walkRight.z * speed;
	}
}
