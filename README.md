# auditor-tests

## Description 

This repository contains tests of various aspects of Glibc support for LD_AUDIT

## Authors

 John Mellor-Crummey, Xiaozhu Meng, Jonathon Anderson, Mark Krentel
 (Rice University)

 A Google Doc with the details about these test cases can be found here:
 https://docs.google.com/document/d/1dVaDBdzySecxQqD6hLLzDrEF18M1UtjDna9gL5BWWI0/edit?usp=sharing

## Test Cases

The test cases are divided up into two classes: Tier1 and Tier2. Tier1 issues are bugs that
significantly impede the ability of the HPCToolkit performance tools 
(https://github.com/hpctoolkit/hpctoolkit) to use LD_AUDIT on forthcoming exascale platforms 
and ARM A64FX.

### Tier 1 Issues

- When using an auditor, there is an unacceptable performance degradation
  of over 50x for PLT calls to small procedures.

- Auditing dlmopen of a shared library fails.  

- la_symbind isn't called on RHEL8.3 with glibc-2.28 while it is called on 
  RHEL 7.9 with glibc-2.17. The bug is likely much more widespread.

- Glibc incorrectly saves registers when auditing on aarch64. 
  Furthermore, there is no way to audit function calls using SVE registers which is currently a problem for 
  HPE and Fujitsu A64FX-based systems and will be a problem for all future ARMv8 and ARMv9 processors which support SVE instructions.

- A failing dl*open called by an auditor is uncatchable and fatal.

- Auditing dlopen of a shared library that uses R_X86_64_TLSDESC fails.

- GLibc does not invoke an auditor specified at link time prior to
  glibc 2.32.

- Auditing calls preloaded allocation functions prior to full GLibc initialization.

### Tier 2 Issues

- Various Glibc functions cannot be called from an auditor.

- La_activity calls are missing or mis-ordered with respect to la_obj* calls.

- A disabled auditor after an enabled auditor causes a SEGV.

- La_objopen, link_map and dladdr disagree on key binaries.

- La_objopen missing for “fake” objects in alternative namespaces

- LA_FLG_BIND* filters do not apply uniformly