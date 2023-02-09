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
extern signed int local_diff_vector[3];
extern signed int weights[3];
extern signed int counter[5];
extern signed int accumulator[5];
extern unsigned int bits_written;
extern unsigned int init_weights;
extern unsigned int previous_sample;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
signed int sgn(signed int llvm_cbe_val);
void init_weights_function(signed int llvm_cbe_init_weights, signed int llvm_cbe_z);
signed int calc_local_sum(signed int llvm_cbe_neighboor);
signed int calc_central_diff(signed int llvm_cbe_sample, signed int llvm_cbe_local_sum);
signed int calc_predic_central(signed int llvm_cbe_z);
signed int calc_high_res(signed int llvm_cbe_predict_central, signed int llvm_cbe_local_sum);
signed int calc_double_res(signed int llvm_cbe_t, signed int llvm_cbe_z, signed int llvm_cbe_high_res);
signed int calc_quantized_index(signed int llvm_cbe_predicted_residual, signed int llvm_cbe_t);
signed int calc_mapped(signed int llvm_cbe_double_res, signed int llvm_cbe_quantized_index, signed int llvm_cbe_theta);
void calc_weight_update(signed int llvm_cbe_clipped, signed int llvm_cbe_double_res, signed int llvm_cbe_t);
signed int predictor(signed int llvm_cbe_sample, signed int llvm_cbe_neighboor, signed int llvm_cbe_t, signed int llvm_cbe_z);
signed int encode_sample(signed int *, signed int *, signed int , signed int , signed int , signed int *);


/* Global Variable Definitions and Initialization */
signed int local_diff_vector[3];
signed int weights[3];
signed int counter[5];
signed int accumulator[5];
unsigned int bits_written;
unsigned int init_weights;
unsigned int previous_sample __ATTRIBUTE_WEAK__;


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

signed int sgn(signed int llvm_cbe_val) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @sgn\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = ashr i32 %%val, 31, !dbg !9 for 0x%I64xth hint within @sgn  --> \n", ++aesl_llvm_cbe_3_count);
  llvm_cbe_tmp__1 = (unsigned int )((signed int )(((signed int )llvm_cbe_val) >> ((signed int )31u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__1));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = or i32 %%1, 1, !dbg !9 for 0x%I64xth hint within @sgn  --> \n", ++aesl_llvm_cbe_4_count);
  llvm_cbe_tmp__2 = (unsigned int )llvm_cbe_tmp__1 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__2);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @sgn}\n");
  return llvm_cbe_tmp__2;
}


