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
extern signed int SAMPLES[125][2];

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
signed int main(void);
signed int predictor(signed int , signed int , signed int , signed int );


/* Global Variable Definitions and Initialization */
signed int SAMPLES[125][2] = { { 2131u, 0u }, { 2201u, 2131u }, { 2360u, 2201u }, { 2742u, 2360u }, { 3568u, 2742u }, { 2126u, 2131u }, { 2224u, 2201u }, { 2382u, 2360u }, { 2785u, 2742u }, { 3637u, 3568u }, { 2151u, 2126u }, { 2235u, 2224u }, { 2393u, 2382u }, { 2798u, 2785u }, { 3661u, 3637u }, { 2152u, 2151u }, { 2236u, 2235u }, { 2397u, 2393u }, { 2792u, 2798u }, { 3658u, 3661u }, { 2161u, 2152u }, { 2249u, 2236u }, { 2403u, 2397u }, { 2827u, 2792u }, { 3699u, 3658u }, { 2132u, 2131u }, { 2215u, 2201u }, { 2353u, 2360u }, { 2740u, 2742u }, { 3554u, 3568u }, { 2144u, 2126u }, { 2239u, 2224u }, { 2394u, 2382u }, { 2764u, 2785u }, { 3603u, 3637u }, { 2140u, 2151u }, { 2221u, 2235u }, { 2380u, 2393u }, { 2767u, 2798u }, { 3601u, 3661u }, { 2151u, 2152u }, { 2241u, 2236u }, { 2383u, 2397u }, { 2810u, 2792u }, { 3697u, 3658u }, { 2162u, 2161u }, { 2244u, 2249u }, { 2417u, 2403u }, { 2858u, 2827u }, { 3815u, 3699u }, { 2131u, 2132u }, { 2206u, 2215u }, { 2334u, 2353u }, { 2700u, 2740u }, { 3447u, 3554u }, { 2132u, 2144u }, { 2212u, 2239u }, { 2344u, 2394u }, { 2696u, 2764u }, { 3460u, 3603u }, { 2128u, 2140u }, { 2209u, 2221u }, { 2350u, 2380u }, { 2709u, 2767u }, { 3487u, 3601u }, { 2136u, 2151u }, { 2226u, 2241u }, { 2368u, 2383u }, { 2743u, 2810u }, { 3584u, 3697u }, { 2133u, 2162u }, { 2221u, 2244u }, { 2366u, 2417u }, { 2752u, 2858u }, { 3563u, 3815u }, { 2116u, 2131u }, { 2184u, 2206u }, { 2301u, 2334u }, { 2619u, 2700u }, { 3284u, 3447u }, { 2116u, 2132u }, { 2189u, 2212u }, { 2309u, 2344u }, { 2614u, 2696u }, { 3278u, 3460u }, { 2108u, 2128u }, { 2181u, 2209u }, { 2311u, 2350u }, { 2617u, 2709u }, { 3286u, 3487u }, { 2112u, 2136u }, { 2180u, 2226u }, { 2307u, 2368u }, { 2614u, 2743u }, { 3275u, 3584u }, { 2112u, 2133u }, { 2200u, 2221u }, { 2291u, 2366u }, { 2623u, 2752u }, { 3276u, 3563u }, { 2116u, 2116u }, { 2187u, 2184u }, { 2311u, 2301u }, { 2626u, 2619u }, { 3279u, 3284u }, { 2114u, 2116u }, { 2188u, 2189u }, { 2302u, 2309u }, { 2606u, 2614u }, { 3224u, 3278u }, { 2109u, 2108u }, { 2169u, 2181u }, { 2300u, 2311u }, { 2581u, 2617u }, { 3202u, 3286u }, { 2106u, 2112u }, { 2180u, 2180u }, { 2306u, 2307u }, { 2585u, 2614u }, { 3203u, 3275u }, { 2103u, 2112u }, { 2170u, 2200u }, { 2287u, 2291u }, { 2569u, 2623u }, { 3212u, 3276u } };
static  char aesl_internal__OC_str[7] = "mapped";


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

