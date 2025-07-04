.. _breaking_concepts_toc:

.. _breaking_concepts:

Breaking changes in concepts
****************************

The STM32Cube HAL2 Drivers introduces several breaking changes in the concepts and principles that drive the library.
Understanding these changes is helpful to successfully migrate your application to the new version.
The improvement items consist of:

- Split Init and configuration APIs and handle optimization
- Split heavy processes like clock management for all sources and IRQ handler for all modes 
- Add atomic configuration methods to provide with the global configuration more granularity in the peripheral setup dynamically
- Let the HAL2 services call exclusively the LL ones instead of direct register access to optimize drivers maintenance and upgrade (the LL has been introduced after the HAL)
- Enhance the lock, state and error management within drivers to reinforce thread safety and prevent race condition in some functional cases
- Provide more control services to reinforce portability especially regarding clock control (one API to control all the peripheral clocks) and filter processes interrupts (user can dynamically disable some processes events)
- Apply new coding rules and naming convention


Table of content of the **Breaking concepts description** section.

Table of content
----------------

- `Optimized init and config APIs <./breaking_concepts_concept_A.rst>`_
- `Atomic configuration methods <./breaking_concepts_concept_B.rst>`_
- `Split clock and IRQ management <./breaking_concepts_concept_C.rst>`_
- `HAL systematic usage of LL services <./breaking_concepts_concept_E.rst>`_
- `Improved driver mechanisms <./breaking_concepts_concept_F.rst>`_
- `Enhanced control services <./breaking_concepts_concept_G.rst>`_
- `New coding rules <./breaking_concepts_concept_I.rst>`_
- `Optimized input checks <./breaking_concepts_concept_J.rst>`_
- `HAL refactoring <./breaking_concepts_concept_L.rst>`_
- `Enhanced asserts <./breaking_concepts_concept_M.rst>`_
- `Flash driver refactoring <./breaking_concepts_concept_N.rst>`_
- `RTOS-aware HAL <./breaking_concepts_concept_O.rst>`_
- `Misc. updates <./breaking_concepts_concept_P.rst>`_