void init_weights_function(signed int llvm_cbe_init_weights, signed int llvm_cbe_z) {
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
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
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @init_weights_function\n");
  if (((llvm_cbe_init_weights&4294967295U) == (1u&4294967295U))) {
    goto llvm_cbe__2e_preheader;
  } else {
    goto llvm_cbe_tmp__3;
  }

llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 224, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 0), align 4, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_16_count);
  *((&weights[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 224u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 224u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 28, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 1), align 4, !dbg !11 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_22_count);
  *((&weights[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 28u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 28u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 3, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 2), align 4, !dbg !11 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_28_count);
  *((&weights[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 3u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 2, i32* getelementptr inbounds ([5 x i32]* @counter, i64 0, i64 0), align 16, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_39_count);
  *((&counter[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 2u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 95, i32* getelementptr inbounds ([5 x i32]* @accumulator, i64 0, i64 0), align 16, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_40_count);
  *((&accumulator[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 95u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 95u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 2, i32* getelementptr inbounds ([5 x i32]* @counter, i64 0, i64 1), align 4, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_47_count);
  *((&counter[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 2u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 95, i32* getelementptr inbounds ([5 x i32]* @accumulator, i64 0, i64 1), align 4, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_48_count);
  *((&accumulator[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 95u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 95u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 2, i32* getelementptr inbounds ([5 x i32]* @counter, i64 0, i64 2), align 8, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_55_count);
  *((&counter[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 2u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 95, i32* getelementptr inbounds ([5 x i32]* @accumulator, i64 0, i64 2), align 8, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_56_count);
  *((&accumulator[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 95u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 95u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 2, i32* getelementptr inbounds ([5 x i32]* @counter, i64 0, i64 3), align 4, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_63_count);
  *((&counter[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 2u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 95, i32* getelementptr inbounds ([5 x i32]* @accumulator, i64 0, i64 3), align 4, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_64_count);
  *((&accumulator[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 95u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 95u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 2, i32* getelementptr inbounds ([5 x i32]* @counter, i64 0, i64 4), align 16, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_71_count);
  *((&counter[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 2u);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 95, i32* getelementptr inbounds ([5 x i32]* @accumulator, i64 0, i64 4), align 16, !dbg !10 for 0x%I64xth hint within @init_weights_function  --> \n", ++aesl_llvm_cbe_72_count);
  *((&accumulator[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])) = 95u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 95u);
  goto llvm_cbe_tmp__3;

llvm_cbe_tmp__3:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @init_weights_function}\n");
  return;
}


signed int calc_local_sum(signed int llvm_cbe_neighboor) {
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_local_sum\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = shl nsw i32 %%neighboor, 2, !dbg !9 for 0x%I64xth hint within @calc_local_sum  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__4 = (unsigned int )llvm_cbe_neighboor << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__4);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_local_sum}\n");
  return llvm_cbe_tmp__4;
}


signed int calc_central_diff(signed int llvm_cbe_sample, signed int llvm_cbe_local_sum) {
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_central_diff\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = shl nsw i32 %%sample, 2, !dbg !9 for 0x%I64xth hint within @calc_central_diff  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__5 = (unsigned int )llvm_cbe_sample << 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sub nsw i32 %%1, %%local_sum, !dbg !9 for 0x%I64xth hint within @calc_central_diff  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__6 = (unsigned int )((unsigned int )(llvm_cbe_tmp__5&4294967295ull)) - ((unsigned int )(llvm_cbe_local_sum&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__6&4294967295ull)));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_central_diff}\n");
  return llvm_cbe_tmp__6;
}


signed int calc_predic_central(signed int llvm_cbe_z) {
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  unsigned int llvm_cbe_tmp__8;
  unsigned int llvm_cbe_tmp__8__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned long long llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  signed int *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  unsigned int llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  signed int *llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned int llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa_count = 0;
  unsigned int llvm_cbe__2e_lcssa;
  unsigned int llvm_cbe__2e_lcssa__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_predic_central\n");
  if ((((signed int )llvm_cbe_z) > ((signed int )0u))) {
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge;
  }

llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = select i1 %%2, i32 %%z, i32 3, !dbg !9 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__7 = (unsigned int )(((((signed int )llvm_cbe_z) < ((signed int )3u))) ? ((unsigned int )llvm_cbe_z) : ((unsigned int )3u));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__7);
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__8__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__17;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__17:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 0, %%.lr.ph ], [ %%13, %%4  for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__16);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = phi i32 [ 0, %%.lr.ph ], [ %%12, %%4  for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__8 = (unsigned int )llvm_cbe_tmp__8__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__8);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__15);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sext i32 %%storemerge1 to i64, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__9 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds [3 x i32]* @local_diff_vector, i64 0, i64 %%6, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__10 = (signed int *)(&local_diff_vector[(((signed long long )llvm_cbe_tmp__9))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__9));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__9) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'local_diff_vector' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load i32* %%7, align 4, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__11 = (unsigned int )*llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds [3 x i32]* @weights, i64 0, i64 %%6, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__12 = (signed int *)(&weights[(((signed long long )llvm_cbe_tmp__9))
#ifdef AESL_BC_SIM
 % 3
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__9));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__9) < 3)) fprintf(stderr, "%s:%d: warning: Read access out of array 'weights' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load i32* %%9, align 4, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__13 = (unsigned int )*llvm_cbe_tmp__12;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = mul nsw i32 %%10, %%8, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_tmp__13&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__11&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = add nsw i32 %%11, %%5, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_tmp__14&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__8&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = add nsw i32 %%storemerge1, 1, !dbg !10 for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__16 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__16&4294967295ull)));
  if (((llvm_cbe_tmp__16&4294967295U) == (llvm_cbe_tmp__7&4294967295U))) {
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__16;   /* for PHI node */
    llvm_cbe_tmp__8__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe_tmp__17;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa = phi i32 [ 0, %%0 ], [ %%12, %%4  for 0x%I64xth hint within @calc_predic_central  --> \n", ++aesl_llvm_cbe__2e_lcssa_count);
  llvm_cbe__2e_lcssa = (unsigned int )llvm_cbe__2e_lcssa__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa = 0x%X",llvm_cbe__2e_lcssa);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__15);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_predic_central}\n");
  return llvm_cbe__2e_lcssa;
}


signed int calc_high_res(signed int llvm_cbe_predict_central, signed int llvm_cbe_local_sum) {
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  unsigned int llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_high_res\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = shl i32 %%local_sum, 8, !dbg !9 for 0x%I64xth hint within @calc_high_res  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__18 = (unsigned int )llvm_cbe_local_sum << 8u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add i32 %%predict_central, 512, !dbg !9 for 0x%I64xth hint within @calc_high_res  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_predict_central&4294967295ull)) + ((unsigned int )(512u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = add i32 %%2, %%1, !dbg !9 for 0x%I64xth hint within @calc_high_res  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__20 = (unsigned int )((unsigned int )(llvm_cbe_tmp__19&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__18&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__20&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%. = select i1 %%4, i32 67109375, i32 %%3, !dbg !10 for 0x%I64xth hint within @calc_high_res  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (unsigned int )(((((signed int )llvm_cbe_tmp__20) > ((signed int )67109375u))) ? ((unsigned int )67109375u) : ((unsigned int )llvm_cbe_tmp__20));
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_high_res}\n");
  return llvm_cbe__2e_;
}


signed int calc_double_res(signed int llvm_cbe_t, signed int llvm_cbe_z, signed int llvm_cbe_high_res) {
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_double_res\n");
  if ((((signed int )llvm_cbe_t) > ((signed int )0u))) {
    goto llvm_cbe_tmp__24;
  } else {
    goto llvm_cbe_tmp__25;
  }

llvm_cbe_tmp__24:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sdiv i32 %%high_res, 512, !dbg !10 for 0x%I64xth hint within @calc_double_res  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__21 = (unsigned int )((signed int )(((signed int )llvm_cbe_high_res) / ((signed int )512u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__21));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__21;   /* for PHI node */
  goto llvm_cbe_tmp__26;

llvm_cbe_tmp__25:
  if (((llvm_cbe_t&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__27;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe_tmp__26;
  }

llvm_cbe_tmp__27:
  if ((((signed int )llvm_cbe_z) > ((signed int )0u))) {
    goto llvm_cbe_tmp__28;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )65536u;   /* for PHI node */
    goto llvm_cbe_tmp__26;
  }

llvm_cbe_tmp__28:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i32* @previous_sample, align 4, !dbg !11 for 0x%I64xth hint within @calc_double_res  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__22 = (unsigned int )*(&previous_sample);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = shl nsw i32 %%9, 1, !dbg !11 for 0x%I64xth hint within @calc_double_res  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__23 = (unsigned int )llvm_cbe_tmp__22 << 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__23;   /* for PHI node */
  goto llvm_cbe_tmp__26;

llvm_cbe_tmp__26:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ %%3, %%2 ], [ 0, %%4 ], [ %%10, %%8 ], [ 65536, %%6  for 0x%I64xth hint within @calc_double_res  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",llvm_cbe_tmp__21);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__23);
printf("\n = 0x%X",65536u);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_double_res}\n");
  return llvm_cbe_storemerge1;
}


signed int calc_quantized_index(signed int llvm_cbe_predicted_residual, signed int llvm_cbe_t) {
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
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_ispos_count = 0;
  static  unsigned long long aesl_llvm_cbe_neg_count = 0;
  unsigned int llvm_cbe_neg;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_predicted_residual_2e__count = 0;
  unsigned int llvm_cbe_predicted_residual_2e_;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_quantized_index\n");
  if ((((signed int )llvm_cbe_t) > ((signed int )0u))) {
    goto llvm_cbe_tmp__32;
  } else {
    goto llvm_cbe_tmp__33;
  }

llvm_cbe_tmp__32:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = tail call i32 @sgn(i32 %%predicted_residual), !dbg !9 for 0x%I64xth hint within @calc_quantized_index  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__29 = (unsigned int ) /*tail*/ sgn(llvm_cbe_predicted_residual);
if (AESL_DEBUG_TRACE) {
printf("\nArgument predicted_residual = 0x%X",llvm_cbe_predicted_residual);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__29);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%neg = sub i32 0, %%predicted_residual, !dbg !9 for 0x%I64xth hint within @calc_quantized_index  --> \n", ++aesl_llvm_cbe_neg_count);
  llvm_cbe_neg = (unsigned int )-(llvm_cbe_predicted_residual);
if (AESL_DEBUG_TRACE)
printf("\nneg = 0x%X\n", ((unsigned int )(llvm_cbe_neg&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = select i1 %%ispos, i32 %%predicted_residual, i32 %%neg, !dbg !9 for 0x%I64xth hint within @calc_quantized_index  --> \n", ++aesl_llvm_cbe_175_count);
  llvm_cbe_tmp__30 = (unsigned int )(((((signed int )llvm_cbe_predicted_residual) > ((signed int )4294967295u))) ? ((unsigned int )llvm_cbe_predicted_residual) : ((unsigned int )llvm_cbe_neg));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = mul nsw i32 %%3, %%4, !dbg !9 for 0x%I64xth hint within @calc_quantized_index  --> \n", ++aesl_llvm_cbe_176_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_tmp__29&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__30&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_quantized_index}\n");
  return llvm_cbe_tmp__31;
llvm_cbe_tmp__33:
if (AESL_DEBUG_TRACE)
printf("\n  %%predicted_residual. = select i1 %%7, i32 %%predicted_residual, i32 0, !dbg !10 for 0x%I64xth hint within @calc_quantized_index  --> \n", ++aesl_llvm_cbe_predicted_residual_2e__count);
  llvm_cbe_predicted_residual_2e_ = (unsigned int )((((llvm_cbe_t&4294967295U) == (0u&4294967295U))) ? ((unsigned int )llvm_cbe_predicted_residual) : ((unsigned int )0u));
if (AESL_DEBUG_TRACE)
printf("\npredicted_residual. = 0x%X\n", llvm_cbe_predicted_residual_2e_);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_quantized_index}\n");
  return llvm_cbe_predicted_residual_2e_;
}


signed int calc_mapped(signed int llvm_cbe_double_res, signed int llvm_cbe_quantized_index, signed int llvm_cbe_theta) {
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  unsigned int llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_quantized_index_2e__count = 0;
  unsigned int llvm_cbe_quantized_index_2e_;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_ispos_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_count = 0;
  bool llvm_cbe_or_2e_cond;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  unsigned int llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2_count = 0;
  unsigned int llvm_cbe_storemerge2;
  unsigned int llvm_cbe_storemerge2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_mapped\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = and i32 %%double_res, 1, !dbg !11 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_198_count);
  llvm_cbe_tmp__34 = (unsigned int )llvm_cbe_double_res & 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sub nsw i32 0, %%quantized_index, !dbg !10 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__35 = (unsigned int )-(llvm_cbe_quantized_index);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__35&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%quantized_index. = select i1 %%2, i32 %%quantized_index, i32 %%3, !dbg !11 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_quantized_index_2e__count);
  llvm_cbe_quantized_index_2e_ = (unsigned int )((((llvm_cbe_tmp__34&4294967295U) == (0u&4294967295U))) ? ((unsigned int )llvm_cbe_quantized_index) : ((unsigned int )llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\nquantized_index. = 0x%X\n", llvm_cbe_quantized_index_2e_);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = select i1 %%ispos, i32 %%quantized_index, i32 %%3, !dbg !10 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_204_count);
  llvm_cbe_tmp__36 = (unsigned int )(((((signed int )llvm_cbe_quantized_index) > ((signed int )4294967295u))) ? ((unsigned int )llvm_cbe_quantized_index) : ((unsigned int )llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
  if ((((signed int )llvm_cbe_tmp__36) > ((signed int )llvm_cbe_theta))) {
    goto llvm_cbe_tmp__41;
  } else {
    goto llvm_cbe_tmp__42;
  }

llvm_cbe_tmp__41:
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = add nsw i32 %%4, %%theta, !dbg !10 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_207_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(llvm_cbe_tmp__36&4294967295ull)) + ((unsigned int )(llvm_cbe_theta&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__37&4294967295ull)));
  llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__37;   /* for PHI node */
  goto llvm_cbe_tmp__43;

llvm_cbe_tmp__42:
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond = or i1 %%9, %%10, !dbg !11 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_or_2e_cond_count);
  llvm_cbe_or_2e_cond = (bool )(((((signed int )llvm_cbe_quantized_index_2e_) < ((signed int )0u)) | (((signed int )llvm_cbe_quantized_index_2e_) > ((signed int )llvm_cbe_theta)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond = 0x%X\n", llvm_cbe_or_2e_cond);
  if (llvm_cbe_or_2e_cond) {
    goto llvm_cbe_tmp__44;
  } else {
    goto llvm_cbe_tmp__45;
  }

llvm_cbe_tmp__45:
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = shl nsw i32 %%4, 1, !dbg !10 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_213_count);
  llvm_cbe_tmp__38 = (unsigned int )llvm_cbe_tmp__36 << 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
  llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__38;   /* for PHI node */
  goto llvm_cbe_tmp__43;

llvm_cbe_tmp__44:
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = shl i32 %%4, 1, !dbg !10 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_216_count);
  llvm_cbe_tmp__39 = (unsigned int )llvm_cbe_tmp__36 << 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = add nsw i32 %%14, -1, !dbg !10 for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__40 = (unsigned int )((unsigned int )(llvm_cbe_tmp__39&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__40&4294967295ull)));
  llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__40;   /* for PHI node */
  goto llvm_cbe_tmp__43;

llvm_cbe_tmp__43:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2 = phi i32 [ %%7, %%6 ], [ %%15, %%13 ], [ %%12, %%11  for 0x%I64xth hint within @calc_mapped  --> \n", ++aesl_llvm_cbe_storemerge2_count);
  llvm_cbe_storemerge2 = (unsigned int )llvm_cbe_storemerge2__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2 = 0x%X",llvm_cbe_storemerge2);
printf("\n = 0x%X",llvm_cbe_tmp__37);
printf("\n = 0x%X",llvm_cbe_tmp__40);
printf("\n = 0x%X",llvm_cbe_tmp__38);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_mapped}\n");
  return llvm_cbe_storemerge2;
}


void calc_weight_update(signed int llvm_cbe_clipped, signed int llvm_cbe_double_res, signed int llvm_cbe_t) {
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  unsigned int llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_op_count = 0;
  unsigned int llvm_cbe__2e_op;
  static  unsigned long long aesl_llvm_cbe_phitmp_count = 0;
  unsigned int llvm_cbe_phitmp;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  unsigned int llvm_cbe_tmp__51;
  unsigned int llvm_cbe_tmp__51__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  unsigned int llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  unsigned int llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  unsigned int llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  unsigned int llvm_cbe_tmp__61;
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
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  unsigned int llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  unsigned int llvm_cbe_tmp__67;
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
  static  unsigned long long aesl_llvm_cbe_311_count = 0;
  static  unsigned long long aesl_llvm_cbe_312_count = 0;
  static  unsigned long long aesl_llvm_cbe_313_count = 0;
  static  unsigned long long aesl_llvm_cbe_314_count = 0;
  static  unsigned long long aesl_llvm_cbe_315_count = 0;
  static  unsigned long long aesl_llvm_cbe_316_count = 0;
  static  unsigned long long aesl_llvm_cbe_317_count = 0;
  static  unsigned long long aesl_llvm_cbe_318_count = 0;
  static  unsigned long long aesl_llvm_cbe_319_count = 0;
  static  unsigned long long aesl_llvm_cbe_320_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_321_count = 0;
  unsigned int llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_322_count = 0;
  unsigned int llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_323_count = 0;
  unsigned int llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_324_count = 0;
  unsigned int llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_325_count = 0;
  unsigned int llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_326_count = 0;
  static  unsigned long long aesl_llvm_cbe_327_count = 0;
  static  unsigned long long aesl_llvm_cbe_328_count = 0;
  static  unsigned long long aesl_llvm_cbe_329_count = 0;
  static  unsigned long long aesl_llvm_cbe_330_count = 0;
  static  unsigned long long aesl_llvm_cbe_331_count = 0;
  static  unsigned long long aesl_llvm_cbe_332_count = 0;
  static  unsigned long long aesl_llvm_cbe_333_count = 0;
  static  unsigned long long aesl_llvm_cbe_334_count = 0;
  static  unsigned long long aesl_llvm_cbe_335_count = 0;
  static  unsigned long long aesl_llvm_cbe_336_count = 0;
  static  unsigned long long aesl_llvm_cbe_337_count = 0;
  static  unsigned long long aesl_llvm_cbe_338_count = 0;
  static  unsigned long long aesl_llvm_cbe_339_count = 0;
  static  unsigned long long aesl_llvm_cbe_340_count = 0;
  static  unsigned long long aesl_llvm_cbe_341_count = 0;
  static  unsigned long long aesl_llvm_cbe_342_count = 0;
  static  unsigned long long aesl_llvm_cbe_343_count = 0;
  static  unsigned long long aesl_llvm_cbe_344_count = 0;
  static  unsigned long long aesl_llvm_cbe_345_count = 0;
  static  unsigned long long aesl_llvm_cbe_346_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @calc_weight_update\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = shl nsw i32 %%clipped, 1, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_226_count);
  llvm_cbe_tmp__46 = (unsigned int )llvm_cbe_clipped << 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sub nsw i32 %%1, %%double_res, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_228_count);
  llvm_cbe_tmp__47 = (unsigned int )((unsigned int )(llvm_cbe_tmp__46&4294967295ull)) - ((unsigned int )(llvm_cbe_double_res&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__47&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = add nsw i32 %%t, -5, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_233_count);
  llvm_cbe_tmp__48 = (unsigned int )((unsigned int )(llvm_cbe_t&4294967295ull)) + ((unsigned int )(4294967291u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__48&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sdiv i32 %%3, 64, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_234_count);
  llvm_cbe_tmp__49 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__48) / ((signed int )64u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__49));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = add nsw i32 %%4, 5, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_235_count);
  llvm_cbe_tmp__50 = (unsigned int )((unsigned int )(llvm_cbe_tmp__49&4294967295ull)) + ((unsigned int )(5u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__50&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__50) > ((signed int )9u))) {
    llvm_cbe_tmp__51__PHI_TEMPORARY = (unsigned int )17u;   /* for PHI node */
    goto llvm_cbe_tmp__74;
  } else {
    goto llvm_cbe_tmp__75;
  }

llvm_cbe_tmp__75:
if (AESL_DEBUG_TRACE)
printf("\n  %%.op = add i32 %%4, 13, !dbg !11 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe__2e_op_count);
  llvm_cbe__2e_op = (unsigned int )((unsigned int )(llvm_cbe_tmp__49&4294967295ull)) + ((unsigned int )(13u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n.op = 0x%X\n", ((unsigned int )(llvm_cbe__2e_op&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%phitmp = select i1 %%8, i32 13, i32 %%.op, !dbg !11 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_phitmp_count);
  llvm_cbe_phitmp = (unsigned int )(((((signed int )llvm_cbe_tmp__48) < ((signed int )4294967233u))) ? ((unsigned int )13u) : ((unsigned int )llvm_cbe__2e_op));
if (AESL_DEBUG_TRACE)
printf("\nphitmp = 0x%X\n", llvm_cbe_phitmp);
  llvm_cbe_tmp__51__PHI_TEMPORARY = (unsigned int )llvm_cbe_phitmp;   /* for PHI node */
  goto llvm_cbe_tmp__74;

llvm_cbe_tmp__74:
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = phi i32 [ 17, %%0 ], [ %%phitmp, %%7 ], !dbg !11 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_245_count);
  llvm_cbe_tmp__51 = (unsigned int )llvm_cbe_tmp__51__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__51);
printf("\n = 0x%X",17u);
printf("\nphitmp = 0x%X",llvm_cbe_phitmp);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = ashr i32 %%2, 31, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_252_count);
  llvm_cbe_tmp__52 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__47) >> ((signed int )31u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__52));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = or i32 %%11, 1, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_253_count);
  llvm_cbe_tmp__53 = (unsigned int )llvm_cbe_tmp__52 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = lshr i32 1, %%10, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_266_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(((unsigned int )(1u&4294967295ull)) >> ((unsigned int )(llvm_cbe_tmp__51&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = mul i32 %%13, %%12, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_267_count);
  llvm_cbe_tmp__55 = (unsigned int )((unsigned int )(llvm_cbe_tmp__54&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__53&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__55&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 0), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_268_count);
  llvm_cbe_tmp__56 = (unsigned int )*((&weights[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 0), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_269_count);
  llvm_cbe_tmp__57 = (unsigned int )*((&local_diff_vector[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = mul i32 %%14, %%16, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_270_count);
  llvm_cbe_tmp__58 = (unsigned int )((unsigned int )(llvm_cbe_tmp__55&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__57&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__58&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%17, 1, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_271_count);
  llvm_cbe_tmp__59 = (unsigned int )((unsigned int )(llvm_cbe_tmp__58&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__59&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = sdiv i32 %%18, 2, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_272_count);
  llvm_cbe_tmp__60 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__59) / ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__60));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = add nsw i32 %%19, %%15, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_273_count);
  llvm_cbe_tmp__61 = (unsigned int )((unsigned int )(llvm_cbe_tmp__60&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__56&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__61&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%20, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 0), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_274_count);
  *((&weights[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = llvm_cbe_tmp__61;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__61);
  if ((((signed int )llvm_cbe_tmp__61) > ((signed int )1023u))) {
    goto llvm_cbe_tmp__76;
  } else {
    goto llvm_cbe_tmp__77;
  }

llvm_cbe_tmp__76:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 1023, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 0), align 4, !dbg !11 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_277_count);
  *((&weights[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 1023u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1023u);
  goto llvm_cbe_tmp__78;

llvm_cbe_tmp__77:
  if ((((signed int )llvm_cbe_tmp__61) < ((signed int )4294966272u))) {
    goto llvm_cbe_tmp__79;
  } else {
    goto llvm_cbe_tmp__80;
  }

llvm_cbe_tmp__79:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 -1024, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 0), align 4, !dbg !12 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_281_count);
  *((&weights[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 4294966272u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 4294966272u);
  goto llvm_cbe_tmp__80;

llvm_cbe_tmp__80:
  goto llvm_cbe_tmp__78;

llvm_cbe_tmp__78:
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 1), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_294_count);
  llvm_cbe_tmp__62 = (unsigned int )*((&weights[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = load i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 1), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_295_count);
  llvm_cbe_tmp__63 = (unsigned int )*((&local_diff_vector[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = mul i32 %%14, %%29, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_296_count);
  llvm_cbe_tmp__64 = (unsigned int )((unsigned int )(llvm_cbe_tmp__55&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__63&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__64&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = add nsw i32 %%30, 1, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_297_count);
  llvm_cbe_tmp__65 = (unsigned int )((unsigned int )(llvm_cbe_tmp__64&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__65&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = sdiv i32 %%31, 2, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_298_count);
  llvm_cbe_tmp__66 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__65) / ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__66));
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = add nsw i32 %%32, %%28, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_299_count);
  llvm_cbe_tmp__67 = (unsigned int )((unsigned int )(llvm_cbe_tmp__66&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__62&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__67&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%33, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 1), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_300_count);
  *((&weights[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = llvm_cbe_tmp__67;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
  if ((((signed int )llvm_cbe_tmp__67) > ((signed int )1023u))) {
    goto llvm_cbe_tmp__81;
  } else {
    goto llvm_cbe_tmp__82;
  }

llvm_cbe_tmp__82:
  if ((((signed int )llvm_cbe_tmp__67) < ((signed int )4294966272u))) {
    goto llvm_cbe_tmp__83;
  } else {
    goto llvm_cbe_tmp__84;
  }

llvm_cbe_tmp__83:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 -1024, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 1), align 4, !dbg !12 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_305_count);
  *((&weights[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 4294966272u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 4294966272u);
  goto llvm_cbe_tmp__84;

llvm_cbe_tmp__84:
  goto llvm_cbe_tmp__85;

llvm_cbe_tmp__81:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 1023, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 1), align 4, !dbg !11 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_308_count);
  *((&weights[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 1023u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1023u);
  goto llvm_cbe_tmp__85;

llvm_cbe_tmp__85:
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = load i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 2), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_320_count);
  llvm_cbe_tmp__68 = (unsigned int )*((&weights[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__68);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = load i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 2), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_321_count);
  llvm_cbe_tmp__69 = (unsigned int )*((&local_diff_vector[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__69);
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = mul i32 %%14, %%42, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_322_count);
  llvm_cbe_tmp__70 = (unsigned int )((unsigned int )(llvm_cbe_tmp__55&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__69&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__70&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = add nsw i32 %%43, 1, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_323_count);
  llvm_cbe_tmp__71 = (unsigned int )((unsigned int )(llvm_cbe_tmp__70&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__71&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = sdiv i32 %%44, 2, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_324_count);
  llvm_cbe_tmp__72 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__71) / ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__72));
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = add nsw i32 %%45, %%41, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_325_count);
  llvm_cbe_tmp__73 = (unsigned int )((unsigned int )(llvm_cbe_tmp__72&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__68&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__73&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%46, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 2), align 4, !dbg !10 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_326_count);
  *((&weights[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = llvm_cbe_tmp__73;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__73);
  if ((((signed int )llvm_cbe_tmp__73) > ((signed int )1023u))) {
    goto llvm_cbe_tmp__86;
  } else {
    goto llvm_cbe_tmp__87;
  }

llvm_cbe_tmp__87:
  if ((((signed int )llvm_cbe_tmp__73) < ((signed int )4294966272u))) {
    goto llvm_cbe_tmp__88;
  } else {
    goto llvm_cbe_tmp__89;
  }

llvm_cbe_tmp__88:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 -1024, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 2), align 4, !dbg !12 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_331_count);
  *((&weights[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 4294966272u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 4294966272u);
  goto llvm_cbe_tmp__89;

llvm_cbe_tmp__89:
  goto llvm_cbe_tmp__90;

llvm_cbe_tmp__86:
if (AESL_DEBUG_TRACE)
printf("\n  store i32 1023, i32* getelementptr inbounds ([3 x i32]* @weights, i64 0, i64 2), align 4, !dbg !11 for 0x%I64xth hint within @calc_weight_update  --> \n", ++aesl_llvm_cbe_334_count);
  *((&weights[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = 1023u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", 1023u);
  goto llvm_cbe_tmp__90;

llvm_cbe_tmp__90:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @calc_weight_update}\n");
  return;
}


signed int predictor(signed int llvm_cbe_sample, signed int llvm_cbe_neighboor, signed int llvm_cbe_t, signed int llvm_cbe_z) {
  static  unsigned long long aesl_llvm_cbe_347_count = 0;
  static  unsigned long long aesl_llvm_cbe_348_count = 0;
  static  unsigned long long aesl_llvm_cbe_349_count = 0;
  static  unsigned long long aesl_llvm_cbe_350_count = 0;
  static  unsigned long long aesl_llvm_cbe_351_count = 0;
  static  unsigned long long aesl_llvm_cbe_352_count = 0;
  static  unsigned long long aesl_llvm_cbe_353_count = 0;
  static  unsigned long long aesl_llvm_cbe_354_count = 0;
  static  unsigned long long aesl_llvm_cbe_355_count = 0;
  static  unsigned long long aesl_llvm_cbe_356_count = 0;
  static  unsigned long long aesl_llvm_cbe_357_count = 0;
  static  unsigned long long aesl_llvm_cbe_358_count = 0;
  static  unsigned long long aesl_llvm_cbe_359_count = 0;
  static  unsigned long long aesl_llvm_cbe_360_count = 0;
  static  unsigned long long aesl_llvm_cbe_361_count = 0;
  static  unsigned long long aesl_llvm_cbe_362_count = 0;
  static  unsigned long long aesl_llvm_cbe_363_count = 0;
  static  unsigned long long aesl_llvm_cbe_364_count = 0;
  static  unsigned long long aesl_llvm_cbe_365_count = 0;
  unsigned int llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_366_count = 0;
  static  unsigned long long aesl_llvm_cbe_367_count = 0;
  static  unsigned long long aesl_llvm_cbe_368_count = 0;
  static  unsigned long long aesl_llvm_cbe_369_count = 0;
  unsigned int llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_370_count = 0;
  unsigned int llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_371_count = 0;
  static  unsigned long long aesl_llvm_cbe_372_count = 0;
  static  unsigned long long aesl_llvm_cbe_373_count = 0;
  unsigned int llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_374_count = 0;
  static  unsigned long long aesl_llvm_cbe_375_count = 0;
  static  unsigned long long aesl_llvm_cbe_376_count = 0;
  static  unsigned long long aesl_llvm_cbe_377_count = 0;
  unsigned int llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_378_count = 0;
  static  unsigned long long aesl_llvm_cbe_379_count = 0;
  static  unsigned long long aesl_llvm_cbe_380_count = 0;
  unsigned int llvm_cbe_tmp__96;
  static  unsigned long long aesl_llvm_cbe_381_count = 0;
  static  unsigned long long aesl_llvm_cbe_382_count = 0;
  static  unsigned long long aesl_llvm_cbe_383_count = 0;
  unsigned int llvm_cbe_tmp__97;
  static  unsigned long long aesl_llvm_cbe_384_count = 0;
  static  unsigned long long aesl_llvm_cbe_385_count = 0;
  static  unsigned long long aesl_llvm_cbe_386_count = 0;
  unsigned int llvm_cbe_tmp__98;
  static  unsigned long long aesl_llvm_cbe_387_count = 0;
  static  unsigned long long aesl_llvm_cbe_388_count = 0;
  static  unsigned long long aesl_llvm_cbe_389_count = 0;
  static  unsigned long long aesl_llvm_cbe_390_count = 0;
  static  unsigned long long aesl_llvm_cbe_391_count = 0;
  unsigned int llvm_cbe_tmp__99;
  static  unsigned long long aesl_llvm_cbe_392_count = 0;
  static  unsigned long long aesl_llvm_cbe_393_count = 0;
  static  unsigned long long aesl_llvm_cbe_394_count = 0;
  static  unsigned long long aesl_llvm_cbe_395_count = 0;
  static  unsigned long long aesl_llvm_cbe_396_count = 0;
  static  unsigned long long aesl_llvm_cbe_397_count = 0;
  static  unsigned long long aesl_llvm_cbe_398_count = 0;
  static  unsigned long long aesl_llvm_cbe_399_count = 0;
  unsigned int llvm_cbe_tmp__100;
  static  unsigned long long aesl_llvm_cbe_400_count = 0;
  static  unsigned long long aesl_llvm_cbe_401_count = 0;
  static  unsigned long long aesl_llvm_cbe_402_count = 0;
  unsigned int llvm_cbe_tmp__101;
  static  unsigned long long aesl_llvm_cbe_403_count = 0;
  static  unsigned long long aesl_llvm_cbe_404_count = 0;
  static  unsigned long long aesl_llvm_cbe_405_count = 0;
  unsigned int llvm_cbe_tmp__102;
  static  unsigned long long aesl_llvm_cbe_406_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  unsigned int llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_407_count = 0;
  static  unsigned long long aesl_llvm_cbe_408_count = 0;
  static  unsigned long long aesl_llvm_cbe_409_count = 0;
  unsigned int llvm_cbe_tmp__103;
  static  unsigned long long aesl_llvm_cbe_410_count = 0;
  static  unsigned long long aesl_llvm_cbe_411_count = 0;
  static  unsigned long long aesl_llvm_cbe_412_count = 0;
  static  unsigned long long aesl_llvm_cbe_413_count = 0;
  static  unsigned long long aesl_llvm_cbe_414_count = 0;
  static  unsigned long long aesl_llvm_cbe_415_count = 0;
  static  unsigned long long aesl_llvm_cbe_416_count = 0;
  static  unsigned long long aesl_llvm_cbe_417_count = 0;
  static  unsigned long long aesl_llvm_cbe_418_count = 0;
  static  unsigned long long aesl_llvm_cbe_419_count = 0;
  static  unsigned long long aesl_llvm_cbe_420_count = 0;
  static  unsigned long long aesl_llvm_cbe_421_count = 0;
  static  unsigned long long aesl_llvm_cbe_422_count = 0;
  static  unsigned long long aesl_llvm_cbe_423_count = 0;
  static  unsigned long long aesl_llvm_cbe_424_count = 0;
  unsigned int llvm_cbe_tmp__104;
  static  unsigned long long aesl_llvm_cbe_425_count = 0;
  static  unsigned long long aesl_llvm_cbe_426_count = 0;
  static  unsigned long long aesl_llvm_cbe_427_count = 0;
  static  unsigned long long aesl_llvm_cbe_428_count = 0;
  static  unsigned long long aesl_llvm_cbe_429_count = 0;
  static  unsigned long long aesl_llvm_cbe_430_count = 0;
  static  unsigned long long aesl_llvm_cbe_431_count = 0;
  unsigned int llvm_cbe_tmp__105;
  static  unsigned long long aesl_llvm_cbe_432_count = 0;
  static  unsigned long long aesl_llvm_cbe_433_count = 0;
  static  unsigned long long aesl_llvm_cbe_434_count = 0;
  static  unsigned long long aesl_llvm_cbe_435_count = 0;
  static  unsigned long long aesl_llvm_cbe_436_count = 0;
  static  unsigned long long aesl_llvm_cbe_437_count = 0;
  static  unsigned long long aesl_llvm_cbe_438_count = 0;
  static  unsigned long long aesl_llvm_cbe_439_count = 0;
  unsigned int llvm_cbe_tmp__106;
  static  unsigned long long aesl_llvm_cbe_440_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @predictor\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = load i32* @init_weights, align 4, !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_365_count);
  llvm_cbe_tmp__91 = (unsigned int )*(&init_weights);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__91);
  if (((llvm_cbe_tmp__91&4294967295U) == (0u&4294967295U))) {
    goto llvm_cbe_tmp__107;
  } else {
    goto llvm_cbe_tmp__108;
  }

llvm_cbe_tmp__107:
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @init_weights_function(i32 0, i32 %%z), !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_368_count);
   /*tail*/ init_weights_function(0u, llvm_cbe_z);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument z = 0x%X",llvm_cbe_z);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load i32* @init_weights, align 4, !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_369_count);
  llvm_cbe_tmp__92 = (unsigned int )*(&init_weights);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__92);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = add nsw i32 %%4, 1, !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_370_count);
  llvm_cbe_tmp__93 = (unsigned int )((unsigned int )(llvm_cbe_tmp__92&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__93&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%5, i32* @init_weights, align 4, !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_371_count);
  *(&init_weights) = llvm_cbe_tmp__93;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__93);
  goto llvm_cbe_tmp__108;

llvm_cbe_tmp__108:
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = tail call i32 @calc_local_sum(i32 %%neighboor), !dbg !10 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_373_count);
  llvm_cbe_tmp__94 = (unsigned int ) /*tail*/ calc_local_sum(llvm_cbe_neighboor);
if (AESL_DEBUG_TRACE) {
printf("\nArgument neighboor = 0x%X",llvm_cbe_neighboor);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__94);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = tail call i32 @calc_central_diff(i32 %%sample, i32 %%7), !dbg !9 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_377_count);
  llvm_cbe_tmp__95 = (unsigned int ) /*tail*/ calc_central_diff(llvm_cbe_sample, llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE) {
printf("\nArgument sample = 0x%X",llvm_cbe_sample);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__94);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__95);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = tail call i32 @calc_predic_central(i32 %%z), !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_380_count);
  llvm_cbe_tmp__96 = (unsigned int ) /*tail*/ calc_predic_central(llvm_cbe_z);
if (AESL_DEBUG_TRACE) {
printf("\nArgument z = 0x%X",llvm_cbe_z);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__96);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = tail call i32 @calc_high_res(i32 %%9, i32 %%7), !dbg !12 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_383_count);
  llvm_cbe_tmp__97 = (unsigned int ) /*tail*/ calc_high_res(llvm_cbe_tmp__96, llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__96);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__94);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__97);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = tail call i32 @calc_double_res(i32 %%t, i32 %%z, i32 %%10), !dbg !10 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_386_count);
  llvm_cbe_tmp__98 = (unsigned int ) /*tail*/ calc_double_res(llvm_cbe_t, llvm_cbe_z, llvm_cbe_tmp__97);
if (AESL_DEBUG_TRACE) {
printf("\nArgument t = 0x%X",llvm_cbe_t);
printf("\nArgument z = 0x%X",llvm_cbe_z);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__97);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__98);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sdiv i32 %%11, 2, !dbg !12 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_391_count);
  llvm_cbe_tmp__99 = (unsigned int )((signed int )(((signed int )llvm_cbe_tmp__98) / ((signed int )2u)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((signed int )llvm_cbe_tmp__99));
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%sample, i32* @previous_sample, align 4, !dbg !9 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_398_count);
  *(&previous_sample) = llvm_cbe_sample;
