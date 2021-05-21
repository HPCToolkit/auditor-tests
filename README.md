# auditor-tests

## Description 

This repository contains tests of various aspects of Glibc support for LD_AUDIT

## Authors

 John Mellor-Crummey, Xiaozhu Meng, Jonathon Anderson, Mark Krentel
 (Rice University)

## Test Cases

- Auditing dlopen of a shared library that uses R_X86_64_TLSDESC fails.

- Auditing dlmopen of a shared library fails.  

- GLibc does not Invoke an auditor specified at link time prior to
  glibc 2.32.

- When using an auditor, there is an unacceptable performance degradation
  of over 50x for PLT calls to small procedures.

- Glibc Incorrectly saves registers when auditing on ARM, which is a
  problem for HPE A64FX-based systems.

