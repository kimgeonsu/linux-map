#pragma once

typedef struct Point {
	int x;
	int y;
} Point;

typedef struct _MapRecord
{
	//_MapRecordHeader	header;
	//_iPoint* pointList;

	//_MapRecord() : pointList(NULL) { };
	~_MapRecord()
	{
		//GlReleaseArray(&pointList);
	}

	long getBuffer(unsigned int bufferSize)
	{
		//GlReleaseArray(&pointList);
		//pointList = new _iPoint[bufferSize];
		return true;
	}

	long releaseBuffer()
	{
		//GlReleaseArray(&pointList);
		return true;
	}
} _MapRecord;