if (AESL_DEBUG_TRACE)
printf("\nsample = 0x%X\n", llvm_cbe_sample);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sub nsw i32 %%sample, %%12, !dbg !9 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_399_count);
  llvm_cbe_tmp__100 = (unsigned int )((unsigned int )(llvm_cbe_sample&4294967295ull)) - ((unsigned int )(llvm_cbe_tmp__99&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__100&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = tail call i32 @calc_quantized_index(i32 %%13, i32 %%t), !dbg !10 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_402_count);
  llvm_cbe_tmp__101 = (unsigned int ) /*tail*/ calc_quantized_index(llvm_cbe_tmp__100, llvm_cbe_t);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__100);
printf("\nArgument t = 0x%X",llvm_cbe_t);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__101);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = sub nsw i32 65535, %%12, !dbg !13 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_405_count);
  llvm_cbe_tmp__102 = (unsigned int )((unsigned int )(65535u&4294967295ull)) - ((unsigned int )(llvm_cbe_tmp__99&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__102&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%. = select i1 %%16, i32 %%12, i32 %%15, !dbg !13 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (unsigned int )(((((signed int )llvm_cbe_tmp__99) < ((signed int )llvm_cbe_tmp__102))) ? ((unsigned int )llvm_cbe_tmp__99) : ((unsigned int )llvm_cbe_tmp__102));
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = tail call i32 @calc_mapped(i32 %%11, i32 %%14, i32 %%.), !dbg !12 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_409_count);
  llvm_cbe_tmp__103 = (unsigned int ) /*tail*/ calc_mapped(llvm_cbe_tmp__98, llvm_cbe_tmp__101, llvm_cbe__2e_);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__98);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__101);