signed int main(void) {
  static  unsigned long long aesl_llvm_cbe_counter_count = 0;
  signed int llvm_cbe_counter[5];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_accumulator_count = 0;
  signed int llvm_cbe_accumulator[5];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
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
   char *llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
   char *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
   char *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
   char *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2_count = 0;
  unsigned int llvm_cbe_storemerge2;
  unsigned int llvm_cbe_storemerge2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  unsigned int llvm_cbe_tmp__5;
  unsigned int llvm_cbe_tmp__5__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  unsigned int llvm_cbe_tmp__6;
  unsigned int llvm_cbe_tmp__6__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned int llvm_cbe_tmp__7;
  unsigned int llvm_cbe_tmp__7__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  unsigned int llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  unsigned long long llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  signed int *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  unsigned short llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  signed int *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  unsigned short llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  unsigned int llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  unsigned int llvm_cbe_tmp__21;
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
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  unsigned int llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe__2e_1_count = 0;
  unsigned int llvm_cbe__2e_1;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  unsigned int llvm_cbe_tmp__24;
  unsigned int llvm_cbe_tmp__24__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  unsigned int llvm_cbe_tmp__25;
  unsigned int llvm_cbe_tmp__25__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  unsigned int llvm_cbe_tmp__26;
  unsigned int llvm_cbe_tmp__26__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;

  CODE_FOR_MAIN();
const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @main\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = bitcast [5 x i32]* %%counter to i8*, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_15_count);
  llvm_cbe_tmp__1 = ( char *)(( char *)(&llvm_cbe_counter));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = call i8* @memset(i8* %%1, i32 0, i64 20 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_16_count);
  ( char *)memset(( char *)llvm_cbe_tmp__1, 0u, 20ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",20ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__2);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = bitcast [5 x i32]* %%accumulator to i8*, !dbg !5 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_18_count);
  llvm_cbe_tmp__3 = ( char *)(( char *)(&llvm_cbe_accumulator));
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = call i8* @memset(i8* %%3, i32 0, i64 20 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_19_count);
  ( char *)memset(( char *)llvm_cbe_tmp__3, 0u, 20ull);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",0u);
printf("\nArgument  = 0x%I64X",20ull);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__4);
}
  llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__5__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__6__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__7__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__28;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__28:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2 = phi i32 [ 0, %%0 ], [ %%32, %%28  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_storemerge2_count);
  llvm_cbe_storemerge2 = (unsigned int )llvm_cbe_storemerge2__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2 = 0x%X",llvm_cbe_storemerge2);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__27);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = phi i32 [ 0, %%0 ], [ %%31, %%28  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__5 = (unsigned int )llvm_cbe_tmp__5__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__5);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__26);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = phi i32 [ 0, %%0 ], [ %%30, %%28  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__6 = (unsigned int )llvm_cbe_tmp__6__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__6);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__25);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = phi i32 [ 0, %%0 ], [ %%29, %%28  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__7 = (unsigned int )llvm_cbe_tmp__7__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__7);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__24);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = mul i32 %%7, 5, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__8 = (unsigned int )((unsigned int )(llvm_cbe_tmp__6&4294967295ull)) * ((unsigned int )(5u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__8&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = add i32 %%9, %%8, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__9 = (unsigned int )((unsigned int )(llvm_cbe_tmp__8&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__7&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__9&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = sext i32 %%storemerge2 to i64, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__10 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge2);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds [125 x [2 x i32]]* @SAMPLES, i64 0, i64 %%11, i64 0, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__11 = (signed int *)(&SAMPLES[(((signed long long )llvm_cbe_tmp__10))
#ifdef AESL_BC_SIM
 % 125
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 2
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__10));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__10) < 125)) fprintf(stderr, "%s:%d: warning: Read access out of array 'SAMPLES' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )0ull) < 2)) fprintf(stderr, "%s:%d: warning: Read access out of array 'SAMPLES' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load i32* %%12, align 8, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__12 = (unsigned int )*llvm_cbe_tmp__11;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = trunc i32 %%13 to i16, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__13 = (unsigned short )((unsigned short )llvm_cbe_tmp__12&65535U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds [125 x [2 x i32]]* @SAMPLES, i64 0, i64 %%11, i64 1, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__14 = (signed int *)(&SAMPLES[(((signed long long )llvm_cbe_tmp__10))
#ifdef AESL_BC_SIM
 % 125
#endif
][(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 2
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__10));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__10) < 125)) fprintf(stderr, "%s:%d: warning: Read access out of array 'SAMPLES' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )1ull) < 2)) fprintf(stderr, "%s:%d: warning: Read access out of array 'SAMPLES' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load i32* %%15, align 4, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__15 = (unsigned int )*llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = trunc i32 %%16 to i16, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__16 = (unsigned short )((unsigned short )llvm_cbe_tmp__15&65535U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = zext i16 %%14 to i32, !dbg !3 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__17 = (unsigned int )((unsigned int )(unsigned short )llvm_cbe_tmp__13&65535U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = zext i16 %%17 to i32, !dbg !3 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(unsigned short )llvm_cbe_tmp__16&65535U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = call i32 @predictor(i32 %%18, i32 %%19, i32 %%10, i32 %%6) nounwind, !dbg !3 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_47_count);
  predictor(llvm_cbe_tmp__17, llvm_cbe_tmp__18, llvm_cbe_tmp__9, llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__17);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__18);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__9);
