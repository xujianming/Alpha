#pragma once

//
// A 3x3 matrix
//
template <class V3>
struct TMatrix3
{
	V3 C[3];	//row vectors

	//default
	TMatrix3()
	{
		//identity
		C[0][0] = 1;
		C[1][1] = 1;
		C[2][2] = 1;
	}

	//initialize
	TMatrix3( const V3& c0, const V3& c1, const V3& c2 )
	{
		C[0] = c0;
		C[1] = c1;
		C[2] = c2;
	}

	//M[col][row]
	//indexing, read
	const V3& operator [] ( long i ) const
	{
		return C[i];
	}
	//indexing, write
	V3& operator [] ( long i )
	{
		return C[i];
	}

	//compare
	const bool operator == ( const TMatrix3& m ) const
	{
		return C[0]==m.C[0] && C[1]==m.C[1] && C[2]==m.C[2];
	}

	const bool operator != ( const TMatrix3& m ) const
	{
		return !(m == *this);
	}

	//assign
	const TMatrix3& operator = ( const TMatrix3& m )
	{
		C[0] = m.C[0];
		C[1] = m.C[1];
		C[2] = m.C[2];

		return *this;
	}

	//increment
	const TMatrix3& operator += ( const TMatrix3& m )
	{
		C[0] += m.C[0];
		C[1] += m.C[1];
		C[2] += m.C[2];

		return *this;
	}

	//decrement
	const TMatrix3& operator -= ( const TMatrix3& m ) 
	{
		C[0] -= m.C[0];
		C[1] -= m.C[1];
		C[2] -= m.C[2];

		return *this;
	}

	//self-multiply by a scalar
	const TMatrix3& operator *= ( float s )
	{
		C[0] *= s;
		C[1] *= s;
		C[2] *= s;

		return *this;
	}

	//self-multiply by a matrix
	const TMatrix3& operator *= ( const TMatrix3& m )
	{
		//NOTE:  don't change the columns
		//in the middle of the operation
		TMatrix3 temp = (*this);

		C[0] = temp * m.C[0];
		C[1] = temp * m.C[1];
		C[2] = temp * m.C[2];

		return *this;
	}

	//self-divide by a scalar
	const TMatrix3& operator /= ( float s )
	{
		C[0] /= s;
		C[1] /= s;
		C[2] /= s;

		return *this;
	}

	//add
	const TMatrix3 operator + ( const TMatrix3& m ) const
	{
		return TMatrix3( C[0] + m.C[0], C[1] + m.C[1], C[2] + m.C[2] );
	}

	//subtract
	const TMatrix3 operator - ( const TMatrix3& m ) const
	{
		return TMatrix3( C[0] - m.C[0], C[1] - m.C[1], C[2] - m.C[2] );
	}

	//divide by a scalar
	const TMatrix3 operator / ( float s ) const
	{
		return TMatrix3( C[0]/s, C[1]/s, C[2]/s );
	}

	//post-multiply by a scalar
	const TMatrix3 operator * ( float s ) const
	{
		return TMatrix3( C[0]*s, C[1]*s, C[2]*s );
	}

	//pre-multiply by a scalar
	friend inline const TMatrix3 operator * ( float s, const TMatrix3& m )
	{
		return m * s;
	}

	//pre-multiply by a vector
	inline friend const V3 operator * ( const V3& v, const TMatrix3& m )
	{
		V3 ret;
		for (uint32 i = 0; i < 3; i ++)
			ret[i] = v[0] * m.C[i][0] + v[1] * m.C[i][1] + v[2] * m.C[i][2];
		return ret;
	}

	//post-multiply by a matrix
	const TMatrix3 operator * ( const TMatrix3& m ) const
	{
		return TMatrix4( C[0] * m, C[1] * m, C[2] * m );
	}

	//transpose
	TMatrix3 transpose() const
	{
		//turn columns on their side
		return TMatrix3(
						V3( C[0].x, C[1].x, C[2].x ),	//column 0
						V3( C[0].y, C[1].y, C[2].y ),	//column 1
						V3( C[0].z, C[1].z, C[2].z )	//column 2
						);
	}

