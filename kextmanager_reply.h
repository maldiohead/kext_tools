#ifndef	_kextmanager_reply_user_
#define	_kextmanager_reply_user_

/* Module kextmanager_reply */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>
	
/* BEGIN VOUCHER CODE */

#ifndef KERNEL
#if defined(__has_include)
#if __has_include(<mach/mig_voucher_support.h>)
#ifndef USING_VOUCHERS
#define USING_VOUCHERS
#endif
#ifndef __VOUCHER_FORWARD_TYPE_DECLS__
#define __VOUCHER_FORWARD_TYPE_DECLS__
#ifdef __cplusplus
extern "C" {
#endif
	extern boolean_t voucher_mach_msg_set(mach_msg_header_t *msg) __attribute__((weak_import));
#ifdef __cplusplus
}
#endif
#endif // __VOUCHER_FORWARD_TYPE_DECLS__
#endif // __has_include(<mach/mach_voucher_types.h>)
#endif // __has_include
#endif // !KERNEL
	
/* END VOUCHER CODE */

	
/* BEGIN MIG_STRNCPY_ZEROFILL CODE */

#if defined(__has_include)
#if __has_include(<mach/mig_strncpy_zerofill_support.h>)
#ifndef USING_MIG_STRNCPY_ZEROFILL
#define USING_MIG_STRNCPY_ZEROFILL
#endif
#ifndef __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__
#define __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__
#ifdef __cplusplus
extern "C" {
#endif
	extern int mig_strncpy_zerofill(char *dest, const char *src, int len) __attribute__((weak_import));
#ifdef __cplusplus
}
#endif
#endif /* __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__ */
#endif /* __has_include(<mach/mig_strncpy_zerofill_support.h>) */
#endif /* __has_include */
	
/* END MIG_STRNCPY_ZEROFILL CODE */


#ifdef AUTOTEST
#ifndef FUNCTION_PTR_T
#define FUNCTION_PTR_T
typedef void (*function_ptr_t)(mach_port_t, char *, mach_msg_type_number_t);
typedef struct {
        char            *name;
        function_ptr_t  function;
} function_table_entry;
typedef function_table_entry   *function_table_t;
#endif /* FUNCTION_PTR_T */
#endif /* AUTOTEST */

#ifndef	kextmanager_reply_MSG_COUNT
#define	kextmanager_reply_MSG_COUNT	8
#endif	/* kextmanager_reply_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <IOKit/kext/kextmanager_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* SimpleRoutine lock_reboot_reply */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_reboot_reply
(
	mach_port_t replyPart,
	kern_return_t rval,
	mountpoint_t busyVol,
	int busyStatus
);

/* SimpleRoutine lock_volume_reply */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t lock_volume_reply
(
	mach_port_t replyPart,
	kern_return_t rval,
	int lockStatus
);

__END_DECLS

/********************** Caution **************************/
/* The following data types should be used to calculate  */
/* maximum message sizes only. The actual message may be */
/* smaller, and the position of the arguments within the */
/* message layout may vary from what is presented here.  */
/* For example, if any of the arguments are variable-    */
/* sized, and less than the maximum is sent, the data    */
/* will be packed tight in the actual message to reduce  */
/* the presence of holes.                                */
/********************** Caution **************************/

/* typedefs for all requests */

#ifndef __Request__kextmanager_reply_subsystem__defined
#define __Request__kextmanager_reply_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t rval;
		mountpoint_t busyVol;
		char busyVolPad[2];
		int busyStatus;
	} __Request__lock_reboot_reply_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t rval;
		int lockStatus;
	} __Request__lock_volume_reply_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__kextmanager_reply_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__kextmanager_reply_subsystem__defined
#define __RequestUnion__kextmanager_reply_subsystem__defined
union __RequestUnion__kextmanager_reply_subsystem {
	__Request__lock_reboot_reply_t Request_lock_reboot_reply;
	__Request__lock_volume_reply_t Request_lock_volume_reply;
};
#endif /* !__RequestUnion__kextmanager_reply_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__kextmanager_reply_subsystem__defined
#define __Reply__kextmanager_reply_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__lock_reboot_reply_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__lock_volume_reply_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__kextmanager_reply_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__kextmanager_reply_subsystem__defined
#define __ReplyUnion__kextmanager_reply_subsystem__defined
union __ReplyUnion__kextmanager_reply_subsystem {
	__Reply__lock_reboot_reply_t Reply_lock_reboot_reply;
	__Reply__lock_volume_reply_t Reply_lock_volume_reply;
};
#endif /* !__RequestUnion__kextmanager_reply_subsystem__defined */

#ifndef subsystem_to_name_map_kextmanager_reply
#define subsystem_to_name_map_kextmanager_reply \
    { "lock_reboot_reply", 70106 },\
    { "lock_volume_reply", 70107 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _kextmanager_reply_user_ */
