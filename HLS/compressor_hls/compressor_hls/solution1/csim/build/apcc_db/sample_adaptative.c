/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;

/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
signed int mlog2(signed int llvm_cbe_x);
void write_bits(signed int llvm_cbe_data, signed int llvm_cbe_size);
void write_bits_mapped(signed int llvm_cbe_data, signed int llvm_cbe_size);
void write_bits_mapped2(signed int llvm_cbe_data, signed int llvm_cbe_size);
signed int encode_sample(signed int *llvm_cbe_counter, signed int *llvm_cbe_accumulator, signed int llvm_cbe_t, signed int llvm_cbe_z, signed int llvm_cbe_mapped, signed int *llvm_cbe_bits_written);
void write_headers(signed int *llvm_cbe_bits_written);


/* Global Variable Definitions and Initialization */
static  char aesl_internal__OC_str[3] = "%d";


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

signed int mlog2(signed int llvm_cbe_x) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  unsigned int llvm_cbe_tmp__1;
  unsigned int llvm_cbe_tmp__1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  unsigned int llvm_cbe_tmp__2;
  unsigned int llvm_cbe_tmp__2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @mlog2\n");
  llvm_cbe_tmp__1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__2__PHI_TEMPORARY = (unsigned int )llvm_cbe_x;   /* for PHI node */
  goto llvm_cbe_tmp__5;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__5:
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = phi i32 [ %%6, %%1 ], [ 0, %%0  for 0x%I64xth hint within @mlog2  --> \n", ++aesl_llvm_cbe_7_count);
  llvm_cbe_tmp__1 = (unsigned int )llvm_cbe_tmp__1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__1);
printf("\n = 0x%X",llvm_cbe_tmp__4);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = phi i32 [ %%4, %%1 ], [ %%x, %%0 ], !dbg !9 for 0x%I64xth hint within @mlog2  --> \n", ++aesl_llvm_cbe_8_count);
  llvm_cbe_tmp__2 = (unsigned int )llvm_cbe_tmp__2__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__2);
