#pragma once

#include <cmath>


//define a 2 component vector template
template<class T>
struct TVector2
{
	T x,y;	//x,y coordinates

	//default
	TVector2()
		:	x(0), y(0)
	{}

	//initialize
	TVector2( const T a, const T b )
		: x(a), y(b)
	{}

	//indexing (read-only)
	const T& operator [] ( const long i ) const
	{
		return *((&x) + i);
	}

	//indexing (write)
	T& operator [] ( const long i )
	{
		return *((&x) + i);
	}

	//assignment
	const TVector2& operator = ( const TVector2& b )
	{
		x = b.x;
		y = b.y;

		return *this;
	}

	//comparison
	const bool operator == ( const TVector2& b ) const
	{
		return( b.x==x && b.y==y );
	}

	const bool operator != ( const TVector2& b ) const
	{
		return !( b == *this );
	}

	const bool nearlyEquals( const TVector2& b, const T r ) const
	{
		//within a tolerance
		const TVector2 t = *this - b;//difference
		return t.dot(t) < r*r;//radius
	}

	//negation
	const TVector2 operator - () const
	{
		return TVector2( -x, -y );
	}

	//increment
	const TVector2& operator += ( const TVector2& b )
	{
		x += b.x;
		y += b.y;

		return *this;
	}

	//decrement
	const TVector2& operator -= ( const TVector2& b ) 
	{
		x -= b.x;
		y -= b.y;

		return *this;
	}

	//self-multiply
	const TVector2& operator *= ( const T s )
	{
		x *= s;
		y *= s;

		return *this;
	}

	//self-divide
	const TVector2& operator /= ( const T s )
	{
		x /= s;
		y /= s;

		return *this;
	}

	//add
	const TVector2 operator + ( const TVector2& b ) const
	{
		return TVector2( x + b.x, y + b.y );
	}

	//subtract
	const TVector2 operator - ( const TVector2& b ) const
	{
		return TVector2( x - b.x, y - b.y );
	}

	//post-multiply by a scalar
	const TVector2 operator * ( const T s ) const
	{
		return TVector2( x*s, y*s );
	}

	//pre-multiply by a scalar
	friend inline const TVector2 operator * ( const T s, const TVector2& v )
	{
		return v * s;
	}

	//divide
	const TVector2 operator / ( const T s ) const
	{
		return TVector2( x/s, y/s );
	}

	//NOTE:  The cross product is not defined for 2D vectors.

	//dot product
	const T dot( const TVector2& b ) const
	{
		return( x*b.x + y*b.y);
	}

	//length squared
	const T length_squared() const
	{
		return this->dot(*this);
	}

	//length
	const T length() const
	{
		//NOTE:  cast the return value of
		//sqrt() from a double to a T
		return (T)sqrt( this->length_squared() );
	}

	//unit vector
	const TVector2 unit() const
	{
		return (*this) / this->length();
	}

	//make this a unit vector
	const TVector2& normalize()
	{
		(*this) /= this->length();

		return *this;
	}
};



//
// A 3D vector template
//
template <class T>
struct TVector3
{
	T x,y,z;	//x,y,z coordinates

	//default
	TVector3()
		:	x(0), y(0), z(0)
	{}

	//initialize
	TVector3( const T a, const T b, const T c )
		:	x(a), y(b), z(c)
	{}

	//indexing (read-only)
	const T& operator [] ( const long i ) const
	{
		return *((&x) + i);
	}

	//indexing (write)
	T& operator [] ( const long i )
	{
		return *((&x) + i);
	}

	//compare
	const bool operator == ( const TVector3& b ) const
	{
		return (b.x==x && b.y==y && b.z==z);
	}

	const bool operator != ( const TVector3& b ) const
	{
		return !(b == *this);
	}

	const bool nearlyEquals( const TVector3& b, const T r ) const
	{
		//within a tolerance
		const TVector3 t = *this - b;//difference
		return t.dot(t) < r*r;//radius
	}

	//negate
	const TVector3 operator - () const
	{
		return TVector3( -x, -y, -z );
	}

	//assign
	const TVector3& operator = ( const TVector3& b )
	{
		x = b.x;
		y = b.y;
		z = b.z;

		return *this;
	}

	//increment
	const TVector3& operator += ( const TVector3& b ) 
	{
		x += b.x;
		y += b.y;
		z += b.z;

		return *this;
	} 

	//decrement
	const TVector3& operator -= ( const TVector3& b ) 
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;