printf("\nArgument . = 0x%X",llvm_cbe__2e_);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__103);
}
  if ((((signed int )llvm_cbe_t) > ((signed int )0u))) {
    goto llvm_cbe_tmp__109;
  } else {
    goto llvm_cbe_tmp__110;
  }

llvm_cbe_tmp__109:
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @calc_weight_update(i32 %%sample, i32 %%11, i32 %%t), !dbg !10 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_417_count);
   /*tail*/ calc_weight_update(llvm_cbe_sample, llvm_cbe_tmp__98, llvm_cbe_t);
if (AESL_DEBUG_TRACE) {
printf("\nArgument sample = 0x%X",llvm_cbe_sample);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__98);
printf("\nArgument t = 0x%X",llvm_cbe_t);
}
  goto llvm_cbe_tmp__110;

llvm_cbe_tmp__110:
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 1), align 4, !dbg !14 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_424_count);
  llvm_cbe_tmp__104 = (unsigned int )*((&local_diff_vector[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__104);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%21, i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 2), align 4, !dbg !14 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_425_count);
  *((&local_diff_vector[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = llvm_cbe_tmp__104;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__104);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 0), align 4, !dbg !14 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_431_count);
  llvm_cbe_tmp__105 = (unsigned int )*((&local_diff_vector[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
]));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__105);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%22, i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 1), align 4, !dbg !14 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_432_count);
  *((&local_diff_vector[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = llvm_cbe_tmp__105;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__105);
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%8, i32* getelementptr inbounds ([3 x i32]* @local_diff_vector, i64 0, i64 0), align 4, !dbg !12 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_438_count);
  *((&local_diff_vector[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])) = llvm_cbe_tmp__95;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__95);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = tail call i32 @encode_sample(i32* getelementptr inbounds ([5 x i32]* @counter, i64 0, i64 0), i32* getelementptr inbounds ([5 x i32]* @accumulator, i64 0, i64 0), i32 %%t, i32 %%z, i32 %%17, i32* @bits_written) nounwind, !dbg !11 for 0x%I64xth hint within @predictor  --> \n", ++aesl_llvm_cbe_439_count);
   /*tail*/ encode_sample((signed int *)((&counter[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])), (signed int *)((&accumulator[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 5
#endif
])), llvm_cbe_t, llvm_cbe_z, llvm_cbe_tmp__103, (signed int *)(&bits_written));
if (AESL_DEBUG_TRACE) {
printf("\nArgument t = 0x%X",llvm_cbe_t);
printf("\nArgument z = 0x%X",llvm_cbe_z);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__103);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__106);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @predictor}\n");
  return llvm_cbe_tmp__103;
}