printf("\n = 0x%X",llvm_cbe_tmp__3);
printf("\nx = 0x%X",llvm_cbe_x);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = lshr i32 %%3, 1, !dbg !9 for 0x%I64xth hint within @mlog2  --> \n", ++aesl_llvm_cbe_9_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__2&4294967295ull)) >> ((unsigned int )(1u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add i32 %%2, 1, !dbg !9 for 0x%I64xth hint within @mlog2  --> \n", ++aesl_llvm_cbe_13_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_tmp__1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
  if (((llvm_cbe_tmp__3&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__6;
  } else {
    llvm_cbe_tmp__1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__4;   /* for PHI node */
    llvm_cbe_tmp__2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__3;   /* for PHI node */
    goto llvm_cbe_tmp__5;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__6:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @mlog2}\n");
  return llvm_cbe_tmp__1;
}


void write_bits(signed int llvm_cbe_data, signed int llvm_cbe_size) {
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2_2e_in_count = 0;
  unsigned int llvm_cbe_storemerge2_2e_in;
  unsigned int llvm_cbe_storemerge2_2e_in__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_storemerge2_count = 0;
  unsigned int llvm_cbe_storemerge2;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @write_bits\n");
  if ((((signed int )llvm_cbe_size) > ((signed int )0u))) {
    llvm_cbe_storemerge2_2e_in__PHI_TEMPORARY = (unsigned int )llvm_cbe_size;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2.in = phi i32 [ %%storemerge2, %%.lr.ph ], [ %%size, %%0  for 0x%I64xth hint within @write_bits  --> \n", ++aesl_llvm_cbe_storemerge2_2e_in_count);
  llvm_cbe_storemerge2_2e_in = (unsigned int )llvm_cbe_storemerge2_2e_in__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2.in = 0x%X",llvm_cbe_storemerge2_2e_in);
printf("\nstoremerge2 = 0x%X",llvm_cbe_storemerge2);
printf("\nsize = 0x%X",llvm_cbe_size);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2 = add nsw i32 %%storemerge2.in, -1, !dbg !10 for 0x%I64xth hint within @write_bits  --> \n", ++aesl_llvm_cbe_storemerge2_count);
  llvm_cbe_storemerge2 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2_2e_in&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nstoremerge2 = 0x%X\n", ((unsigned int )(llvm_cbe_storemerge2&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%data) nounwind, !dbg !9 for 0x%I64xth hint within @write_bits  --> \n", ++aesl_llvm_cbe_26_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_data);
if (AESL_DEBUG_TRACE) {
printf("\nArgument data = 0x%X",llvm_cbe_data);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__7);
}
  if ((((signed int )llvm_cbe_storemerge2) > ((signed int )0u))) {
    llvm_cbe_storemerge2_2e_in__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge2;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @write_bits}\n");
  return;
}


void write_bits_mapped(signed int llvm_cbe_data, signed int llvm_cbe_size) {
  static  unsigned long long aesl_llvm_cbe_mapped_count = 0;
  signed int llvm_cbe_mapped[16];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
   char *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
   char *llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  unsigned int llvm_cbe_tmp__11;
  unsigned int llvm_cbe_tmp__11__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  unsigned long long llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  signed int *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_count = 0;
  unsigned int llvm_cbe_storemerge12;
  unsigned int llvm_cbe_storemerge12__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned long long llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  signed int *llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @write_bits_mapped\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast [16 x i32]* %%mapped to i8*, !dbg !10 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__8 = ( char *)(( char *)(&llvm_cbe_mapped));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call i8* @memset(i8* %%1, i32 0, i64 64 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_38_count);
  ( char *)memset(( char *)llvm_cbe_tmp__8, 0u, 64ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",64ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__9);
}
  if ((((signed int )llvm_cbe_data) > ((signed int )0u))) {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__11__PHI_TEMPORARY = (unsigned int )llvm_cbe_data;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph5;
  } else {
    goto llvm_cbe__2e_preheader;
  }

llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add nsw i32 %%size, -1, !dbg !10 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__10 = (unsigned int )((unsigned int )(llvm_cbe_size&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__10&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__10) > ((signed int )0u))) {
    llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph5' to make GCC happy */
llvm_cbe__2e_lr_2e_ph5:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ %%11, %%.lr.ph5 ], [ 0, %%0  for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",llvm_cbe_tmp__16);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = phi i32 [ %%10, %%.lr.ph5 ], [ %%data, %%0  for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_61_count);
  llvm_cbe_tmp__11 = (unsigned int )llvm_cbe_tmp__11__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__11);
printf("\n = 0x%X",llvm_cbe_tmp__15);
printf("\ndata = 0x%X",llvm_cbe_data);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = srem i32 %%6, 2, !dbg !9 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__12 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__11) % ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sext i32 %%storemerge3 to i64, !dbg !9 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__13 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds [16 x i32]* %%mapped, i64 0, i64 %%8, !dbg !9 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__14 = (signed int *)(&llvm_cbe_mapped[(((signed long long )llvm_cbe_tmp__13))
#ifdef AESL_BC_SIM
 % 16
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__13));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__13) < 16 && "Write access out of array 'mapped' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%7, i32* %%9, align 4, !dbg !9 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_65_count);
  *llvm_cbe_tmp__14 = llvm_cbe_tmp__12;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sdiv i32 %%6, 2, !dbg !9 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__15 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__11) / ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = add nsw i32 %%storemerge3, 1, !dbg !11 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__16 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__16&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__11) > ((signed int )1u))) {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__16;   /* for PHI node */
    llvm_cbe_tmp__11__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph5;
  } else {
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.lr.ph5' */
  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12 = phi i32 [ %%17, %%.lr.ph ], [ 0, %%.preheader  for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_storemerge12_count);
  llvm_cbe_storemerge12 = (unsigned int )llvm_cbe_storemerge12__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12 = 0x%X",llvm_cbe_storemerge12);
printf("\n = 0x%X",llvm_cbe_tmp__21);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sext i32 %%storemerge12 to i64, !dbg !11 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__17 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds [16 x i32]* %%mapped, i64 0, i64 %%13, !dbg !11 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_81_count);
  llvm_cbe_tmp__18 = (signed int *)(&llvm_cbe_mapped[(((signed long long )llvm_cbe_tmp__17))
#ifdef AESL_BC_SIM
 % 16
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__17));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__17) < 16)) fprintf(stderr, "%s:%d: warning: Read access out of array 'mapped' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i32* %%14, align 4, !dbg !11 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__19 = (unsigned int )*llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%15) nounwind, !dbg !11 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_83_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__19);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__20);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = add nsw i32 %%storemerge12, 1, !dbg !11 for 0x%I64xth hint within @write_bits_mapped  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__21 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__21&4294967295ull)));
  if (((llvm_cbe_tmp__21&4294967295U) == (llvm_cbe_tmp__10&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__21;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @write_bits_mapped}\n");
  return;
}


void write_bits_mapped2(signed int llvm_cbe_data, signed int llvm_cbe_size) {
  static  unsigned long long aesl_llvm_cbe_mapped_count = 0;
  signed int llvm_cbe_mapped[16];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
   char *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
   char *llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge4_count = 0;
  unsigned int llvm_cbe_storemerge4;
  unsigned int llvm_cbe_storemerge4__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned int llvm_cbe_tmp__24;
  unsigned int llvm_cbe_tmp__24__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  unsigned long long llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  signed int *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  unsigned int llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge13_2e_in_count = 0;
  unsigned int llvm_cbe_storemerge13_2e_in;
  unsigned int llvm_cbe_storemerge13_2e_in__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_storemerge13_count = 0;
  unsigned int llvm_cbe_storemerge13;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  unsigned long long llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  signed int *llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned int llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  unsigned int llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @write_bits_mapped2\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast [16 x i32]* %%mapped to i8*, !dbg !10 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__22 = ( char *)(( char *)(&llvm_cbe_mapped));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call i8* @memset(i8* %%1, i32 0, i64 64 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_101_count);
  ( char *)memset(( char *)llvm_cbe_tmp__22, 0u, 64ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",64ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__23);
}
  if ((((signed int )llvm_cbe_data) > ((signed int )0u))) {
    llvm_cbe_storemerge4__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe_tmp__24__PHI_TEMPORARY = (unsigned int )llvm_cbe_data;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph6;
  } else {
    goto llvm_cbe__2e_preheader;
  }

llvm_cbe__2e_preheader:
  if ((((signed int )llvm_cbe_size) > ((signed int )0u))) {
    llvm_cbe_storemerge13_2e_in__PHI_TEMPORARY = (unsigned int )llvm_cbe_size;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph6' to make GCC happy */
llvm_cbe__2e_lr_2e_ph6:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge4 = phi i32 [ %%10, %%.lr.ph6 ], [ 0, %%0  for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_storemerge4_count);
  llvm_cbe_storemerge4 = (unsigned int )llvm_cbe_storemerge4__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge4 = 0x%X",llvm_cbe_storemerge4);
printf("\n = 0x%X",llvm_cbe_tmp__29);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = phi i32 [ %%9, %%.lr.ph6 ], [ %%data, %%0  for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__24 = (unsigned int )llvm_cbe_tmp__24__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__24);
printf("\n = 0x%X",llvm_cbe_tmp__28);
printf("\ndata = 0x%X",llvm_cbe_data);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = srem i32 %%5, 2, !dbg !9 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__25 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__24) % ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__25));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%storemerge4 to i64, !dbg !9 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__26 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge4);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds [16 x i32]* %%mapped, i64 0, i64 %%7, !dbg !9 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__27 = (signed int *)(&llvm_cbe_mapped[(((signed long long )llvm_cbe_tmp__26))
#ifdef AESL_BC_SIM
 % 16
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__26));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__26) < 16 && "Write access out of array 'mapped' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%6, i32* %%8, align 4, !dbg !9 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_122_count);
  *llvm_cbe_tmp__27 = llvm_cbe_tmp__25;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sdiv i32 %%5, 2, !dbg !9 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__28 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__24) / ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__28));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = add nsw i32 %%storemerge4, 1, !dbg !11 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__29 = (unsigned int )((unsigned int )(llvm_cbe_storemerge4&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__29&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__24) > ((signed int )1u))) {
    llvm_cbe_storemerge4__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__29;   /* for PHI node */
    llvm_cbe_tmp__24__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__28;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph6;
  } else {
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.lr.ph6' */
  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge13.in = phi i32 [ %%storemerge13, %%.lr.ph ], [ %%size, %%.preheader  for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_storemerge13_2e_in_count);
  llvm_cbe_storemerge13_2e_in = (unsigned int )llvm_cbe_storemerge13_2e_in__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge13.in = 0x%X",llvm_cbe_storemerge13_2e_in);
printf("\nstoremerge13 = 0x%X",llvm_cbe_storemerge13);
printf("\nsize = 0x%X",llvm_cbe_size);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge13 = add nsw i32 %%storemerge13.in, -1, !dbg !11 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_storemerge13_count);
  llvm_cbe_storemerge13 = (unsigned int )((unsigned int )(llvm_cbe_storemerge13_2e_in&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\nstoremerge13 = 0x%X\n", ((unsigned int )(llvm_cbe_storemerge13&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sext i32 %%storemerge13 to i64, !dbg !11 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__30 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge13);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds [16 x i32]* %%mapped, i64 0, i64 %%12, !dbg !11 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__31 = (signed int *)(&llvm_cbe_mapped[(((signed long long )llvm_cbe_tmp__30))
#ifdef AESL_BC_SIM
 % 16
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__30));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__30) < 16)) fprintf(stderr, "%s:%d: warning: Read access out of array 'mapped' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = load i32* %%13, align 4, !dbg !11 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__32 = (unsigned int )*llvm_cbe_tmp__31;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str, i64 0, i64 0), i32 %%14) nounwind, !dbg !11 for 0x%I64xth hint within @write_bits_mapped2  --> \n", ++aesl_llvm_cbe_141_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__32);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__33);
}
  if ((((signed int )llvm_cbe_storemerge13) > ((signed int )0u))) {
    llvm_cbe_storemerge13_2e_in__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge13;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @write_bits_mapped2}\n");
  return;
}


