#include <stdint.h>
#include <cmath>
#include "../include/gl3d.h"

namespace CenoGL{

	gl3D::gl3D(PixelMatrix* pixels_buf){
		this->mGraphicsBaseHAL = new GraphicsBaseHAL();
		this->pixel_matrix_buffer = pixels_buf;
	}

	Vec3D gl3D::glVertex3f(float x,float y,float z){
		Vec3D vec;
		vec.x =  x;
		vec.y =  y;
		vec.z =  z;
		return vec;
	}

	uint32_t gl3D::glColor3i(uint32_t r,uint32_t g,uint32_t b){
		if(r >= 0xFF){
			r = 0xFF;
		}
		if(g >= 0xFF){
			g = 0xFF;
		}
		if(b >= 0xFF){
			b = 0xFF;
		}
		return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
	}

	Vec3D gl3D::glColor3f(float r,float g,float b){
		Vec3D vec;
		vec.x =  fmod(r,1.0f);
		vec.y =  fmod(g,1.0f);
		vec.z =  fmod(b,1.0f);
		return vec;
	}

	Vec3D gl3D::glColor1iTov(uint32_t color){
		Vec3D col;
		col.x = ((float)((color >> 24) & 0xFF) / 255.0f);
		col.y = ((float)((color >> 16) & 0xFF) / 255.0f);
		col.z = ((float)((color >> 8) & 0xFF) / 255.0f);
		return col;
	}

	uint32_t gl3D::glColorvTo1i(Vec3D color){
		return this->glColor3i((uint32_t)(color.x * 255.0f),(uint32_t)(color.y * 255.0f),(uint32_t)(color.z * 255.0f));
	}


	Mat4x4 gl3D::glMatrixMakeIdentity(){
		Mat4x4 mat;
		mat.m[0][0] = 1.0f;
		mat.m[1][1] = 1.0f;
		mat.m[2][2] = 1.0f;
		mat.m[3][3] = 1.0f;
		return mat;
	}

