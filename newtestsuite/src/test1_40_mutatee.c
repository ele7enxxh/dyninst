#include "mutatee_util.h"

/* group_mutatee_boilerplate.c is prepended to this file by the make system */

typedef void (*intFuncArg) (void);

/* Externally accessed function prototypes.  These must have globally unique
 * names.  I suggest following the pattern <testname>_<function>
 */

void test1_40_monitorFunc(unsigned int callee_addr, unsigned int callsite_addr);
void test1_40_call1(void);
void test1_40_call2(void);
void test1_40_call3(void);
void test1_40_call4(void);
int test1_40_call5(intFuncArg callme);

/* Global variables accessed by the mutator.  These must have globally unique
 * names.
 */

unsigned int test1_40_addr_of_call1 = 0;
unsigned int test1_40_addr_of_call2 = 0;
unsigned int test1_40_addr_of_call3 = 0;

unsigned test1_40_callsite5_addr =  0;

/* Internally used function prototypes.  These should be declared with the
 * keyword static so they don't interfere with other mutatees in the group.
 */

/* Global variables used internally by the mutatee.  These should be declared
 * with the keyword static so they don't interfere with other mutatees in the
 * group.
 */

static int gvDummy40 = 0;

/*  these should be set by the monitoring function
  (and will be checked afterwards)
   callees: */
static unsigned gv40_call40_1_addr = (unsigned)-1;
static unsigned gv40_call40_2_addr = (unsigned)-1;
static unsigned gv40_call40_3_addr = (unsigned)-1;

/*   callsite addr -- measured thrice: */
static unsigned gv40_call40_5_addr1 = (unsigned)-1;
static unsigned gv40_call40_5_addr2 = (unsigned)-1;
static unsigned gv40_call40_5_addr3 = (unsigned)-1;

static int call_counter = 0;

/* Function definitions follow */

/* Test #40 (monitor dynamic function calls) */

int test1_40_mutatee(void) {
#ifdef __XLC__
  /*  xlc does not produce dynamic inst points with this example, 
      so we just ignore it.
  */
   logerror("Skipped test #40 (monitor dynamic call sites)\n");
   logerror("\t- not implemented for mutatees compiled with xlc \n");
   test_passes(testname);
   return 0; /* Test "passed" */
#endif
   
#if !defined(alpha_dec_osf4_0) \
 && !defined(ia64_unknown_linux2_4) \
 && !defined(mips_sgi_irix6_4) \
 && !defined(os_windows)

   int failed = FALSE;

    test1_40_call5(test1_40_call1);
    test1_40_call5(test1_40_call2);
    test1_40_call5(test1_40_call3);

    if (test1_40_addr_of_call1 != gv40_call40_1_addr) {
      logerror( "Failed test #40 (monitor dynamic call site)\n" );
      logerror( "%s[%d]: addr %p != addr %p\n", __FILE__, __LINE__,
              (void *)test1_40_addr_of_call1, (void *)gv40_call40_1_addr);
      failed = TRUE;
    }

    if (test1_40_addr_of_call2 != gv40_call40_2_addr) {
      logerror( "Failed test #40 (monitor dynamic call site)\n" );
      logerror( "%s[%d]: addr %p != addr %p\n", __FILE__, __LINE__,
              (void *)test1_40_addr_of_call2, (void *)gv40_call40_2_addr);
      failed = TRUE;
    }

    if (test1_40_addr_of_call3 != gv40_call40_3_addr) {
      logerror( "Failed test #40 (monitor dynamic call site)\n" );
      logerror( "%s[%d]: addr %p != addr %p\n", __FILE__, __LINE__,
              (void *)test1_40_addr_of_call3, (void *)gv40_call40_3_addr);
      failed = TRUE;
    }

    if (test1_40_callsite5_addr != gv40_call40_5_addr1) {
      logerror( "Failed test #40 (monitor dynamic call site)\n" );
      logerror( "%s[%d]: addr %p != addr %p\n", __FILE__, __LINE__,
              (void *)test1_40_callsite5_addr, (void *)gv40_call40_5_addr1);
      failed = TRUE;
    }

    if (test1_40_callsite5_addr != gv40_call40_5_addr2) {
      logerror( "Failed test #40 (monitor dynamic call site)\n" );
      logerror( "%s[%d]: addr %p != addr %p\n", __FILE__, __LINE__,
              (void *)test1_40_callsite5_addr, (void *)gv40_call40_5_addr2);
      failed = TRUE;
    }

    if (test1_40_callsite5_addr != gv40_call40_5_addr3) {
      logerror( "Failed test #40 (monitor dynamic call site)\n" );
      logerror( "%s[%d]: addr %p != addr %p\n", __FILE__, __LINE__,
              (void *)test1_40_callsite5_addr, (void *)gv40_call40_5_addr3);
      failed = TRUE;
    }

    if (FALSE == failed) {
      logerror( "Passed test #40 (monitor dynamic call site)\n" );
      fflush(NULL);
      test_passes(testname);
      return 0; /* Test passed */
    } else {
      return -1; /* Test failed */
    }
#else /* ia64 or Windows */
   /*  no alpha yet */
   logerror("Skipped test #40 (monitor dynamic call sites)\n");
   logerror("\t- not implemented on this platform\n");
   test_passes(testname);
   return 0; /* Test "passed" */
#endif
}

void test1_40_call1(void) {  gvDummy40 += 401;}
void test1_40_call2(void) {  gvDummy40 += 402;}
void test1_40_call3(void) {  gvDummy40 += 403;}
void test1_40_call4(void) {  gvDummy40 += -1;}

int test1_40_call5(intFuncArg callme)
{
  int ret = 0;
  intFuncArg tocall = (intFuncArg) callme;

  test1_40_call4(); /* lets have a non-dynamic call site here too */

  if (!tocall) {
    logerror("%s[%d]:  FIXME!\n", __FILE__, __LINE__);
    return ret;
  }

  (tocall)();

  return ret;
}

void test1_40_monitorFunc(unsigned int callee_addr, unsigned int callsite_addr)
{
  if (call_counter == 0) {
    gv40_call40_5_addr1 = callsite_addr;
    gv40_call40_1_addr = callee_addr;
    call_counter++;
    return;
  }
  if (call_counter == 1) {
    gv40_call40_5_addr2 = callsite_addr;
    gv40_call40_2_addr = callee_addr;
    call_counter++;
    return;
  }
  if (call_counter == 2) {
    gv40_call40_5_addr3 = callsite_addr;
    gv40_call40_3_addr = callee_addr;
    call_counter++;
    return;
  }
   logerror("%s[%d]:  FIXME! call counter = %d\n", __FILE__, __LINE__, call_counter);
  return;
}