signed int encode_sample(signed int *llvm_cbe_counter, signed int *llvm_cbe_accumulator, signed int llvm_cbe_t, signed int llvm_cbe_z, signed int llvm_cbe_mapped, signed int *llvm_cbe_bits_written) {
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  unsigned int llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_putchar_count = 0;
  unsigned int llvm_cbe_putchar;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  unsigned long long llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  signed int *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  signed int *llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  unsigned int llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  unsigned int llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  unsigned int llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_putchar1_count = 0;
  unsigned int llvm_cbe_putchar1;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  unsigned int llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_putchar2_count = 0;
  unsigned int llvm_cbe_putchar2;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge_count = 0;
  unsigned int llvm_cbe_storemerge;
  unsigned int llvm_cbe_storemerge__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  unsigned int llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  unsigned int llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  unsigned int llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  unsigned int llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @encode_sample\n");
  if (((llvm_cbe_t&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__67;
  } else {
    goto llvm_cbe_tmp__68;
  }

llvm_cbe_tmp__67:
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 %%mapped, i32 16), !dbg !11 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_183_count);
   /*tail*/ write_bits_mapped2(llvm_cbe_mapped, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument mapped = 0x%X",llvm_cbe_mapped);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_184_count);
  llvm_cbe_tmp__34 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add nsw i32 %%3, 16, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_185_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(llvm_cbe_tmp__34&4294967295ull)) + ((unsigned int )(16u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__35&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%4, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_186_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%putchar = tail call i32 @putchar(i32 10) nounwind, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_putchar_count);
   /*tail*/ putchar(10u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",10u);
printf("\nReturn putchar = 0x%X",llvm_cbe_putchar);
}
  goto llvm_cbe_tmp__69;

llvm_cbe_tmp__68:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sext i32 %%z to i64, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__36 = (unsigned long long )((signed long long )(signed int )llvm_cbe_z);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds i32* %%accumulator, i64 %%6, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__37 = (signed int *)(&llvm_cbe_accumulator[(((signed long long )llvm_cbe_tmp__36))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__36));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load i32* %%7, align 4, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_190_count);
  llvm_cbe_tmp__38 = (unsigned int )*llvm_cbe_tmp__37;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds i32* %%counter, i64 %%6, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__39 = (signed int *)(&llvm_cbe_counter[(((signed long long )llvm_cbe_tmp__36))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__36));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load i32* %%9, align 4, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__40 = (unsigned int )*llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = mul nsw i32 %%10, 49, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_193_count);
  llvm_cbe_tmp__41 = (unsigned int )((unsigned int )(llvm_cbe_tmp__40&4294967295ull)) * ((unsigned int )(49u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__41&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = ashr i32 %%11, 7, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_194_count);
  llvm_cbe_tmp__42 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__41) >> ((signed int )7u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__42));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = add nsw i32 %%12, %%8, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_195_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_tmp__42&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__38&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sdiv i32 %%13, %%10, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_196_count);
  llvm_cbe_tmp__44 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__43) / ((signed int )llvm_cbe_tmp__40)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__44));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = tail call i32 @mlog2(i32 %%14), !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_197_count);
  llvm_cbe_tmp__45 = (unsigned int ) /*tail*/ mlog2(llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__44);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__45);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = select i1 %%16, i32 0, i32 %%15, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__46 = (unsigned int )(((((signed int )llvm_cbe_tmp__45) < ((signed int )0u))) ? ((unsigned int )0u) : ((unsigned int )llvm_cbe_tmp__45));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = select i1 %%18, i32 14, i32 %%17, !dbg !13 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__47 = (unsigned int )(((((signed int )llvm_cbe_tmp__46) > ((signed int )14u))) ? ((unsigned int )14u) : ((unsigned int )llvm_cbe_tmp__46));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = ashr i32 %%mapped, %%19, !dbg !11 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_226_count);
  llvm_cbe_tmp__48 = (unsigned int )((signed int )(((signed int )llvm_cbe_mapped) >> ((signed int )llvm_cbe_tmp__47)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__48));
  if ((((signed int )llvm_cbe_tmp__48) < ((signed int )16u))) {
    goto llvm_cbe_tmp__70;
  } else {
    goto llvm_cbe_tmp__71;
  }

llvm_cbe_tmp__70:
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 %%20), !dbg !13 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_233_count);
   /*tail*/ write_bits(0u, llvm_cbe_tmp__48);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 1, i32 1), !dbg !13 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_234_count);
   /*tail*/ write_bits(1u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 %%mapped, i32 %%19), !dbg !11 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_235_count);
   /*tail*/ write_bits_mapped2(llvm_cbe_mapped, llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE) {
printf("\nArgument mapped = 0x%X",llvm_cbe_mapped);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__47);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%putchar1 = tail call i32 @putchar(i32 10) nounwind, !dbg !13 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_putchar1_count);
   /*tail*/ putchar(10u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",10u);
printf("\nReturn putchar1 = 0x%X",llvm_cbe_putchar1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_236_count);
  llvm_cbe_tmp__49 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add i32 %%19, 1, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_237_count);
  llvm_cbe_tmp__50 = (unsigned int )((unsigned int )(llvm_cbe_tmp__47&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__50&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = add i32 %%24, %%20, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_238_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_tmp__50&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__48&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = add i32 %%25, %%23, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_239_count);
  llvm_cbe_tmp__52 = (unsigned int )((unsigned int )(llvm_cbe_tmp__51&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__49&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__52&4294967295ull)));
  llvm_cbe_storemerge__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__52;   /* for PHI node */
  goto llvm_cbe_tmp__72;