	Mat4x4 gl3D::glMatrixMakeRotationX(float angle){
		Mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = cosf(angle);
		matrix.m[1][2] = sinf(angle);
		matrix.m[2][1] = -sinf(angle);
		matrix.m[2][2] = cosf(angle);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 gl3D::glMatrixMakeRotationY(float angle){
		Mat4x4 matrix;
		matrix.m[0][0] = cosf(angle);
		matrix.m[0][2] = sinf(angle);
		matrix.m[2][0] = -sinf(angle);
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = cosf(angle);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 gl3D::glMatrixMakeRotationZ(float angle){
		Mat4x4 matrix;
		matrix.m[0][0] = cosf(angle);
		matrix.m[0][1] = sinf(angle);
		matrix.m[1][0] = -sinf(angle);
		matrix.m[1][1] = cosf(angle);
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 gl3D::glMatrixMakeTranslation(float x, float y, float z){
		Mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		matrix.m[3][0] = x;
		matrix.m[3][1] = y;
		matrix.m[3][2] = z;
		return matrix;
	}

	Mat4x4 gl3D::glMatrixMakeProjection(float fovDegree, float aspectRatio, float near, float far){
		float fFovRad = 1.0f / tanf(fovDegree * 0.5f / 180.0f * 3.14159f);
		Mat4x4 matrix;
		matrix.m[0][0] = aspectRatio * fFovRad;
		matrix.m[1][1] = fFovRad;
		matrix.m[2][2] = far / (far - near);
		matrix.m[3][2] = (-far * near) / (far - near);
		matrix.m[2][3] = 1.0f;
		matrix.m[3][3] = 0.0f;
		return matrix;
	}

	Mat4x4 gl3D::glMatrixPointAt(Vec3D &pos,Vec3D &target,Vec3D &up){
		// caculate new forward direction
		Vec3D newForward = glmVectorSub(target,pos);
		newForward = glmVectorNormalise(newForward);

		// caculate new up direction
		Vec3D a = glmVectorMul(newForward,glmVectorDotProduct(up,newForward));
		Vec3D newUp = glmVectorSub(up,a);
		newUp = glmVectorNormalise(newUp);

		// New Right direction is easy, its just cross product
		Vec3D newRight = glmVectorCrossProduct(newUp, newForward);

		// Construct Dimensioning and Translation Matrix	
		Mat4x4 matrix;
		matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	 matrix.m[0][2] = newRight.z;	 matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = newUp.x;		 matrix.m[1][1] = newUp.y;		   matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos.x;			  matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			  matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Vec3D gl3D::glVectorIntersectPlane(Vec3D &plane_p, Vec3D &plane_n, Vec3D &lineStart, Vec3D &lineEnd)
	{
		plane_n = glmVectorNormalise(plane_n);
		float plane_d = -glmVectorDotProduct(plane_n, plane_p);
		float ad = glmVectorDotProduct(lineStart, plane_n);
		float bd = glmVectorDotProduct(lineEnd, plane_n);
		float t = (-plane_d - ad) / (bd - ad);
		Vec3D lineStartToEnd = glmVectorSub(lineEnd, lineStart);
		Vec3D lineToIntersect = glmVectorMul(lineStartToEnd, t);
		return glmVectorAdd(lineStart, lineToIntersect);
	}

	int gl3D::glTriangleClipAgainstPlane(Vec3D plane_p, Vec3D plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2)
	{
		// Make sure plane normal is indeed normal
		plane_n = glmVectorNormalise(plane_n);

		// Return signed shortest distance from point to plane, plane normal must be normalised
		auto dist = [&](Vec3D &p)
		{
			Vec3D n = glmVectorNormalise(p);
			return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - glmVectorDotProduct(plane_n, plane_p));
		};

		// Create two temporary storage arrays to classify points either side of plane
		// If distance sign is positive, point lies on "inside" of plane
		Vec3D* inside_points[3];  int nInsidePointCount = 0;
		Vec3D* outside_points[3]; int nOutsidePointCount = 0;

		// Get signed distance of each point in triangle to plane
		float d0 = dist(in_tri.p[0]);
		float d1 = dist(in_tri.p[1]);
		float d2 = dist(in_tri.p[2]);

		if (d0 >= 0) { 
			inside_points[nInsidePointCount++] = &in_tri.p[0]; 
		}else { 
			outside_points[nOutsidePointCount++] = &in_tri.p[0]; 
		}
		if (d1 >= 0) { 
			inside_points[nInsidePointCount++] = &in_tri.p[1]; 
		}else { 
			outside_points[nOutsidePointCount++] = &in_tri.p[1]; 
		}
		if (d2 >= 0) { 
			inside_points[nInsidePointCount++] = &in_tri.p[2]; 
		}else { 
			outside_points[nOutsidePointCount++] = &in_tri.p[2]; 
		}

		// Now classify triangle points, and break the input triangle into 
		// smaller output triangles if required. There are four possible
		// outcomes...

		if (nInsidePointCount == 0)
		{
			// All points lie on the outside of plane, so clip whole triangle
			// It ceases to exist

			return 0; // No returned triangles are valid
		}

		if (nInsidePointCount == 3)
		{
			// All points lie on the inside of plane, so do nothing
			// and allow the triangle to simply pass through
			out_tri1 = in_tri;

			return 1; // Just the one returned original triangle is valid
		}

		if (nInsidePointCount == 1 && nOutsidePointCount == 2)
		{
			// Triangle should be clipped. As two points lie outside
			// the plane, the triangle simply becomes a smaller triangle

			// Copy appearance info to new triangle
			out_tri1.color = in_tri.color;

			// The inside point is valid, so keep that...
			out_tri1.p[0] = *inside_points[0];

			// but the two new points are at the locations where the 
			// original sides of the triangle (lines) intersect with the plane
			out_tri1.p[1] = this->glVectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
			out_tri1.p[2] = this->glVectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

			return 1; // Return the newly formed single triangle
		}

		if (nInsidePointCount == 2 && nOutsidePointCount == 1)
		{
			// Triangle should be clipped. As two points lie inside the plane,
			// the clipped triangle becomes a "quad". Fortunately, we can
			// represent a quad with two new triangles

			// Copy appearance info to new triangles
			out_tri1.color = in_tri.color;

			out_tri2.color = in_tri.color;

			// The first triangle consists of the two inside points and a new
			// point determined by the location where one side of the triangle
			// intersects with the plane
			out_tri1.p[0] = *inside_points[0];
			out_tri1.p[1] = *inside_points[1];
			out_tri1.p[2] = this->glVectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

			// The second triangle is composed of one of he inside points, a
			// new point determined by the intersection of the other side of the 
			// triangle and the plane, and the newly created point above
			out_tri2.p[0] = *inside_points[1];
			out_tri2.p[1] = out_tri1.p[2];
			out_tri2.p[2] = this->glVectorIntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

			return 2; // Return two newly formed triangles which form a quad
		}
	}

	uint32_t gl3D::glGetLumColor(uint32_t color,float lum){
		// liner light, color_vec * (n.l)
		uint32_t r = (uint32_t)(((color >> 24) & 0xFF) * lum);
		uint32_t g = (uint32_t)(((color >> 16) & 0xFF) * lum);
		uint32_t b = (uint32_t)(((color >> 8) & 0xFF) * lum);
		uint32_t a = (uint32_t)(((color >> 0) & 0xFF) * lum);

		return (uint32_t)(r << 24 | g << 16 | b << 8 | a << 0);
	}


	Vec3D gl3D::glGetSpecularColor(Vec3D mspec,Vec3D sspec,float lum){
		Vec3D color = glmVectorMul(mspec,sspec);
		Vec3D result = glmVectorMul(color,fmax(0.0f,lum));
		return result;
	}

	// specular=Ks∗lightColor∗(max(dot(N,R)),0)^shininess
	// R=2∗(N·L)∗N−L
	Vec3D gl3D::glGetSpecularColor(Vec3D mspec,Vec3D sspec, Vec3D normal, Vec3D light,float shiness){
		float lum = glmVectorDotProduct(normal,light);
		Vec3D R1 = glmVectorMul(normal,2.0f*lum);
		Vec3D R = glmVectorSub(R1,light);
		lum = glmVectorDotProduct(normal,R);
		return this->glGetSpecularColor(mspec,sspec,powf(lum,shiness));
	}

	// diffuse=Kd∗lightColor∗max(dot(N,L),0)
	Vec3D gl3D::glGetDiffuseColor(Vec3D mdiff,Vec3D sdiff, Vec3D normal, Vec3D light){
		float cos = glmVectorDotProduct(normal,light);
		Vec3D color = glmVectorMul(mdiff,sdiff);
		Vec3D result = glmVectorMul(color,fmax(0.0f,cos));

		return result;
	}
	
	// ambient=Ka∗globalAmbient
	Vec3D gl3D::glGetAmbientColor(Vec3D mamb,Vec3D gamb){
		Vec3D color = glmVectorMul(mamb,gamb);
		return color;
	}


	float getAttenuationFactor(float d){
		return 1.0f / (GL_CONSTANT_ATTENUATION + GL_LINEAR_ATTENUATION * d + GL_QUADRATIC_ATTENUATION * d * d);
	}

	gl3D::~gl3D(){
	}



}; // CenoGL