		return *this;
	} 

	//self-multiply
	const TVector3& operator *= ( const T s )
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	//self-divide
	const TVector3& operator /= ( const T s )
	{
		x /= s;
		y /= s;
		z /= s;

		return *this;
	}

	//add
	const TVector3 operator + ( const TVector3& b ) const
	{
		return TVector3( x + b.x, y + b.y, z + b.z );
	}

	//subtract
	const TVector3 operator - ( const TVector3& b ) const
	{
		return TVector3( x - b.x, y - b.y, z - b.z );
	}

	//post-multiply by a scalar
	const TVector3 operator * ( const T s) const
	{
		return TVector3( x*s, y*s, z*s );
	}

	//pre-multiply by a scalar
	friend inline const TVector3 operator * ( const T s, const TVector3& v )
	{
		return v * s;
	}

	//divide
	const TVector3 operator / ( const T s ) const
	{
		return TVector3( x/s, y/s, z/s );
	}

	//cross product
	const TVector3 cross( const TVector3& b ) const
	{
		return TVector3( y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x );
	}

	//scalar dot product
	const T dot( const TVector3& b ) const
	{
		return x*b.x + y*b.y + z*b.z;
	}

	//length squared
	const T length_squared() const
	{
		return this->dot(*this);
	}

	//length
	const T length() const
	{
		//NOTE:  cast the return value of
		//sqrt() from a double to a T
		return (T)sqrt( this->length_squared() );
	}

	//unit vector
	const TVector3 unit() const
	{
		return (*this) / this->length();
	}

	//make this a unit vector
	const TVector3& normalize()
	{
		(*this) /= this->length();

		return *this;
	}
};






//define a 4 component template
template<class T>
struct TVector4
{
	T x,y,z,w;	//x,y,z,w coordinates

	//default
	TVector4()
		:	x(0), y(0), z(0), w(0)
	{}

	//initialize
	TVector4( const T a, const T b, const T c, const T d )
		:	x (a),
			y (b),
			z (c),
			w (d)
	{}

	//indexing, read
	const T& operator [] ( const long i ) const
	{
		return *((&x) + i);
	}

	//indexing, write
	T& operator [] ( const long i )
	{
		return *((&x) + i);
	}

	//comparison
	const bool operator == ( const TVector4& b ) const
	{
		return( b.x==x && b.y==y && b.z==z && b.w==w );
	}

	const bool operator != ( const TVector4& b ) const
	{
		return !( b == *this );
	}

	const bool nearlyEquals( const TVector4& b, const T r ) const
	{
		//within a tolerance
		const TVector4 t = *this - b;//difference
		return t.dot(t) < r*r;//radius
	}

	//negate
	TVector4 operator - ( void ) const
	{
		return TVector4( -x, -y, -z, -w );
	}

	//assign
	const TVector4& operator = ( const TVector4& b )
	{
		x = b.x;
		y = b.y;
		z = b.z;
		w = b.w;

		return *this;
	}

	//increment
	const TVector4& operator += ( const TVector4& b ) 
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;

		return *this;
	} 

	//decrement
	const TVector4& operator -= ( const TVector4& b ) 
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;

		return *this;
	} 

	//self-multiply
	const TVector4& operator *= ( const T s )
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	} 

	//self-divide
	const TVector4& operator /= ( const T s )
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;

		return *this;
	}

	//add vectors, return sum
	const TVector4 operator + ( const TVector4& b ) const
	{
		return TVector4( x+b.x, y+b.y, z+b.z, w+b.w );
	}

	//subtract vectors
	const TVector4 operator - ( const TVector4& b ) const
	{
		return TVector4( x-b.x, y-b.y, z-b.z, w-b.w );
	}

	//multiply
	const TVector4 operator * ( const T s ) const
	{
		return TVector4( x*s, y*s, z*s, w*s );
	}

	//pre - multiply
	friend inline const TVector4 operator * ( const T s, const TVector4& v )
	{
		return v * s;
	}

	//divide
	const TVector4 operator / ( const T s ) const
	{
		return TVector4( x/s, y/s, z/s, w/s );
	}

	//the cross product needs two other vectors

	//dot product
	const T dot( const TVector4& b ) const
	{
		return( x*b.x + y*b.y + z*b.z + w*b.w );
	}

	//length squared
	const T length_squared() const
	{
		return this->dot(*this);
	}

	//length
	const T length() const
	{
		//NOTE:  cast the return value of
		//sqrt() from a double to a T
		return (T)sqrt( this->length_squared() );
	}

	//unit vector
	const struct TVector3 unit() const
	{
		return (*this) / this->length();
	}

	//make this a unit vector
	const TVector4& normalize()
	{
		(*this) /= this->length();

		return *this;
	}
};

