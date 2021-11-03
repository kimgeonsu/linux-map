#pragma once

#include "MyType.h"
#include <list>

class CMapDataRecord {
private :
	long _level;
	Point _parcelPos;
	Point _parcelID;

public:
	std::list<_MapRecord> _drawDataList;

public:
	void AddDataList(_MapRecord* inData);
	void SetLevel(long level) { _level = level; };
	long GetLevel() { return _level; };
	void GetLevel(long& level) { level = _level; };

	void SetParcelPos(Point parcelPos) { _parcelPos = parcelPos; };
	void SetParcelPos(long xPos, long yPos) { _parcelPos.x = xPos;	_parcelPos.y = yPos; };
	Point GetParcelPos() { return _parcelPos; };
	void GetParcelPos(Point& parcelPos) { parcelPos = _parcelPos; };
	void GetParcelPos(long& xPos, long& yPos) { xPos = _parcelPos.x; yPos = _parcelPos.y; };

	void SetParcelID(Point parcelID) { _parcelID = parcelID; };
	void SetParcelID(long xPos, long yPos) { _parcelID.x = xPos; _parcelID.y = yPos; };
	Point GetParcelID() { return _parcelID; };
	void GetParcelID(Point& parcelID) { parcelID = _parcelID; };
	void GetParcelID(long& xPos, long& yPos) { xPos = _parcelID.x; yPos = _parcelID.y; };

	bool IsEqualParcel(long level, Point parcelPos)
	{
		if ((_level == level) && (_parcelPos.x == parcelPos.x) && (_parcelPos.y == parcelPos.y))
			return true;
		return false;
	}

	void GetParcelPosDiff(Point parcelPos, Point& diffValue)
	{
		diffValue.x = parcelPos.x - _parcelPos.x;
		diffValue.y = parcelPos.y - _parcelPos.y;
	}

	void Init();

public:
	CMapDataRecord();
	virtual ~CMapDataRecord();

};