printf("\nArgument  = 0x%X",llvm_cbe_tmp__5);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__19);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([7 x i8]* @aesl_internal_.str, i64 0, i64 0)) nounwind, !dbg !7 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_48_count);
  printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 7
#endif
])));
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__20);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = add i32 %%6, 1, !dbg !3 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__21 = (unsigned int )((unsigned int )(llvm_cbe_tmp__5&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__21&4294967295ull)));
  if (((llvm_cbe_tmp__21&4294967295U) == (5u&4294967295U))) {
    goto llvm_cbe_tmp__29;
  } else {
    llvm_cbe_tmp__24__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__7;   /* for PHI node */
    llvm_cbe_tmp__25__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__6;   /* for PHI node */
    llvm_cbe_tmp__26__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__21;   /* for PHI node */
    goto llvm_cbe_tmp__30;
  }

llvm_cbe_tmp__30:
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = phi i32 [ %%8, %%5 ], [ %%., %%24  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__24 = (unsigned int )llvm_cbe_tmp__24__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__24);
printf("\n = 0x%X",llvm_cbe_tmp__7);
printf("\n. = 0x%X",llvm_cbe__2e_);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = phi i32 [ %%7, %%5 ], [ %%.1, %%24  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__25 = (unsigned int )llvm_cbe_tmp__25__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__25);
printf("\n = 0x%X",llvm_cbe_tmp__6);
printf("\n.1 = 0x%X",llvm_cbe__2e_1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = phi i32 [ %%22, %%5 ], [ 0, %%24  for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__26 = (unsigned int )llvm_cbe_tmp__26__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__26);
printf("\n = 0x%X",llvm_cbe_tmp__21);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = add nsw i32 %%storemerge2, 1, !dbg !6 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__27 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__27&4294967295ull)));
  if (((llvm_cbe_tmp__27&4294967295U) == (125u&4294967295U))) {
    goto llvm_cbe_tmp__31;
  } else {
    llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__27;   /* for PHI node */
    llvm_cbe_tmp__5__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__26;   /* for PHI node */
    llvm_cbe_tmp__6__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__25;   /* for PHI node */
    llvm_cbe_tmp__7__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__24;   /* for PHI node */
    goto llvm_cbe_tmp__28;
  }

llvm_cbe_tmp__29:
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = add i32 %%8, 1, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__22 = (unsigned int )((unsigned int )(llvm_cbe_tmp__7&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__22&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = add i32 %%7, 1, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__23 = (unsigned int )((unsigned int )(llvm_cbe_tmp__6&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__23&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%. = select i1 %%26, i32 0, i32 %%25, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (unsigned int )((((llvm_cbe_tmp__22&4294967295U) == (5u&4294967295U))) ? ((unsigned int )0u) : ((unsigned int )llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
if (AESL_DEBUG_TRACE)
printf("\n  %%.1 = select i1 %%26, i32 %%27, i32 %%7, !dbg !4 for 0x%I64xth hint within @main  --> \n", ++aesl_llvm_cbe__2e_1_count);
  llvm_cbe__2e_1 = (unsigned int )((((llvm_cbe_tmp__22&4294967295U) == (5u&4294967295U))) ? ((unsigned int )llvm_cbe_tmp__23) : ((unsigned int )llvm_cbe_tmp__6));
if (AESL_DEBUG_TRACE)
printf("\n.1 = 0x%X\n", llvm_cbe__2e_1);
  llvm_cbe_tmp__24__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_;   /* for PHI node */
  llvm_cbe_tmp__25__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_1;   /* for PHI node */
  llvm_cbe_tmp__26__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__30;

  } while (1); /* end of syntactic loop '' */
llvm_cbe_tmp__31:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @main}\n");
  return 0u;
}