	//determinant
	float determinant() const
	{
		return C[0].dot( C[1].cross(C[2]) );
	}

	//matrix inverse
	const TMatrix3 inverse() const;
};



//4x4 matrix for linear transformations
template <class V4>
class TMatrix4
{
public:

	V4 C[4];	//row vectors

public:

	TMatrix4()
	{
		//identity
		C[0] = V4(1,0,0,0);
		C[1] = V4(0,1,0,0);
		C[2] = V4(0,0,1,0);
		C[3] = V4(0,0,0,1);
	}

	TMatrix4(
				const V4& c0,
				const V4& c1,
				const V4& c2,
				const V4& c3
				)
	{
		C[0] = c0;
		C[1] = c1;
		C[2] = c2;
		C[3] = c3;
	}

	//M[col][row]

	//index a column,
	V4& operator [] ( long i )
	{
		return C[i];
	}

	//(read-only)
	const V4& operator [] ( long i ) const
	{
		return C[i];
	}

	//assign
	const TMatrix4& operator = ( const TMatrix4& m )
	{
		C[0] = m.C[0];
		C[1] = m.C[1];
		C[2] = m.C[2];
		C[3] = m.C[3];

		return *this;
	}

	//increment
	const TMatrix4& operator += ( const TMatrix4& m )
	{
		C[0] += m.C[0];
		C[1] += m.C[1];
		C[2] += m.C[2];
		C[3] += m.C[3];

		return *this;
	}

	//decrement
	const TMatrix4& operator -= ( const TMatrix4& m ) 
	{
		C[0] -= m.C[0];
		C[1] -= m.C[1];
		C[2] -= m.C[2];
		C[3] -= m.C[3];

		return *this;
	}

	//self-multiply by a scalar
	const TMatrix4& operator *= ( float s )
	{
		C[0] *= s;
		C[1] *= s;
		C[2] *= s;
		C[3] *= s;

		return *this;
	}

	//self-multiply by a matrix
	const TMatrix4& operator *= ( const TMatrix4& m )
	{
		//NOTE:  don't change the columns
		//in the middle of the operation
		TMatrix4 temp = (*this);

		C[0] = temp * m.C[0];
		C[1] = temp * m.C[1];
		C[2] = temp * m.C[2];
		C[4] = temp * m.C[4];

		return *this;
	}

	//self-divide by a scalar
	const TMatrix4& operator /= ( float s )
	{
		C[0] /= s;
		C[1] /= s;
		C[2] /= s;
		C[3] /= s;

		return *this;
	}

	//add
	const TMatrix4 operator + ( const TMatrix4& m ) const
	{
		return TMatrix4( C[0] + m.C[0], C[1] + m.C[1], C[2] + m.C[2], C[3] + m.C[3] );
	}

	//subtract
	const TMatrix4 operator - ( const TMatrix4& m ) const
	{
		return TMatrix4( C[0] - m.C[0], C[1] - m.C[1], C[2] - m.C[2], C[3] - m.C[3] );
	}

	//divide by a scalar
	const TMatrix4 operator / ( float s ) const
	{
		return TMatrix4( C[0]/s, C[1]/s, C[2]/s, C[3]/s );
	}

	//post-multiply by a scalar
	const TMatrix4 operator * ( float s ) const
	{
		return TMatrix4( C[0]*s, C[1]*s, C[2]*s, C[3]*s );
	}

	//pre-multiply by a scalar
	friend inline const TMatrix4 operator * ( float s, const TMatrix4& m )
	{
		return m * s;
	}

	//pre-multiply by a vector
	inline friend const V4 operator * ( const V4& v, const TMatrix4& m )
	{
		V4 ret;
		for (uint32 i = 0; i < 4; i ++)
			ret[i] = v[0] * m.C[0][i] + v[1] * m.C[1][i] + v[2] * m.C[2][i] + v[3] * m.C[3][i];
		return ret;
	}

