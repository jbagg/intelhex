/**************************************************************************************************
---------------------------------------------------------------------------------------------------
	Copyright (c) 2018, Jonathan Bagg
	All rights reserved.
	 Redistribution and use in source and binary forms, with or without modification, are permitted
	 provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright notice, this list of
	  conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice, this list of
	  conditions and the following disclaimer in the documentation and/or other materials provided
	  with the distribution.
	* Neither the name of Jonathan Bagg nor the names of its contributors may be used to
	  endorse or promote products derived from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------------------------------
   File name    : intelhex.h
   Created      : 5 April 2018
   Author(s)    : Jonathan Bagg
---------------------------------------------------------------------------------------------------
   Parsers hex file
---------------------------------------------------------------------------------------------------
**************************************************************************************************/
#ifndef INTELHEX_H
#define INTELHEX_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QtCore/QtGlobal>

#if (!defined(QT_STATIC) && !defined(INTELHEX_STATIC))
#	ifdef QT_BUILD_ZEROCONF_LIB
#		define Q_INTELHEX_EXPORT Q_DECL_EXPORT
#	else
#		define Q_INTELHEX_EXPORT Q_DECL_IMPORT
#	endif
#else
#	define Q_INTELHEX_EXPORT
#endif

class Q_INTELHEX_EXPORT IntelHexSegment
{
public:
	IntelHexSegment() {;}
	quint32    startAdress;
	quint32    totalPages;
	QByteArray data;
};

class Q_INTELHEX_EXPORT IntelHex : public QObject
{
	Q_OBJECT
public:
	explicit IntelHex(QObject *parent = 0);
	bool open(QString fileName, quint32 pageSize);
	inline void reReadAll() { segmentIdx = 0; segmentPos = 0; }
	inline void reReadSegment() { segmentPos = 0; }
	inline quint32 totalSegments() { return segments.size(); }
	inline quint32 segmentSize() { return segments.at(segmentIdx).data.size(); }
	inline quint32 segmentPages() { return segments.at(segmentIdx).totalPages; }
	inline qint32 selectNextSegment() { return selectSegment(segmentIdx + 1); }
	qint32 selectSegment(qint32 segment);
	qint32 readPage(quint32 &currentAddress, char **data, bool readAllSegments = 1);
	inline qint32 totalPages() { return pagesInFile; }

private:
	void processHexLine(QString &line);
	quint32 getLineType(QString line);
	quint32 getLength(QString line);
	quint32 getAddress(QString line);
	quint32 getSegmentAddress(QString &line);
	quint32 getLinearAddress(QString &line);
	void checkForSkippedAddresses(quint32 address);
	QList<IntelHexSegment> segments;
	QFile file;
	quint32 linearAddress, segmentAddress, filledAddress;
	quint32 pageSize, pagesInFile;
	qint32 segmentIdx, segmentPos;
	bool oneShot;

signals:

public slots:
};

#endif // INTELHEX_H