llvm_cbe_tmp__71:
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 16), !dbg !13 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_241_count);
   /*tail*/ write_bits(0u, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 %%mapped, i32 16), !dbg !11 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_242_count);
   /*tail*/ write_bits_mapped2(llvm_cbe_mapped, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument mapped = 0x%X",llvm_cbe_mapped);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%putchar2 = tail call i32 @putchar(i32 10) nounwind, !dbg !13 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_putchar2_count);
   /*tail*/ putchar(10u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",10u);
printf("\nReturn putchar2 = 0x%X",llvm_cbe_putchar2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_243_count);
  llvm_cbe_tmp__53 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = add nsw i32 %%28, 32, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_244_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(llvm_cbe_tmp__53&4294967295ull)) + ((unsigned int )(32u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
  llvm_cbe_storemerge__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__54;   /* for PHI node */
  goto llvm_cbe_tmp__72;

llvm_cbe_tmp__72:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge = phi i32 [ %%29, %%27 ], [ %%26, %%22  for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_storemerge_count);
  llvm_cbe_storemerge = (unsigned int )llvm_cbe_storemerge__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge = 0x%X",llvm_cbe_storemerge);
printf("\n = 0x%X",llvm_cbe_tmp__54);
printf("\n = 0x%X",llvm_cbe_tmp__52);
}
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%storemerge, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_246_count);
  *llvm_cbe_bits_written = llvm_cbe_storemerge;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge = 0x%X\n", llvm_cbe_storemerge);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = load i32* %%9, align 4, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_248_count);
  llvm_cbe_tmp__55 = (unsigned int )*llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__55);
  if ((((signed int )llvm_cbe_tmp__55) < ((signed int )63u))) {
    goto llvm_cbe_tmp__73;
  } else {
    goto llvm_cbe_tmp__74;
  }

llvm_cbe_tmp__73:
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = load i32* %%7, align 4, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_252_count);
  llvm_cbe_tmp__56 = (unsigned int )*llvm_cbe_tmp__37;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = add nsw i32 %%34, %%mapped, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_253_count);
  llvm_cbe_tmp__57 = (unsigned int )((unsigned int )(llvm_cbe_tmp__56&4294967295ull)) + ((unsigned int )(llvm_cbe_mapped&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__57&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%35, i32* %%7, align 4, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_254_count);
  *llvm_cbe_tmp__37 = llvm_cbe_tmp__57;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = load i32* %%9, align 4, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_255_count);
  llvm_cbe_tmp__58 = (unsigned int )*llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__58);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = add nsw i32 %%36, 1, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_256_count);
  llvm_cbe_tmp__59 = (unsigned int )((unsigned int )(llvm_cbe_tmp__58&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__59&4294967295ull)));
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__59;   /* for PHI node */
  goto llvm_cbe_tmp__75;

llvm_cbe_tmp__74:
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = load i32* %%7, align 4, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_258_count);
  llvm_cbe_tmp__60 = (unsigned int )*llvm_cbe_tmp__37;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = add i32 %%mapped, 1, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_259_count);
  llvm_cbe_tmp__61 = (unsigned int )((unsigned int )(llvm_cbe_mapped&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__61&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = add i32 %%40, %%39, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_260_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(llvm_cbe_tmp__61&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__60&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__62&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = ashr i32 %%41, 1, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_261_count);
  llvm_cbe_tmp__63 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__62) >> ((signed int )1u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__63));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%42, i32* %%7, align 4, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_262_count);
  *llvm_cbe_tmp__37 = llvm_cbe_tmp__63;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = load i32* %%9, align 4, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_263_count);
  llvm_cbe_tmp__64 = (unsigned int )*llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = add nsw i32 %%43, 1, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_264_count);
  llvm_cbe_tmp__65 = (unsigned int )((unsigned int )(llvm_cbe_tmp__64&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__65&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = ashr i32 %%44, 1, !dbg !10 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_265_count);
  llvm_cbe_tmp__66 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__65) >> ((signed int )1u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__66));
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__66;   /* for PHI node */
  goto llvm_cbe_tmp__75;

llvm_cbe_tmp__75:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ %%45, %%38 ], [ %%37, %%33  for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",llvm_cbe_tmp__66);
printf("\n = 0x%X",llvm_cbe_tmp__59);
}
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%storemerge3, i32* %%9, align 4, !dbg !9 for 0x%I64xth hint within @encode_sample  --> \n", ++aesl_llvm_cbe_267_count);
  *llvm_cbe_tmp__39 = llvm_cbe_storemerge3;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge3 = 0x%X\n", llvm_cbe_storemerge3);
  goto llvm_cbe_tmp__69;

llvm_cbe_tmp__69:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @encode_sample}\n");
  return 1u;
}


