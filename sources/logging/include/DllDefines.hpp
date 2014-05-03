#ifndef logging_DLLDEFINES_H_
#define logging_DLLDEFINES_H_

/* Cmake will define MyLibrary_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the visual studio
projects by hand you need to define MyLibrary_EXPORTS when
building a DLL on windows.
*/
// We are using the Visual Studio Compiler and building Shared libraries

#if defined (_WIN32) 
#if defined(logging_EXPORTS)
#define  LOGGING_EXPORT __declspec(dllexport)
#else
#define  LOGGING_EXPORT __declspec(dllimport)
#endif /* MyLibrary_EXPORTS */
#else /* defined (_WIN32) */
#define LOGGING_EXPORT
#endif

#endif