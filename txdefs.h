/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	This file contains macros, enums and other global definitions of TXLibrary.
	
*/

#ifndef TXDEFS_H
#define TXDEFS_H
#define RGB(r, g, b) ((int(r)<<16) | (int(g)<<8) | int(b))

// windows definitions for text_align functions
#define TA_BOTTOM Qt::AlignBottom   //	Опорная точка на нижней кромке рабочего прямоугольника.
#define TA_TOP Qt::AlignTop      //	Опорная точка на верхней кромке рабочего прямоугольника.
#define TA_CENTER Qt::AlignCenter //4   //	Опорная точка выравнивается горизонтально по центру рабочего прямоугольника.
#define TA_LEFT Qt::AlignLeft     //	Опорная точка находится на левой кромке рабочего прямоугольника.
#define TA_RIGHT Qt::AlignRight    //	//Опорная точка находится на правой кромке рабочего прямоугольника.


#define _TX_V_FROM_CVS(_1,file,ver,rev,date,auth,_2)  "TXLib [Ver: " #ver ", Rev: " #rev "]"
#define _TX_A_FROM_CVS(_1,file,ver,rev,date,auth,_2)  "Copyright (C) " auth
#define _TX_v_FROM_CVS(_1,file,ver,rev,date,auth,_2)  ((0x##ver << 16) | 0x##rev)

#define _TX_VERSION           _TX_V_FROM_CVS ($VersionInfo: , TXLib.h, 00172a, 104, 2014-08-09 16:37:26 +0400, "Ded (Ilya Dedinsky, http://txlib.ru) <mail@txlib.ru>", $)
#define _TX_AUTHOR            _TX_A_FROM_CVS ($VersionInfo: , TXLib.h, 00172a, 104, 2014-08-09 16:37:26 +0400, "Ded (Ilya Dedinsky, http://txlib.ru) <mail@txlib.ru>", $)
#define _TX_VER               _TX_v_FROM_CVS ($VersionInfo: , TXLib.h, 00172a, 104, 2014-08-09 16:37:26 +0400, "Ded (Ilya Dedinsky, http://txlib.ru) <mail@txlib.ru>", $)

#define MAX( a, b )     ( (a) > (b) ? (a) : (b) )
#define MIN( a, b )     ( (a) < (b) ? (a) : (b) )
#define ROUND( x )  ( (int) round (x) )
#define ZERO( type )    zero <type> ()
template <typename T> inline T zero();

#define  tx_auto_func(    func )  _tx_auto_fun1 ( __LINE__, func )
#define _tx_auto_fun1( n, func )  _tx_auto_fun2 ( n,        func )
#define _tx_auto_fun2( n, func )  auto _tx_auto_func_##n = _tx_auto_func ([&]() { func; })

template <typename T>
struct _tx_auto_func_
    {
    typedef _tx_auto_func_ this_t;
    T func_;

    _tx_auto_func_ (T func) : func_ (func) {}
   ~_tx_auto_func_ () { func_(); }

    private: this_t& operator= (const this_t&) { return *this; }
    };

template <typename T>
_tx_auto_func_<T> _tx_auto_func  (T   func)
    {
    return        _tx_auto_func_ <T> (func);
    }

#define TX_FINALLY( param_t, param, func )  TX_AUTO_FUNC (param_t, param, func)
#define tx_finally( func )                  tx_auto_func (func)

#if !defined (NDEBUG)
    #undef  assert
    #define assert( cond )    _txNOP ( !(cond)? (TX_ERROR ("\a" "Error: %s."    \
                                                           TX_COMMA #cond), \
                                                 0/(int)!!(cond)) : 1 )
#else
    #undef  assert
    #define assert( cond )    ((void) 1)

#endif

#if !defined (NDEBUG)
    #define asserted          || TX_ERROR ("\a" "нАМЮПСФЕМ МСКЕБНИ ХКХ КНФМШИ ПЕГСКЭРЮР.")

#else
    #define asserted          || _txNOP (0)

#endif

#define verified              asserted  //!< For compatibility with assert macro

//! @cond INTERNAL
#define TX_NEEDED             asserted  //!< For compatibility with earlier releases
//! @endcond

#if !defined (NDEBUG)
    #undef  verify
    #define verify            assert

#else
    #undef  verify
    #define verify( expr )    ( expr )

#endif

#if defined (__STRICT_ANSI__) || defined (_MSC_VER) && (_MSC_VER < 1400)
    #define TX_ERROR( msg )   _txError (__FILE__, __LINE__, __TX_FUNCTION__, msg)

#else
    #define TX_ERROR( ... )   _txError (__FILE__, __LINE__, __TX_FUNCTION__, __VA_ARGS__)

#endif

//! @cond INTERNAL
#define TX_THROW              TX_ERROR  //!< For compatibility with earlier releases
//! @endcond

#if !defined (NDEBUG)
    #define TX_DEBUG_ERROR    TX_ERROR

#else
    #define TX_DEBUG_ERROR(m) ((void) 0)

#endif

#if   defined (__GNUC__)
    #define __TX_COMPILER__   "GNU g++ "            TX_PREPROCESS (__GNUC__)       "."  \
                                                    TX_PREPROCESS (__GNUC_MINOR__) "."  \
                                                    TX_PREPROCESS (__GNUC_PATCHLEVEL__) \
                              ", std="              TX_PREPROCESS (__cplusplus)
#elif defined (_MSC_VER)
    #define __TX_COMPILER__   "MSVS "               TX_PREPROCESS (_MSC_VER)            \
                              ", std="              TX_PREPROCESS (__cplusplus)