void write_headers(signed int *llvm_cbe_bits_written) {
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  static  unsigned long long aesl_llvm_cbe_300_count = 0;
  static  unsigned long long aesl_llvm_cbe_301_count = 0;
  static  unsigned long long aesl_llvm_cbe_302_count = 0;
  static  unsigned long long aesl_llvm_cbe_303_count = 0;
  static  unsigned long long aesl_llvm_cbe_304_count = 0;
  static  unsigned long long aesl_llvm_cbe_305_count = 0;
  static  unsigned long long aesl_llvm_cbe_306_count = 0;
  static  unsigned long long aesl_llvm_cbe_307_count = 0;
  static  unsigned long long aesl_llvm_cbe_308_count = 0;
  static  unsigned long long aesl_llvm_cbe_309_count = 0;
  static  unsigned long long aesl_llvm_cbe_310_count = 0;
  unsigned int llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_311_count = 0;
  unsigned int llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_312_count = 0;
  static  unsigned long long aesl_llvm_cbe_313_count = 0;
  static  unsigned long long aesl_llvm_cbe_314_count = 0;
  static  unsigned long long aesl_llvm_cbe_315_count = 0;
  unsigned int llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_316_count = 0;
  unsigned int llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_317_count = 0;
  static  unsigned long long aesl_llvm_cbe_318_count = 0;
  static  unsigned long long aesl_llvm_cbe_319_count = 0;
  static  unsigned long long aesl_llvm_cbe_320_count = 0;
  unsigned int llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_321_count = 0;
  unsigned int llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_322_count = 0;
  static  unsigned long long aesl_llvm_cbe_323_count = 0;
  static  unsigned long long aesl_llvm_cbe_324_count = 0;
  static  unsigned long long aesl_llvm_cbe_325_count = 0;
  unsigned int llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_326_count = 0;
  unsigned int llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_327_count = 0;
  static  unsigned long long aesl_llvm_cbe_328_count = 0;
  static  unsigned long long aesl_llvm_cbe_329_count = 0;
  static  unsigned long long aesl_llvm_cbe_330_count = 0;
  unsigned int llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_331_count = 0;
  unsigned int llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_332_count = 0;
  static  unsigned long long aesl_llvm_cbe_333_count = 0;
  static  unsigned long long aesl_llvm_cbe_334_count = 0;
  unsigned int llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_335_count = 0;
  unsigned int llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_336_count = 0;
  static  unsigned long long aesl_llvm_cbe_337_count = 0;
  static  unsigned long long aesl_llvm_cbe_338_count = 0;
  static  unsigned long long aesl_llvm_cbe_339_count = 0;
  unsigned int llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_340_count = 0;
  unsigned int llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_341_count = 0;
  static  unsigned long long aesl_llvm_cbe_342_count = 0;
  static  unsigned long long aesl_llvm_cbe_343_count = 0;
  static  unsigned long long aesl_llvm_cbe_344_count = 0;
  unsigned int llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_345_count = 0;
  unsigned int llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_346_count = 0;
  static  unsigned long long aesl_llvm_cbe_347_count = 0;
  static  unsigned long long aesl_llvm_cbe_348_count = 0;
  static  unsigned long long aesl_llvm_cbe_349_count = 0;
  unsigned int llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_350_count = 0;
  unsigned int llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_351_count = 0;
  static  unsigned long long aesl_llvm_cbe_352_count = 0;
  static  unsigned long long aesl_llvm_cbe_353_count = 0;
  static  unsigned long long aesl_llvm_cbe_354_count = 0;
  unsigned int llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_355_count = 0;
  unsigned int llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_356_count = 0;
  static  unsigned long long aesl_llvm_cbe_357_count = 0;
  static  unsigned long long aesl_llvm_cbe_358_count = 0;
  unsigned int llvm_cbe_tmp__96;
  static  unsigned long long aesl_llvm_cbe_359_count = 0;
  unsigned int llvm_cbe_tmp__97;
  static  unsigned long long aesl_llvm_cbe_360_count = 0;
  static  unsigned long long aesl_llvm_cbe_361_count = 0;
  static  unsigned long long aesl_llvm_cbe_362_count = 0;
  static  unsigned long long aesl_llvm_cbe_363_count = 0;
  unsigned int llvm_cbe_tmp__98;
  static  unsigned long long aesl_llvm_cbe_364_count = 0;
  unsigned int llvm_cbe_tmp__99;
  static  unsigned long long aesl_llvm_cbe_365_count = 0;
  static  unsigned long long aesl_llvm_cbe_366_count = 0;
  static  unsigned long long aesl_llvm_cbe_367_count = 0;
  static  unsigned long long aesl_llvm_cbe_368_count = 0;
  unsigned int llvm_cbe_tmp__100;
  static  unsigned long long aesl_llvm_cbe_369_count = 0;
  unsigned int llvm_cbe_tmp__101;
  static  unsigned long long aesl_llvm_cbe_370_count = 0;
  static  unsigned long long aesl_llvm_cbe_371_count = 0;
  static  unsigned long long aesl_llvm_cbe_372_count = 0;
  unsigned int llvm_cbe_tmp__102;
  static  unsigned long long aesl_llvm_cbe_373_count = 0;
  unsigned int llvm_cbe_tmp__103;
  static  unsigned long long aesl_llvm_cbe_374_count = 0;
  static  unsigned long long aesl_llvm_cbe_375_count = 0;
  static  unsigned long long aesl_llvm_cbe_376_count = 0;
  static  unsigned long long aesl_llvm_cbe_377_count = 0;
  unsigned int llvm_cbe_tmp__104;
  static  unsigned long long aesl_llvm_cbe_378_count = 0;
  unsigned int llvm_cbe_tmp__105;
  static  unsigned long long aesl_llvm_cbe_379_count = 0;
  static  unsigned long long aesl_llvm_cbe_380_count = 0;
  static  unsigned long long aesl_llvm_cbe_381_count = 0;
  unsigned int llvm_cbe_tmp__106;
  static  unsigned long long aesl_llvm_cbe_382_count = 0;
  unsigned int llvm_cbe_tmp__107;
  static  unsigned long long aesl_llvm_cbe_383_count = 0;
  static  unsigned long long aesl_llvm_cbe_384_count = 0;
  static  unsigned long long aesl_llvm_cbe_385_count = 0;
  unsigned int llvm_cbe_tmp__108;
  static  unsigned long long aesl_llvm_cbe_386_count = 0;
  unsigned int llvm_cbe_tmp__109;
  static  unsigned long long aesl_llvm_cbe_387_count = 0;
  static  unsigned long long aesl_llvm_cbe_388_count = 0;
  static  unsigned long long aesl_llvm_cbe_389_count = 0;
  unsigned int llvm_cbe_tmp__110;
  static  unsigned long long aesl_llvm_cbe_390_count = 0;
  unsigned int llvm_cbe_tmp__111;
  static  unsigned long long aesl_llvm_cbe_391_count = 0;
  static  unsigned long long aesl_llvm_cbe_392_count = 0;
  static  unsigned long long aesl_llvm_cbe_393_count = 0;
  unsigned int llvm_cbe_tmp__112;
  static  unsigned long long aesl_llvm_cbe_394_count = 0;
  unsigned int llvm_cbe_tmp__113;
  static  unsigned long long aesl_llvm_cbe_395_count = 0;
  static  unsigned long long aesl_llvm_cbe_396_count = 0;
  static  unsigned long long aesl_llvm_cbe_397_count = 0;
  static  unsigned long long aesl_llvm_cbe_398_count = 0;
  unsigned int llvm_cbe_tmp__114;
  static  unsigned long long aesl_llvm_cbe_399_count = 0;
  unsigned int llvm_cbe_tmp__115;
  static  unsigned long long aesl_llvm_cbe_400_count = 0;
  static  unsigned long long aesl_llvm_cbe_401_count = 0;
  static  unsigned long long aesl_llvm_cbe_402_count = 0;
  static  unsigned long long aesl_llvm_cbe_403_count = 0;
  unsigned int llvm_cbe_tmp__116;
  static  unsigned long long aesl_llvm_cbe_404_count = 0;
  unsigned int llvm_cbe_tmp__117;
  static  unsigned long long aesl_llvm_cbe_405_count = 0;
  static  unsigned long long aesl_llvm_cbe_406_count = 0;
  static  unsigned long long aesl_llvm_cbe_407_count = 0;
  unsigned int llvm_cbe_tmp__118;
  static  unsigned long long aesl_llvm_cbe_408_count = 0;
  unsigned int llvm_cbe_tmp__119;
  static  unsigned long long aesl_llvm_cbe_409_count = 0;
  static  unsigned long long aesl_llvm_cbe_410_count = 0;
  static  unsigned long long aesl_llvm_cbe_411_count = 0;
  static  unsigned long long aesl_llvm_cbe_412_count = 0;
  unsigned int llvm_cbe_tmp__120;
  static  unsigned long long aesl_llvm_cbe_413_count = 0;
  unsigned int llvm_cbe_tmp__121;
  static  unsigned long long aesl_llvm_cbe_414_count = 0;
  static  unsigned long long aesl_llvm_cbe_415_count = 0;
  static  unsigned long long aesl_llvm_cbe_416_count = 0;
  static  unsigned long long aesl_llvm_cbe_417_count = 0;
  unsigned int llvm_cbe_tmp__122;
  static  unsigned long long aesl_llvm_cbe_418_count = 0;
  unsigned int llvm_cbe_tmp__123;
  static  unsigned long long aesl_llvm_cbe_419_count = 0;
  static  unsigned long long aesl_llvm_cbe_420_count = 0;
  static  unsigned long long aesl_llvm_cbe_421_count = 0;
  static  unsigned long long aesl_llvm_cbe_422_count = 0;
  unsigned int llvm_cbe_tmp__124;
  static  unsigned long long aesl_llvm_cbe_423_count = 0;
  unsigned int llvm_cbe_tmp__125;
  static  unsigned long long aesl_llvm_cbe_424_count = 0;
  static  unsigned long long aesl_llvm_cbe_425_count = 0;
  static  unsigned long long aesl_llvm_cbe_426_count = 0;
  static  unsigned long long aesl_llvm_cbe_427_count = 0;
  unsigned int llvm_cbe_tmp__126;
  static  unsigned long long aesl_llvm_cbe_428_count = 0;
  unsigned int llvm_cbe_tmp__127;
  static  unsigned long long aesl_llvm_cbe_429_count = 0;
  static  unsigned long long aesl_llvm_cbe_430_count = 0;
  static  unsigned long long aesl_llvm_cbe_431_count = 0;
  static  unsigned long long aesl_llvm_cbe_432_count = 0;
  unsigned int llvm_cbe_tmp__128;
  static  unsigned long long aesl_llvm_cbe_433_count = 0;
  unsigned int llvm_cbe_tmp__129;
  static  unsigned long long aesl_llvm_cbe_434_count = 0;
  static  unsigned long long aesl_llvm_cbe_435_count = 0;
  static  unsigned long long aesl_llvm_cbe_436_count = 0;
  static  unsigned long long aesl_llvm_cbe_437_count = 0;
  unsigned int llvm_cbe_tmp__130;
  static  unsigned long long aesl_llvm_cbe_438_count = 0;
  unsigned int llvm_cbe_tmp__131;
  static  unsigned long long aesl_llvm_cbe_439_count = 0;
  static  unsigned long long aesl_llvm_cbe_440_count = 0;
  static  unsigned long long aesl_llvm_cbe_441_count = 0;
  unsigned int llvm_cbe_tmp__132;
  static  unsigned long long aesl_llvm_cbe_442_count = 0;
  unsigned int llvm_cbe_tmp__133;
  static  unsigned long long aesl_llvm_cbe_443_count = 0;
  static  unsigned long long aesl_llvm_cbe_444_count = 0;
  static  unsigned long long aesl_llvm_cbe_445_count = 0;
  static  unsigned long long aesl_llvm_cbe_446_count = 0;
  unsigned int llvm_cbe_tmp__134;
  static  unsigned long long aesl_llvm_cbe_447_count = 0;
  unsigned int llvm_cbe_tmp__135;
  static  unsigned long long aesl_llvm_cbe_448_count = 0;
  static  unsigned long long aesl_llvm_cbe_449_count = 0;
  static  unsigned long long aesl_llvm_cbe_450_count = 0;
  static  unsigned long long aesl_llvm_cbe_451_count = 0;
  unsigned int llvm_cbe_tmp__136;
  static  unsigned long long aesl_llvm_cbe_452_count = 0;
  unsigned int llvm_cbe_tmp__137;
  static  unsigned long long aesl_llvm_cbe_453_count = 0;
  static  unsigned long long aesl_llvm_cbe_454_count = 0;
  static  unsigned long long aesl_llvm_cbe_455_count = 0;
  static  unsigned long long aesl_llvm_cbe_456_count = 0;
  unsigned int llvm_cbe_tmp__138;
  static  unsigned long long aesl_llvm_cbe_457_count = 0;
  unsigned int llvm_cbe_tmp__139;
  static  unsigned long long aesl_llvm_cbe_458_count = 0;
  static  unsigned long long aesl_llvm_cbe_459_count = 0;
  static  unsigned long long aesl_llvm_cbe_460_count = 0;
  static  unsigned long long aesl_llvm_cbe_461_count = 0;
  unsigned int llvm_cbe_tmp__140;
  static  unsigned long long aesl_llvm_cbe_462_count = 0;
  unsigned int llvm_cbe_tmp__141;
  static  unsigned long long aesl_llvm_cbe_463_count = 0;
  static  unsigned long long aesl_llvm_cbe_464_count = 0;
  static  unsigned long long aesl_llvm_cbe_465_count = 0;
  static  unsigned long long aesl_llvm_cbe_466_count = 0;
  unsigned int llvm_cbe_tmp__142;
  static  unsigned long long aesl_llvm_cbe_467_count = 0;
  unsigned int llvm_cbe_tmp__143;
  static  unsigned long long aesl_llvm_cbe_468_count = 0;
  static  unsigned long long aesl_llvm_cbe_469_count = 0;
  static  unsigned long long aesl_llvm_cbe_470_count = 0;
  static  unsigned long long aesl_llvm_cbe_471_count = 0;
  unsigned int llvm_cbe_tmp__144;
  static  unsigned long long aesl_llvm_cbe_472_count = 0;
  unsigned int llvm_cbe_tmp__145;
  static  unsigned long long aesl_llvm_cbe_473_count = 0;
  static  unsigned long long aesl_llvm_cbe_474_count = 0;
  static  unsigned long long aesl_llvm_cbe_475_count = 0;
  static  unsigned long long aesl_llvm_cbe_476_count = 0;
  unsigned int llvm_cbe_tmp__146;
  static  unsigned long long aesl_llvm_cbe_477_count = 0;
  unsigned int llvm_cbe_tmp__147;
  static  unsigned long long aesl_llvm_cbe_478_count = 0;
  static  unsigned long long aesl_llvm_cbe_479_count = 0;
  static  unsigned long long aesl_llvm_cbe_480_count = 0;
  static  unsigned long long aesl_llvm_cbe_481_count = 0;
  unsigned int llvm_cbe_tmp__148;
  static  unsigned long long aesl_llvm_cbe_482_count = 0;
  unsigned int llvm_cbe_tmp__149;
  static  unsigned long long aesl_llvm_cbe_483_count = 0;
  static  unsigned long long aesl_llvm_cbe_484_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @write_headers\n");
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 8), !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_309_count);
   /*tail*/ write_bits(0u, 8u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",8u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = load i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_310_count);
  llvm_cbe_tmp__76 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__76);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add nsw i32 %%1, 8, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_311_count);
  llvm_cbe_tmp__77 = (unsigned int )((unsigned int )(llvm_cbe_tmp__76&4294967295ull)) + ((unsigned int )(8u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__77&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%2, i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_312_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__77;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 5, i32 16), !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_314_count);
   /*tail*/ write_bits_mapped2(5u, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",5u);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_315_count);
  llvm_cbe_tmp__78 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__78);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add nsw i32 %%3, 16, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_316_count);
  llvm_cbe_tmp__79 = (unsigned int )((unsigned int )(llvm_cbe_tmp__78&4294967295ull)) + ((unsigned int )(16u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__79&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%4, i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_317_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__79;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 5, i32 16), !dbg !14 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_319_count);
   /*tail*/ write_bits_mapped2(5u, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",5u);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_320_count);
  llvm_cbe_tmp__80 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__80);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%5, 16, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_321_count);
  llvm_cbe_tmp__81 = (unsigned int )((unsigned int )(llvm_cbe_tmp__80&4294967295ull)) + ((unsigned int )(16u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__81&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%6, i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_322_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__81;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__81);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 5, i32 16), !dbg !14 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_324_count);
   /*tail*/ write_bits_mapped2(5u, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",5u);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = load i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_325_count);
  llvm_cbe_tmp__82 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__82);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = add nsw i32 %%7, 16, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_326_count);
  llvm_cbe_tmp__83 = (unsigned int )((unsigned int )(llvm_cbe_tmp__82&4294967295ull)) + ((unsigned int )(16u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__83&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%8, i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_327_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__83;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__83);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !14 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_329_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_330_count);
  llvm_cbe_tmp__84 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__84);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = add nsw i32 %%9, 1, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_331_count);
  llvm_cbe_tmp__85 = (unsigned int )((unsigned int )(llvm_cbe_tmp__84&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__85&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%10, i32* %%bits_written, align 4, !dbg !9 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_332_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__85;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !14 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_333_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_334_count);
  llvm_cbe_tmp__86 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__86);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = add nsw i32 %%11, 1, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_335_count);
  llvm_cbe_tmp__87 = (unsigned int )((unsigned int )(llvm_cbe_tmp__86&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__87&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%12, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_336_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__87;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__87);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !15 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_338_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_339_count);
  llvm_cbe_tmp__88 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = add nsw i32 %%13, 1, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_340_count);
  llvm_cbe_tmp__89 = (unsigned int )((unsigned int )(llvm_cbe_tmp__88&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__89&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%14, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_341_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__89;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__89);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 16, i32 4), !dbg !15 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_343_count);
   /*tail*/ write_bits_mapped2(16u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",16u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_344_count);
  llvm_cbe_tmp__90 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__90);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = add nsw i32 %%15, 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_345_count);
  llvm_cbe_tmp__91 = (unsigned int )((unsigned int )(llvm_cbe_tmp__90&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__91&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%16, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_346_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__91;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__91);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !15 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_348_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_349_count);
  llvm_cbe_tmp__92 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__92);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%17, 1, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_350_count);
  llvm_cbe_tmp__93 = (unsigned int )((unsigned int )(llvm_cbe_tmp__92&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__93&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%18, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_351_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__93;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__93);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 3, i32 16), !dbg !16 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_353_count);
   /*tail*/ write_bits_mapped2(3u, 16u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",3u);
printf("\nArgument  = 0x%X",16u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_354_count);
  llvm_cbe_tmp__94 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = add nsw i32 %%19, 16, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_355_count);
  llvm_cbe_tmp__95 = (unsigned int )((unsigned int )(llvm_cbe_tmp__94&4294967295ull)) + ((unsigned int )(16u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__95&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%20, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_356_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__95;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__95);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 2), !dbg !16 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_357_count);
   /*tail*/ write_bits(0u, 2u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",2u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_358_count);
  llvm_cbe_tmp__96 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__96);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = add nsw i32 %%21, 2, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_359_count);
  llvm_cbe_tmp__97 = (unsigned int )((unsigned int )(llvm_cbe_tmp__96&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__97&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%22, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_360_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__97;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__97);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 4, i32 3), !dbg !16 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_362_count);
   /*tail*/ write_bits_mapped2(4u, 3u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",4u);
printf("\nArgument  = 0x%X",3u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_363_count);
  llvm_cbe_tmp__98 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__98);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%23, 3, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_364_count);
  llvm_cbe_tmp__99 = (unsigned int )((unsigned int )(llvm_cbe_tmp__98&4294967295ull)) + ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__99&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%24, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_365_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__99;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__99);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 2), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_367_count);
   /*tail*/ write_bits(0u, 2u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",2u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_368_count);
  llvm_cbe_tmp__100 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__100);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = add nsw i32 %%25, 2, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_369_count);
  llvm_cbe_tmp__101 = (unsigned int )((unsigned int )(llvm_cbe_tmp__100&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__101&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%26, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_370_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__101;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__101);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_371_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_372_count);
  llvm_cbe_tmp__102 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__102);
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = add nsw i32 %%27, 1, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_373_count);
  llvm_cbe_tmp__103 = (unsigned int )((unsigned int )(llvm_cbe_tmp__102&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__103&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%28, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_374_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__103;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__103);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 2), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_376_count);
   /*tail*/ write_bits(0u, 2u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",2u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = load i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_377_count);
  llvm_cbe_tmp__104 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__104);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = add nsw i32 %%29, 2, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_378_count);
  llvm_cbe_tmp__105 = (unsigned int )((unsigned int )(llvm_cbe_tmp__104&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__105&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%30, i32* %%bits_written, align 4, !dbg !10 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_379_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__105;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__105);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 2), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_380_count);
   /*tail*/ write_bits(0u, 2u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",2u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_381_count);
  llvm_cbe_tmp__106 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__106);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = add nsw i32 %%31, 2, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_382_count);
  llvm_cbe_tmp__107 = (unsigned int )((unsigned int )(llvm_cbe_tmp__106&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__107&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%32, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_383_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__107;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__107);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 4), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_384_count);
   /*tail*/ write_bits(0u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_385_count);
  llvm_cbe_tmp__108 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__108);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = add nsw i32 %%33, 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_386_count);
  llvm_cbe_tmp__109 = (unsigned int )((unsigned int )(llvm_cbe_tmp__108&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__109&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%34, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_387_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__109;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__109);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_388_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_389_count);
  llvm_cbe_tmp__110 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__110);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = add nsw i32 %%35, 1, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_390_count);
  llvm_cbe_tmp__111 = (unsigned int )((unsigned int )(llvm_cbe_tmp__110&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__111&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%36, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_391_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__111;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__111);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !17 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_392_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_393_count);
  llvm_cbe_tmp__112 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__112);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = add nsw i32 %%37, 1, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_394_count);
  llvm_cbe_tmp__113 = (unsigned int )((unsigned int )(llvm_cbe_tmp__112&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__113&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%38, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_395_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__113;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__113);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 3, i32 4), !dbg !18 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_397_count);
   /*tail*/ write_bits_mapped2(3u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",3u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_398_count);
  llvm_cbe_tmp__114 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__114);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = add nsw i32 %%39, 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_399_count);
  llvm_cbe_tmp__115 = (unsigned int )((unsigned int )(llvm_cbe_tmp__114&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__115&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%40, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_400_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__115;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__115);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 1, i32 1), !dbg !18 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_402_count);
   /*tail*/ write_bits(1u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_403_count);
  llvm_cbe_tmp__116 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__116);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = add nsw i32 %%41, 1, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_404_count);
  llvm_cbe_tmp__117 = (unsigned int )((unsigned int )(llvm_cbe_tmp__116&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__117&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%42, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_405_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__117;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__117);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !18 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_406_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_407_count);
  llvm_cbe_tmp__118 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__118);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = add nsw i32 %%43, 1, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_408_count);
  llvm_cbe_tmp__119 = (unsigned int )((unsigned int )(llvm_cbe_tmp__118&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__119&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%44, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_409_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__119;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__119);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 1, i32 1), !dbg !18 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_410_count);
   /*tail*/ write_bits(1u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !19 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_411_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_412_count);
  llvm_cbe_tmp__120 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__120);
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = add nsw i32 %%45, 2, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_413_count);
  llvm_cbe_tmp__121 = (unsigned int )((unsigned int )(llvm_cbe_tmp__120&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__121&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%46, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_414_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__121;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__121);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 32, i32 6), !dbg !19 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_416_count);
   /*tail*/ write_bits_mapped2(32u, 6u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",32u);
printf("\nArgument  = 0x%X",6u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_417_count);
  llvm_cbe_tmp__122 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__122);
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = add nsw i32 %%47, 6, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_418_count);
  llvm_cbe_tmp__123 = (unsigned int )((unsigned int )(llvm_cbe_tmp__122&4294967295ull)) + ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__123&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%48, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_419_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__123;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__123);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 4, i32 4), !dbg !19 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_421_count);
   /*tail*/ write_bits_mapped2(4u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",4u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = load i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_422_count);
  llvm_cbe_tmp__124 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__124);
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = add nsw i32 %%49, 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_423_count);
  llvm_cbe_tmp__125 = (unsigned int )((unsigned int )(llvm_cbe_tmp__124&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__125&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%50, i32* %%bits_written, align 4, !dbg !11 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_424_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__125;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__125);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 4, i32 4), !dbg !20 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_426_count);
   /*tail*/ write_bits_mapped2(4u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",4u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_427_count);
  llvm_cbe_tmp__126 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__126);
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = add nsw i32 %%51, 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_428_count);
  llvm_cbe_tmp__127 = (unsigned int )((unsigned int )(llvm_cbe_tmp__126&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__127&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%52, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_429_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__127;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__127);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 8, i32 4), !dbg !20 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_431_count);
   /*tail*/ write_bits_mapped2(8u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",8u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_432_count);
  llvm_cbe_tmp__128 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__128);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = add nsw i32 %%53, 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_433_count);
  llvm_cbe_tmp__129 = (unsigned int )((unsigned int )(llvm_cbe_tmp__128&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__129&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%54, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_434_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__129;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__129);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 9, i32 4), !dbg !20 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_436_count);
   /*tail*/ write_bits_mapped2(9u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",9u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_437_count);
  llvm_cbe_tmp__130 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__130);
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = add nsw i32 %%55, 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_438_count);
  llvm_cbe_tmp__131 = (unsigned int )((unsigned int )(llvm_cbe_tmp__130&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__131&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%56, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_439_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__131;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__131);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !20 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_440_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_441_count);
  llvm_cbe_tmp__132 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__132);
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = add nsw i32 %%57, 1, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_442_count);
  llvm_cbe_tmp__133 = (unsigned int )((unsigned int )(llvm_cbe_tmp__132&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__133&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%58, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_443_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__133;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__133);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !21 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_445_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_446_count);
  llvm_cbe_tmp__134 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__134);
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = add nsw i32 %%59, 1, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_447_count);
  llvm_cbe_tmp__135 = (unsigned int )((unsigned int )(llvm_cbe_tmp__134&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__135&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%60, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_448_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__135;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__135);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !21 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_450_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_451_count);
  llvm_cbe_tmp__136 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__136);
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = add nsw i32 %%61, 1, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_452_count);
  llvm_cbe_tmp__137 = (unsigned int )((unsigned int )(llvm_cbe_tmp__136&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__137&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%62, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_453_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__137;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__137);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 5), !dbg !21 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_455_count);
   /*tail*/ write_bits(0u, 5u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",5u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_456_count);
  llvm_cbe_tmp__138 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__138);
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = add nsw i32 %%63, 5, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_457_count);
  llvm_cbe_tmp__139 = (unsigned int )((unsigned int )(llvm_cbe_tmp__138&4294967295ull)) + ((unsigned int )(5u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__139&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%64, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_458_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__139;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__139);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 16, i32 5), !dbg !22 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_460_count);
   /*tail*/ write_bits_mapped2(16u, 5u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",16u);
printf("\nArgument  = 0x%X",5u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_461_count);
  llvm_cbe_tmp__140 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__140);
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = add nsw i32 %%65, 5, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_462_count);
  llvm_cbe_tmp__141 = (unsigned int )((unsigned int )(llvm_cbe_tmp__140&4294967295ull)) + ((unsigned int )(5u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__141&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%66, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_463_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__141;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__141);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 4, i32 3), !dbg !22 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_465_count);
   /*tail*/ write_bits_mapped2(4u, 3u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",4u);
printf("\nArgument  = 0x%X",3u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_466_count);
  llvm_cbe_tmp__142 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__142);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = add nsw i32 %%67, 3, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_467_count);
  llvm_cbe_tmp__143 = (unsigned int )((unsigned int )(llvm_cbe_tmp__142&4294967295ull)) + ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__143&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%68, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_468_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__143;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__143);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 1, i32 3), !dbg !22 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_470_count);
   /*tail*/ write_bits(1u, 3u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",1u);
printf("\nArgument  = 0x%X",3u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = load i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_471_count);
  llvm_cbe_tmp__144 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__144);
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = add nsw i32 %%69, 3, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_472_count);
  llvm_cbe_tmp__145 = (unsigned int )((unsigned int )(llvm_cbe_tmp__144&4294967295ull)) + ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__145&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%70, i32* %%bits_written, align 4, !dbg !12 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_473_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__145;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__145);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits_mapped2(i32 5, i32 4), !dbg !23 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_475_count);
   /*tail*/ write_bits_mapped2(5u, 4u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",5u);
printf("\nArgument  = 0x%X",4u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = load i32* %%bits_written, align 4, !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_476_count);
  llvm_cbe_tmp__146 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__146);
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = add nsw i32 %%71, 4, !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_477_count);
  llvm_cbe_tmp__147 = (unsigned int )((unsigned int )(llvm_cbe_tmp__146&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__147&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%72, i32* %%bits_written, align 4, !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_478_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__147;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__147);
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @write_bits(i32 0, i32 1), !dbg !23 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_480_count);
   /*tail*/ write_bits(0u, 1u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%X",1u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = load i32* %%bits_written, align 4, !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_481_count);
  llvm_cbe_tmp__148 = (unsigned int )*llvm_cbe_bits_written;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__148);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = add nsw i32 %%73, 1, !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_482_count);
  llvm_cbe_tmp__149 = (unsigned int )((unsigned int )(llvm_cbe_tmp__148&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__149&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%74, i32* %%bits_written, align 4, !dbg !13 for 0x%I64xth hint within @write_headers  --> \n", ++aesl_llvm_cbe_483_count);
  *llvm_cbe_bits_written = llvm_cbe_tmp__149;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__149);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @write_headers}\n");
  return;
}

