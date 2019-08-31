// Frame.h
// Implementation of the GLFrame Class
// Richard S. Wright Jr.
// Code by Richard S. Wright Jr.
/* Copyright (c) 2005-2009, Richard S. Wright Jr.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

Neither the name of Richard S. Wright Jr. nor the names of other contributors may be used 
to endorse or promote products derived from this software without specific prior 
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <math3d.h>

#ifndef _ORTHO_FRAME_
#define _ORTHO_FRAME_

// The GLFrame (OrthonormalFrame) class. Possibly the most useful little piece of 3D graphics
// code for OpenGL immersive environments.
// Richard S. Wright Jr.
/*
 GLFrame叫参考帧，其中存储了1个世界坐标点和2个世界坐标下的方向向量，也就是9个GLfloat值，分别用来表示：当前为支点，向前方向向量，向上方向向量
 GLFrame可以表示世界坐标系中任意物体的位置与方向。无论是相机还是模型，都可以使用GLFrame来表示。对任意一个使用GLFrame来表示的物体而言，
 涉及到的坐标系有两个：永远不变的世界坐标系，针对于自身的物体坐标系（即绘图坐标系）。
 一般来说，针对于物体自身的物体坐标系有如下特点：X轴永远平行于视口的水平方向，+X的方向根据右手定则由+Y与+Z得出；Y轴永远平行于视口的竖直方向，
 竖直向上为+Y；Z轴永远平行于视口的垂直纸面向里方向，正前方为+Z。也就是说，在世界坐标系中，物体坐标系的Y轴看上去就是GLFrame的向上方向向量，
 Z轴看上去就是GLFrame的向前方向向量，而X轴由Y轴方向向量与Z轴方向向量根据右手定则可得出。
 实际上，GLFrame就是一系列的变换。由GLFrame可以得出变换矩阵，只要与该变换矩阵相乘，任何物体都可以进行GLFrame所指定的变换。GLFrame会将
 物体坐标系(也就是当前绘图坐标系)做指定变换，在变换完成后我们就可以进行指定的绘制操作。比如有两个物体A与B，根据A的GLFrame导出变换矩阵Ma，
 然后令变换矩阵与B相乘。本来B的位置与方向都是相对于世界坐标系原点，经过变换后，B的位置与方向改变为相对于A的物体坐标系原点。
 */
