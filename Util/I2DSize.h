#pragma once

enum eChildConstraint {Fill,MutableSize,ImmutableSize};

template <typename T,eChildConstraint constraint>
struct IHorzSize {};

template <typename T>
struct IHorzSize<T, MutableSize>
{

public:
	virtual const T &getWidth() const = 0;
	virtual const T &changeWidth(const T& width) = 0;
};

template <typename T>
struct IHorzSize<T, ImmutableSize>
{
	public:
		virtual const T& getWidth() const = 0;
};

template <typename T, eChildConstraint constraint>
struct IVertSize {};

template <typename T>
struct IVertSize<T, MutableSize>
{

public:
	virtual const T& getHeight() const = 0;
	virtual const T& changeHeight(const T& width) = 0;
};

template <typename T>
struct IVertSize<T, ImmutableSize>
{
public:
	virtual const T& getHeight() const = 0;
};

template <typename T,eChildConstraint horz,eChildConstraint vert>
struct I2DSize :
	virtual public IHorzSize<T,horz>,
	virtual public IVertSize<T,vert>
{

};

enum class eParam { Supplied, MutableChild, ImmutableChild };

template <typename T, eParam horz>
struct IHorzSizeParent {};

template <typename T, eParam::Supplied>
struct IHorzSizeParent 
{
	void setWidth();
	const T& getWidth();
};

template <typename T, eParam::ImmutableChild >
struct IHorzSizeParent
{
	const T& getChildWidth();
};