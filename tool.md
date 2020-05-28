# Doc

## Sphinx vs. Doxygen

*   Sphinx is only for Python
*   Doxygen support inline comment documentation for C/C++

# Modern HDL Design Language

## Chisel

*   Scala based HDL
*   Use FIRRTL to convert into RTL (mostly not human readable)
*   Supported by SiFive

##  [Magma](https://github.com/phanrahan/magma)

*   Python based HDL
*   Also use FIRRTL to convert into RTL
*   Supported by Facebook
*   If combined with Cocotb, full Python based design-verification flow

# Unittest for SystemVerilog

## SVUnit

*   Based on SystemVerilog
*   Very simple and easy to use
*   Not maintained anymore
*   Doesn't support open-source simulator

## VUnit

*   Good support for VHDL, poor for Verilog

## Cocotb

*   Full verification framework that support writing testbench using Python
*   Support open-source simulator, e.g Verilator
*   Part of CHIPS Alliance
*   If combined with Magma, full Python based design-verification flow

# Non Standard Libraries for C

## [CException](https://github.com/ThrowTheSwitch/CException)

*   Add exception and error handling to C, using pure ANSI C

# Unittest for C (embedded)

## [Unity](http://www.throwtheswitch.org/unity/)



# Unittest for C++

## [Catch2](https://github.com/catchorg/Catch2)



# Build system

## CMake

## SCon

## Buck