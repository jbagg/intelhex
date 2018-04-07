
IntelHex is a library for reading Intel HEX files for Qt apps specifically for programming micro controllers.  Hex files can have voids or gaps between address, sometimes only a few bytes to 10-100K.  An example is a hex file containing both a bootloader and application.  It is not ideal to program / store all the blank bytes between the bootloader and application.  The gaps are not necessarialy aligned on page boundaries.  IntelHex will place all the "blobs" in their own segments and gaurentee the segments are aligned on page boundaries so the programming logic is super simple.

### Building

IntelHex can be built directly into your project without worry as it is [BSD](https://opensource.org/licenses/BSD-3-Clause) compatible.

#### Building into your project

1. Clone or download IntelHex.  If you download, unzip.
2. Copy the intelhex directory to be under your project's directory.
3. Include the intelhex.pri file in your projects .pro file

    include(intelhex/intelhex.pri)

4. Add INTELHEX_STATIC define in your projects .pro file

    DEFINES+= INTELHEX_STATIC

#### Compiling as a dynamic library

1. Clone or download IntelHex.  If you download, unzip.
2. Enter the intelhex directory, run qmake and then make.

### API

#### Quick Example

The easiest way to read the whole file.  This example reads all pages, one at a time.  Page size = 256 bytes....
```c++
#include "intelhex.h"

IntelHex hexFile;
int32_t address;
int8_t *data;

hexFile.open("myfile.hex", 256);
while (hexFile.readPage(address, &data)
    myPageWriteFunction(address, data);

```
address will increase in size by page size (256 bytes in this example) every time readPage() is called as long as pages are consequtive (in the same segment).  If there are multiple segments in the hex file, readPage() automatically advances to the next segment when it reaches the end of a segment.  address will reflect the new segment (change will be more than page size) on a segment change.  readPage() will return the page size as long as there are pages to be read.  readPage() will return 0 when there are no more pages to be read.

```c++
bool open(QString fileName, quint32 pageSize);
```
```c++
void reReadAll()
```
Resets the read position so readPage() will start from the beginning of the file.
```c++
void reReadSegment()
```
Resets the read position to the begining of the segment so readPage() will start from the beginning of the current segment.
```c++
quint32 totalSegments()
```
Returns the total number of segments contained in the hex file.  Usually there is only one segment.
```c++
quint32 segmentSize()
```
Returns the total number of bytes in the segment.
```c++
quint32 segmentPages()
```
Returns the total number of pages contained in the segment.
```c++
qint32 selectNextSegment()
```
Selects the next segment, so the next time readPage() is called, it will return the pages from the next segment.  This will return -1 if already on the last segment.
```c++
qint32 selectSegment(qint32 segment);
```
Switches the segment.  This will return -1 if the segment does not exist.
```c++
qint32 readPage(quint32 &currentAddress, char **data, bool readAllSegments = 1);
```
See example.
```c++
qint32 totalPages()
```
Returns the total number of pages contained in the hex file.
