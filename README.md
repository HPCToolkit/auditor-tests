# auditor-tests

## Description 

This repository contains tests of various aspects of Glibc support for LD_AUDIT

## Authors

 John Mellor-Crummey, Xiaozhu Meng, Jonathon Anderson, Mark Krentel
 (Rice University)

 A Google Doc with the details about these test cases can be found here:
 https://docs.google.com/document/d/1dVaDBdzySecxQqD6hLLzDrEF18M1UtjDna9gL5BWWI0/edit?usp=sharing

## Test Cases

- Auditing dlopen of a shared library that uses R_X86_64_TLSDESC fails.

- Auditing dlmopen of a shared library fails.  

- GLibc does not Invoke an auditor specified at link time prior to
  glibc 2.32.

- When using an auditor, there is an unacceptable performance degradation
  of over 50x for PLT calls to small procedures.

- la_symbind isn't called on RHEL8.3 with glibc-2.28 while it is called on 
  RHEL 7.9 with glibc-2.17. The bug is likely much more widespread.

- Glibc Incorrectly saves registers when auditing on ARM, which is a
  problem for HPE A64FX-based systems.