	//post-multiply by a matrix
	const TMatrix4 operator * ( const TMatrix4& m ) const
	{
		return TMatrix4( C[0] * m, C[1] * m, C[2] * m, C[3] * m );
	}

	TMatrix4 transpose() const
	{
		//turn columns on their side
		return TMatrix4(
			V4( C[0].x, C[1].x, C[2].x, C[3].x ),	//row 0
			V4( C[0].y, C[1].y, C[2].y, C[3].y ),	//row 1
			V4( C[0].z, C[1].z, C[2].z, C[3].z ),	//row 2
			V4( C[0].w, C[1].w, C[2].w, C[3].w )	//row 2
			);
	}
};



// Symmetric matrices can be optimized
template< class V3, class TMatrix3 >
class T_SYMMETRIC_MATRIX3
{
	public:

		float xx, yy, zz;	//diagonal elements
		float xy, xz, yz;	//off-diagonal elements

	public:

		T_SYMMETRIC_MATRIX3()
		{
			//identity
			xx = yy = zz = 1;
			xy = xz = yz = 0;
		}

		T_SYMMETRIC_MATRIX3(
							float xx,
							float yy,
							float zz,
							float xy,
							float xz,
							float yz
							)
		{
			this->xx = xx;
			this->yy = yy;
			this->zz = zz;

			this->xy = xy;
			this->xz = xz;
			this->yz = yz;
		}

		//set equal to another matrix
		const T_SYMMETRIC_MATRIX3& operator = ( const T_SYMMETRIC_MATRIX3& m )
		{
			this->xx = m.xx;
			this->yy = m.yy;
			this->zz = m.zz;

			this->xy = m.xy;
			this->xz = m.xz;
			this->yz = m.yz;

			return *this;
		}

		//increment by another matrix
		const T_SYMMETRIC_MATRIX3& operator += ( const T_SYMMETRIC_MATRIX3& m )
		{
			this->xx += m.xx;
			this->yy += m.yy;
			this->zz += m.zz;

			this->xy += m.xy;
			this->xz += m.xz;
			this->yz += m.yz;

			return *this;
		}

		//decrement by another matrix
		const T_SYMMETRIC_MATRIX3& operator -=( const T_SYMMETRIC_MATRIX3& m ) 
		{
			this->xx -= m.xx;
			this->yy -= m.yy;
			this->zz -= m.zz;

			this->xy -= m.xy;
			this->xz -= m.xz;
			this->yz -= m.yz;

			return *this;
		}

		//add two matrices
		T_SYMMETRIC_MATRIX3 operator + ( const T_SYMMETRIC_MATRIX3& m ) const
		{
			return T_SYMMETRIC_MATRIX3(
										xx + m.xx,
										yy + m.yy,
										zz + m.zz,

										xy + m.xy,
										xz + m.xz,
										yz + m.yz
										);
		}

		//subtract two matrices
		T_SYMMETRIC_MATRIX3 operator - ( const T_SYMMETRIC_MATRIX3& m ) const
		{
			return T_SYMMETRIC_MATRIX3(
										xx - m.xx,
										yy - m.yy,
										zz - m.zz,

										xy - m.xy,
										xz - m.xz,
										yz - m.yz
										);
		}


		//post-multiply by a vector
		V3 operator * ( const V3& v ) const
		{
			return V3(	v.x*xx + v.y*xy + v.z*xz,
							v.x*xy + v.y*yy + v.z*yz,
							v.z*xz + v.y*yz + v.z*zz );
		}

		//pre-multiply by a vector
		friend inline V3 operator * ( const V3& v, const T_SYMMETRIC_MATRIX3& m )
		{
			return m * v;
		}

		//NOTE:  Can't do a self-multiply because the product of two symmetric matrices
		//is not necessarily a symmetric matrix

		//multiply two symmetric matrices
//		T_SYMMETRIC_MATRIX3 operator * ( const T_SYMMETRIC_MATRIX3& m ) const
//		{
//			return TMatrix3();
//		}

		// - matrix specific - //
		//a symmetric matrix is equal to its transpose

		//Is there a simplified formula for the inverse of a symmetric matrix?
};
