/*
 *  kext_tools_util.h
 *  kext_tools
 *
 *  Created by Nik Gervae on 4/25/08.
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */
#ifndef _KEXT_TOOLS_UTIL_H
#define _KEXT_TOOLS_UTIL_H

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/kext/OSKext.h>
#include <mach/mach_error.h>

#include <getopt.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#pragma mark Types
/*******************************************************************************
* Types
*******************************************************************************/
typedef int ExitStatus;

typedef enum {
    kUsageLevelBrief = 0,
    kUsageLevelFull  = 1
} UsageLevel;

typedef struct {
    CFURLRef   saveDirURL;
    Boolean    overwrite;
    Boolean    fatal;
} SaveFileContext;

#pragma mark Constants
/*******************************************************************************
* Constants
*******************************************************************************/
#define _kKextPropertyValuesCacheBasename  "KextPropertyValues_"
#define __kOSKextApplePrefix        CFSTR("com.apple.")

#define kAppleInternalPath      "/AppleInternal"
#define kDefaultKernelDevPath   "/System/Library/Kernels/kernel.development"
#define kDefaultKernelSuffix    ".development"

#pragma mark Macros
/*********************************************************************
* Macros
*********************************************************************/

#define SAFE_FREE(ptr)  do {          \
    if (ptr) free(ptr);               \
    } while (0)
#define SAFE_FREE_NULL(ptr)  do {     \
    if (ptr) free(ptr);               \
    (ptr) = NULL;                     \
    } while (0)
#define SAFE_RELEASE(ptr)  do {       \
    if (ptr) CFRelease(ptr);          \
    } while (0)
#define SAFE_RELEASE_NULL(ptr)  do {  \
    if (ptr) CFRelease(ptr);          \
    (ptr) = NULL;                     \
    } while (0)

#define RANGE_ALL(a)   CFRangeMake(0, CFArrayGetCount(a))

#define COMPILE_TIME_ASSERT(pred)   switch(0){case 0:case pred:;}

/*********************************************************************
*********************************************************************/

/* Library default is not to log Basic, but kextd & kextcache spawned
 * by kextd want to do that.
 */
#define kDefaultServiceLogFilter ((OSKextLogSpec) kOSKextLogBasicLevel | \
                                             kOSKextLogVerboseFlagsMask)

#pragma mark Shared Command-line Option Definitions
/*******************************************************************************
* Command-line options. This data is used by getopt_long_only().
*******************************************************************************/
#define kOptNameArch                    "arch"
#define kOptNameBundleIdentifier        "bundle-id"
#define kOptNameRepository              "repository"

#define kOptNameSafeBoot                "safe-boot"
#define kOptNameSystemExtensions        "system-extensions"
#define kOptNameKernel                  "kernel"
#define kOptNameNoAuthentication        "no-authentication"

#define kOptNameHelp                    "help"
#define kOptNameQuiet                   "quiet"
#define kOptNameVerbose                 "verbose"

#define kOptNameLongindexHack           "________"

// Can't use -a globally for -arch because of kextutil...?
#define kOptBundleIdentifier 'b'
// Can't use -r globally for -repository because of kextcache...?

// Can't use -x globally for -safe-boot because of kextcache's -s...?
// Can't use -e globally for -system-extensions because of kextutil...?
// Can't use -k globally for -kernel because of kextcache...?
#define kOptNoAuthentication 'z'

#define kOptHelp             'h'
#define kOptQuiet            'q'
#define kOptVerbose          'v'

// Long opts always defined in each program to avoid # collisions

#pragma mark Function Protos
/*********************************************************************
* Function Protos
*********************************************************************/

Boolean createCFMutableArray(CFMutableArrayRef * arrayOut,
    const CFArrayCallBacks * callbacks);
Boolean createCFMutableDictionary(CFMutableDictionaryRef * dictionaryOut);
Boolean createCFMutableSet(CFMutableSetRef * setOut,
    const CFSetCallBacks * callbacks);
Boolean createCFDataFromFile(CFDataRef  *dataRefOut,
                             const char *filePath);

void addToArrayIfAbsent(CFMutableArrayRef array, const void * value);

ExitStatus checkPath(
    const char * path,
    const char * suffix,  // w/o the dot
    Boolean      directoryRequired,
    Boolean      writableRequired);

ExitStatus setLogFilterForOpt(
    int            argc,
    char * const * argv,
    OSKextLogSpec  forceOnFlags);

void beQuiet(void);

FILE *  g_log_stream;
// tool_openlog(), tool_log() copied to bootroot.h for libBootRoot clients
void tool_openlog(const char * name);
void tool_log(
    OSKextRef aKext,
    OSKextLogSpec logSpec,
    const char * format,
    ...);
void log_CFError(
    OSKextRef     aKext __unused,
    OSKextLogSpec msgLogSpec,
    CFErrorRef    error);

const char * safe_mach_error_string(mach_error_t error_code);

#define REPLY_ERROR (-1)
#define REPLY_NO     (0)
#define REPLY_YES    (1)
#define REPLY_ALL    (2)

int user_approve(Boolean ask_all, int default_answer, const char * format, ...);

const char * user_input(Boolean * eof, const char * format, ...);
void saveFile(const void * vKey, const void * vValue, void * vContext);

CFStringRef copyKextPath(OSKextRef aKext);
Boolean readSystemKextPropertyValues(
    CFStringRef        propertyKey,
    const NXArchInfo * arch,
    Boolean            forceUpdateFlag,
    CFArrayRef       * valuesOut);

ExitStatus writeToFile(
    int           fileDescriptor,
    const UInt8 * data,
    CFIndex       length);

ExitStatus statURL(CFURLRef anURL, struct stat * statBuffer);
ExitStatus statPath(const char *path, struct stat *statBuffer);
ExitStatus statParentPath(const char *thePath, struct stat *statBuffer);
ExitStatus getLatestTimesFromCFURLArray(
                                        CFArrayRef          fileURLArray,
                                        struct timeval      fileTimes[2]);
ExitStatus getLatestTimesFromDirURL(
                                    CFURLRef       dirURL,
                                    struct timeval dirTimeVals[2]);

ExitStatus getLatestTimesFromDirPath(
                                     const char *   dirPath,
                                     struct timeval dirTimeVals[2]);

ExitStatus getFilePathTimes(
                            const char        * filePath,
                            struct timeval      cacheFileTimes[2]);

ExitStatus getParentPathTimes(
                              const char        * thePath,
                              struct timeval      cacheFileTimes[2] );

void postNoteAboutKexts(
                        CFStringRef theNotificationCenterName,
                        CFMutableDictionaryRef theDict );

void postNoteAboutKextLoadsMT(
                            CFStringRef theNotificationCenterName,
                            CFMutableArrayRef theKextPathArray );

void addKextToAlertDict(
                        CFMutableDictionaryRef *theDictPtr,
                        OSKextRef theKext );

char * getPathExtension(const char * pathPtr);

// bootcaches.plist helpers
CFDictionaryRef copyBootCachesDictForURL(CFURLRef theVolRootURL);
Boolean getKernelPathForURL(
                            CFURLRef theVolRootURL,
                            char * theBuffer,
                            int theBufferSize );

// Development kernel support
Boolean useDevelopmentKernel(const char * theKernelPath);
Boolean isDebugSetInBootargs(void);


/*********************************************************************
* From IOKitUser/kext.subproj/OSKext.c.
*********************************************************************/

extern char * createUTF8CStringForCFString(CFStringRef aString);

#endif /* _KEXT_TOOLS_UTIL_H */
