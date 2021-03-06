/*
CARTOTYPE_ERRORS.H
Copyright (C) 2004-2017 CartoType Ltd.
See www.cartotype.com for more information.
*/

#ifndef CARTOTYPE_ERRORS_H__
#define CARTOTYPE_ERRORS_H__

#include <cartotype_types.h>
#include <assert.h>
#include <stdlib.h>

namespace CartoType
{

/** No error; a successful result. */
constexpr int32 KErrorNone = 0;

/**
Use KErrorGeneral where an error has occurred but no other CartoType
error is applicable. For example, this error code can be used
when FreeType returns an error code for illegal TrueType hinting instructions.
*/
constexpr int32 KErrorGeneral = 1;

/** Use KErrorNoMemory when an attempted memory allocation fails. */
constexpr int32 KErrorNoMemory = 2;

/**
KErrorEndOfData is returned by iterators and streams when no more data
is available. It may be treated as an error or not depending on the
circumstances.
*/
constexpr int32 KErrorEndOfData = 3;

/**
KErrorTextUnmodifiable is returned when an attempt is made to
modify an unmodifiable string represented by a class derived
from MString.
*/
constexpr int32 KErrorTextUnmodifiable = 4;

/**
KErrorTextTruncated is returned when text inserted into
a string derived from MString is too long for a fixed-size
buffer.
*/
constexpr int32 KErrorTextTruncated = 5;

/**
KErrorNotFound is returned whenever a resource like a file
is not found, or a search fails. 
It may be treated as an error or not depending on the
circumstances.
*/
constexpr int32 KErrorNotFound = 6;

/**
The code KErrorUnimplemented is used for functions that have
not yet been implemented, or for circumstances or options
within functions that remain unimplemented because they
are deemed to be either rarely or never useful.
*/
constexpr int32 KErrorUnimplemented = 7;

/**
If the graphics system detects an invalid outline, such as one
that starts with a cubic control point, it returns
KErrorInvalidOutline.
*/
constexpr int32 KErrorInvalidOutline = 8;

/**
The code KErrorIo should be used for unexpected read or write
errors on files or other data streams. This is for where you
attempt to read data that should be there, but the OS says
it's unavailable (e.g., someone has taken the CD out of the drive
or the network is down). 
*/
constexpr int32 KErrorIo = 9;

/**
Use KErrorCorrupt when illegal values are found when reading data
from a file or other serialized form.
*/
constexpr int32 KErrorCorrupt = 10;

/**
This error is returned by database accessors, typeface accessors, etc.,
to indicate that this data format is unknown to a particular accessor.
It is not really an error but tells the caller to try the next
accessor in the list.
*/
constexpr int32 KErrorUnknownDataFormat = 11;

/**
This error is returned by transformation inversion if the transformation 
has no inverse.
*/
constexpr int32 KErrorNoInverse = 12;

/**
This error is returned by the projection system if the projection 
causes overflow.
*/
constexpr int32 KErrorProjectionOverflow = 13;

/**
The code KErrorCancel is returned to cancel an asynchronous
operation that uses callbacks. The callback or virtual function
returns this code. the caller must terminate further processing
on receipt of any error, but this one indicates that there has been
no actual error, but the handler has canceled the operation.
*/
constexpr int32 KErrorCancel = 14;

/**
This error is returned when an invalid argument has been given to a function.
*/
constexpr int32 KErrorInvalidArgument = 15;

/**
This error is returned by a data reader when it cannot deal with the data version.
*/
constexpr int32 KErrorUnknownVersion = 16;

/**
This error is returned by the base library when reading data or calculations result
in overflow.
*/
constexpr int32 KErrorOverflow = 17;

/**
Graphics functions can use this code to indicate that two graphics objects
overlap.
*/
constexpr int32 KErrorOverlap = 18;

/**
The error code returned by line intersection algorithms when the lines are parallel.
*/
constexpr int32 KErrorParallelLines = 19;

/**
Text was drawn along a path but the path was too short
for all the text.
*/
constexpr int32 KErrorPathLengthExceeded = 20;

/**
Text was drawn along a path but the maximum allowed angle between
the baselines of successive characters was exceeded.
*/
constexpr int32 KErrorMaxTurnExceeded = 21;

/**
An attempt was made to draw a bitmap needing a color palette
but no palette was provided.
*/
constexpr int32 KErrorNoPalette = 22;

/**
An attempt was made to insert a duplicate object into a collection
class that does not allow duplicates.
*/
constexpr int32 KErrorDuplicate = 23;

/**
The projection for converting latitude and longitude to map coordinates
is unknown or unavailable.
*/
constexpr int32 KErrorNoProjection = 24;

/**
A palette is full and no new entries can be added.
*/
constexpr int32 KErrorPaletteFull = 25;

/**
The dash array for drawing strokes is invalid.
*/
constexpr int32 KErrorInvalidDashArray = 26;

/**
The central-path system failed to create a usable path.
*/
constexpr int32 KErrorCentralPath = 27;

/**
A route was needed by the navigation system
but no route was available.
*/
constexpr int32 KErrorNoRoute = 28;

/**
There was an attempt to zoom beyond the legal zoom limits for a map.
*/
constexpr int32 KErrorZoomLimitReached = 29;

/**
There was an attempt to project a map object that had already been projected.
*/
constexpr int32 KErrorAlreadyProjected = 30;

/**
Conditions are too deeply nested in the style sheet.
*/
constexpr int32 KErrorConditionsTooDeeplyNested = 31;

/**
There was an attempt to use a null font for drawing text.
*/
constexpr int32 KErrorNullFont = 32;

/**
An attempt to read data from the internet failed.
*/
constexpr int32 KErrorInternetIo = 33;

/**
Division by zero in an interpreted expression.
*/
constexpr int32 KErrorDivideByZero = 34;

/**
A transform failed because an argument or result was out of range.
*/
constexpr int32 KErrorTransformFailed = 35;

/**
Reading a bitmap from PNG format failed.
*/
constexpr int32 KErrorPngRead = 36;

/**
Reading a bitmap from JPG format failed.
*/
constexpr int32 KErrorJpgRead = 37;

/**
An object did not intersect a specified region.
*/
constexpr int32 KErrorNoIntersection = 38;

/**
An operation was interrupted, for example by another thread writing to a shared flag.
*/
constexpr int32 KErrorInterrupt = 39;

/**
There was an attempt to use map databases of incompatible formats
(TMapGrid values containing point format, datum and axis orientations)
to draw a map or find objects in a map.
*/
constexpr int32 KErrorMapDataBaseFormatMismatch = 40;

/** A key supplied for encryption was too short. */
constexpr int32 KErrorEncryptionKeyTooShort = 41;

/** No encryption key has been set. */
constexpr int32 KErrorNoEncryptionKey = 42;

/** A code for standard emergency messages. */
constexpr int32 KErrorEmergencyMessage = 43;

/** A code for standard alert messages. */
constexpr int32 KErrorAlertMessage = 44;

/** A code for standard critical messages. */
constexpr int32 KErrorCriticalMessage = 45;

/** A code for standard error messages. */
constexpr int32 KErrorErrorMessage = 46;

/** A code for standard warning messages. */
constexpr int32 KErrorWarningMessage = 47;

/** A code for standard notice messages. */
constexpr int32 KErrorNoticeMessage = 48;

/** A code for standard information messages. */
constexpr int32 KErrorInfoMessage = 49;

/** A code for standard debug messages. */
constexpr int32 KErrorDebugMessage = 50;

/** A function has been called which is available only when navigating. */
constexpr int32 KErrorNotNavigating = 51;

/** The global framework object does not exist. */
constexpr int32 KErrorNoFramework = 52;

/** The global framework object already exists. */
constexpr int32 KErrorFrameworkAlreadyExists = 53;

/** A string was not transliterable. */
constexpr int32 KErrorUntransliterable = 54;

/** Writing a bitmap to PNG format failed. */
constexpr int32 KErrorPngWrite = 55;

/** There was an attempt to write to a read-only map database. */
constexpr int32 KErrorReadOnlyMapDataBase = 56;

/** There was an error in the PROJ.4 projection library error other than a projection overflow. */
constexpr int32 KErrorProj4 = 57;

/** A function was called from the unlicensed version of CartoType that is available only in the licensed version. */
constexpr int32 KErrorUnlicensed = 58;

/** No route could be created because there were no roads near the start point of a route section. */
constexpr int32 KErrorNoRoadsNearStartOfRoute = 59;

/** No route could be created because there were no roads near the end point of a route section. */
constexpr int32 KErrorNoRoadsNearEndOfRoute = 60;

/** No route could be created because the start and end point were not connected. */
constexpr int32 KErrorNoRouteConnectivity = 61;

/** The number of standard error codes. */
constexpr int32 KStandardErrorCodeCount = 62;

/**
Get a short description of an error, given its code.
If the error code is unknown return the empty string.
*/
const char* ErrorString(int32 aErrorCode);

/**
The base of error codes for returning system and C library errors.
The high two bytes of this number are the ASCII characters 's' and 'y'.
The system error code itself is placed in the lower two bytes.
*/
constexpr int32 KErrorSystem = 0x73790000;

/**
The result and error code type is a class if _DEBUG is defined,
so that a breakpoint can be placed in the constructor if necessary,
and to enforce initialisation. For speed - because result codes
are used and checked everywhere, and on some GCC compilers even
tiny class objects (32 bits or less) are not passed in registers,
while ordinary integers are - it is normally just an integer.

Benchmarking on 32-bit Windows reveals a 4% speed increase when
using the plain integer, compared to the class, in release mode,
so it's not feasible to use the class version in release builds.
*/
#ifdef _DEBUG
class TResult
    {
    public:
    TResult(int32 aCode) { *this = aCode; }
    operator int32() const { return iCode; }
    void operator=(int32 aCode)
        {
        if (aCode)
            iCode = aCode; // put a breakpoint here to catch errors
        else
            iCode = aCode;
        }

    private:
    int32 iCode;
    };
#else
typedef int32 TResult;
#endif

// For unit tests
#ifdef CARTOTYPE_TEST
inline void Panic() { abort(); }
inline void Check(bool aExp) { if (!aExp) Panic(); }
inline void Check(int aExp) { if (!aExp) Panic(); }
inline void Check(const void* aPtr) { if (!aPtr) Panic(); }
#endif

} // namespace CartoType

#endif