#elif defined (__INTEL_COMPILER)
    #define __TX_COMPILER__   "Intel C++ "          TX_PREPROCESS (__INTEL_COMPILER)    \
                              ", std="              TX_PREPROCESS (__cplusplus)

#else
    #define __TX_COMPILER__   "Unknown C++, std="   TX_PREPROCESS (__cplusplus)

#endif

#define __TX_FILELINE__       __FILE__ " (" TX_PREPROCESS (__LINE__) ")"

#if defined (__GNUC__)
    #define __TX_FUNCTION__   __PRETTY_FUNCTION__

#elif defined (__FUNCSIG__)
    #define __TX_FUNCTION__   __FUNCSIG__

#elif defined (__FUNCTION__)
    #define __TX_FUNCTION__   __FUNCTION__

#elif defined (__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)
    #define __TX_FUNCTION__   __FUNCTION__

#elif defined (__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #define __TX_FUNCTION__   __FUNC__

#elif defined (__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    #define __TX_FUNCTION__   __func__

#elif defined (__PYTHON__)
    #error No Python. No. Using parseltongue languages can lead you to Slytherin.

#else
    #define __TX_FUNCTION__   "(" __TX_FILELINE__ ")"

#endif

#if   !defined (NDEBUG) &&  defined (_DEBUG)
    #define _TX_BUILDMODE     "DEBUG"

#elif !defined (NDEBUG) && !defined (_DEBUG)
    #define _TX_BUILDMODE     "Debug"

#elif  defined (NDEBUG)
    #define _TX_BUILDMODE     "Release"
#endif

#define  TX_PREPROCESS( sym ) _TX_QUOTE (sym)
#define _TX_QUOTE( sym )      #sym

#if !defined (_TX_MODULE)
    #define   _TX_MODULE      "TXLib"
#endif

#define sizearr( arr )    ( sizeof (get_size_of_an_array_with_unknown_or_nonconst_size_ (arr)) )
template <typename T, int N> char (&get_size_of_an_array_with_unknown_or_nonconst_size_ (T (&) [N])) [N]; // ;)

#define SIZEARR( arr )        ( sizeof (arr) / sizeof (0[arr]) )
#define CLR_INVALID -1

typedef struct _RECT {
  long left;
  long top;
  long right;
  long bottom;
} RECT, *PRECT;

typedef struct _SMALL_RECT {
  int left;
  int top;
  int right;
  int bottom;
} SMALL_RECT;

typedef struct _COORD {
  int X;
  int Y;
} COORD, *PCOORD;

typedef struct tagSIZE {
  long cx;
  long cy;
} SIZE, *PSIZE;

typedef unsigned int COLORREF;

typedef QTxPoint POINT;
typedef Qtx* TXWINDOW;
typedef unsigned long DWORD;
#ifndef HDC
typedef QPixmap *HDC;
#endif
#ifndef HBITMAP
typedef unsigned char *HBITMAP;
#endif
typedef void (*KEYEVENTHANDLER)(int);
typedef void (*MOUSEEVENTHANDLER)(int, int, int, bool);
typedef void (*TIMEREVENTHANDLER)(void*);
typedef void(*TXSLOT)();

enum txColors {
  TX_BLACK = RGB (0, 0, 0),
  TX_BLUE = RGB (0, 0, 128),
  TX_GREEN = RGB (0, 128, 0),
  TX_CYAN = RGB (0, 128, 128),
  TX_RED = RGB (128, 0, 0),
  TX_MAGENTA = RGB (128, 0, 128),
  TX_BROWN = RGB (128, 128, 0),
  TX_ORANGE = RGB (255, 128, 0),
  TX_GRAY = RGB (160, 160, 160),
  TX_DARKGRAY = RGB (128, 128, 128),
  TX_LIGHTGRAY = RGB (192, 192, 192),
  TX_LIGHTBLUE = RGB (0, 0, 255),
  TX_LIGHTGREEN = RGB (0, 255, 128),
  TX_LIGHTCYAN = RGB (0, 255, 255),
  TX_LIGHTRED = RGB (255, 0, 0),
  TX_LIGHTMAGENTA = RGB (255, 0, 255),
  TX_PINK = RGB (255, 128, 255),
  TX_YELLOW = RGB (255, 255, 128),
  TX_WHITE = RGB (255, 255, 255),
  TX_TRANSPARENT = 0xFFFFFFFF,
  TX_NULL = TX_TRANSPARENT,
  TX_HUE = 0x04000000,
  TX_SATURATION = 0x05000000,
  TX_LIGHTNESS = 0x06000000 };

enum CONTROL {
  DIALOG = 0x00000000,
  BUTTON = 0xFFFF0080,
  EDIT = 0xFFFF0081,
  STATIC = 0xFFFF0082,
  LISTBOX = 0xFFFF0083,
  SCROLLBAR = 0xFFFF0084,
  COMBOBOX = 0xFFFF0085,
  END = 0x00000000 };

const int _TX_TIMEOUT = 1000;
const unsigned _TX_BUFSIZE = 1024;
const unsigned _TX_BIGBUFSIZE = 2048;
const double txPI = 3.1415926;
unsigned _txConsoleMode = 0;
unsigned _txWindowStyle = 0;
const char *_txConsoleFont = "Lucida Console";
unsigned _txCursorBlinkInterval = 500;
int _txWindowUpdateInterval = 25;


template <typename T>
inline T zero()
#ifdef _MSC_VER_6
    { T __zero = {0}; return __zero; }

#else
    { T __zero = { }; return __zero; }

#endif

template <typename T>
inline bool In (T x, T a, T b)
    {
    return a <= x && x <= b;
    }


#endif