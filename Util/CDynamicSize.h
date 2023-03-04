#pragma once

enum eSizeChange {None,Width,Height,Both};
enum eSizeFrom {Specifiy,FromChild};

Manager :
Fill,Pack, AlignSpecify,AlignChild,RelativeSpecify,RelativeChild. 

Child<Fill,ChangeSize,CHangePosition>

Horz / Vert : Parent/Fill/Stretch, AlignSpecify,AlignFromChild,PackFromChild,RelativeSpecify,RelativeFromChild

CLMConnector<Fill,PackFromChild>

Horz :
Vert : 
 Fill/Pack
AlignSpecify & RelativeSpecify
AlignChild,RelativeChild. 

class<FromParent,Calculated>

template <eSizeChange sc>
class CParent
{
};

template <eSizeChange Width>
class CParent
{
	changeWidth()
	{
	}
};


template <typename T,eSizeChange sc>
class CDynamicSize
{
};

template <typename T>
class CDynamicSize<T, eSizeChange::None>
{

public:
	CDynamicSize()
	{
	}
};


template <typename T>
class CDynamicSize<T,eSizeChange::Width>
{

public:
	CDynamicSize(const T& width) :
		m_Width(width)
	{
	}

	const T& getWidth() const
	{
		return this->m_Width;
	}

	void setWidth(const T& width)
	{
		this->m_Width = width;
	}
private:
	T m_Width;

};

template <typename T>
class CDynamicSize<T,eSizeChange::Height>
{
public:
	CDynamicSize(const T& height) :
		m_Height(height)
	{
	}

	const T& getHeight() const
	{
		return this->m_Height;
	}

	void setHeight(const T& height)
	{
		this->m_Height = height;
	}
private:
	T m_Height;
};

template <typename T>
class CDynamicSize<T,eSizeChange::Both>
{
public:
	CDynamicSize(const T& width, const T& height) :
	m_Width(width),m_Height(height)
	{
	}

	const T& getWidth() const
	{
		return this->m_Width;
	}

	const T& getHeight() const
	{
		return this->m_Height;
	}

	void setWidth(const T& width)
	{
		this->m_Width = width;
		this->getParent()->changeWidth();

	}

	void setHeight(const T& height)
	{
		this->m_Height = height;
		this->getParent()->changeHeight();
	}

	void setBoth(const T& width, const T& height)
	{
		this->m_Width = width;
		this->m_Height = height;
		this->getParent()->changeBoth(width, height);
	}

private:
	T m_Height;
	T m_Width;

};