class GLFrame
    {
	protected:
        M3DVector3f vOrigin;	// Where am I?
        M3DVector3f vForward;	// Where am I going?
        M3DVector3f vUp;		// Which way is up?

    public:
		// 默认构造函数（世界坐标系，位置在（0，0，0）点，up为（0，1，0）朝向+Y，forward为（0，0，-1）朝向-Z)
		GLFrame(void) {
			// At origin
            vOrigin[0] = 0.0f; vOrigin[1] = 0.0f; vOrigin[2] = 0.0f; 

			// Up is up (+Y)
            vUp[0] = 0.0f; vUp[1] = 1.0f; vUp[2] = 0.0f;

			// Forward is -Z (default OpenGL)
            vForward[0] = 0.0f; vForward[1] = 0.0f; vForward[2] = -1.0f;
            }


        /////////////////////////////////////////////////////////////
        // 设置/获取 世界坐标系下 模型/相机 的位置。
        inline void SetOrigin(const M3DVector3f vPoint) {
			m3dCopyVector3(vOrigin, vPoint); }
        
        inline void SetOrigin(float x, float y, float z) { 
			vOrigin[0] = x; vOrigin[1] = y; vOrigin[2] = z; }

		inline void GetOrigin(M3DVector3f vPoint) {
			m3dCopyVector3(vPoint, vOrigin); }

        // 获取世界坐标系下 模型/相机 位置的X/Y/Z分量
		inline float GetOriginX(void) { return vOrigin[0]; }
		inline float GetOriginY(void) { return vOrigin[1]; } 
		inline float GetOriginZ(void) { return vOrigin[2]; }

        /////////////////////////////////////////////////////////////
        // 设置/获取 世界坐标系下 模型/相机 向前的方向向量
        inline void SetForwardVector(const M3DVector3f vDirection) {
			m3dCopyVector3(vForward, vDirection); }

        inline void SetForwardVector(float x, float y, float z)
            { vForward[0] = x; vForward[1] = y; vForward[2] = z; }

        inline void GetForwardVector(M3DVector3f vVector) { m3dCopyVector3(vVector, vForward); }

        /////////////////////////////////////////////////////////////
        // 设置/获取 世界坐标系下 模型/相机 向上的方向向量
        inline void SetUpVector(const M3DVector3f vDirection) {
			m3dCopyVector3(vUp, vDirection); }

        inline void SetUpVector(float x, float y, float z)
			{ vUp[0] = x; vUp[1] = y; vUp[2] = z; }

        inline void GetUpVector(M3DVector3f vVector) { m3dCopyVector3(vVector, vUp); }


		/////////////////////////////////////////////////////////////
		// 获取世界坐标系下模型/相机X/Y/Z轴方向向量
		inline void GetZAxis(M3DVector3f vVector) { GetForwardVector(vVector); }
		inline void GetYAxis(M3DVector3f vVector) { GetUpVector(vVector); }
		inline void GetXAxis(M3DVector3f vVector) { m3dCrossProduct3(vVector, vUp, vForward); }


		/////////////////////////////////////////////////////////////
        // 以世界坐标系下（x,y,z）偏移量移动 模型/相机
        inline void TranslateWorld(float x, float y, float z)
			{ vOrigin[0] += x; vOrigin[1] += y; vOrigin[2] += z; }

        // 以物体坐标系下(x,y,z)偏移量移动模型/相机
        inline void TranslateLocal(float x, float y, float z)
			{ MoveForward(z); MoveUp(y); MoveRight(x);	}


		/////////////////////////////////////////////////////////////
		// 沿物体坐标系下Z轴以指定偏移fDelta量移动模型/相机
		inline void MoveForward(float fDelta)
			{
		    // Move along direction of front direction
			vOrigin[0] += vForward[0] * fDelta;
			vOrigin[1] += vForward[1] * fDelta;
			vOrigin[2] += vForward[2] * fDelta;
			}

		// 沿物体坐标系下Y轴以指定偏移fDelta移动物体/相机
		inline void MoveUp(float fDelta)
			{
		    // Move along direction of up direction
			vOrigin[0] += vUp[0] * fDelta;
			vOrigin[1] += vUp[1] * fDelta;
			vOrigin[2] += vUp[2] * fDelta;
			}

		// 沿物体坐标系下X轴以指定偏移fDelta移动物体/相机
		inline void MoveRight(float fDelta)
			{
			// Move along direction of right vector
			M3DVector3f vCross;
			m3dCrossProduct3(vCross, vUp, vForward);

			vOrigin[0] += vCross[0] * fDelta;
			vOrigin[1] += vCross[1] * fDelta;
			vOrigin[2] += vCross[2] * fDelta;
			}


		///////////////////////////////////////////////////////////////////////
		// 获取一个用于描述模型属性的4×4的矩阵
        void GetMatrix(M3DMatrix44f matrix, bool bRotationOnly = false)
			{
			// 计算向右的向量（x),并将它放在矩阵中的右边
			M3DVector3f vXAxis;
			m3dCrossProduct3(vXAxis, vUp, vForward);

			// 设置矩阵列，并没有填充第四个值
            m3dSetMatrixColumn44(matrix, vXAxis, 0);
            matrix[3] = 0.0f;
           
            // Y Column
			m3dSetMatrixColumn44(matrix, vUp, 1);
            matrix[7] = 0.0f;       
                                    
            // Z Column
			m3dSetMatrixColumn44(matrix, vForward, 2);
            matrix[11] = 0.0f;

            // Translation (already done)
			if(bRotationOnly == true)
				{
				matrix[12] = 0.0f;
				matrix[13] = 0.0f;
				matrix[14] = 0.0f;
				}
			else
				m3dSetMatrixColumn44(matrix, vOrigin, 3);

            matrix[15] = 1.0f;
			}



       ////////////////////////////////////////////////////////////////////////
        void GetCameraMatrix(M3DMatrix44f m, bool bRotationOnly = false)
            {
            M3DVector3f x, z;
			
			// Make rotation matrix
			// Z vector is reversed
			z[0] = -vForward[0];
			z[1] = -vForward[1];
			z[2] = -vForward[2];

			// X vector = Y cross Z 
			m3dCrossProduct3(x, vUp, z);

			// Matrix has no translation information and is
			// transposed.... (rows instead of columns)
			#define M(row,col)  m[col*4+row]
			   M(0, 0) = x[0];
			   M(0, 1) = x[1];
			   M(0, 2) = x[2];
			   M(0, 3) = 0.0;
			   M(1, 0) = vUp[0];
			   M(1, 1) = vUp[1];
			   M(1, 2) = vUp[2];
			   M(1, 3) = 0.0;
			   M(2, 0) = z[0];
			   M(2, 1) = z[1];
			   M(2, 2) = z[2];
			   M(2, 3) = 0.0;
			   M(3, 0) = 0.0;
			   M(3, 1) = 0.0;
			   M(3, 2) = 0.0;
			   M(3, 3) = 1.0;
			#undef M

			
            if(bRotationOnly)
                return;
                
            // Apply translation too
            M3DMatrix44f trans, M;
            m3dTranslationMatrix44(trans, -vOrigin[0], -vOrigin[1], -vOrigin[2]);  
			
            m3dMatrixMultiply44(M, m, trans);
        
            // Copy result back into m
            memcpy(m, M, sizeof(float)*16);
            }

        /////////////////////////////////////////////////////////////
        // 获取一个用于描述相机属性的4×4的矩阵
        inline void GetCameraOrientation(M3DMatrix44f m)
        {
            M3DVector3f x, z;
            
            // Make rotation matrix
            // Z vector is reversed
            z[0] = -vForward[0];
            z[1] = -vForward[1];
            z[2] = -vForward[2];
            
            // X vector = Y cross Z
            m3dCrossProduct3(x, vUp, z);
            
            // Matrix has no translation information and is
            // transposed.... (rows instead of columns)
        #define M(row,col)  m[col*4+row]
            M(0, 0) = x[0];
            M(0, 1) = x[1];
            M(0, 2) = x[2];
            M(0, 3) = 0.0;
            M(1, 0) = vUp[0];
            M(1, 1) = vUp[1];
            M(1, 2) = vUp[2];
            M(1, 3) = 0.0;
            M(2, 0) = z[0];
            M(2, 1) = z[1];
            M(2, 2) = z[2];
            M(2, 3) = 0.0;
            M(3, 0) = 0.0;
            M(3, 1) = 0.0;
            M(3, 2) = 0.0;
            M(3, 3) = 1.0;
        #undef M
        }
        
        
        /////////////////////////////////////////////////////////////
        // Perform viewing or modeling transformations
        // Position as the camera (for viewing). Apply this transformation
        // first as your viewing transformation
        // The default implementation of gluLookAt can be considerably sped up
        // since it uses doubles for everything... then again profile before you
        // tune... ;-) You might get a boost form page fault reduction too... if
        // no other glu routines are used...
        // This will get called once per frame.... go ahead and inline
        // 应用所有的相机变换。该函数仅用于相机
        inline void ApplyCameraTransform(bool bRotOnly = false)
        {
            M3DMatrix44f m;
            
            GetCameraOrientation(m);
            
            // Camera Transform
            glMultMatrixf(m);
            
            // If Rotation only, then do not do the translation
            if(!bRotOnly)
                glTranslatef(-vOrigin[0], -vOrigin[1], -vOrigin[2]);
            
            /*gluLookAt(vOrigin[0], vOrigin[1], vOrigin[2],
             vOrigin[0] + vForward[0],
             vOrigin[1] + vForward[1],
             vOrigin[2] + vForward[2],
             vUp[0], vUp[1], vUp[2]);
             */
        }
        
        
        // Position as an object in the scene. This places and orients a
        // coordinate frame for other objects (besides the camera)
        // There is ample room for optimization here...
        // This is going to be called alot... don't inline
        // Add flag to perform actor rotation only and not the translation
        // 应用所有的物体变换。该函数仅用于除相机外的物体
        void ApplyActorTransform(bool bRotationOnly = false)
        {
            M3DMatrix44f rotMat;
            
            GetMatrix(rotMat, bRotationOnly);
            
            // Apply rotation to the current matrix
            glMultMatrixf(rotMat);
        }

		//  令物体/相机以自身位置为中心，绕Y轴旋转。其角度以PI为单位
        void RotateLocalY(float fAngle)
			{
	        M3DMatrix44f rotMat;

			// Just Rotate around the up vector
			// Create a rotation matrix around my Up (Y) vector
			m3dRotationMatrix44(rotMat, fAngle,
                         vUp[0], vUp[1], vUp[2]);

			M3DVector3f newVect;

	        // Rotate forward pointing vector (inlined 3x3 transform)
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	
			m3dCopyVector3(vForward, newVect);
			}

        
        //  令物体/相机以自身位置为中心，绕Z轴旋转。其角度以PI为单位
        void RotateLocalZ(float fAngle)
			{
			M3DMatrix44f rotMat;

			// Only the up vector needs to be rotated
			m3dRotationMatrix44(rotMat, fAngle,
							vForward[0], vForward[1], vForward[2]);

			M3DVector3f newVect;
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	
			m3dCopyVector3(vUp, newVect);
			}
        
        //  令物体/相机以自身位置为中心，绕轴旋转。其角度以PI为单位
		void RotateLocalX(float fAngle)
			{
			M3DMatrix33f rotMat;
			M3DVector3f  localX;
			M3DVector3f  rotVec;

			// Get the local X axis
			m3dCrossProduct3(localX, vUp, vForward);

			// Make a Rotation Matrix
			m3dRotationMatrix33(rotMat, fAngle, localX[0], localX[1], localX[2]);

			// Rotate Y, and Z
			m3dRotateVector(rotVec, vUp, rotMat);
			m3dCopyVector3(vUp, rotVec);

			m3dRotateVector(rotVec, vForward, rotMat);
			m3dCopyVector3(vForward, rotVec);
			}


		// Reset axes to make sure they are orthonormal. This should be called on occasion
		// if the matrix is long-lived and frequently transformed.
		void Normalize(void)
			{
			M3DVector3f vCross;

			// Calculate cross product of up and forward vectors
			m3dCrossProduct3(vCross, vUp, vForward);

			// Use result to recalculate forward vector
			m3dCrossProduct3(vForward, vCross, vUp);	

			// Also check for unit length...
			m3dNormalizeVector3(vUp);
			m3dNormalizeVector3(vForward);
			}


		// 模型/相机绕世界坐标系下的指定轴(x,y,z)旋转fAngle度
		void RotateWorld(float fAngle, float x, float y, float z)
			{
            M3DMatrix44f rotMat;

			// Create the Rotation matrix
			m3dRotationMatrix44(rotMat, fAngle, x, y, z);

			M3DVector3f newVect;
			
			// Transform the up axis (inlined 3x3 rotation)
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	
			m3dCopyVector3(vUp, newVect);

			// Transform the forward axis
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	
			m3dCopyVector3(vForward, newVect);
            }


        // 模型/相机绕当前物体坐标系下的指定轴(x,y,z)旋转fAngle度
        void RotateLocal(float fAngle, float x, float y, float z) 
            {
            M3DVector3f vWorldVect;
			M3DVector3f vLocalVect;
			m3dLoadVector3(vLocalVect, x, y, z);

            LocalToWorld(vLocalVect, vWorldVect, true);
            RotateWorld(fAngle, vWorldVect[0], vWorldVect[1], vWorldVect[2]);
            }
    

		// Convert Coordinate Systems
        // This is pretty much, do the transformation represented by the rotation
        // and position on the point
		// Is it better to stick to the convention that the destination always comes
		// first, or use the conventions that "sounds" like the function...
        // 将点/向量vLocal从当前物体坐标系转换为世界坐标系
        void LocalToWorld(const M3DVector3f vLocal, M3DVector3f vWorld, bool bRotOnly = false)
            {
             // Create the rotation matrix based on the vectors
			M3DMatrix44f rotMat;

			GetMatrix(rotMat, true);

			// Do the rotation (inline it, and remove 4th column...)
			vWorld[0] = rotMat[0] * vLocal[0] + rotMat[4] * vLocal[1] + rotMat[8] *  vLocal[2];	
			vWorld[1] = rotMat[1] * vLocal[0] + rotMat[5] * vLocal[1] + rotMat[9] *  vLocal[2];	
			vWorld[2] = rotMat[2] * vLocal[0] + rotMat[6] * vLocal[1] + rotMat[10] * vLocal[2];	

            // Translate the point
            if(!bRotOnly) {
                vWorld[0] += vOrigin[0];
                vWorld[1] += vOrigin[1];
                vWorld[2] += vOrigin[2];
                }
            }

		// Change world coordinates into "local" coordinates
        // 将点/向量vLocal从世界坐标系转换为当前物体坐标系
        void WorldToLocal(const M3DVector3f vWorld, M3DVector3f vLocal)
            {
			////////////////////////////////////////////////
            // Translate the origin
			M3DVector3f vNewWorld;
            vNewWorld[0] = vWorld[0] - vOrigin[0];
            vNewWorld[1] = vWorld[1] - vOrigin[1];
            vNewWorld[2] = vWorld[2] - vOrigin[2];

            // Create the rotation matrix based on the vectors
			M3DMatrix44f rotMat;
            M3DMatrix44f invMat;
			GetMatrix(rotMat, true);

			// Do the rotation based on inverted matrix
            m3dInvertMatrix44(invMat, rotMat);

			vLocal[0] = invMat[0] * vNewWorld[0] + invMat[4] * vNewWorld[1] + invMat[8] *  vNewWorld[2];	
			vLocal[1] = invMat[1] * vNewWorld[0] + invMat[5] * vNewWorld[1] + invMat[9] *  vNewWorld[2];	
			vLocal[2] = invMat[2] * vNewWorld[0] + invMat[6] * vNewWorld[1] + invMat[10] * vNewWorld[2];	
            }
        
        /////////////////////////////////////////////////////////////////////////////
        // Transform a point by frame matrix
        // 通过当前frame矩阵将vPointSrc点变换为vPointDst点
        void TransformPoint(M3DVector3f vPointSrc, M3DVector3f vPointDst)
            {
            M3DMatrix44f m;
            GetMatrix(m, false);    // Rotate and translate
            vPointDst[0] = m[0] * vPointSrc[0] + m[4] * vPointSrc[1] + m[8] *  vPointSrc[2] + m[12];// * v[3];	 
            vPointDst[1] = m[1] * vPointSrc[0] + m[5] * vPointSrc[1] + m[9] *  vPointSrc[2] + m[13];// * v[3];	
            vPointDst[2] = m[2] * vPointSrc[0] + m[6] * vPointSrc[1] + m[10] * vPointSrc[2] + m[14];// * v[3];	
            }
        
        ////////////////////////////////////////////////////////////////////////////
        // Rotate a vector by frame matrix
        //通过当前frame矩阵将vVectorSrc向量旋转为vVectorDst向量
        void RotateVector(M3DVector3f vVectorSrc, M3DVector3f vVectorDst)
            {
            M3DMatrix44f m;
            GetMatrix(m, true);    // Rotate only
            
            vVectorDst[0] = m[0] * vVectorSrc[0] + m[4] * vVectorSrc[1] + m[8] *  vVectorSrc[2];	 
            vVectorDst[1] = m[1] * vVectorSrc[0] + m[5] * vVectorSrc[1] + m[9] *  vVectorSrc[2];	
            vVectorDst[2] = m[2] * vVectorSrc[0] + m[6] * vVectorSrc[1] + m[10] * vVectorSrc[2];	
            }
        };


#endif
